<template>
    <div class="edit-label">
        
        
        <md-field v-if="showEdit" @blur="labelChange">
            <md-input v-model="text"></md-input>
        </md-field>
        <div v-else class="slot-placeholder">
            {{value}}
            <md-button  @click="editLabel" class="md-icon-button">
                <md-icon>edit</md-icon>
            </md-button>
        </div>
    </div>
</template>

<style lang="scss">
    .edit-label {
        
        .slot-placeholder {
            display:inline-block;
            margin-right: 10px;
            .md-button.md-icon-button {
                vertical-align:middle;
            }
           
    
        }
       
    }
        
</style>

<script lang="ts">
import { Component, Prop, Vue } from 'vue-property-decorator';
@Component
export default class EditLabel extends Vue {
    @Prop({default:false}) showEdit!:boolean;
    @Prop({default:''}) value!:string;
    editLabel(){
        this.showEdit=true;
    }
    labelChange(){
        this.$emit('label-change',this.value);
        this.showEdit=false;
    }
}
</script>

