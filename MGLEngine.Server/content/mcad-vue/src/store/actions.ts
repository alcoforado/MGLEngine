import { ActionTree } from 'vuex';
import axios from 'axios';
import * as Model from './models'

export enum Actions {
    INITIALIZE="fetchData"
}

export const actions: ActionTree<Model.StoreRootState, Model.StoreRootState> = {
    [Actions.INITIALIZE]({ commit }): any {
        axios.get('/api/shape/rendertypes').then((response) => {
            
        }, (error) => {
            console.log(error);
        });
    }
};



