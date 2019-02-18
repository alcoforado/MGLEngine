<template>
  <div class="page-container">
    <md-app md-mode="reveal">
      <md-app-toolbar class="md-primary">
        <md-button class="md-icon-button" @click="menuVisible = !menuVisible">
          <md-icon>menu</md-icon>
        </md-button>
        <span class="md-title">My Title</span>

        <div class="md-toolbar-section-end">
            <md-button class="md-icon-button">
              <md-icon>more_vert</md-icon>
            </md-button>
        </div>
      </md-app-toolbar>



      <md-app-drawer :md-active.sync="menuVisible">
        <md-toolbar class="md-transparent" md-elevation="0">Navigation</md-toolbar>

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
        
        <m-modal title="Create Shape"> 
          <m-select-list :items="its"></m-select-list>

        </m-modal>

       
      </md-app-content>
    </md-app>
  </div>
</template>


<style lang="scss">


@import "~vue-material/dist/theme/all"; // Apply the theme
@import "./scss/fonts.scss";
@import "./scss/material-icons.scss";



 


  


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
Vue.use(VueMaterial);

export interface MSelectListItem {
    image:string;
    text:string;
}


@Component ({
  components:{
    MModal,
    MSelectList
  }
})
export default class App extends Vue {
  private menuVisible: boolean = false;
  public $store!:Store<Models.StoreRootState>;
  public its:MSelectListItem[]= [{image: "image1",text: "text1"},{image: "image2",text: "text2"}];
  
  created(){
     
     this.$store.dispatch(Actions.INITIALIZE);
  }

}
</script>




