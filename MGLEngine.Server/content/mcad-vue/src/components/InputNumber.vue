<template>
         <md-field :class="hasError ? 'md-invalid':''">
            <md-input  spellcheck="false" :value="value.getValue()" @input="valueChange" ></md-input>
         </md-field>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'vue-property-decorator';
import {IMFormNode} from '../shared/forms/MForm';
@Component
export default class InputNumber extends Vue {
    @Prop() value:IMFormNode;
   
    
    
    constructor()
    {
        super();
        
    }
    
    valueChange(v:string)
    {
        var n = this.map(v);
        var ev = this.value.change(n);
        

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
                if (isNaN(x)){
                    throw 'Not a Number'
                return x;
                }
            }
            throw 'Not a Number'
        }
        return null;

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