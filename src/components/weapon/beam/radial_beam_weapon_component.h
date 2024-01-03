#ifndef RADIAL_BEAM_WEAPON_COMPONENT_H
#define RADIAL_BEAM_WEAPON_COMPONENT_H


#include <SFML/Graphics.hpp>
#include <memory>

#include "components/weapon/i_weapon_component.h"

class IBulletSystem;
class IBulletFactory;
class Beam;

class RadialBeamWeaponComponent
    : public IWeaponComponent,
      public WeaponBulletSystemAccess,
      public WeaponBulletFactoryAccess
{
public:
	RadialBeamWeaponComponent(
        float duration,
        float coolDown,
        float arcAngle,
        float numBeams
    );
	~RadialBeamWeaponComponent() override = default;

    [[nodiscard]] WeaponState getWeaponState() const override;
	void Fire(sf::Vector2f position, BulletConfig& config) override;
	void Cease() override;

private:
	std::vector<std::shared_ptr<Beam>> beams;

	float arcAngle;
	float numBeams;

	sf::Clock clock;
	float accumulator;
	float duration;
	float coolDown;
};

#endif