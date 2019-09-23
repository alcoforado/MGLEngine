import {  Vue } from 'vue-property-decorator';

export interface MFormValue {
  isError: boolean;
  value: any;
}

export interface AddFieldEvent {
  eventName:string,
  fieldPath:string[]
  value:any;
}

export class MForm {
  
    constructor(public component:Vue){}
    private _root:any;
    GetValuePrimitive(obj: any, map: (v: any) => any): any {
    try {
      if (obj) {
        if (obj.isError) {
          return obj;
        } else {
          return map == null ? obj : map(obj);
        }
      } else {
        return null;
      }
    } catch (e) {
      return {
        isError: true,
        message: e,
        value: obj
      };
    }
  }

  private GetValueBase(obj: any, field: string, map: (v: any) => any,isRoot:boolean): any {
    if (field == null || field.trim() == "") {
      return this.GetValuePrimitive(obj, map);
    }
    if (obj == null || typeof obj[field] == 'undefined') {
        this.component.$emit('input', {
            eventName:'createField',
            fieldPath:[field]
        });
        return null;
    }
    return this.GetValuePrimitive(obj[field],map);              
  }

  public GetValue(obj: any, field: string, map: (v: any) => any):any
  {
    return this.GetValueBase(obj,field,map,false);
  }

  public Root(rootObj: object):object
  {
    if (!rootObj)
      throw "Root object cannot be null";
    if (typeof rootObj !== "object")
      throw "Root must be an object"
    this._root=rootObj;
    return this._root;
  }

  public onChange(event:AddFieldEvent,obj:any,field?:string)
  {
    var result={...event};
    result.fieldPath=[field,...result.fieldPath];
    this.component.$emit('input',result);
    if (event.eventName && event.eventName == 'createField' )
    {
      if (field && field!='')
      { 
        var result={...event};
        result.fieldPath=[field,...result.fieldPath];
      }
    }
    else if (event.eventName && event.eventName == 'valueChange')
    {

    }
  }  


  HasError(value: any): any {
    if (value==null)
        return false; 
    
    if (value.isError)
     {
         return true;
     }

     if (typeof value == "object")
     {
         var keys=Object.keys(value);
         for(var key in keys)
         {
             if (this.HasError(value[key]))
                return true;
         }
     }
     return false;



  }



  
}
