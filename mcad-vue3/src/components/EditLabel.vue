<template>
    <div class="edit-label">
        
        
        <md-field v-if="showEdit" >
            <md-input class="editInput" ref="editInput" spellcheck="false" :value="value" @input="valueChange" @blur="exitEdit"></md-input>
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
        .md-field {
            padding-top:0px;
            margin:0px;
            width:80%;
            min-height:0px;
        }
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
    showEdit:boolean=false;
    @Prop({default:''}) value!:string;
    
    editLabel(){
        this.showEdit=true;
        setTimeout(()=>((this.$refs.editInput as Vue).$el as HTMLElement).focus(),0);
    }
    valueChange(v:string){
        this.value=v;
    }
    exitEdit()
    {
        this.showEdit=false;
        this.$emit("input",this.value)
    }
}
</script>

