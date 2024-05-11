#ifndef EVENTBUS_ECHO2D_H
#define EVENTBUS_ECHO2D_H
#include "../Core/Core.h"
#include "../ECS/ECS.h"
#include "../Event/Event.h"

class IEventCallback {
private:
	virtual void Call(Event& e) = 0;
public:
	virtual ~IEventCallback() = default;

	void Execute(Event& e) {
		Call(e);
	}
};

template <typename TOwner, typename TEvent>
class EventCallback : public IEventCallback {
private:
	typedef void(TOwner::* CallbackFunction)(TEvent&);

	TOwner* mOwnerInstance;
	CallbackFunction mCallbackFunction;

	virtual void Call(Event& e) override {
		std::invoke(mCallbackFunction, mOwnerInstance, static_cast<TEvent&>(e));
	}
public:
	EventCallback(TOwner* pOwnerInstance, CallbackFunction pCallbackFunction) {
		this->mOwnerInstance = pOwnerInstance;
		this->mCallbackFunction = pCallbackFunction;
	}
	virtual ~EventCallback() override = default;
};

typedef std::list<std::unique_ptr<IEventCallback>> HandlerList;

class EventBus
{
private:
	std::map<std::type_index, std::unique_ptr<HandlerList>> subscribers;
public:
	EventBus() {
		LOG_INFO("Event constructor called");
	}
	~EventBus() {
		LOG_INFO("Event destructor called");
	}

	void Reset() {
		subscribers.clear();
	}

	template<typename TEvent, typename TOwner>
	void SubscribeToEvent(TOwner* pOwnerInstance, void (TOwner::* callbackFunction)(TEvent&)) {
		//TODO
		if (!subscribers[typeid(TEvent)].get()) {
			subscribers[typeid(TEvent)] = std::make_unique<HandlerList>();
		}
		auto subscriber = std::make_unique<EventCallback<TOwner, TEvent>>(pOwnerInstance, callbackFunction);
		subscribers[typeid(TEvent)]->push_back(std::move(subscriber));
	};
	template<typename TEvent, typename ...TArgs> 
	void InvokeEvent(TArgs&& ...pArgs) {
		//TODO
		auto handlers = subscribers[typeid(TEvent)].get();
		if (handlers) {
			for (auto it = handlers->begin(); it != handlers->end(); it++) {
				auto handler = it->get();
				TEvent event(std::forward<TArgs>(pArgs)...);
				handler->Execute(event);
			}
		}
	};
};

#endif

