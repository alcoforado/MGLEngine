<template>
<section class="topology">
<component :is="dynamicRender" top="topology"></component>

</section>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'vue-property-decorator';
import {Store} from 'vuex';
import store from '../store/store';
import {Mutations,Actions} from '../store/constants'
import * as Models from '../store/models';
@Component
export default class Topology extends Vue {
    public $store!:Store<Models.StoreRootState>;
    @Prop() shapeId:string;

    dynamicRender()
    {
        if (this.$store.state.SObjects[this.shapeId])
        {
            return this.$store.state.SObjects[this.shapeId].TopologyType;

        }
        return "Empty";

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

</style>