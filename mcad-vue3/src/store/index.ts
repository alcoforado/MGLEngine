import { createStore } from 'vuex'
import {StoreRootState} from './models'
import actions from './actions'
import mutations from './mutations'
import getters from './getters'

export default createStore<StoreRootState>({
  state() {
    return ({
      PaiterTypes:[],
      TopologyTypes:[],
      SObjects:{},
      DisplayCreateShapeDialog:false
    }) as StoreRootState;
  },
  actions,
  mutations,
  getters
})



