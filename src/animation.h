#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
public:

	Animation(std::shared_ptr<sf::Sprite> sprite, std::shared_ptr<sf::Texture> textureSheet,
		float frameDuration, int startFrameX, int startFrameY, int framesX, int framesY, int width, int height);

	virtual ~Animation();

	const bool& IsDone() const;
	const bool& Play();
	const bool& Play(float modPercent);
	void Reset();

private:
	void NextFrame();

	//Variables
	std::shared_ptr<sf::Sprite> sprite;
	std::shared_ptr<sf::Texture> textureSheet;

	int width;
	int height;
	sf::IntRect startRect;
	sf::IntRect currentRect;
	sf::IntRect endRect;

	float frameDuration;
	sf::Clock clockAnimate;
	bool done;
};
