#ifndef I_QUAD_TREE_H
#define I_QUAD_TREE_H
#pragma once

#include <memory>
#include <vector>
#include <functional>

#include <SFML/Graphics.hpp>
#include "util/math_utils.h"
#include "renderer/i_renderer.h"

#include "shapes.h"

template <typename C, typename P>
class QuadTree
{
public:
	QuadTree(sf::FloatRect boundry, unsigned int capacity);
	virtual ~QuadTree() = default;

	bool Insert(std::shared_ptr<Point<P>> point);
	void Query(
		ShapeQuery* range,
		std::vector<std::shared_ptr<C>>& found,
		std::function<std::shared_ptr<C>(std::shared_ptr<Point<P>>)> test) const;
	void Draw(std::shared_ptr<IRenderer> renderer) const;

private:
	void Subdivide();

private:
	sf::FloatRect boundry;
	unsigned int capacity;

	std::vector<std::shared_ptr<Point<P>>> points;

	std::unique_ptr<QuadTree<C, P>> nw;
	std::unique_ptr<QuadTree<C, P>> ne;
	std::unique_ptr<QuadTree<C, P>> se;
	std::unique_ptr<QuadTree<C, P>> sw;

	bool isDivided;
};

template <typename C, typename P>
QuadTree<C, P>::QuadTree(sf::FloatRect boundry, unsigned int capacity)
	: boundry(boundry),
	capacity(capacity),
	points({}),
	nw(nullptr), ne(nullptr), se(nullptr), sw(nullptr),
	isDivided(false)
{
}

template <typename C, typename P>
bool QuadTree<C, P>::Insert(std::shared_ptr<Point<P>> point)
{
	if (!this->boundry.contains(point->position))
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

template <typename C, typename P>
void QuadTree<C, P>::Query(
	ShapeQuery* range,
	std::vector<std::shared_ptr<C>>& found,
	std::function<std::shared_ptr<C>(std::shared_ptr<Point<P>>)> test) const
{
	if (!range->Intersects(this->boundry))
	{
		return;
	}

	for (auto& p : this->points)
	{
		auto output = test(p);
		if (output) {
			found.push_back(output);
		}
	}

	if (this->isDivided)
	{
		this->ne->Query(range, found, test);
		this->nw->Query(range, found, test);
		this->se->Query(range, found, test);
		this->sw->Query(range, found, test);
	}
}

template <typename C, typename P>
void QuadTree<C, P>::Draw(std::shared_ptr<IRenderer> renderer) const
{
	if (this->isDivided)
	{
		this->nw->Draw(renderer);
		this->ne->Draw(renderer);
		this->sw->Draw(renderer);
		this->se->Draw(renderer);
	}

	auto rectangle = sf::RectangleShape();
	rectangle.setPosition(sf::Vector2f(this->boundry.left, this->boundry.top));
	rectangle.setSize(sf::Vector2f(this->boundry.width, this->boundry.height));
	rectangle.setFillColor(sf::Color::Transparent);
	rectangle.setOutlineColor(sf::Color::White);
	rectangle.setOutlineThickness(-1.0f);

	renderer->GetDebugTarget().draw(rectangle);
}

template <typename C, typename P>
void QuadTree<C, P>::Subdivide()
{
	auto w = this->boundry.width / 2;
	auto h = this->boundry.height / 2;
	auto x = this->boundry.left + w;
	auto y = this->boundry.top + h;

	this->ne = std::make_unique<QuadTree<C, P>>(sf::FloatRect(x, y - h, w, h), this->capacity);
	this->nw = std::make_unique<QuadTree<C, P>>(sf::FloatRect(x - w, y - h, w, h), this->capacity);
	this->se = std::make_unique<QuadTree<C, P>>(sf::FloatRect(x, y, w, h), this->capacity);
	this->sw = std::make_unique<QuadTree<C, P>>(sf::FloatRect(x - w, y, w, h), this->capacity);

	this->isDivided = true;
}

#endif // I_QUAD_TREE_H

