<template>
<img svg-inline class="icon" :src=src alt="example" />
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'vue-property-decorator';
export default class SvgIcon extends Vue {
@Prop({default:""}) src!:string;
}
</script>

<style lang="scss">

</style>