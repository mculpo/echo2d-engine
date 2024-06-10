#include "LoaderLevel.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/CameraFollowComponent.h"
#include "../Components/ProjectileEmmiterComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/TextComponent.h"
#include "../Components/KeyboardControlComponent.h"
#include "EchoGame.h"
#include "../Components/ScriptComponent.h"

LoaderLevel::LoaderLevel()
{
	LOG_INFO("LoaderLevel inicialized!");
}

LoaderLevel::~LoaderLevel()
{
	LOG_INFO("LoaderLevel destroyed!");
}

void LoaderLevel::LoadLevel(
	sol::state& pLua,
	std::unique_ptr<Registry>& pRegister, 
	std::unique_ptr<AssetStore>& pAssetStore, 
	SDL_Renderer* pRenderer,  
	unsigned int pLevel)
{
	sol::load_result script = pLua.load_file("./assets/scripts/Level" + std::to_string(pLevel) + ".lua");

	if (!script.valid()) {
		sol::error err = script;
		std::string message = err.what();
		LOG_ERROR("Error loading the lua script " + message);
		return;
	}

	pLua.script_file("./assets/scripts/Level" + std::to_string(pLevel) + ".lua");

	/////////////////////////////////////////////////////////////
	// Read level assets like textures, fonts, audios
	// TODO update
	/////////////////////////////////////////////////////////////

	sol::table level = pLua["Level"];
	sol::table assets = level["assets"];

	int i = 0;
	while (true) {

		sol::optional<sol::table> hasAsset = assets[i];

		if (hasAsset == sol::nullopt) {
			break;
		}

		sol::table asset = assets[i];
		std::string assetType = asset["type"];
		if (assetType == "texture") {
			pAssetStore->AddTexture(pRenderer, asset["id"], asset["file"]);
		}
		if (assetType == "font") {
			pAssetStore->AddFont(asset["id"], asset["file"], asset["font_size"]);
		}
		i++;
	}

	/////////////////////////////////////////////////////////////
	// Read level tilemap
	// TODO update
	/////////////////////////////////////////////////////////////

	sol::table map = level["tilemap"];
	std::string mapFilePath = map["map_file"];
	std::string mapTextureAssetId = map["texture_asset_id"];

	int mapNumRows		= static_cast<int>(map["num_rows"]);
	int mapNumCols		= static_cast<int>(map["num_cols"]);
	int tileSize		= static_cast<int>(map["tile_size"]);
	double tileScale	= static_cast<int>(map["scale"]);

	/*std::fstream mapFile;
	mapFile.open(mapFilePath);
	for (int y = 0; y < mapNumRows; y++) {
		for (int x = 0; x < mapNumCols; x++) {
			char ch;
			mapFile.get(ch);
			int srcRectY = std::atoi(&ch) * tileSize;
			mapFile.get(ch);
			int srcRectX = std::atoi(&ch) * tileSize;
			mapFile.ignore();

			Entity _mapEntity = pRegister->CreateEntity();
			_mapEntity.AddComponent<TransformComponent>(glm::vec2(x * (tileScale * tileSize), y * (tileScale * tileSize)), glm::vec2(tileScale, tileScale), 0.0);
			_mapEntity.AddComponent<SpriteComponent>(mapTextureAssetId, tileSize, tileSize, 0, false, srcRectX, srcRectY);
		}
	}
	mapFile.close();*/
	EchoGame::mapWidth = mapNumCols * tileSize * static_cast<int>(tileScale);
	EchoGame::mapHeight = mapNumRows * tileSize * static_cast<int>(tileScale);

	/////////////////////////////////////////////////////////////
	// Read level entities
	// TODO update
	/////////////////////////////////////////////////////////////

	sol::table entities = level["entities"];
	i = 0;
	while (true) {
		sol::optional<sol::table> hasEntity = entities[i];
		if (hasEntity == sol::nullopt) {
			break;
		}

		sol::table entity = entities[i];
		Entity _entity = pRegister->CreateEntity();

		//Tag operation
		sol::optional<std::string> tag = entity["tag"];
		
		if (tag != sol::nullopt) {
			_entity.Tag(entity["tag"]);
		}

		sol::optional<std::string> group = entity["group"];
		if (group != sol::nullopt) {
			_entity.Group(entity["group"]);
		}

		//Components operation
		sol::optional<sol::table> hasComponents = entity["components"];
		if (hasComponents != sol::nullopt) {
			sol::optional<sol::table> hasTransform = entity["components"]["transform"];
			if (hasTransform != sol::nullopt) {
				_entity.AddComponent<TransformComponent>(
					glm::vec2(entity["components"]["transform"]["position"]["x"], entity["components"]["transform"]["position"]["y"]),
					glm::vec2(entity["components"]["transform"]["scale"]["x"], entity["components"]["transform"]["scale"]["y"]),
					entity["components"]["transform"]["rotation"].get_or(0)
				);
			}

			sol::optional<sol::table> hasRigidbody = entity["components"]["rigidbody"];
			if (hasRigidbody != sol::nullopt) {
				_entity.AddComponent<RigidBodyComponent>(
					glm::vec2(
						entity["components"]["rigidbody"]["velocity"]["x"].get_or(0),
						entity["components"]["rigidbody"]["velocity"]["y"].get_or(0)
					)
				);
			}

			sol::optional<sol::table> hasSprite = entity["components"]["sprite"];
			if (hasSprite != sol::nullopt) {
				_entity.AddComponent<SpriteComponent>(
					entity["components"]["sprite"]["texture_asset_id"],
					entity["components"]["sprite"]["width"],
					entity["components"]["sprite"]["height"],
					entity["components"]["sprite"]["z_index"].get_or(1),
					entity["components"]["sprite"]["fixed"].get_or(false),
					entity["components"]["sprite"]["src_rect_x"].get_or(0),
					entity["components"]["sprite"]["src_rect_y"].get_or(0)
				);
			}

			sol::optional<sol::table> hasAnimation = entity["components"]["animation"];
			if (hasAnimation != sol::nullopt) {
				_entity.AddComponent<AnimationComponent>(
					entity["components"]["animation"]["num_frames"].get_or(1),
					entity["components"]["animation"]["speed_rate"].get_or(1),
					entity["components"]["animation"]["loop"].get_or(false)
				);
			}

			sol::optional<sol::table> hasBoxCollider = entity["components"]["boxcollider"];
			if (hasBoxCollider != sol::nullopt) {
				_entity.AddComponent<BoxColliderComponent>(
					entity["components"]["boxcollider"]["width"].get_or(0),
					entity["components"]["boxcollider"]["height"].get_or(0),
					glm::vec2(
						entity["components"]["boxcollider"]["offset"]["x"].get_or(0),
						entity["components"]["boxcollider"]["offset"]["y"].get_or(0)
					)
				);
			}

			sol::optional<sol::table> hasHealth = entity["components"]["health"];
			if (hasHealth != sol::nullopt) {
				_entity.AddComponent<HealthComponent>(
					static_cast<int>(entity["components"]["health"]["health_percentage"].get_or(1))
				);
			}

			sol::optional<sol::table> hasProjectileEmmiter = entity["components"]["projectile_emitter"];
			if (hasProjectileEmmiter != sol::nullopt) {
				_entity.AddComponent<ProjectileEmmiterComponent>(
					glm::vec2(
						entity["components"]["projectile_emitter"]["projectile_velocity"]["x"].get_or(0),
						entity["components"]["projectile_emitter"]["projectile_velocity"]["y"].get_or(0)
					),
					entity["components"]["projectile_emitter"]["projectile_duration"].get_or(1) * 1000,
					entity["components"]["projectile_emitter"]["repeat_frequency"].get_or(10) * 1000,
					entity["components"]["projectile_emitter"]["hit_percentage_damage"].get_or(10),
					entity["components"]["projectile_emitter"]["friendly"].get_or(false)
				);
			}

			sol::optional<sol::table> hasKeyboard  = entity["components"]["keyboard_controller"];
			if (hasKeyboard != sol::nullopt) {
				_entity.AddComponent<KeyboardControlComponent>(
					glm::vec2(
						entity["components"]["keyboard_controller"]["velocity"]["x"].get_or(0),
						entity["components"]["keyboard_controller"]["velocity"]["y"].get_or(0)
					)
				);
			}

			sol::optional<sol::table> hasCamera = entity["components"]["camera_follow"];
			if (hasCamera != sol::nullopt) {
				_entity.AddComponent<CameraFollowComponent>();
			}

			sol::optional<sol::table> hasTextTransform = entity["components"]["text_transform"];
			if (hasTextTransform != sol::nullopt) {
				SDL_Color color =
				{
					static_cast<int>(entity["components"]["text_transform"]["color"]["r"]) ,
					static_cast<int>(entity["components"]["text_transform"]["color"]["g"]) ,
					static_cast<int>(entity["components"]["text_transform"]["color"]["b"]) ,
					static_cast<int>(entity["components"]["text_transform"]["color"]["a"])
				};
				_entity.AddComponent<TextComponent>(
					glm::vec2(
						entity["components"]["text_transform"]["position"]["x"].get_or(0),
						entity["components"]["text_transform"]["position"]["y"].get_or(0)
					),
					entity["components"]["text_transform"]["title"],
					entity["components"]["text_transform"]["font_key_id"],
					color,
					entity["components"]["text_transform"]["fixed"].get_or(false)
				);
			}

			sol::optional<sol::table> hasScript = entity["components"]["on_update_script"];
			if (hasScript != sol::nullopt) {
				sol::function _func = entity["components"]["on_update_script"][0];
				_entity.AddComponent<ScriptComponent>(_func);
			}
		}

		i++;
	}
	////TODO: Initialize the GameObjects
	//Entity chopper = pRegister->CreateEntity();
	//chopper.Tag("player");
	//chopper.AddComponent<TransformComponent>(glm::vec2(240.0, 105.0), glm::vec2(1, 1), 0.0);
	//chopper.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));
	//chopper.AddComponent<SpriteComponent>("chopper-texture", 32, 32, 1);
	//chopper.AddComponent<AnimationComponent>(2, 20, true);
	//chopper.AddComponent<BoxColliderComponent>(32, 32);
	//chopper.AddComponent<ProjectileEmmiterComponent>(glm::vec2(500.0, 500.0), 0, 5000, 40, true);
	//chopper.AddComponent<KeyboardControlComponent>(glm::vec2(300, 300));
	//chopper.AddComponent<CameraFollowComponent>();
	//chopper.AddComponent<HealthComponent>(100);

	//Entity radar = pRegister->CreateEntity();
	//radar.AddComponent<TransformComponent>(glm::vec2(EchoGame::windowWidth - 74.0, EchoGame::windowHeight - 74.0), glm::vec2(1, 1), 0.0);
	//radar.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));
	//radar.AddComponent<SpriteComponent>("radar-image", 64, 64, 1, true);
	//radar.AddComponent<AnimationComponent>(8, 3, true);


	//Entity tank = pRegister->CreateEntity();
	//tank.Group("enemies");
	//tank.AddComponent<TransformComponent>(glm::vec2(120.0, 500.0), glm::vec2(1.0, 1.0), 0.0);
	//tank.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));
	//tank.AddComponent<SpriteComponent>("tank-texture", 32, 32, 1);
	//tank.AddComponent<BoxColliderComponent>(32, 32, glm::vec2(0.0, 0.0));
	//tank.AddComponent<ProjectileEmmiterComponent>(glm::vec2(100.0, 0.0), 1000, 3000, 10, false);
	//tank.AddComponent<HealthComponent>(100);

	//Entity tank2 = pRegister->CreateEntity();
	//tank2.Group("enemies");
	//tank2.AddComponent<TransformComponent>(glm::vec2(500.0, 500.0), glm::vec2(1.0, 1.0), 0.0);
	//tank2.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0));
	//tank2.AddComponent<SpriteComponent>("tank-texture", 32, 32, 1);
	//tank2.AddComponent<BoxColliderComponent>(32, 32, glm::vec2(0.0, 0.0));
	//tank2.AddComponent<ProjectileEmmiterComponent>(glm::vec2(0.0, 100.0), 1000, 4000, 10, false);
	//tank2.AddComponent<HealthComponent>(100);

	/*Entity label = pRegister->CreateEntity();
	label.Group("labels");
	label.AddComponent<TextComponent>(glm::vec2(EchoGame::windowWidth / 2, 10), "CHOOPER", "pico8-font-10", SDL_COLOR_GREEN, true);*/
}
