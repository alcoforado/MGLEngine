<template>
<div>
    <div class="row">
        <span class="top-label">Point0: </span> <point2 :value="mform.member('P0')"/>
    </div>
    <div class="row">
    <span class="top-label">Point1: </span> <point2 :value="mform.member('P1')"/>
    </div>

    <div class="row">
    <span class="top-label">Point2: </span> <point2 :value="mform.member('P2')"/>
    </div>
</div>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'vue-property-decorator';
import {MForm} from '../../shared/forms/MForm'
@Component
export default class Triangle2D extends Vue {
    @Prop() value:any;
    mform:MForm=new MForm(this.value);
    
    

    

    
}
</script>

<style lang="scss">
.row {
    position:relative;
    vertical-align:middle;
}
</style>