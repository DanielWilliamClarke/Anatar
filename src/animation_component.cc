#include "animation_component.h"
#include "animation.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet)
	:sprite(sprite), textureSheet(textureSheet), lastAnimation(NULL), priorityAnimation(NULL)
{}

AnimationComponent::~AnimationComponent()
{}

//Accessors
const bool& AnimationComponent::IsDone(const int key)
{
	return this->animations[key]->IsDone();
}

//Functions
void AnimationComponent::AddAnimation(const int key,
	float frameDuration,
	int startFrameX, int startFrameY, int framesX, int framesY, int width, int height)
{
	this->animations[key] = std::make_shared<Animation>(
		this->sprite, this->textureSheet,
		frameDuration,
		startFrameX, startFrameY, framesX, framesY, width, height);
}

const bool& AnimationComponent::Play(const int key, const bool priority)
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
			if (this->animations[key]->Play())
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

		this->animations[key]->Play();
	}

	return this->animations[key]->IsDone();
}

const bool& AnimationComponent::Play(const int key, const float& modifier, const float& modifier_max, const bool priority)
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
			if (this->animations[key]->Play(abs(modifier / modifier_max)))
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

		this->animations[key]->Play(abs(modifier / modifier_max));
	}

	return this->animations[key]->IsDone();
}