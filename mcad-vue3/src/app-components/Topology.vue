<template>
<section class="topology">

<component :is="dynamicRender" :value="topology()"></component>

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
export default class Topology extends Vue {
    public $store!:Store<Models.StoreRootState>;
    @Prop() shapeId:string;

    dynamicRender()
    {
        if (this.$store.state.SObjects[this.shapeId])
        {
            const type=this.$store.state.SObjects[this.shapeId].TopologyType;
            return import(`./topologies/${type}.vue`)

        }
        throw "Topology not found."

    }
    topology():any {
        if (this.$store.state.SObjects[this.shapeId])
        {
           return this.$store.state.SObjects[this.shapeId].Topology;
        }
        return {};
    }
}
</script>

<style lang="scss">
.topology {
    .top-label {
    display:inline-block;
   
    margin-right:4px;
    height:32px;
    }
}
</style>