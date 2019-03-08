<template>
<img class="icon" :src="src"  alt="example" />
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'vue-property-decorator';

@Component
export default class SvgIcon extends Vue {
@Prop({default:""}) src!:string;
@Prop({default:""}) size!:string;
}

</script>

<style lang="scss">

</style>

