<template>
<div class="shape-browser">
    <div class="master-panel" draggable="false" >
        <md-toolbar class="md-dense md-accent" md-elevation="0">
            Shapes
            <md-button  @click="$emit('addShape')" class="md-icon-button">
                <md-icon>add</md-icon>
            </md-button>
        </md-toolbar>
    </div>
    <div class="separator" draggable="false" >
    </div>
    <div class="detail-panel" draggable="false" >
        <md-toolbar class="md-dense md-accent" md-elevation="0">
            <h4 class="md-title" style="flex: 1">Shape Details</h4>
            <md-button  @click="$emit('addShape')" class="md-icon-button">
                <md-icon>add</md-icon>
            </md-button>
        </md-toolbar>
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
        width:200px;
        
    }

    .separator {
        width:0px;
        border-right: 2px white solid;
        cursor: ew-resize;
    }
    .detail-panel {
        flex-grow: 1;
    }

}
</style>