#pragma once
#include <MGLEngine.Shared/Utils/pointers.h>
#include <vector>
#include <functional>

template<class EventDataT>
class EventListener {

public:
	virtual void Process(const EventDataT& ev)=0;

};
template<class EventDataT>
class IObservable
{
public:
	using function_listener = std::function<void(const EventDataT&)>;

protected:
	std::vector<s_ptr<EventListener<EventDataT> > > subscribers;
	std::vector<function_listener> fSubscribers;
public:
	void Subscribe(s_ptr<EventListener<EventDataT> >& listener) 
	{
		subscribers.push_back(listener);
	}
	void Subscribe(const function_listener& f)  {
		fSubscribers.push_back(f);
	}
	
};

template<class EventDataT>
class EventSource : public IObservable<EventDataT>
{
public:
	using Observable = IObservable<EventDataT>;
	

	void EmitEvent(const EventDataT& ev)
	{
		for (auto& sub : this->subscribers)
		{
			sub->Process(ev);
		}
	}

	
};