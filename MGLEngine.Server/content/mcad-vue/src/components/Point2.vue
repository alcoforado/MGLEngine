<template>
     
     <div class="point2d">
         
         
         
         <md-field :class="hasErrorX ? 'md-invalid':''">
         
            <md-input  spellcheck="false" :value="value.x" @input="valueChangeX" ></md-input>
         </md-field>
        
         <span class="field-separator">, </span> 
         
        
         <md-field :class="hasErrorY ? 'md-invalid':''"> 
         
            <md-input  spellcheck="false" :value="value.y" @input="valueChangeY"></md-input>
            
        </md-field>
       
     </div>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'vue-property-decorator';
import {MFormNode} from '../shared/forms/MForm'
@Component
export default class Point2 extends Vue {
    @Prop() value:MFormNode;
   
    public _value:any=null;
    public hasErrorX:boolean=false;
    public hasErrorY:boolean=false;
   
    get displayValue() {
       return  this._value ? this._value : this.value;

    }

    

    sendEvent(){
            if (this.hasErrorY || this.hasErrorX)
                this.$emit("error","Expect number");
            else
                this.$emit('input',this.value);
    }
   
    valueChangeX(v:string){
        if (this.value.x && this.value.y)
        {
        
        this._value = {
            x: v,
            y: this.value.y.toString()
        };
        
        var regexp = /[+-]?[0-9]+(.[0-9]*)?([eE][+-][0-9]+)?/;
        var content = regexp.exec(v);

        if (content!= null && content[0]==v.trim())
        {

        }
        
        this._value


        var x=parseFloat(v.trim());
        if (isNaN(this.value.x)){
            this.value.x=null;
            this.hasErrorX=true;
        }
        else {
            this.hasErrorX=false;
        }
        this.sendEvent();
    }
    valueChangeY(v:string){
        if (this.value==null)
            this.value={x:null,y:null};
        this.value.y=parseFloat(v);
        if (isNaN(this.value.y))
        {
            this.value.y=null;
            this.hasErrorY=true;
        }
        else {
            this.hasErrorY=false;
        }
        this.sendEvent();

    }
}
</script>

<style lang="scss">
.point2d {
    display:inline-block;
.md-field {
    width:100px;
    display:inline-block;
    margin:0px;
    padding:0px;
    min-height:initial;
}


.field-separator {
    position:relative;
    top:11px;
    margin: 0px 5px;
}

}
</style>