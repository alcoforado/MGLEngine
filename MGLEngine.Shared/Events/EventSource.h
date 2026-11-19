#pragma once
#include <MGLEngine.Shared/Utils/pointers.h>
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
public:
	using function_listener = std::function<void(const EventDataT&)>;

protected:
	struct Listener {
		s_ptr<EventListener<EventDataT> > eventListener;
		function_listener functional;
		bool isPaused;
		 
	};

	class Subscription {
		Listener* pListener;
		size_t index;
	public:
		void Pause() { pListener->isPaused = true; }
		void Resume() { pListener->isPaused = false; }

	};

	std::deque<Listener> subscribers;
public:
	void Subscribe(s_ptr<EventListener<EventDataT> >& listener) 
	{
		subscribers.push_back(Listener{
			.eventListener = listener,
			.isPaused = false
		});
	}
	void Subscribe(const function_listener& f)  {
		
		
		subscribers.push_back(Listener{
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