import { MutationTree } from 'vuex';
import * as Model from './models'
import {Mutations} from './constants'


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
        state.SObjects.push(sh);
    }

};

export default mutations;

