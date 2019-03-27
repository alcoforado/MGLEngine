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
        Vue.set(state.SObjects,sh.Id,sh);
        Object.keys(state.SObjects).forEach(key => {
            state.SObjects[key].UI.Selected // value of the current key
        
        })
        var newArray = [...state.SObjects];
        newArray.forEach(x=>x.UI.Selected=false);
        newArray.push(sh);
        state.SObjects=newArray;
    }

    [Mutations.SELECT_SOBJECT](state:Model.StoreRootState,sh:Model.SceneObject)
    {
        state.SObjects.in
        Vue.set(state.SObjects)
        state.SObjects=newArray;
    }
};

export default mutations;

