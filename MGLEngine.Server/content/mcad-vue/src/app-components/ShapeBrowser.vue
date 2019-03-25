<template>
<div class="shape-browser">
    <div class="master-panel" draggable="false" >
        <md-toolbar class="md-dense" md-elevation="0">
            <h4 class="md-title" style="flex: 1">Shapes</h4>
            <md-button  @click="addShape" class="md-icon-button">
                <md-icon>add</md-icon>
            </md-button>
        </md-toolbar>
        <md-divider></md-divider>
        <div v-bind:key="item.Id" v-for="item in $store.SObjects">
            <span>{{item.Name}}</span> 
        </div>



    </div>
    <div class="separator" draggable="false" >
    </div>
    <div class="detail-panel" draggable="false" >
        <md-toolbar class="md-dense" md-elevation="0">
            <h4 class="md-title" style="flex: 1">Shape Details</h4>
        </md-toolbar>
        <md-divider></md-divider>
    </div>
</div>
    
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'vue-property-decorator';
import {Store} from 'vuex';
import store from '../store/store';
import {Mutations,Actions} from '../store/constants'
import * as Models from '../store/models';

@Component({})
export default class ShapeBrowser extends Vue {
    public $store!:Store<Models.StoreRootState>;


    addShape(){
        this.$store.commit(Mutations.DISPLAY_CREATE_SHAPE_DIALOG,true);
    }

    created() {


    }
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
        width:4px;
        background-color: rgba(255, 255, 255, 0.2);
        cursor: ew-resize;
    }
    .detail-panel {
        flex-grow: 1;
    }

}
</style>