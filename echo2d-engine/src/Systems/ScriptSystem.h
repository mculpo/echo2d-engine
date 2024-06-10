#ifndef SCRIPTSYSTEM_H
#define SCRIPTSYSTEM_H

#include "../Core/Core.h"
#include "../Components/ScriptComponent.h"

std::tuple<double, double> GetPositionEntity(Entity pEntity) {
	if (pEntity.HasComponent<TransformComponent>()) {
		auto& transform = pEntity.GetComponent<TransformComponent>();
		return std::make_tuple(transform.position.x, transform.position.y);
	}
	else {
		LOG_WARN("Trying to get the position of an entity that has no TransformComponent");
	}
	return std::make_tuple(0,0);
}

std::tuple<double, double> GetVelocityEntity(Entity pEntity) {
	if (pEntity.HasComponent<RigidBodyComponent>()) {
		auto& rigidbody = pEntity.GetComponent<RigidBodyComponent>();
		return std::make_tuple(rigidbody.velocity.x, rigidbody.velocity.y);
	}
	else {
		LOG_WARN("Trying to get the velocity of an entity that has no RigidBodyComponent");
	}
	return std::make_tuple(0, 0);
}


void SetEntityPosition(Entity pEntity, double pX, double pY) {
	if (pEntity.HasComponent<TransformComponent>()) {
		auto& transform = pEntity.GetComponent<TransformComponent>();
		transform.position.x = pX;
		transform.position.y = pY;
	}
	else {
		LOG_WARN("Trying to set the position of an entity that has no TransformComponent");
	}
}
void SetEntityRotation(Entity pEntity, double pRotate) {
	if (pEntity.HasComponent<TransformComponent>()) {
		auto& transform = pEntity.GetComponent<TransformComponent>();
		transform.rotation = pRotate;
	}
	else {
		LOG_WARN("Trying to set the rotation of an entity that has no TransformComponent");
	}
	
}
void SetEntityVelocity(Entity pEntity, double pX, double pY) {
	if (pEntity.HasComponent<RigidBodyComponent>()) {
		auto& rigidbody = pEntity.GetComponent<RigidBodyComponent>();
		rigidbody.velocity.x = pX;
		rigidbody.velocity.y = pY;
	}
	else {
		LOG_WARN("Trying to set the velocity of an entity that has no RigidBodyComponent");
	}
}

void SetProjectileVelocity(Entity pEntity, double pX, double pY) {
	if (pEntity.HasComponent<ProjectileEmmiterComponent>()) {
		auto& projectile = pEntity.GetComponent<ProjectileEmmiterComponent>();
		projectile.projectileVelocity.x = pX;
		projectile.projectileVelocity.y = pY;
	}
	else {
		LOG_WARN("Trying to set the velocity of an entity that has no ProjectileEmmiterComponent");
	}
}

class ScriptSystem : public System {
public:
	ScriptSystem() {
		RequireComponent<ScriptComponent>();
	}
	
	void CreateLuaBindings(sol::state& pLua) {
		pLua.new_usertype<Entity>(
			"entity", 
			"get_id", &Entity::GetId, 
			"destroy", &Entity::Destroy, 
			"has_tag", &Entity::HasTag,
			"belongs_to_group", &Entity::BelongsToGroup
		);

		pLua.set_function("set_position", SetEntityPosition);
		pLua.set_function("set_velocity", SetEntityVelocity);
		pLua.set_function("set_rotation", SetEntityRotation);
		pLua.set_function("set_projectile_velocity", SetProjectileVelocity);
		pLua.set_function("get_position", GetPositionEntity);
		pLua.set_function("get_velocity", GetVelocityEntity);
	}

	void Update() {
		auto _time = Time::GetInstance();
		for (auto entity : GetSystemEntities()) {
			const auto script = entity.GetComponent<ScriptComponent>();
			script.func(entity, _time.DeltaTime(), _time.ElapsedTime());
		}
	}
};

#endif // !SCRIPTSYSTEM_H
