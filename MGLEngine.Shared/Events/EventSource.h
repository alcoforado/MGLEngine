#pragma once
#include <MGLEngine.Shared/Utils/pointers.h>
#include <MGLEngine.Shared/Utils/eassert.h>

#include <deque>
#include <functional>

template<class EventDataT>
class EventListener {

public:
	virtual void Process(const EventDataT& ev)=0;
	virtual ~EventListener() {}

};

template<class EventDataT>
class Subscription {

};

template<class EventDataT>
class IObservable
{

private:
	
public:

	using function_listener = std::function<void(const EventDataT&)>;
	struct Listener {
		s_ptr<EventListener<EventDataT> > eventListener;
		function_listener functional;
		bool isPaused = false;
		bool isDeleted = false;
	};
	
	class Subscription {
		Listener* pListener;
		size_t index;
		IObservable<EventDataT>* observable;
	public:
		void Pause() {
			eassert(!pListener->isDeleted, "Subscription Deleted");
			pListener->isPaused = true;
		}
		void Resume() {
			eassert(!pListener->isDeleted, "Subscription Deleted");
			pListener->isPaused = false;
		}
		void Delete() {
			eassert(!pListener->isDeleted, "Subscription Deleted");
			pListener->isDeleted = true;
			pListener->isPaused = true;
			observable->availableSlots.push_back(index);
		}
		Subscription(Listener* p1, size_t i, IObservable<EventDataT>* pOwner)
			:pListener(p1), index(i), observable(pOwner) {
		}
	};
	friend class Subscription;

protected:
	

	std::deque<Listener> subscribers;
	std::deque<size_t> availableSlots;

	
	
	//private common function to add a listener
	s_ptr<Subscription> AddListener(const Listener& listener)
	{
		if (availableSlots.empty())
		{
			subscribers.push_back(listener);
			return std::make_shared<Subscription>(&(subscribers.back()),subscribers.size() - 1,this);
		}
		else
		{
			size_t index = availableSlots.front();
			availableSlots.pop_front();
			subscribers[index] = listener;
			return std::make_shared<Subscription>(&(subscribers[index]), index,this);
		}
	}


public:

	


	s_ptr<Subscription> Subscribe(s_ptr<EventListener<EventDataT> >& listener)
	{
			return AddListener(Listener{
				.eventListener = listener,
				.isPaused = false
				});

	}
	s_ptr<Subscription> Subscribe(const function_listener& f)  {
		return AddListener(Listener{
			.eventListener = nullptr,
			.functional=f,
			.isPaused=false
		});
	}
	
};

template<class EventDataT>
class EventSource : public IObservable<EventDataT>
{
public:
	using Observable = IObservable<EventDataT>;
	using SubscriptionHandle = s_ptr<typename IObservable<EventDataT>::Subscription>;

	void EmitEvent(const EventDataT& ev)
	{
		for (auto& sub : this->subscribers)
		{
			if (sub.isPaused)
				continue;
			if (sub.eventListener == nullptr)
				sub.functional(ev);
			else
				sub.eventListener->Process(ev);
		}
		
	}

	
};