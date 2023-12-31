#include <SFML/Graphics.hpp>

#include "animation_component.h"
#include "animation.h"

AnimationComponent::AnimationComponent()
	: lastAnimation(nullptr), priorityAnimation(nullptr)
{}

void AnimationComponent::SetAssets(std::shared_ptr<sf::Sprite> sprite, std::shared_ptr<sf::Texture> textureSheet) {
	this->sprite = sprite;
	this->textureSheet = textureSheet;
	this->sprite->setTexture(*textureSheet);
}

void AnimationComponent::AddAnimation(int key, float frameDuration,
	int startFrameX, int startFrameY, int framesX, int framesY, int width, int height)
{
	this->animations[key] = std::make_shared<Animation>(this->sprite, this->textureSheet,
		frameDuration, startFrameX, startFrameY, framesX, framesY, width, height);
}

bool AnimationComponent::IsDone(int key)
{
	return this->animations[key]->IsDone();
}

bool AnimationComponent::Play(int key, bool loop, bool priority)
{
	if (this->priorityAnimation) //If there is a priority animation
	{
		if (this->priorityAnimation == this->animations[key])
		{
			if (this->lastAnimation != this->animations[key])
			{
				if (this->lastAnimation == nullptr)
					this->lastAnimation = this->animations[key];
				else
				{
					this->lastAnimation->Reset();
					this->lastAnimation = this->animations[key];
				}
			}

			//If the priority animation is done, remove it
			if (this->animations[key]->Play(loop))
			{
				this->priorityAnimation = nullptr;
			}
		}
	}
	else //Play animation of no other priority animation is set
	{
		//If this is a priority animation, set it.
		if (priority)
		{
			this->priorityAnimation = this->animations[key];
		}

 		if (this->lastAnimation != this->animations[key])
		{
			if (this->lastAnimation == nullptr)
				this->lastAnimation = this->animations[key];
			else
			{
				this->lastAnimation->Reset();
				this->lastAnimation = this->animations[key];
			}
		}

		this->animations[key]->Play(loop);
	}

	return this->animations[key]->IsDone();
}

bool AnimationComponent::Play(int key, float modifier, float modifier_max, bool loop, bool priority)
{
	if (this->priorityAnimation) //If there is a priority animation
	{
		if (this->priorityAnimation == this->animations[key])
		{
			if (this->lastAnimation != this->animations[key])
			{
				if (this->lastAnimation == NULL)
					this->lastAnimation = this->animations[key];
				else
				{
					this->lastAnimation->Reset();
					this->lastAnimation = this->animations[key];
				}
			}

			//If the priority animation is done, remove it
			if (this->animations[key]->Play(abs(modifier / modifier_max), loop))
			{
				this->priorityAnimation = NULL;
			}
		}
	}
	else //Play animation of no other priority animation is set
	{
		//If this is a priority animation, set it.
		if (priority)
		{
			this->priorityAnimation = this->animations[key];
		}

		if (this->lastAnimation != this->animations[key])
		{
			if (this->lastAnimation == NULL)
				this->lastAnimation = this->animations[key];
			else
			{
				this->lastAnimation->Reset();
				this->lastAnimation = this->animations[key];
			}
		}

		this->animations[key]->Play(abs(modifier / modifier_max), loop);
	}

	return this->animations[key]->IsDone();
}