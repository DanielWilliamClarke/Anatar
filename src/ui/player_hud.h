#ifndef PLAYER_HUD
#define PLAYER_HUD

#include <SFML/Graphics.hpp>

#include "i_player_hud.h"
#include "entity/entity_update.h"

struct WeaponTriggerState;
struct WeaponState;

struct PlayerAttributeUpdate
{
    float health;
    float maxHealth;
    float shields;
    float maxShields;
    float score;
};

class PlayerHud : public IPlayerHud
{
public:
	explicit PlayerHud(sf::FloatRect bounds);
	~PlayerHud() override = default;

	void Update(PlayerAttributeUpdate& attributeUpdate) override;
	void Update(WeaponTriggerState& triggerState, WeaponState& weaponState) override;
	void Draw(const std::shared_ptr<IRenderer>& renderer) const override;

private:
	static sf::Color BlendColor(const sf::Color& start, const sf::Color& end, float percentage);

	sf::FloatRect bounds;
	float margin;

	sf::Font font;
	sf::Text scoreText;
	sf::Text playerText;

	sf::RectangleShape healthBar;
	sf::RectangleShape shieldBar;
};

#endif