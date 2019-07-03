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


    async [Actions.CREATE_SHAPE]({commit},shapeType:string ){
        var sh = new Model.SceneObject();
        sh.TopologyType=shapeType;

        var response=await axios.get('/api/shape/reserveid/'+shapeType);
        sh.Id=response.data;
        sh.Name=response.data;
        sh.UI.Selected=true;
        sh.Topology=null;
        commit(Mutations.ADD_SHAPE,sh);
    },


    async [Actions.SAVE_SHAPE]({commit},shape) {
        return axios.post('/api/shape',shape);
    }
};

export default actions;

