<template>
    <md-dialog  :md-active.sync="showDialog" :md-backdrop="false">
        <md-toolbar class="md-accent">
            <h3 class="md-title" style="flex: 1">{{title}}</h3>
            <md-button  @click="$emit('cancel')" class="md-icon-button">
                <md-icon>clear</md-icon>
            </md-button>
    </md-toolbar>


        <div class="my-modal-content">
            <slot></slot>
        </div>
       
       <md-dialog-actions>
        <md-button class="md-raised md-primary" @click="$emit('cancel')">Cancel</md-button>
        <md-button class="md-raised md-primary" @click="$emit('confirm')">Save</md-button>
      </md-dialog-actions>
    </md-dialog>

</template>

<style lang="scss">
.my-modal-content {
    padding: 10px;
    padding-top: 20px;
    padding-bottom: 20px;
}


</style>



<script lang="ts">
import { Component, Prop, Vue } from 'vue-property-decorator';


@Component
export default class MModal extends Vue {
    @Prop({default:true}) showDialog!:boolean;
    @Prop({default:""}) title!:string;
}
</script>