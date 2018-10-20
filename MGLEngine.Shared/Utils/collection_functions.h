#pragma once

namespace mstd {

	template<class K, class T>
	class DM
	{
		std::map<K, T> *_m;

	public:
		DM(std::map<K, T> &m)
			:_m(&m) {}

		bool Have(K key)
		{
			return _m->find(key) != _m->end();
		}
	};

	template<class K,class T>
	DM<K,T> Does(std::map<K,T> &m)
	{
		return DM<K,T>(m);
	}


	


}