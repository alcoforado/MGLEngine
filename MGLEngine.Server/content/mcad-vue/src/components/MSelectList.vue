<template>
    <md-list >
        <md-list-item class="mselect-list-item" @click="itemSelected()" v-bind:key="item.text" v-for="item in items">
           <svg-icon class="md-size-2x" src="@/assets/images/triangle2d.svg"/><span class="md-list-item-text">{{item.text}}</span>
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

}


</style>

<script lang="ts">
import { Component, Prop, Vue } from 'vue-property-decorator';
import {MSelectListItem} from './mmodels'
import SvgIcon from './svgicon.vue'

@Component({
    components: {
        SvgIcon
    }
})
export default class MSelectList extends Vue {
    @Prop({default:[]}) items!:MSelectListItem[];
    itemSelected(){}
}
</script>