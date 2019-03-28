<template>
    <div class="edit-label">
        
        
        <md-field v-if="showEdit" @blur="changeLabel">
            <md-input v-model="text"></md-input>
        </md-field>
        <div v-else class="slot-placeholder">
            {{text}} <md-icon>edit</md-icon>
            
        </div>
    </div>
</template>

<style lang="scss">
    .edit-label {
       
        .slot-placeholder {
            display:inline-block;
            margin-right: 10px;
            .edit-button {
                display: inline-block;
                margin-left:20px;
             
            
            }
            .md-icon {
                  margin-left:10px;
                  color: var(--md-theme-default-divider-on-background) !important;
                  &:hover {
                      color:var(--md-theme-default-icon-on-background) !important;
                  }
                
            }
        }
    }
        
</style>

<script lang="ts">
import { Component, Prop, Vue } from 'vue-property-decorator';
@Component
export default class EditLabel extends Vue {
    @Prop({default:false}) showEdit!:boolean;
    @Prop({default:''}) text!:string;
    changeLabel() {
        this.$emit("labelChanged",this.text);
        this.showEdit=false;
    }
}
</script>

