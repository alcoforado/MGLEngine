<template>
    <md-list>
        <md-list-item v-bind:key="item.text" v-for="item in items">
           <span class="md-list-item-text">{{item.text}}</span>
        </md-list-item>
    </md-list>

</template>




<script lang="ts">
import { Component, Prop, Vue } from 'vue-property-decorator';

export interface MSelectListItem {
    image:string;
    text:string;
}

@Component
export default class MSelectList extends Vue {
    @Prop({default:[]}) items!:MSelectListItem[];
}
</script>