import {  Vue } from 'vue-property-decorator';


export enum PropertyType {
  Object = "object",
  Array = "array",
  Primitive = "primitive"
}


export class PropertyInfo {
  private name:string;
  type:PropertyType;
  private index:number;

  constructor(field:string|number,type:PropertyType)
  {
    this.type=type;
    this.setField(field);
  }

  clone():PropertyInfo{
    return new PropertyInfo(this.getFieldId(),this.type);
  }
  getFieldId():string|number
  {
    if (this.name!=null) return this.name;
    return this.index;
  }

  getField():string {
    if (this.name!=null)
      return this.name
   if (this.index!=null)
    return this.index.toString()
   else
    return ''
  }

  isIndex():boolean {return this.index!=null};
  isName():boolean {return this.name!=null};
  setField(field:string|number)
    {
      if (typeof field == "number")
        {
          this.index=field;
          this.name=null;
        }
      else 
      {
        this.name=field;
        this.index=null;
      }      
    }
}

export interface MFormChangeEvent {
  sourceNode:MFormNode;
  value:any;
}


export class MFormNode {
  toMFormEvent(n: number) {
    throw new Error("Method not implemented.");
  }
  
  field:PropertyInfo
  fieldValue:any;
  parent:MFormNode;
  hasError:boolean;
  errorMessage:string;
  isMFormNode:boolean = true;
  children:{[key:string]:MFormNode}

  constructor(){
    this.field=new PropertyInfo('',null);
    this.isMFormNode=true;
    this.fieldValue=null;
    this.parent=null;
    this.children={};
  }

  private isRoot():boolean {
    return this.parent == null;
  }

  private isDefined():boolean
  {
    return this.field.type!=null;
  }


  private hasProperty(p:string|number):boolean
  {
    return this.isDefined() && this.children[p] && this.children[p].isDefined();
  }

  private createUndefinedProperty(field: string|number): MFormNode {
    
    var result=new MFormNode();
    result.field = new PropertyInfo(field,null)
    result.hasError=false;
    result.errorMessage=null;
    result.fieldValue=null; //Value not defined yet.
    result.parent=this;
    result.children={};
    return result;
  }
  
  private setValue(value:any)
  {
    if (this.hasChildren())
      throw `Can't set value at Node ${this.getStringPath()}, node has children`;
    
    var vtype:PropertyType= MFormNode.getType(value);
    if (this.field.type==null)
    {
      this.field.type=vtype;
    }
    if (vtype == this.field.type)
    {
      this.fieldValue=value;
      if (!this.isRoot())
      {
        if (!this.parent.fieldValue)
          throw `Can't set value at ${this.getStringPath()}, the parent is not allocated`
        this.parent.fieldValue[this.field.getField()]=value;
      }
    }
    else
      throw `Error on set value for node ${this.getStringPath}, type incompatibility between ${vtype} and ${this.field.type}`
  }
  
  
  private getRoot():MFormNode
  {
    var it:MFormNode=this;
    while(it.isRoot())
    {
      it=it.parent;
    }
    return it;
  }
  private getPath():PropertyInfo[] 
  {
    var result:PropertyInfo[]= [];
    var it:MFormNode = this;
    while (it)
    {
      result.push(it.field.clone());
      it=it.parent;
    }
    return result.reverse();
  }
  
  private getStringPath():string {
    var path = this.getPath();
    var result="";
    path.forEach(p=>{result+="/"+p.getField()})
    return result;
  }
  

  private static getType(value: any): PropertyType {
    if (value == null)
      return null;
    if (typeof value != "object")
      return PropertyType.Primitive;
    else 
    {
      return Array.isArray(value)  ? PropertyType.Array : PropertyType.Object;
    }
    
    throw new Error("Method not implemented.");
  }
  private hasChildren():boolean {
    return Object.keys(this.children).length > 0;
  }
  
  private  getOrCreateChild(field: PropertyInfo): MFormNode {
    
    if (!this.isDefined())  //the node is not defined, set as an object or an array so it can have fields
    {
      this.field.type=field.isIndex() ? PropertyType.Array : PropertyType.Object
      this.fieldValue=field.isIndex() ? [] : {};
      if (!this.isRoot())
      {
        if (this.parent.isDefined())
          this.parent.fieldValue[this.field.getFieldId()]=this.fieldValue;
      }
    }

   
      
      if (this.field.type !== PropertyType.Object && this.field.type !== PropertyType.Array)
        throw `Cannot create field property for ${this.getStringPath()}, node is not an object or array`
      if (this.children[field.getFieldId()])
      {
        var child=this.children[field.getFieldId()]
        if (child.field.type != field.type)
          throw `Expect children ${child.field.getField()} to be ${child.field.type}, but it is ${field.type}`
        return this.children[field.getFieldId()];
      }
      else //create child
      {
        var child:MFormNode = new MFormNode();
        child.field=field.clone();
        child.parent=this;
        this.children[field.getFieldId()]=child;
        return child;
      }
    
  }

  public onChange(v:any):MFormNode
  {
    if (!v.isMFormNode)
    {
       this.setValue(v);
       return this;
    }
    else if (!this.isRoot()) //v is a Node move it up in the component tree
      return v;
    else //root found, process object
    {
      this.onChangeRoot(v);
      return null;
    }
  }
  public delegateField(fieldName:string):MFormNode
  {
    if (this.field.type != null)
    {
      if (this.field.type !== PropertyType.Object)
      {
        throw "Cannot delegate a field of a non object node";
      }
    }
    
    var result = new MFormNode();
    if (this.hasProperty(fieldName))
    {
      return this.children[fieldName];
    }
    else
    {
      return this.createUndefinedProperty(fieldName);
    }
  }

  
  public onChangeRoot(ev: MFormChangeEvent) 
  {
    var v=ev.sourceNode;
    var value = ev.value;
    var path = v.getPath();
    var it:MFormNode = this;
    for (var i=1;i<path.length;i++)
    {
      var field:PropertyInfo = path[i];
      var child:MFormNode = it.getOrCreateChild(field);
      it=child;
    }
    it.setValue(ev.value)
    //Ok define the type of the last child based on the value changed
  }
  
  
  public static createMFormTree(obj:any):MFormNode
  {
    var objectsTraversed:any[]=[];
    var createNodeAux = (parent:MFormNode,field:string|number,obj:any)=>{


      var n = new MFormNode();
      n.fieldValue=obj;
      n.field.setField(field);


      n.parent=parent;
      if (parent!=null)
        parent.children[field]=n;
      
      if (obj!=null)
      {
        n.field.type = MFormNode.getType(obj)
        
        if (n.field.type == PropertyType.Object)
        {
          if (objectsTraversed.indexOf(obj)!=-1) throw 'object is recursive';

          objectsTraversed.push(obj);
          var keys=Object.keys(obj);
          for (var i=0;i<keys.length;i++){
            var k = keys[i];
            createNodeAux(n,k,obj[k])
          }
        }
        else if (n.field.type == PropertyType.Array)
        {
          if (objectsTraversed.indexOf(obj)!=-1) throw 'object is recursive';
          objectsTraversed.push(obj);
          var a = obj as any[];
          for (var i=0;i<a.length;i++)
          {
            createNodeAux(n,i,a[i]);
          }
        }

      }
      return n;
    }

    return createNodeAux(null,'',obj);
  }  
}

