#include "EventManager.h"

void EventManager::AddObserver(const id_t& id, Observer* observer, EventHandler eventHandler)
{
	Dispatcher dispatcher;
	dispatcher.observer = observer;
	dispatcher.eventHandler = eventHandler;

	_dispatchers[id].push_back(dispatcher);
}

void EventManager::RemoveObserver(Observer* observer)
{
	for (auto& element : _dispatchers)
	{
		auto dispatchers = element.second;
		std::erase_if(dispatchers/*the element*/, [observer/*pass in the parameters*/](auto& dispatcher) {return dispatcher.observer==observer; });
	}
}

void EventManager::Notify(const Event& event)
{
	auto iter = _dispatchers.find(event.id);
	if (iter != _dispatchers.end())
	{
		auto dispatchers = iter->second; //get list of dispatchers
		for (auto& dispatcher : dispatchers)
		{
			dispatcher.eventHandler(event);
		}
	}
}
