#include "play_state_builder.h"

#include <algorithm>

#include "util/texture_atlas.h"
#include "util/threaded_workload.h"
#include "util/random_number_mersenne_source.cc"

#include "level/space_level.h"
#include "bullet/types/debris_factory.h"
#include "components/weapon/burst/random_shot_weapon_component.h"
#include "player/player_entity_builder.h"
#include "components/movement/player_movement_component.h"
#include "ui/player_hud.h"
#include "components/attributes/player_attribute_component.h"
#include "components/collision_detection/collision_detection_component.h"
#include "bullet/types/projectile_factory.h"
#include "bullet/types/homing_projectile_factory.h"
#include "bullet/types/beam_factory.h"
#include "enemy/enemy_type_factory.h"
#include "enemy/enemy_system.h"
#include "components/weapon/single/single_shot_weapon_component_factory.h"
#include "components/weapon/burst/burst_shot_weapon_component_factory.h"
#include "components/weapon/beam/radial_beam_weapon_component_factory.h"
#include "bullet/bullet_system.h"
#include "util/ray_caster.h"
#include "player/player_input.h"

PlayStateBuilder::PlayStateBuilder(sf::FloatRect bounds, std::shared_ptr<ITextureAtlas> textureAtlas)
  	: bounds(bounds), textureAtlas(textureAtlas)
{
}

std::shared_ptr<SpaceLevel> PlayStateBuilder::BuildLevel() const
{
	auto seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
	auto randGenerator = std::make_shared<RandomNumberMersenneSource<int>>(seed);
	return std::make_shared<SpaceLevel>(std::make_shared<ThreadedWorkload>(), randGenerator, sf::Vector2f(bounds.width, bounds.height));
}

std::shared_ptr<IBulletSystem> PlayStateBuilder::BuildBulletSystem() const
{
	return  std::make_shared<BulletSystem>(bounds);
}

std::shared_ptr<IWeaponComponent> PlayStateBuilder::BuildDebrisSystem(std::shared_ptr<IBulletSystem> bulletSystem) const {
	auto factory = std::make_shared<DebrisFactory>();
	auto seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
	auto randGenerator = std::make_shared<RandomNumberMersenneSource<int>>(seed);
	return std::make_shared<RandomShotWeaponComponent>(bulletSystem, factory, randGenerator, WeaponSlot::ONE, 5.0f);
}

std::shared_ptr<IPlayerHud> PlayStateBuilder::BuildPlayerHud() const
{
	return std::make_shared<PlayerHud>(this->bounds);
}

std::shared_ptr<PlayerInput> PlayStateBuilder::BuildPlayerInput() const
{
	return std::make_shared<PlayerInput>();
}

std::shared_ptr<Player> PlayStateBuilder::BuildPlayer(std::shared_ptr<IBulletSystem> bulletSystem, std::shared_ptr<IWeaponComponent> debrisGenerator, std::shared_ptr<IPlayerHud> hud, float worldSpeed) const {

	auto playerBuilder = std::make_shared<PlayerEntityBuilder>(this->textureAtlas, bulletSystem, this->bounds);
	auto movementComponent = std::make_shared<PlayerMovementComponent>(this->bounds, worldSpeed);

	auto healthDamageColor = sf::Color(248, 99, 0, 255);
	auto sheildDamageColor = sf::Color(75, 108, 183, 255);
	auto attenuation = 50.0f;

	auto mediators = BulletMediators()
		.SetBulletResolver([](bool kill, float damage) {})
		.SetPositionSampler([]() -> sf::Vector2f { return {}; });

	auto playerDamageEffects = std::make_shared<DamageEffects>(
		debrisGenerator,
		std::make_shared<BulletConfig>(
			mediators.SetShapeBuilder([=]() -> std::shared_ptr<sf::Shape> { return std::make_shared<sf::CircleShape>(2.0f, 3); }),
			"debris", healthDamageColor, attenuation / 2, 0.0f, 20.0f, AFFINITY::RIGHT, false, 0.0f, 7.0f),
		std::make_shared<BulletConfig>(
			mediators.SetShapeBuilder([=]() -> std::shared_ptr<sf::Shape> { return std::make_shared<sf::CircleShape>(0.0f, 3); }),
			"debris", healthDamageColor, attenuation, 0.0f, 50.0f, AFFINITY::RIGHT, false, 0.0f, 0.3f),
		std::make_shared<BulletConfig>(
			mediators.SetShapeBuilder([=]() -> std::shared_ptr<sf::Shape> { return std::make_shared<sf::CircleShape>(0.0f, 3); }),
			"debris", sheildDamageColor, attenuation, 0.0f, 50.0f, AFFINITY::RIGHT, false, 0.0f, 0.3f));

	auto attributeComponent = std::make_shared<PlayerAttributeComponent>(hud, playerDamageEffects, PlayerAttributeConfig(100.0f, 50.0f, 10.0f, 3.0f));

	auto rayCaster = std::make_shared<RayCaster>();
	auto collectionDetectionComponent = std::make_shared<CollisionDetectionComponent>(rayCaster);

	return std::make_shared<Player>(playerBuilder->Build(), movementComponent, attributeComponent, collectionDetectionComponent);
} 

std::shared_ptr<EnemySystem> PlayStateBuilder::BuildEnemySystem(std::shared_ptr<IBulletSystem> bulletSystem, std::shared_ptr<IWeaponComponent> debrisGenerator, float worldSpeed) const
{
	auto projectileFactory = std::make_shared<ProjectileFactory>();
	auto homingProjectileFactory = std::make_shared<HomingProjectileFactory>();
	auto beamFactory = std::make_shared<BeamFactory>(std::make_shared<RayCaster>(), this->bounds, 0.1f);

	auto healthDamageColor = sf::Color(248, 99, 0, 255);
	auto attenuation = 50.0f;

	auto mediators = BulletMediators()
		.SetBulletResolver([](bool kill, float damage) {})
		.SetPositionSampler([]() -> sf::Vector2f { return {}; });

	auto enemyDamageEffects = std::make_shared<DamageEffects>(
		debrisGenerator,
		std::make_shared<BulletConfig>(
			mediators.SetShapeBuilder([=]() -> std::shared_ptr<sf::Shape> { return std::make_shared<sf::CircleShape>(2.0f, 3); }),
			"debris", healthDamageColor, attenuation / 2, 0.0f, 20.0f, AFFINITY::LEFT, false, 0.0f, 0.7f),
		std::make_shared<BulletConfig>(
			mediators.SetShapeBuilder([=]() -> std::shared_ptr<sf::Shape> { return std::make_shared<sf::CircleShape>(0.0f, 3); }),
			"debris", healthDamageColor, attenuation, 0.0f, 50.0f, AFFINITY::LEFT, false, 0.0f, 0.3f),
		nullptr);

	return std::make_shared<EnemySystem>()
		->AddFactory(1.0f, std::make_shared<EnemyTypeFactory>(
			EnemyConfig(EnemyTypeFactory::BuildOribitalEnemy,
				EnemyMotionConfig(bounds, worldSpeed, 200.0f),
				EnemyAnimationConfig(this->textureAtlas->GetTexture("enemy1"), 6, 0.1f, 1.0f),
				EnemyWeaponConfig(std::make_shared<SingleShotWeaponComponentFactory>(projectileFactory), bulletSystem, 3.0f),
				EnemyAttributeConfig(enemyDamageEffects, 20.0f, 0.0f))))

		->AddFactory(2.0f, std::make_shared<EnemyTypeFactory>(
			EnemyConfig(EnemyTypeFactory::BuildLinearEnemy,
				EnemyMotionConfig(bounds, worldSpeed, 300.0f),
				EnemyAnimationConfig(this->textureAtlas->GetTexture("enemy2"), 14, 0.1f, 1.0f),
				EnemyWeaponConfig(std::make_shared<SingleShotWeaponComponentFactory>(homingProjectileFactory), bulletSystem, 3.0f),
				EnemyAttributeConfig(enemyDamageEffects, 40.0f, 0.0f))))

		->AddFactory(4.0f, std::make_shared<EnemyTypeFactory>(
			EnemyConfig(EnemyTypeFactory::BuildLinearEnemy,
				EnemyMotionConfig(bounds, worldSpeed, 75.0f),
				EnemyAnimationConfig(this->textureAtlas->GetTexture("enemy3"), 9, 0.1f, 1.0f),
				EnemyWeaponConfig(std::make_shared<BurstShotWeaponComponentFactory>(projectileFactory, 7.0f, 45.0f), bulletSystem, 4.0f),
				EnemyAttributeConfig(enemyDamageEffects, 60.0f, 0.0f))))

		->AddFactory(6.0f, std::make_shared<EnemyTypeFactory>(
			EnemyConfig(EnemyTypeFactory::BuildLinearEnemy,
				EnemyMotionConfig(bounds, worldSpeed, 100.0f),
				EnemyAnimationConfig(this->textureAtlas->GetTexture("enemy4"), 4, 0.1f, 1.0f),
				EnemyWeaponConfig(std::make_shared<BurstShotWeaponComponentFactory>(projectileFactory, 8.0f, 360.0f), bulletSystem, 4.0f),
				EnemyAttributeConfig(enemyDamageEffects, 30.0f, 0.0f))))

		->AddFactory(15.0f, std::make_shared<EnemyTypeFactory>(
			EnemyConfig(EnemyTypeFactory::BuildLinearEnemy,
				EnemyMotionConfig(bounds, worldSpeed, 75.0f),
				EnemyAnimationConfig(this->textureAtlas->GetTexture("boss1"), 12, 0.5f, 2.0f),
				EnemyWeaponConfig(std::make_shared<RadialBeamWeaponComponentFactory>(beamFactory, 0.5f, 10.0f, 3.0f), bulletSystem, 10.0f),
				EnemyAttributeConfig(enemyDamageEffects, 150.0f, 0.0f))));
}

CollisionQuadTree PlayStateBuilder::BuildQuadTree() const
{
	return std::make_shared<QuadTree<Collision, CollisionMediators>>(bounds, 4);
}