#ifndef I_QUAD_TREE_H
#define I_QUAD_TREE_H
#pragma once

#include <memory>
#include <vector>
#include <functional>

#include <SFML/Graphics.hpp>
#include "util/math_utils.h"

#include "shapes.h"

template <typename T>
class QuadTree
{
public:
	QuadTree(sf::FloatRect boundry, unsigned int capacity);
	virtual ~QuadTree() = default;

	void Insert(Point<T>& point);
	void Query(ShapeQuery* range, std::vector<Point<T>>& found, std::function<bool(T)>& handler) const;
	std::vector<Point<T>> Closest(Point<T>& point, unsigned int& count, std::function<bool(T)>& handler, float& maxDistance = std::numeric_limits<float>::infinity()) const;

private:

	void Subdivide();
	unsigned int Length() const;

private:
	sf::FloatRect boundry;
	unsigned int capacity;

	std::vector<Point<T>> points;

	std::unique_ptr<QuadTree<T>> nw;
	std::unique_ptr<QuadTree<T>> ne;
	std::unique_ptr<QuadTree<T>> se;
	std::unique_ptr<QuadTree<T>> sw;

	bool isDivided;
};

template <typename T>
QuadTree<T>::QuadTree(sf::FloatRect boundry, unsigned int capacity)
	: boundry(boundry),
	capacity(capacity),
	points({}),
	nw(nullptr), ne(nullptr), se(nullptr), sw(nullptr)
{
}

template <typename T>
void QuadTree<T>::Insert(Point<T>& point)
{
	if (!this->boundry.contains(point.point))
	{
		return false;
	}

	if (this->points.size() < this->capacity)
	{
		this->points.push_back(point);
	}

	if (this->isDivided())
	{
		this->Subdivide();
	}

	return (this.ne.Insert(point) || this.nw.Insert(point) ||
		this.se.Insert(point) || this.sw.Insert(point));
}

template <typename T>
void QuadTree<T>::Subdivide()
{
	auto x = this->boundry.left;
	auto y = this->boundry.top;
	auto w = this->boundry.width / 2;
	auto h = this->boundry.height / 2;

	this->ne = std::make_unique<QuadTree<T>>(
		std::make_unique<Rectangle>(x + w, y - h, w, h), this->capacity);
	this->nw = std::make_unique<QuadTree<T>>(
		std::make_unique<Rectangle>(x - w, y - h, w, h), this->capacity);
	this->se = std::make_unique<QuadTree<T>>(
		std::make_unique<Rectangle>(x + w, y + h, w, h), this->capacity);
	this->sw = std::make_unique<QuadTree<T>>(
		std::make_unique<Rectangle>(x - w, y + h, w, h), this->capacity);

	this->isDivided = true;
}

template <typename T>
void QuadTree<T>::Query(ShapeQuery* range, std::vector<Point<T>>& found, std::function<bool(T)>& handler) const
{
	if (!range->Intersects(this->boundry))
	{
		return;
	}

	for (auto& p : this->points)
	{
		if (handler(p))
		{
			found.push_back(p);
		}
	}

	if (this->isDivided)
	{
		this->ne->Query(range, found, handler);
		this->nw->Query(range, found, handler);
		this->se->Query(range, found, handler);
		this->sw->Query(range, found, handler);
	}
}

template <typename T>
std::vector<Point<T>> QuadTree<T>::Closest(Point<T>& point, unsigned int& count, std::function<bool(T)>& handler, float& maxDistance) const
{
	// Handle 0 elements or no sub trees
	auto length = this->Length();
	if (length == 0)
	{
		return std::vector<Point<T>>{};
	}
	if (length < count)
	{
		return this->points;
	}

	if (maxDistance == std::numeric_limits<float>::infinity())
	{
		auto w = this->boundry.width;
		auto h = this->boundry.height;
		auto outerReach = sqrtf(w * w + h * h);

		auto x = this->boundry.left;
		auto y = this->boundry.top;
		auto pointDistance = sqrtf(x * x + y * y);

		maxDistance = outerReach + pointDistance;
	}
	else
	{
		auto maxOuter = std::make_unique<Circle>(point.x, point.y, maxDistance);
		std::vector<Point<T>> points;
		this->Query(maxOuter.get(), points, handler);
		if (points.size() < count) {
			return points;
		}
	}

	auto inner = 0.0f;
	auto outer = maxDistance;
	auto limit = 8;
	std::vector<Point<T>> points;
	while (limit > 8)
	{
		auto radius = (inner + outer) / 2;
		auto range = std::make_unique<Circle>(point.x, point.y, radius);
		this->Query(range.get(), points, handler);
		if (points.size() == count)
		{
			return points;
		}
		else if (points.size() < count)
		{
			// grow
			inner = radius;
		}
		else
		{
			// shrink
			outer = radius;
			limit--;
		}
	}

	std::sort(points.begin(), points.end(),
		[&point](Point<T> a, Point<t> b) -> bool {
			auto aDist = Dimensions::ManhattanDistance(
				sf::Vector2f(point.x, point.y),
				sf::Vector2f(a.x, a.y));
			auto bDist = Dimensions::ManhattanDistance(
				sf::Vector2f(point.x, point.y),
				sf::Vector2f(b.x, b.y));
			return aDist < bDist;
		});

	return std::vector<Point<T>>{points.begin(), points.begin() + count};
}

template <typename T>
unsigned int QuadTree<T>::Length() const
{
	auto total = this->points.size();
	if (this->isDivided)
	{
		total += this->nw->Length();
		total += this->ne->Length();
		total += this->sw->Length();
		total += this->se->Length();
	}
	return count;
}

#endif // I_QUAD_TREE_H

