#ifndef ECS_ECHO2D_H
#define ECS_ECHO2D_H
#include "../Core/Core.h"

const unsigned int MAX_COMPONENTS = 32;
/*
* Signature
* 
* We use a bitset( 0 and 1 ) to keep track of which components an entity has,
* and also helps keep track of which entities a system is interested in.
*/
typedef std::bitset<MAX_COMPONENTS> Signature;

struct IComponent {
protected:
	static int mNextId;
};
/*
* Component
* 
* Used to assign a unique id to a component type
*/
template<typename T>
class Component : public IComponent {
	static int GetId() {
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
	Entity(int pId) : mId(pId) {};
	Entity(const Entity& pEntity) = default;
	~Entity() {};
	int GetId() const;
	Entity& operator =(const Entity& other) = default;
	bool operator ==(const Entity& pEntity) const { return mId == pEntity.GetId(); }
	bool operator !=(const Entity& pEntity) const { return mId != pEntity.GetId(); }
	bool operator >(const Entity& pEntity) const { return mId > pEntity.GetId(); }
	bool operator <(const Entity& pEntity) const { return mId < pEntity.GetId(); }
	//...
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

	void AddEntityToSystem(Entity entity);
	void RemoveEntityFromSystem(Entity entity);
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
	std::vector<IPool*> mComponentPools;

	// Vector of component signatures 
	// The signatures lets us know which components are turned "on" for an entity
	// [Vector index = entity id]
	std::vector<Signature> mEntityComponentSignatures;

	// Map of active systems [index = system typeid]
	std::unordered_map<std::type_index, System> mSystems;

	std::set<Entity> entitiesToBeAdded;
	std::set<Entity> entitiesToBeKilled;

public:
	Registry() = default;

	void Update();

	Entity CreateEntity();
	
	void AddEntityToSystem(Entity entity);

	void KillEntity();
};

template<typename TComponent>
inline void System::RequireComponent()
{
	const auto componentId = Component<TComponent>::GetId();
	mComponentSignature.set(componentId);
}


#endif // !ECS_ECHO2D_H
