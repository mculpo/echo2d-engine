#ifndef ECS_ECHO2D_H
#define ECS_ECHO2D_H
#include "../Core/Core.h"

const unsigned int MAX_COMPONENTS = 64;
/*
* Signature
* 
* We use a bitset( 0 and 1 ) to keep track of which components an entity has,
* and also helps keep track of which entities a system is interested in.
*/
typedef std::bitset<MAX_COMPONENTS> Signature;


/*
* Component
* 
* Used to assign a unique id to a component type
*/
struct IComponent {
protected:
	static int mNextId;
};

template<typename T>
class Component : public IComponent {
public:
	static int GetId() {
		/*
		* The variable "static auto id" inside the function is static local variable. this means that it keeps your value between the calling functions.
		* But is diferent for each T type, that is, for each type there will be a "static id"
		*/
		static auto id = mNextId++;
		return id;
	}
};

/*
* Entity
*/
class Entity {
private:
	int mId;
	
public:
	Entity(int pId){
		mId = pId;
	};
	Entity(const Entity& pEntity) = default;
	~Entity() {};
	int GetId() const;
	void Destroy();
	Entity& operator =(const Entity& other) = default;
	bool operator ==(const Entity& pEntity) const { return mId == pEntity.GetId(); }
	bool operator !=(const Entity& pEntity) const { return mId != pEntity.GetId(); }
	bool operator >(const Entity& pEntity) const { return mId > pEntity.GetId(); }
	bool operator <(const Entity& pEntity) const { return mId < pEntity.GetId(); }
	
	class Registry* mRegistry;
	template<typename TComponent, typename ...TArgs>
	void AddComponent(TArgs&& ...pArgs);

	template<typename TComponent>
	void RemoveComponent();

	template<typename TComponent>
	bool HasComponent();

	template<typename TComponent>
	TComponent& GetComponent();
};

/*
* System
*
* The System processes entities that contain a specific methods
*/
class System {
private:
	Signature mComponentSignature;
	std::vector<Entity> mEntities;
public:
	System() = default;
	~System() = default;

	void AddEntityToSystem(Entity pEntity);
	void RemoveEntityFromSystem(Entity pEntity);
	std::vector<Entity> GetSystemEntities() const;
	const Signature& GetComponentSignature() const;

	template<typename TComponent> void RequireComponent();
};

/*
* Pool
*
* Just a vector (contiguous data) of object of type T
*/
class IPool {
public:
	virtual ~IPool() {};
};

template <typename T>
class Pool : public IPool{
private:
	std::vector<T> mData;
public:
	Pool(int pSize = 100) {
		mData.resize(pSize);
	}
	virtual ~Pool() = default;
	bool IsEmpty() const {
		return mData.empty();
	}

	int GetSize() const {
		return mData.size();
	}

	void Resize(int pValue) {
		mData.resize(pValue);
	}

	void Clear() {
		mData.clear();
	}

	void Add(T pObject) {
		mData.push_back(pObject);
	}

	void Set(int pIndex, T pObject) {
		mData[pIndex] = pObject;
	}

	T& Get(int pIndex) {
		return static_cast<T&> (mData[pIndex]);
	}
	T& operator [] (unsigned int pIndex) {
		return mData[pIndex];
	}
};

/*
* Registry
* 
* The registry manages the creation and destruction of entites, system and components
*/
class Registry {
private:
	int mNumEntities = 0;
	// Vector of component pools
	// Each pool constains all the data for a certain component type
	// [Vector index = component type id] , [Pool index = entity id]
	std::vector<std::shared_ptr<IPool>> mComponentPools;

	// Vector of component signatures 
	// The signatures lets us know which components are turned "on" for an entity
	// [Vector index = entity id]
	std::vector<Signature> mEntityComponentSignatures;

	// Map of active systems [index = system typeid]
	std::unordered_map<std::type_index, std::shared_ptr<System>> mSystems;

	std::set<Entity> mEntitiesToBeAdded;
	std::set<Entity> mEntitiesToBeKilled;

	std::deque<int> mFreeIds;
public:
	Registry();
	~Registry();

	void Update();

	Entity CreateEntity();

	template<typename TComponent, typename ...TArgs>
	void AddComponent(Entity pEntity, TArgs&& ...pArgs);

	template<typename TComponent>
	void RemoveComponent(Entity pEntity);

	template<typename TComponent>
	bool HasComponent(Entity pEntity);

	template<typename TComponent>
	TComponent& GetComponent(Entity pEntity);

	template<typename TSystem, typename ...TArgs>
	void AddSystem(TArgs&& ...pArgs);

	template<typename TSystem>
	void RemoveSystem();

	template<typename TSystem>
	bool HasSystem() const;

	template<typename TSystem>
	TSystem& GetSystem() const;

	void AddEntityToSystem(Entity pEntity);
	void RemoveEntityFromSystem(Entity pEntity);
	void DestroyEntity(Entity pEntity);
};

/*
* Template implementation of Registry
* AddComponent for all Args when necessery
*/
template<typename TComponent, typename ...TArgs>
inline void Registry::AddComponent(Entity pEntity, TArgs && ...pArgs)
{
	unsigned int componentId = Component<TComponent>::GetId();
	const auto entityId = pEntity.GetId();
	// if the component id is greater than the current size of the componentPools, then resize the vector
	if (componentId >= mComponentPools.size()) {
		mComponentPools.resize(componentId + 1, nullptr);
	}

	// If we still dont have a Pool for that component type
	if (!mComponentPools[componentId]) {
		std::shared_ptr<Pool<TComponent>> newComponentPool = std::make_shared<Pool<TComponent>>();
		mComponentPools[componentId] = newComponentPool;
	}

	//Get the pool of component values for that component type
	std::shared_ptr<Pool<TComponent>> componentPool = std::static_pointer_cast<Pool<TComponent>>(mComponentPools[componentId]);

	// if the entity id is greater than current size of the component pool, then resize the pool
	if (entityId >= componentPool->GetSize()) {
		componentPool->Resize(mNumEntities);
	}

	//Create a new Component object of the type T, and foward the various parameters to the construction
	TComponent newComponent(std::forward<TArgs>(pArgs)...);

	//add the new component to the component pool list, using the entity id as index
	componentPool->Set(entityId, newComponent);

	// finally, change the component signature of the entity and set the component id on the bitset to 1
	mEntityComponentSignatures[entityId].set(componentId);

	//LOG_INFO("Component id " + std::to_string(componentId) + " was added to entity id " + std::to_string(entityId));
}

template<typename TComponent>
inline void Registry::RemoveComponent(Entity pEntity)
{
	const auto componentId = Component<TComponent>::GetId();
	const auto entityId = pEntity.GetId();
	mEntityComponentSignatures[entityId].set(componentId, false);
	LOG_INFO("Component id " + std::to_string(componentId) + " was removed to entity id " + std::to_string(entityId));
}

template<typename TComponent>
inline bool Registry::HasComponent(Entity pEntity)
{
	const auto componentId = Component<TComponent>::GetId();
	const auto entityId = pEntity.GetId();
	return mEntityComponentSignatures[entityId].test(componentId);
}

template<typename TComponent>
inline TComponent& Registry::GetComponent(Entity pEntity)
{
	const auto componentId = Component<TComponent>::GetId();
	const auto entityId = pEntity.GetId();
	auto componentPool = std::static_pointer_cast<Pool<TComponent>>(mComponentPools[componentId]);
	return componentPool->Get(entityId);
}

template<typename TSystem, typename ...TArgs>
inline void Registry::AddSystem(TArgs && ...pArgs)
{
	std::shared_ptr<TSystem> newSystem = std::make_shared<TSystem>(std::forward<TArgs>(pArgs)...);
	mSystems.insert(
		std::make_pair(
			std::type_index(typeid(TSystem)), 
			newSystem
		)
	);
}

template<typename TSystem>
inline void Registry::RemoveSystem()
{
	auto system = mSystems.find(std::type_index(typeid(TSystem)));
	mSystems.erase(system);
}

template<typename TSystem>
inline bool Registry::HasSystem() const
{
	return mSystems.find(std::type_index(typeid(TSystem)) != mSystems.end());
}

template<typename TSystem>
inline TSystem& Registry::GetSystem() const
{
	auto system = mSystems.find(std::type_index(typeid(TSystem)));
	return *(std::static_pointer_cast<TSystem>(system->second));
}

/*
* Template implementation of System
*/
template<typename TComponent>
inline void System::RequireComponent()
{
	const auto componentId = Component<TComponent>::GetId();
	mComponentSignature.set(componentId);
}

template<typename TComponent, typename ...TArgs>
inline void Entity::AddComponent(TArgs && ...pArgs)
{
	mRegistry->AddComponent<TComponent>(*this, std::forward<TArgs>(pArgs)...);
}

template<typename TComponent>
inline void Entity::RemoveComponent()
{
	mRegistry->RemoveComponent<TComponent>(*this);
}

template<typename TComponent>
inline bool Entity::HasComponent()
{
	return mRegistry->HasComponent<TComponent>(*this);;
}

template<typename TComponent>
inline TComponent& Entity::GetComponent()
{
	return mRegistry->GetComponent<TComponent>(*this);;
}


#endif // !ECS_ECHO2D_H

