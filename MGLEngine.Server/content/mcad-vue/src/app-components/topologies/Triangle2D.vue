<template>
<div>
    <point2d v-model="top.P0"/>
    <point2d v-model="top.P1"/>
    <point2d v-model="top.P2"/>
</div>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'vue-property-decorator';

@Component
export default class Triangle2D extends Vue {
    @Prop() value:any;
}
</script>

<style lang="scss">

</style>