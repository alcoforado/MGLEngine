import Vue from 'vue';
import Vuex from 'vuex';
import gactions from 'actions'
import {StoreOptions} from 'vuex';
import {StoreRootState} from './models'


Vue.use(Vuex);

const store: StoreOptions<StoreRootState> = {
    state: {
        PaiterTypes:[],
        ShapeTypes:[]
    },
};

export default new Vuex.Store(store);

