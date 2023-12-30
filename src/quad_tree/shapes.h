#ifndef SHAPES_H
#define SHAPES_H


#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>

template<typename P>
struct Point {
	sf::Vector2f position;
	std::string tag;
	std::shared_ptr<P> payload;

	Point(
		sf::Vector2f position,
		std::string tag,
		std::shared_ptr<P> payload)
		: position(position), tag(tag), payload(payload)
	{}
};

class RectangleQuery;
class ShapeQuery
{
public:
	ShapeQuery() = default;
 	virtual ~ShapeQuery() = default;
	virtual bool Intersects(sf::FloatRect range) const = 0;
};

class RectangleQuery : public ShapeQuery
{
public:
	RectangleQuery(sf::FloatRect rec);
	virtual ~RectangleQuery() = default;

	virtual bool Intersects(sf::FloatRect range) const override;
	sf::FloatRect Get() const;

private:
	sf::FloatRect rect;
};

class IRayCaster;
class RayQuery : public ShapeQuery
{
public:
	RayQuery(std::shared_ptr<IRayCaster> rayCaster, sf::Vector2f origin, sf::Vector2f direction);
	virtual ~RayQuery() = default;

	virtual bool Intersects(sf::FloatRect range) const override;

private:
	std::shared_ptr<IRayCaster> rayCaster;
	sf::Vector2f origin;
	sf::Vector2f direction;
};

#endif // SHAPES_H