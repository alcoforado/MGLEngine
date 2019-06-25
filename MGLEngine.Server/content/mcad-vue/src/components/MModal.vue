<template>
    <md-dialog  :md-active.sync="showDialog" :md-backdrop="false">
        <md-toolbar class="md-accent" md-elevation="0">
            <h3 class="md-title" style="flex: 1">{{title}}</h3>
            <md-button  @click="$emit('cancel')" class="md-icon-button">
                <md-icon>clear</md-icon>
            </md-button>
    </md-toolbar>


        <div class="my-modal-content">
            <slot></slot>
        </div>
       

       <md-dialog-actions v-if="cancelButtonText!='' && confirmButtonText!=''">
        <md-button class="md-flat" @click="$emit('cancel')">{{cancelButtonText}}</md-button>
        <md-button class="md-flat" @click="$emit('confirm')">{{confirmButtonText}}</md-button>
      </md-dialog-actions>
    </md-dialog>

</template>

<style lang="scss">
.my-modal-content {
    padding: 10px;
    padding-top: 20px;
    padding-bottom: 20px;
}
.md-flat {
    text-decoration:underline;
}


</style>



<script lang="ts">
import { Component, Prop, Vue } from 'vue-property-decorator';


@Component
export default class MModal extends Vue {
    @Prop({default:true}) showDialog!:boolean;
    @Prop({default:""}) title!:string;
    @Prop({default:"Cancel"}) cancelButtonText!:string;
    @Prop({default:"OK"}) confirmButtonText!:string;

}
</script>