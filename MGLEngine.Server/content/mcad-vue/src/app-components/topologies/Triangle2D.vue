<template>
<div>
    <div class="row">
        <span class="top-label">Point0: </span> <point2 v-model="top.P0"/>
    </div>
    <div class="row">
    <span class="top-label">Point1: </span> <point2 v-model="top.P1"/>
    </div>

    <div class="row">
    <span class="top-label">Point2: </span> <point2 v-model="top.P2"/>
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
.row {
    position:relative;
    vertical-align:middle;
}
</style>