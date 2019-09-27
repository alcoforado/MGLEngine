import {  Vue } from 'vue-property-decorator';

export class MFormValue {
  isError: boolean;
  value: any;
  message:string;
  isMFormValue:boolean;
  

  static createError(message:string,value?:any):MFormValue
  {
    var result = new MFormValue();
    result.isError=true;
    result.isMFormValue=true;
    result.message=message;
    result.value=value
    return result;
  }

  static createValue(value:any):MFormValue{
    if (value && value.isMFormValue)
      return value;
    
    var result = new MFormValue();
    result.isError=false;
    result.isMFormValue=true;
    result.value=value;
    return result;
  }

  static getRaw(value:any):any {
    if (!value)
      return value;
    
    if (value.isMFormValue)
    {
      return value.value;
    }
    else
    {
      return value;
    }
  }

}
export enum PropertyType {
  Object="object",
  Array="array",
}


export interface PropertyInfo {
  name:string;
  type:PropertyType;
  index?:number;

}


export class MFormNode {
  field:PropertyInfo
  fieldValue:MFormValue;
  path:PropertyInfo[];
  


  isRoot():boolean {
    return this.path==null || this.path.length == 0;
  }


  DelegateField(fieldName:string):MFormNode
  {
    if (this.field.type != null)
    {
      if (this.field.type !== PropertyType.Object)
      {
        throw "Cannot delegate a field of a non object node";
      }
    }
    
    var result = new MFormNode();
    if (this.fieldValue && this.fieldValue.value && !this.fieldValue.isError && typeof this.fieldValue.value[fieldName]!=="undefined")
    {
      result.fieldValue=MFormValue.createValue(this.fieldValue.value[fieldName]);
      
    }
    else
      result.fieldValue=null //Value not defined yet.
    result.field.name=fieldName;
    


  }
}

export class MForm {
  

    static Root(value:any):MFormNode
    {
      if (!value)
        throw "Value must not be null"
      var result = new MFormNode();
      
      var typeName = typeof value;
      if (typeName == "object")
        result.field.type=PropertyType.Object
      else if (Array.isArray(value))
        result.field.type=PropertyType.Array
      else
        throw "Value must be object or array"
      result.field.name="/";
      result.path=[];
      result.fieldValue = MFormValue.createValue(value);

    }


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
            fieldPath:[{
              name:field,
              type:PropertyType.Object
            }],
            fieldValue: {
              value:null
            }
        } as ChangeEvent);
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

  public onChange(event:ChangeEvent,obj:any,field?:string,map?: (v: any) => any)
  {
    var result={...event};
    if (field)
    {
      var p:PropertyInfo= {
        name:field,
        type:PropertyType.Object
      };
      result.fieldPath=[p,...result.fieldPath];
    }
    this.component.$emit('input',result);
  }  

  public onChangeRoot(event:ChangeEvent,rootObj:any,field?:string)
  {

    var result:ChangeEvent={...event};
    if (field)
    {
      var p:PropertyInfo = {name:field,type:PropertyType.Object};
      result.fieldPath=[p,...result.fieldPath];
    }
    var it=rootObj;
    for (var i=0;i<result.fieldPath.length;i++)
    {
      var p = result.fieldPath[i];
      if(typeof it[p.name] == 'undefined')
      {
        it[p.name]=p.type == PropertyType.Object ? {} : [];  
      }
      it = it[p.name];
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
