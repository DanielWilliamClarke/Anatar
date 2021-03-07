#ifndef SHAPES_H
#define SHAPES_H
#pragma once

#include <SFML/Graphics.hpp>

template <typename T>
struct Point {
	sf::Vector2f point;
	T data;

	Point(sf::Vector2f point, T data)
		: point(point), data(data)
	{}
};

class RectangleQuery;
class ShapeQuery
{
public:
	ShapeQuery() = default;
 	virtual ~ShapeQuery() = default;
	virtual bool Intersects(sf::FloatRect& range) const = 0;
};

class RectangleQuery : public ShapeQuery
{
public:
	RectangleQuery(sf::FloatRect rec);
	virtual ~RectangleQuery() = default;

	virtual bool Intersects(sf::FloatRect& range) const override;
	sf::FloatRect Get() const;

private:
	sf::FloatRect rect;
};

class CircleQuery : public ShapeQuery
{
public:
	CircleQuery(sf::Vector2f origin, float r);
	virtual ~CircleQuery() = default;

	virtual bool Intersects(sf::FloatRect& range) const override;

private:
	sf::Vector2f origin;
	float r;
	float rSq;
};

class IRayCaster;
class RayQuery : public ShapeQuery
{
public:
	RayQuery(std::shared_ptr<IRayCaster> rayCaster, sf::Vector2f origin, sf::Vector2f direction);
	virtual ~RayQuery() = default;

	virtual bool Intersects(sf::FloatRect& range) const override;

private:
	std::shared_ptr<IRayCaster> rayCaster;
	sf::Vector2f origin;
	sf::Vector2f direction;
};

#endif // SHAPES_H