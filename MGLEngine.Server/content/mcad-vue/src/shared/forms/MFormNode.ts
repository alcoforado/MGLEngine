import {  Vue } from 'vue-property-decorator';


export enum PropertyType {
  Object = "object",
  Array = "array",
  Primitive = "primitive"
}


export class PropertyInfo {
   name:string;
  type:PropertyType;
   index:number;

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

export interface IMFormChangeEvent {
  sourceNode:MFormNode;
  value:any;
}



export interface IMFormNode {
  change(value:any):void
  value():any
  member(fieldName:string):IMFormNode
  
}

export class MFormNode implements IMFormNode{
  
  bus:Vue;
  field:PropertyInfo
  parent:MFormNode;
  hasError:boolean;
  errorMessage:string;
  isMFormNode:boolean = true;
  children:{[key:string]:MFormNode}
  primitiveValue:any=null;
  constructor(pMasterComponent:Vue){
    this.field=new PropertyInfo('',null);
    this.isMFormNode=true;
    this.parent=null;
    this.children={};
    this.bus=pMasterComponent;
  }

   isRoot():boolean {
    return this.parent == null;
  }

   isDefined():boolean
  {
    return this.field.type!=null;
  }


   hasProperty(p:string|number):boolean
  {
    return this.isDefined() && this.children[p] && this.children[p].isDefined();
  }

   createUndefinedProperty(field: string|number): MFormNode {
    
    var result=new MFormNode(this.bus);
    result.field = new PropertyInfo(field,null)
    result.hasError=false;
    result.errorMessage=null;
    result.parent=this;
    result.children={};
    return result;
  }
  
 



  private setPrimitiveValue(value:any)
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
      this.primitiveValue=value;
      
    }
    else
      throw `Error on set value for node ${this.getStringPath}, type incompatibility between ${vtype} and ${this.field.type}`
  }
  
  
   getRoot():MFormNode
  {
    var it:MFormNode=this;
    while(!it.isRoot())
    {
      it=it.parent;
    }
    return it;
  }
   getPath():PropertyInfo[] 
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
  
   getStringPath():string {
    var path = this.getPath();
    var result="";
    path.forEach(p=>{result+=p.getField()+"."})
    result.substr(0,result.length-1); // remove last trailing .
    return result;
  }
  

   static getType(value: any): PropertyType {
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
   hasChildren():boolean {
    return Object.keys(this.children).length > 0;
  }
  
    getOrCreateChild(field: PropertyInfo): MFormNode {
    
    if (!this.isDefined())  //the node is not defined, set as an object or an array so it can have fields
    {
      this.field.type=field.isIndex() ? PropertyType.Array : PropertyType.Object
     
     
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
        var child:MFormNode = new MFormNode(this.bus);
        child.field=field.clone();
        child.parent=this;
        this.children[field.getFieldId()]=child;
        return child;
      }
    
  }


  onModelChange(ev: IMFormChangeEvent) {
    var path=ev.sourceNode.getStringPath().split(".");
    var cNode=this as MFormNode;
    for (var i=0;i<path.length;i++)
    {
        var isLast = i == path.length-1;
        var field = new PropertyInfo(path[i],isLast?PropertyType.Primitive:PropertyType.Object);
        cNode=cNode.getOrCreateChild(field);
    }
    cNode.setPrimitiveValue(ev.value);   
}
 
  public change(value:any):void{
    this.bus.$emit("change",{
      sourceNode: this,
      value:value
    } as IMFormChangeEvent)
  }
  
  public value():any {
      if (this.hasChildren())
      {
        throw `Can't set value at Node ${this.getStringPath()}, because it is not a final value, use the "member" method to go further in the object tree`; 
      }
      return this.primitiveValue;
  }
 
 
  public member(fieldName:string):IMFormNode
  {
    if (this.field.type != null)
    {
      if (this.field.type !== PropertyType.Object)
      {
        throw "Cannot delegate a field of a non object node";
      }
    }
    
    var result = new MFormNode(this.bus);
    if (this.hasProperty(fieldName))
    {
      return this.children[fieldName];
    }
    else
    {
      return this.createUndefinedProperty(fieldName);
    }
  }

  public buildObject() {

      


  }
  
  
  
  public static createMFormTree(bus:Vue,obj:any):MFormNode
  {
    var objectsTraversed:any[]=[];
    var createNodeAux = (parent:MFormNode,field:string|number,obj:any)=>{


      var n = new MFormNode(bus)
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
        else {
          n.primitiveValue=obj;
        }

      }
      return n;
    }

    return createNodeAux(null,'',obj);
  }  
}

