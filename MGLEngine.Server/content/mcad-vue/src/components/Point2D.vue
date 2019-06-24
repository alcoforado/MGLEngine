<template>
     
     <div class="point2d">
        <md-input type="numeric" spellcheck="false" :value="value.x" @input="valueChangeX"></md-input>, 
        <md-input type="numeric" spellcheck="false" :value="value.y" @input="valueChangeY"></md-input>
     </div>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'vue-property-decorator';
@Component
export default class Point2D extends Vue {
    @Prop() value:any;

    valueChangeX(v:string){
        this.value.x=parseInt(v);
        if (isNaN(this.value.x))
            this.value.x=null;
        this.$emit('input',this.value)
    }
    valueChangeY(v:string){
        this.value.y=parseInt(v);
        if (isNaN(this.value.y))
            this.value.y=null;
        this.$emit('input',this.value)
    }
}
</script>

<style lang="scss">

</style>