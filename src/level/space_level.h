#ifndef SPACE_LEVEL_H
#define SPACE_LEVEL_H
#pragma once

#include <SFML/Graphics.hpp>
#include <array>

#include "../util/i_random_number_source.h"

class SpaceLevel
{
public:
	SpaceLevel(std::shared_ptr<IRandomNumberSource<int>> randSource, sf::Vector2f viewSize);
	virtual ~SpaceLevel() = default;

	void Update(float worldSpeed, float dt);
	void Draw(sf::RenderTarget& target, sf::Sprite& glowSprite, sf::Shader& shader) const;

private:
	std::shared_ptr<IRandomNumberSource<int>> randSource;
	std::array<sf::CircleShape, 750> stars;
	sf::Vector2f viewSize;
};

#endif //SPACE_LEVEL_H
