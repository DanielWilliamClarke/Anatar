#ifndef PLAYER_HUD
#define PLAYER_HUD


#include <SFML/Graphics.hpp>

#include "i_player_hud.h"

class PlayerHud : public IPlayerHud
{
public:
	explicit PlayerHud(sf::FloatRect bounds);
	~PlayerHud() override = default;

	virtual void Update(float health, float maxHealth, float shields, float maxShields, float score) override;
	virtual void Draw(const std::shared_ptr<IRenderer>& renderer) const override;

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

#endif // PLAYER_HUD