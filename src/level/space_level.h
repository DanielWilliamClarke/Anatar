#ifndef SPACE_LEVEL_H
#define SPACE_LEVEL_H


#include <SFML/Graphics.hpp>
#include <array>
#include <memory>

#include "util/i_random_number_source.h"

class IRenderer;
class IThreadedWorkload;

typedef std::vector<std::unique_ptr<sf::CircleShape>>::const_iterator StarIter;

class SpaceLevel
{
public:
	SpaceLevel(std::shared_ptr<IThreadedWorkload> threadableWorkload, std::shared_ptr<IRandomNumberSource<int>> randSource, sf::Vector2f viewSize);
	virtual ~SpaceLevel() = default;

	void Update(float worldSpeed, float dt);
	void Draw(std::shared_ptr<IRenderer> renderer) const;

private:

	void UpdateStars(StarIter start, StarIter end, size_t index, float worldSpeed, float dt) const;

private:
	std::shared_ptr<IThreadedWorkload> threadableWorkload;
	std::shared_ptr<IRandomNumberSource<int>> randSource;
	std::vector<std::unique_ptr<sf::CircleShape>> stars;
	int totalStars;
	sf::Vector2f viewSize;
};

#endif //SPACE_LEVEL_H
