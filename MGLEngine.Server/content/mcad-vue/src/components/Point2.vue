<template>
     
     <div class="point2d">
         <span class="field">
         
         
         <md-field :class="hasErrorX ? 'md-invalid':''">
         
            <md-input  spellcheck="false" :value="point.x" @input="valueChangeX" @onkeydown="validateInput"></md-input>
         </md-field>
         </span>
         <span class="field-separator">, </span> 
         
         <span class="field">
         <md-field :class="hasErrorY ? 'md-invalid':''"> 
         
            <md-input  spellcheck="false" :value="point.y" @input="valueChangeY"></md-input>
        </md-field>
        </span>
         
     </div>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'vue-property-decorator';
@Component
export default class Point2 extends Vue {
    @Prop() value:any;

    public hasErrorX:boolean=false;
    public hasErrorY:boolean=false;
    get point() {
        return this.value==null ? {x:"",y:""}:this.value;
    }

    validateInputX(e:KeyboardEvent)
    {
        var v = (e.target as HTMLInputElement).value;
        if ((e.key == "+" || e.key == "-") && (v==null || v==""))
            return;
        
        
            e.preventDefault();

    }
    valueChangeX(v:string){
        this.value.x=parseFloat(v);
        if (isNaN(this.value.x)){
            this.value.x=null;
            this.hasErrorX=true;
        }
        this.hasErrorX=false;
        this.$emit('input',this.value)
    }
    valueChangeY(v:string){
        this.value.y=parseFloat(v);
        if (isNaN(this.value.y)){
            this.value.y=null;
            this.hasErrorY=true;
        }
        this.hasErrorY=false;
        this.$emit('input',this.value)
    }
}
</script>

<style lang="scss">
.point2d {
    display:inline-block;
.md-field {
    margin:0px;
    padding:0px;
    min-height:initial;
}

.field {
    display:inline-block;
    
    width:100px;
    
}
.field-separator {
    position:relative;
    top:18px;
    margin: 0px 5px;
}

}
</style>