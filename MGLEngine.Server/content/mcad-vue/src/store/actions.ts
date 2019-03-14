import { ActionTree } from 'vuex';
import axios from 'axios';
import * as Model from './models'
import {Mutations,Actions} from './constants'



const actions: ActionTree<Model.StoreRootState, Model.StoreRootState> = {
    async [Actions.INITIALIZE]({ commit }) {
        var p1 = axios.get('/api/shape/rendertypes').then((response) => {
            commit(Mutations.SET_PAINTER_TYPES,response.data);
        }, (error) => {
            console.log(error);
        });
        var p2 = axios.get('/api/shape/topologytypes').then((response) => {
            commit(Mutations.SET_TOPOLOGY_TYPES,response.data);
        }, (error) => {
            console.log(error);
        });
        return await Promise.all([p1,p2]);
    },

    async [Actions.SAVE_SHAPE]({commit},shape) {
        return axios.post('/api/shape',shape);
    }
};

export default actions;

