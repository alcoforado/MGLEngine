#ifndef NTREE_H
#define NTREE_H


#include <list>
#include <functional>

	template<class Data>
	class NTreeNode
	{
	private:
		std::list<NTreeNode<Data>*> _childs;
		NTreeNode<Data>* _parent;
		Data _data;

	public:
		
		NTreeNode(Data data)
		{
			_parent = nullptr;
			_data = data;
		}

		bool IsChildless()
		{
			return  _childs.size() == 0;
		}

		bool IsRoot()
		{
			return _parent == null;
		}

		void AppendChild(NTreeNode<Data> *child)
		{
			_childs.push_back(child);
			child._parent = this;
		}




		Data& GetData()
		{
			return _data;
		}

		NTreeNode<Data>* GetParent()
		{
			return _parent;
		}

		

		std::list<NTreeNode<Data>*>& GetChilds()
		{
			return _childs;
		}

		

		void ForItselfAndAllParents(std::function<void(NTreeNode<Data>*)> action)
		{
			auto ptr = this;
			auto next = _parent;
			while (next != nullptr)
			{
				action(ptr);
				ptr = next;
				next = ptr._parent;
			}
			action(ptr);
		}

		void ForAllPreOrderControlDescent(std::function<bool(NTreeNode<Data>*)> visitor)
		{
			if (this->IsChildless())
			{
				visitor(this);
				return;
			}
			else
			{
				if (!visitor(this))
					return;
				for (auto ch : _childs)
				{
					ch->ForAllInOrder(visitor);
				}
				
			}
		}


		void ForAllInOrder(std::function<void(NTreeNode<Data>*)> visitor)
		{
			if (this->IsChildless())
			{
				visitor(this);
				return;
			}
			else
			{
				for (auto ch : _childs)
				{
					ch->ForAllInOrder(visitor);
				}
				visitor(this);
			}
		}

		
		NTreeNode<Data>* FindNodeWhere(std::function<bool(NTreeNode<Data>*)> search)
		{
			if (this.IsChildless())
			{
				return search(this) ? this : nullptr;
			}
			else
			{
				for(auto ch : _childs)
				{
					auto result = ch->FindNodeWhere(search);
					if (result != nullptr)
						return result;
				}
				return search(this) ? this : nullptr;
			}
		}
		

		void CutSubTree()
		{
			if (this->IsRoot())
				return;
			auto parent = this->_parent;
			this->_parent = nullptr;
			parent->_childs.remove(this);
		}
	};















#endif // NTREE_H
