<template>
  <div class="page-container">
    <md-app md-mode="reveal">
      <md-app-toolbar class="md-primary">
        <md-button class="md-icon-button" @click="menuVisible = !menuVisible">
          <md-icon>menu</md-icon>
        </md-button>
        <span class="md-title">MCad</span>

        <div class="md-toolbar-section-end">
            <md-button class="md-icon-button">
              <md-icon>more_vert</md-icon>
            </md-button>
        </div>
      </md-app-toolbar>



      <md-app-drawer :md-active.sync="menuVisible">
        
        <md-list>
          <md-list-item>
            <md-icon>move_to_inbox</md-icon>
            <span class="md-list-item-text">Inbox</span>
          </md-list-item>

          <md-list-item>
            <md-icon>send</md-icon>
            <span class="md-list-item-text">Sent Mail</span>
          </md-list-item>

          <md-list-item>
            <md-icon>delete</md-icon>
            <span class="md-list-item-text">Trash</span>
          </md-list-item>

          <md-list-item>
            <md-icon>error</md-icon>
            <span class="md-list-item-text">Spam</span>
          </md-list-item>
        </md-list>
      </md-app-drawer>

      <md-app-content>
        <shape-browser>

        </shape-browser>
        
        <m-modal title="Create Shape" v-on:cancel="showCreateShapeDialog(false)"  :showDialog="$store.state.DisplayCreateShapeDialog" cancelButtonText="" confirmButtonText=""> 
          <m-select-list v-on:item_selected="createShape" :items="topologiesList"></m-select-list>

        </m-modal>

       
      </md-app-content>
    </md-app>
  </div>
</template>


<style lang="scss">

.page-container {
  height:100%;
}


@import "./scss/material-icons.scss";
@import "./scss/fonts.scss";

.md-app-content {
  padding:0;
}


</style>



<script lang="ts">
import VueMaterial from 'vue-material';
import {Store} from 'vuex';
import 'vue-material/dist/vue-material.min.css';
import { Component, Vue } from 'vue-property-decorator';
import store from './store/store';
import {Mutations,Actions} from './store/constants'
import * as Models from './store/models';
import MModal from './components/modal.vue';
import MSelectList from './components/MSelectList.vue'
import {MSelectListItem} from './components/mmodels'
import ShapeBrowser from './app-components/ShapeBrowser.vue'
import EditLabel from './components/EditLabel.vue'
import SvgIcon from './components/SvgIcon.vue'
Vue.use(VueMaterial);

Vue.component('edit-label',EditLabel)

@Component ({
  components:{
    MModal,
    MSelectList,
    ShapeBrowser,
    SvgIcon
  }
})
export default class App extends Vue {
  private menuVisible: boolean = false;
  public $store!:Store<Models.StoreRootState>;
  
  

  get topologiesList():MSelectListItem[] {
    
    return this.$store.getters.topologiesList;
  }

  showCreateShapeDialog(b:boolean) {
    this.$store.commit(Mutations.DISPLAY_CREATE_SHAPE_DIALOG,b);
  }
  createShape(it:MSelectListItem)
  {
    this.$store.dispatch(Actions.CREATE_SHAPE,it.text);
  }

  created(){
     
     this.$store.dispatch(Actions.INITIALIZE);
  }

}
</script>




