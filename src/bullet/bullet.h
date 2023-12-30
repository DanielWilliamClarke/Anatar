#ifndef BULLET_H
#define BULLET_H


#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>
#include <list>
#include <memory>

struct Collision;
struct CollisionMediators;

class IRenderer;

template<typename C, typename P>
class QuadTree;

enum class AFFINITY :int { LEFT = -1, RIGHT = 1 };

struct BulletMediators {
	std::function<void(bool, float)> resolver;
	std::function<sf::Vector2f(void)> positionSampler;
	std::function<std::shared_ptr<sf::Shape>(void)> shapeBuilder;

	BulletMediators Inject(std::function<void(bool, float)> r) {
		this->resolver = r;
		return *this;
	}

	BulletMediators Inject(std::function<sf::Vector2f(void)> p) {
		this->positionSampler = p;
		return *this;
	}

	BulletMediators Inject(std::function<std::shared_ptr<sf::Shape>(void)> s) {
		this->shapeBuilder = s;
		return *this;
	}
};

struct BulletConfig
{
	BulletMediators mediators;
	std::string tag;

	sf::Color color;
	float glowAttenuation;

	float rotation;
	float speed;
	AFFINITY affinity;

	bool penetrating;
	float damage;
	float lifeTime;

	BulletConfig(
		BulletMediators mediators,
		std::string tag,
		sf::Color color, 
		float glowAttenuation,
		float rotation, 
		float speed, 
		AFFINITY affinity,
		bool penetrating, 
		float damage, 
		float lifeTime = 20.0f)
		: mediators(mediators),
		tag(tag),
		color(color),
		glowAttenuation(glowAttenuation),
		speed(speed),
		affinity(affinity), 
		rotation(rotation),
		penetrating(penetrating),
		damage(damage), 
		lifeTime(lifeTime)
	{}
};

struct BulletTrajectory
{
	sf::Vector2f position;
	sf::Vector2f velocity;
	float speed;

	BulletTrajectory(sf::Vector2f position, sf::Vector2f velocity, float speed)
		: position(position), velocity(velocity), speed(speed)
	{}
};

class Bullet : public std::enable_shared_from_this<Bullet>
{
public:
	Bullet(BulletTrajectory& trajectory, BulletConfig& config);
	virtual ~Bullet() = default;

	virtual void Update(float dt, float worldSpeed) = 0;
	virtual void Draw(std::shared_ptr<IRenderer> renderer, float interp) = 0;
	virtual std::vector<std::shared_ptr<Collision>> DetectCollisions(const std::shared_ptr<QuadTree<Collision, CollisionMediators>>& quadTree) = 0;

	bool isSpent() const;
	sf::Vector2f GetPosition() const;
	sf::Vector2f GetVelocity() const;
	float GetDamage() const;
	std::string GetTag() const;
	std::function<void(bool, float)> GetCollisionResolver() const;


protected:
	BulletConfig config;
	sf::Vector2f position;
	sf::Vector2f lastPosition;
	sf::Vector2f velocity;
	float speed;
	bool spent; // used in hit detection

	float accumulator;
	float minFadeout;
	float maxFadeout;
};

#endif // BULLET_H
