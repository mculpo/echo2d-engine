#include "ECS.h"

int IComponent::mNextId = 0;

int Entity::GetId() const {
	return mId;
}

void Entity::Destroy()
{
	mRegistry->DestroyEntity(*this);
}

void Entity::Tag(const std::string& pTag)
{
	mRegistry->TagEntity(*this, pTag);
}

bool Entity::HasTag(const std::string& pTag) const
{
	return mRegistry->EntityHasTag(*this, pTag);
}

void Entity::Group(const std::string& pGroup)
{
	mRegistry->GroupEntity(*this, pGroup);
}

bool Entity::BelongsToGroup(const std::string& pGroup) const
{
	return mRegistry->EntityBelongsToGroup(*this, pGroup);
}

void System::AddEntityToSystem(Entity pEntity)
{
	mEntities.push_back(pEntity);
}

void System::RemoveEntityFromSystem(Entity pEntity)
{
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

void Registry::TagEntity(Entity pEntity, const std::string& pTag)
{
	mEntityPerTag.emplace(pTag, pEntity);
	mTagPerEntity.emplace(pEntity.GetId(), pTag);
}

bool Registry::EntityHasTag(Entity pEntity, const std::string& pTag) const
{
	if (mTagPerEntity.find(pEntity.GetId()) == mTagPerEntity.end()) {
		return false;
	}
	return mEntityPerTag.find(pTag)->second == pEntity;
}

Entity Registry::GetEntityByTag(const std::string& pTag) const
{
	return mEntityPerTag.at(pTag);
}

void Registry::RemoveEntityTag(Entity pEntity)
{
	//auto
	std::unordered_map<int, std::string>::iterator taggedEntity = mTagPerEntity.find(pEntity.GetId());
	if (taggedEntity != mTagPerEntity.end()) {
		std::string tag = taggedEntity->second;
		mEntityPerTag.erase(tag);
		mTagPerEntity.erase(taggedEntity);
	}
}

void Registry::GroupEntity(Entity pEntity, const std::string& pGroup)
{
	mEntitiesPerGroup.emplace(pGroup, std::set<Entity>());
	mEntitiesPerGroup[pGroup].emplace(pEntity);
	mGroupPerEntities.emplace(pEntity.GetId(), pGroup);
}

bool Registry::EntityBelongsToGroup(Entity pEntity, const std::string& pGroup) const
{
	if (mEntitiesPerGroup.find(pGroup) == mEntitiesPerGroup.end()) {
		return false;
	}
	auto groupEntities = mEntitiesPerGroup.at(pGroup);
	return groupEntities.find(pEntity.GetId()) != groupEntities.end();
}

std::vector<Entity> Registry::GetEntitiesByGroup(const std::string& pGroup) const
{
	auto& groupEntities = mEntitiesPerGroup.at(pGroup);
	return std::vector<Entity>(groupEntities.begin(), groupEntities.end());
}

void Registry::RemoveEntityGroup(Entity pEntity)
{
	auto groupedEntity = mGroupPerEntities.find(pEntity.GetId());
	if (groupedEntity != mGroupPerEntities.end()) {
		auto group = mEntitiesPerGroup.find(groupedEntity->second);
		if (group != mEntitiesPerGroup.end()) {
			auto entityInGroup = group->second.find(pEntity);
			if (entityInGroup != group->second.end()) {
				group->second.erase(entityInGroup);
			}
		}
		mGroupPerEntities.erase(groupedEntity);
	}
}

int Registry::GetAmountOfObjects() const
{
	return mNumEntities;
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

		for (auto pool : mComponentPools) {
			if (pool) {
				pool->RemoveEntityFromPool(entity.GetId());
			}
		}

		mFreeIds.push_back(entity.GetId());

		RemoveEntityTag(entity);
		RemoveEntityGroup(entity);
	}
	mEntitiesToBeKilled.clear();

}
