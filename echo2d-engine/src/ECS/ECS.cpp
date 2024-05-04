#include "ECS.h"

int Entity::GetId() const {
	return mId;
}

void System::AddEntityToSystem(Entity entity)
{
	mEntities.push_back(entity);
}

void System::RemoveEntityFromSystem(Entity entity)
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
			[&entity](Entity other) {
				return entity == other;
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
	int entityId = mNumEntities++;
	
	Entity entity(entityId);
	entitiesToBeAdded.insert(entity);
	
	LOG_INFO("Entity created with id" + std::to_string(entityId));
	return entity;
}

void Registry::Update() {

}
