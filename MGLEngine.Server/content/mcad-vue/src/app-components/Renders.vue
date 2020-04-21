<template>
<section class="render">

    <component v-if="isPainterTypeDefined()" :is="dynamicRender" :value="render()"></component>
</section>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'vue-property-decorator';
import Triangle2D from './topologies/Triangle2D.vue';
import {Store} from 'vuex';
import store from '../store/store';
import {Mutations,Actions} from '../store/constants'
import * as Models from '../store/models';
@Component({
    components:{
    }
})
export default class Render extends Vue {
    public $store!:Store<Models.StoreRootState>;
    @Prop() shapeId:string;

    isPainterTypeDefined() {
        return this.$store.state.SObjects[this.shapeId] && this.$store.state.SObjects[this.shapeId].PainterType;
    }

    dynamicRender()
    {
        if (this.$store.state.SObjects[this.shapeId])
        {
            const type=this.$store.state.SObjects[this.shapeId].PainterType;
            return import(`./renders/${type}.vue`)

        }
        throw "Topology not found."

    }
    render():any {
        if (this.$store.state.SObjects[this.shapeId])
        {
           return this.$store.state.SObjects[this.shapeId].Painter;
        }
        return {};
    }
}
</script>

<style lang="scss">
.render {
    .top-label {
    display:inline-block;
   
    margin-right:4px;
    height:32px;
    }
}
</style>