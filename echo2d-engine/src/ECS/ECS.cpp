#include "ECS.h"

int IComponent::mNextId = 0;

int Entity::GetId() const {
	return mId;
}

void Entity::Destroy()
{
	mRegistry->DestroyEntity(*this);
}

void System::AddEntityToSystem(Entity pEntity)
{
	mEntities.push_back(pEntity);
}

void System::RemoveEntityFromSystem(Entity pEntity)
{
	/*for (auto it = mEntities.begin(); it != mEntities.end(); ++it) {
		if (it->GetId() == entity.GetId()) {
			mEntities.erase(it);
			break;
		}
	}*/
	mEntities.erase(
		std::remove_if(
			mEntities.begin(),
			mEntities.end(),
			[&pEntity](Entity other) {
				return pEntity == other;
			}
		),
		mEntities.end());
}

std::vector<Entity> System::GetSystemEntities() const
{
	return mEntities;
}

const Signature& System::GetComponentSignature() const
{
	return mComponentSignature;
}

Entity Registry::CreateEntity()
{
	unsigned int entityId;
	
	if (mFreeIds.empty()) {
		entityId = mNumEntities++;
		if (entityId >= mEntityComponentSignatures.size()) {
			mEntityComponentSignatures.resize(entityId + 1);
		}
	}
	else {
		entityId = mFreeIds.front();
		mFreeIds.pop_front();
	}

	Entity entity(entityId);
	entity.mRegistry = this;
	mEntitiesToBeAdded.insert(entity);
	
	return entity;
}

void Registry::AddEntityToSystem(Entity pEntity)
{
	const auto entityId = pEntity.GetId();
	const auto entityComponentSignaure = mEntityComponentSignatures[entityId];
	// Loop all the Systems
	for (auto& system : mSystems) {
		const auto& systemComponentSignature = system.second->GetComponentSignature();
		if ((entityComponentSignaure & systemComponentSignature) == systemComponentSignature) {
			system.second->AddEntityToSystem(pEntity);
		}
	}
}

void Registry::RemoveEntityFromSystem(Entity pEntity)
{
	for (auto system : mSystems) {
		system.second->RemoveEntityFromSystem(pEntity);
	}
}

void Registry::DestroyEntity(Entity pEntity)
{
	mEntitiesToBeKilled.insert(pEntity);
}

Registry::Registry()
{
	LOG_INFO("Registry created!");
}
Registry::~Registry()
{
	LOG_INFO("Registry deleted!");
}

void Registry::Update() {
	for (auto entity : mEntitiesToBeAdded) {
		AddEntityToSystem(entity);
	}
	mEntitiesToBeAdded.clear();
	for (auto entity : mEntitiesToBeKilled) {
		RemoveEntityFromSystem(entity);
		mEntityComponentSignatures[entity.GetId()].reset();
		mFreeIds.push_back(entity.GetId());
	}

	mEntitiesToBeKilled.clear();

}
