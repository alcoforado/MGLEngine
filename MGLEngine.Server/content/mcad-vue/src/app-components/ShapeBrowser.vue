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
        <md-list>
        <md-list-item :class="{selected: item.UI.Selected}" @click="selectObject(item.Id)" v-bind:key="item.Id" v-for="item in $store.state.SObjects">
           
            <svg-icon :src="item.TopologyType"></svg-icon><span class="md-list-item-text">{{item.Name}}</span> 
        </md-list-item>



        </md-list>



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

<style lang="scss">
.shape-browser {
    display:flex;
    flex-wrap:wap;
    height:100%;
    width:100%;
    .master-panel {
        width:200px;
        .md-list-item {
            margin: 5px 0px;
            
        }
        .md-list-item.selected {
            .md-list-item-button {
            background-color: var(--md-theme-default-primary);
            &:hover {
                 background-color: var(--md-theme-default-primary) !important;
            }
            }
        }
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

<script lang="ts">
import { Component, Prop, Vue } from 'vue-property-decorator';
import {Store} from 'vuex';
import store from '../store/store';
import {Mutations,Actions} from '../store/constants'
import * as Models from '../store/models';
import SvgIcon from '../components/SvgIcon.vue';
@Component({
    components:{
    SvgIcon
    }
})
export default class ShapeBrowser extends Vue {
    public $store!:Store<Models.StoreRootState>;


    addShape(){
        this.$store.commit(Mutations.DISPLAY_CREATE_SHAPE_DIALOG,true);
    }

    selectObject(id:string)
    {
        this.$store.commit(Mutations.SELECT_SOBJECT,id);
    }

    created() {


    }
}
</script>

