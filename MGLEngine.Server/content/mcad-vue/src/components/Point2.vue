<template>
     
     <div class="point2d">
         
         
         
         <md-field :class="hasErrorX ? 'md-invalid':''">
         
            <input-number  spellcheck="false" :value="value.member('x')" @input="valueChangeX" ></input-number>
         </md-field>
        
         <span class="field-separator">, </span> 
         
        
         <md-field :class="hasErrorY ? 'md-invalid':''"> 
         
            <input-number  spellcheck="false" :value="value.member('y')" @input="valueChangeY"></input-number>
            
        </md-field>
       
     </div>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'vue-property-decorator';
import {IMFormNode} from '../shared/forms/MFormNode'
@Component
export default class Point2 extends Vue {
    @Prop() value:IMFormNode;
   
   
   
  
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