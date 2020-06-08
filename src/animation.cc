#include "animation.h"

Animation::Animation(std::shared_ptr<sf::Sprite> sprite, std::shared_ptr<sf::Texture> textureSheet,
	float frameDuration, int startFrameX, int startFrameY, int framesX, int framesY, int width, int height)
	: sprite(sprite), textureSheet(textureSheet),
	frameDuration(frameDuration), done(false),
	width(width), height(height)
{
	this->startRect = sf::IntRect(startFrameX * width, startFrameY * height, width, height);
	this->currentRect = this->startRect;
	this->endRect = sf::IntRect(framesX * width, framesY * height, width, height);
	this->sprite->setTextureRect(this->startRect);
}

Animation::~Animation() 
{}

const bool& Animation::IsDone() const
{
	return this->done;
}

const bool& Animation::Play()
{
	if (clockAnimate.getElapsedTime().asSeconds() >= this->frameDuration)
	{
		NextFrame();
	}

	return this->done;
}

const bool& Animation::Play(float modPercent)
{
	if (modPercent < 0.5f)
	{
		modPercent = 0.5f;
	}
		
	const auto frameLength = this->frameDuration * (1 / modPercent);
	if (this->clockAnimate.getElapsedTime().asSeconds() >= frameLength)
	{
		NextFrame();
	}

	return this->done;
}

void Animation::NextFrame()
{
	this->done = false;
	//Animate
	if (this->currentRect != this->endRect)
	{
		this->currentRect.left += this->width;
	}
	else //Reset
	{
		this->currentRect.left = this->startRect.left;
		this->done = true;
	}

	this->sprite->setTextureRect(this->currentRect);
	this->clockAnimate.restart();
}

void Animation::Reset()
{
	this->clockAnimate.restart();
	this->currentRect = this->startRect;
}