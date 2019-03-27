import { MutationTree } from 'vuex';
import * as Model from './models'
import {Mutations} from './constants'
import { Vue } from 'vue-property-decorator'

const mutations: MutationTree<Model.StoreRootState> = {
    [Mutations.SET_PAINTER_TYPES](state:Model.StoreRootState, payload:Array<Model.PainterType>) {
        state.PaiterTypes=payload;
    },
    [Mutations.SET_TOPOLOGY_TYPES](state:Model.StoreRootState, payload:Array<Model.TopologyType>) {
        state.TopologyTypes=payload;
    },
    [Mutations.DISPLAY_CREATE_SHAPE_DIALOG](state:Model.StoreRootState,payload:boolean) {
        state.DisplayCreateShapeDialog=payload;
    },
    [Mutations.ADD_SHAPE](state:Model.StoreRootState,sh:Model.SceneObject)
    {
       
        Object.keys(state.SObjects).forEach(key => {
            state.SObjects[key].UI.Selected=false; // value of the current key
        
        })
        Vue.set(state.SObjects,sh.Id,sh);
    },

    [Mutations.SELECT_SOBJECT](state:Model.StoreRootState,itemId:string)
    {
        Object.keys(state.SObjects).forEach(key => {
            state.SObjects[key].UI.Selected=false; // value of the current key
        })
        state.SObjects[itemId].UI.Selected=true;
    }
};

export default mutations;

