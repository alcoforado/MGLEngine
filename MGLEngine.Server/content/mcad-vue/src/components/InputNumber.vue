<template>
         <md-field :class="hasError ? 'md-invalid':''">
            <md-input  spellcheck="false" :value="displayValue" @input="valueChange" ></md-input>
         </md-field>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'vue-property-decorator';
import {MForm} from '../shared/forms/MForm';
@Component
export default class Point2 extends Vue {
    @Prop({default:{x:null,y:null}}) value:any;
   
    public _value:any=null;
    public mForm:MForm;
    
    constructor()
    {
        super();
        this.mForm=new MForm(this);
    }
    
    
    get displayValue() {
       return  this.mForm.GetValue(this.value,'',this.map);
    }
    get hasError() {
        return this.mForm.HasError(this.value);
    }

    map(v:string):number
    {
        if (v!=null)
        {
            var vt = v.trim().toLowerCase();
            var regexp = /[+-]?[0-9]+(.[0-9]*)?([eE][+-][0-9]+)?/;
            var content= regexp.exec(vt);
            if (content[0]==vt)
            {

                 var x=parseFloat(v.trim());
                if (isNaN(this.value.x)){
                    throw 'Not a Number'
                return x;
                }
            }
            throw 'Not a Number'
        }
        throw 'required'

    }
    valueChange(v:string)
    {
        this.mForm.valueChane(v,'',this.map);
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