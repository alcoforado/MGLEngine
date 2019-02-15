import { MutationTree } from 'vuex';
import * as Model from './models'
import {Mutations} from './constants'


const mutations: MutationTree<Model.StoreRootState> = {
    [Mutations.SET_PAINTER_TYPES](state:Model.StoreRootState, payload:Array<Model.PainterType>) {
        state.PaiterTypes=payload;
    },
    [Mutations.SET_TOPOLOGY_TYPES](state:Model.StoreRootState, payload:Array<Model.TopologyType>) {
        state.TopologyTypes=payload;
    }
    


};

export default mutations;

