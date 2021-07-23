import { Getter, GetterTree } from 'vuex';
import * as Model from './models'
import {MSelectListItem} from '../components/mmodels';

const getters: GetterTree<Model.StoreRootState,Model.StoreRootState> = {
    topologiesList(state):MSelectListItem[] {
        return state.TopologyTypes.map(x=>{return {image:`/images/icon-font/theme-white/${x.Name}.svg`,text:x.Name}})
    },
    
    visibleShapes(state):Model.SceneObject[] {
        console.log('visibleShapes Called');
        var result:Model.SceneObject[]=[];
        Object.keys(state.SObjects).forEach(k=>{
            var o = state.SObjects[k];
            if (o.UI.Selected)
                result.push(o);
        });
        return result;
    }

};

export default getters;

