<template>
<img class="svg-icon" :src="getSourcePath()"  alt="example" />
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'vue-property-decorator';

@Component
export default class SvgIcon extends Vue {

@Prop({default:""}) src!:string;
@Prop({default:""}) size!:string;

getSourcePath():string {
    if (!this.src.startsWith("/"))
    {
        var result= `/images/icon-font/theme-white/${this.src}`
        if (!result.endsWith('.svg'))
        {
            result+='.svg'
        }
        return result;
    }
    else
        return this.src;
}

}

</script>

<style lang="scss">
.md-list-item-content {
    .svg-icon {
        width:1.25em;
        margin-right:15px;
    }
}
</style>

