
import {MFormNode,IMFormNode,IMFormChangeEvent,PropertyInfo, PropertyType} from './MFormNode'
import {Vue} from 'vue-property-decorator'

export {IMFormNode} 
export class MForm implements IMFormNode {
   

    root:MFormNode;
    bus:Vue;

    change(value:any):void    {this.root.change(value)}
    value():any{return this.root.value()}
    member(fieldName:string):IMFormNode{return this.root.member(fieldName)}
    setError(value:any,message:string)
    {
        this.root.error(value,message);
    }

    error get

    constructor(model:any)
    {
        this.bus=new Vue({});
        this.root=MFormNode.createMFormTree(this.bus,model);
        this.bus.$on('change',(ev:IMFormChangeEvent)=>{this.root.onModelChange(ev)})
    }
}