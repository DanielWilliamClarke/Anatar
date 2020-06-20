#ifndef ANIMATION_H
#define ANIMATION_H

#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
public:

	Animation(std::shared_ptr<sf::Sprite> sprite, std::shared_ptr<sf::Texture> textureSheet,
		float frameDuration, int startFrameX, int startFrameY, int framesX, int framesY, int width, int height);

	virtual ~Animation() = default;

	const bool& IsDone() const;
	const bool& Play(const bool loop = true);
	const bool& Play(float modPercent, const bool loop = true);
	void Reset();

private:
	void NextFrame(const bool loop);

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

#endif //ANIMATION_H