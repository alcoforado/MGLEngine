<template>
     
     <div class="point2d">
         
         
         
         <md-field :class="hasErrorX ? 'md-invalid':''">
         
            <md-input  spellcheck="false" :value="point.x" @input="valueChangeX" ></md-input>
         </md-field>
        
         <span class="field-separator">, </span> 
         
        
         <md-field :class="hasErrorY ? 'md-invalid':''"> 
         
            <md-input  spellcheck="false" :value="point.y" @input="valueChangeY"></md-input>
            
        </md-field>
       
     </div>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'vue-property-decorator';
@Component
export default class Point2 extends Vue {
    @Prop({default:{x:null,y:null}}) value:any;
   
    public hasErrorX:boolean=false;
    public hasErrorY:boolean=false;
    get point() {
        return this.value==null ? {x:"",y:""}:this.value;
    }

    sendEvent(){
            if (this.hasErrorY || this.hasErrorX)
                this.$emit("error","Expect number");
            else
                this.$emit('input',this.value);
    }
   
    valueChangeX(v:string){
        debugger;
        if (this.value==null)
            this.value={x:null,y:null};
        this.value.x=parseFloat(v);
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
        if (isNaN(this.value.y)){
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