import Vue from 'vue';
import Vuex from 'vuex';
import actions from './actions'
import mutations from './mutations'
import {StoreOptions} from 'vuex';
import {StoreRootState} from './models'


Vue.use(Vuex);

const store: StoreOptions<StoreRootState> = {
    state: {
        PaiterTypes:[],
        TopologyTypes:[]
    },
    actions,
    mutations
};

export default new Vuex.Store<StoreRootState>(store);