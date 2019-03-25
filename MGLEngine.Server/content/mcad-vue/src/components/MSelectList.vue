<template>
    <md-list >
        <md-list-item class="mselect-list-item" @click="itemSelected(item)" v-bind:key="item.text" v-for="item in items">
           <img :src="item.image"/><span class="md-list-item-text">{{item.text}}</span>
        </md-list-item>
    </md-list>

</template>



<style lang="scss">



@keyframes hover-highlight {
  from {
    background-color: map-get($app-theme,background);
  }

  to {
      background-color: map-get($app-theme,background-highlight);
  }
}

.mselect-list-item {
  &:hover
  {
        animation: hover-highlight 0.55s ;
        background-color: map-get($app-theme,background-highlight);
        animation-timing-function: cubic-bezier(0.4, 0.0, 0.2, 1);
        border-radius: 5px;

        button {
        border-radius: 5px;
        }
  }
  img {
    width: 20px;
  }
  span {
    margin-left:10px;
  }

}


</style>

<script lang="ts">
import { Component, Prop, Vue } from 'vue-property-decorator';
import {MSelectListItem} from './mmodels'
import SvgIcon from './SvgIcon.vue'

@Component({
    components: {
        SvgIcon
    }
})
export default class MSelectList extends Vue {
    @Prop({default:[]}) items!:MSelectListItem[];
    itemSelected(item:MSelectListItem){
     
     this.$emit("item_selected",item)
    }
}
</script>