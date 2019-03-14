import { Getter, GetterTree } from 'vuex';
import * as Model from './models'
import {MSelectListItem} from '../components/mmodels';

const getters: GetterTree<Model.StoreRootState,Model.StoreRootState> = {
    topologiesList(state):MSelectListItem[] {
        return state.TopologyTypes.map(x=>{return {image:`/images/icon-font/theme-white/${x.Name}.svg`,text:x.Name}})
    }
    


};

export default getters;

