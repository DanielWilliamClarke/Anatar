#ifndef I_QUAD_TREE_H
#define I_QUAD_TREE_H
#pragma once

#include <memory>
#include <vector>
#include <functional>

#include <SFML/Graphics.hpp>
#include "util/math_utils.h"

#include "shapes.h"

template <typename U, typename C>
class QuadTree
{
public:
	QuadTree(sf::FloatRect boundry, unsigned int capacity);
	virtual ~QuadTree() = default;

	bool Insert(Point<U>& point);
	void Query(ShapeQuery* range, std::vector<std::shared_ptr<C>>& found, std::function<std::shared_ptr<C>(U)> handler) const;
	void Draw(sf::RenderTarget& target) const;

private:

	void Subdivide();

private:
	sf::FloatRect boundry;
	unsigned int capacity;

	std::vector<Point<U>> points;

	std::unique_ptr<QuadTree<U, C>> nw;
	std::unique_ptr<QuadTree<U, C>> ne;
	std::unique_ptr<QuadTree<U, C>> se;
	std::unique_ptr<QuadTree<U, C>> sw;

	bool isDivided;
};

template <typename U, typename C>
QuadTree<U, C>::QuadTree(sf::FloatRect boundry, unsigned int capacity)
	: boundry(boundry),
	capacity(capacity),
	points({}),
	nw(nullptr), ne(nullptr), se(nullptr), sw(nullptr),
	isDivided(false)
{
}

template <typename U, typename C>
bool QuadTree<U, C>::Insert(Point<U>& point)
{
	if (!this->boundry.contains(point.point))
	{
		return false;
	}

	if (this->points.size() < this->capacity)
	{
		this->points.push_back(point);
		return true;
	}

	if (!this->isDivided)
	{
		this->Subdivide();
	}

	return this->ne->Insert(point) || this->nw->Insert(point) ||
		this->se->Insert(point) || this->sw->Insert(point);
}

template <typename U, typename C>
void QuadTree<U, C>::Query(ShapeQuery* range, std::vector<std::shared_ptr<C>>& found, std::function<std::shared_ptr<C>(U)> handler) const
{
	if (!range->Intersects(this->boundry))
	{
		return;
	}

	for (auto& p : this->points)
	{
		auto output = handler(p.data);
		if (output)
		{
			found.push_back(output);
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

template <typename U, typename C>
void QuadTree<U, C>::Draw(sf::RenderTarget& target) const
{
	if (this->isDivided)
	{
		this->nw->Draw(target);
		this->ne->Draw(target);
		this->sw->Draw(target);
		this->se->Draw(target);
	}

	auto rectangle = sf::RectangleShape();
	rectangle.setPosition(
		sf::Vector2f(this->boundry.left, this->boundry.top));
	rectangle.setSize(
		sf::Vector2f(this->boundry.width, this->boundry.height));
	rectangle.setFillColor(sf::Color::Transparent);
	rectangle.setOutlineColor(sf::Color::White);
	rectangle.setOutlineThickness(-1.0f);
	target.draw(rectangle);
}

template <typename U, typename C>
void QuadTree<U, C>::Subdivide()
{
	auto w = this->boundry.width / 2;
	auto h = this->boundry.height / 2;

	auto x = this->boundry.left + w;
	auto y = this->boundry.top + h;

	this->ne = std::make_unique<QuadTree<U, C>>(
		sf::FloatRect(x, y - h, w, h), this->capacity);
	this->nw = std::make_unique<QuadTree<U, C>>(
		sf::FloatRect(x - w, y - h, w, h), this->capacity);
	this->se = std::make_unique<QuadTree<U, C>>(
		sf::FloatRect(x, y, w, h), this->capacity);
	this->sw = std::make_unique<QuadTree<U, C>>(
		sf::FloatRect(x - w, y, w, h), this->capacity);

	this->isDivided = true;
}

#endif // I_QUAD_TREE_H

