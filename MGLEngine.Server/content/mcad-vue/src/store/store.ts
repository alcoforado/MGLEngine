import Vue from 'vue';
import Vuex from 'vuex';
import actions from './actions'
import mutations from './mutations'
import {StoreOptions} from 'vuex';
import {StoreRootState} from './models'
import getters from './getters'


Vue.use(Vuex);

const store: StoreOptions<StoreRootState> = {
    state: {
        PaiterTypes:[],
        TopologyTypes:[],
        SObjects:[],
        DisplayCreateShapeDialog:false
    },
    actions,
    mutations,
    getters
};

export default new Vuex.Store<StoreRootState>(store);
