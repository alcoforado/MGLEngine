<template>
<div class="shape-browser">
    <div class="master-panel" draggable="false" >
        Shapes
    </div>
    <div class="separator" draggable="false" >
    </div>
    <div class="detail-panel" draggable="false" >
        Form Here
    </div>
</div>
    
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'vue-property-decorator';

@Component({})
export default class ShapeBrowser extends Vue {




}
</script>

<style lang="scss">
.shape-browser {
    display:flex;
    flex-wrap:wap;
    height:100%;
    width:100%;
    .master-panel {
        width:100px;
        
    }

    .separator {
        width:5px;
        border-right: 2px white solid;
        cursor: ew-resize;
    }
    .detail-panel {
        flex-grow: 1;
    }

}
</style>