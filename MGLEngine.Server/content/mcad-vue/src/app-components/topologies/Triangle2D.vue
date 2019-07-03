<template>
<div>
    <div class="row">
        <label class="top-label">Point0: </label> <point2 v-model="top.P0"/>
    </div>
    <div class="row">
    <label class="top-label">Point1: </label> <point2 v-model="top.P1"/>
    </div>

    <div class="row">
    <label class="top-label">Point2: </label> <point2 v-model="top.P2"/>
    </div>
</div>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'vue-property-decorator';

@Component
export default class Triangle2D extends Vue {
    @Prop() value:any;

    get top() {
        return this.value == null ? {P0:null,P1:null,P2:null} : this.value;
    }

    
}
</script>

<style lang="scss">

</style>