#include "ray_caster.h"

#include <range/v3/algorithm.hpp>

#include "util/math_utils.h"

using Line = std::pair<sf::Vector2f, sf::Vector2f>;

// See https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection for details
std::shared_ptr<RayIntersection> RayCaster::RayBoxIntersects(
    const sf::Vector2f& origin,
    const sf::Vector2f& direction,
    sf::FloatRect box
) const
{
	auto top = box.top;
	auto bottom = box.top + box.height;
	auto left = box.left;
	auto right = box.left + box.width;

	// Here I define each line of the hitbox
    std::vector<Line> lines {
        { // left
            sf::Vector2f(left, top),
            sf::Vector2f(left, bottom)
        },
        { // bottom
            sf::Vector2f(left, bottom),
            sf::Vector2f(right, bottom)
        },
        { // right
            sf::Vector2f(right, bottom),
            sf::Vector2f(right, top)
        },
        { // top
            sf::Vector2f(right, top),
            sf::Vector2f(left, top)
        }
    };

	ranges::sort(lines,
        [&origin](const auto& lineA, const auto& lineB) -> bool {
            sf::Vector2f centerA {
                (lineA.first.x + lineA.second.x) / 2,
                (lineA.first.y + lineA.second.y) / 2
            };

            sf::Vector2f centerB {
                (lineB.first.x + lineB.second.x) / 2,
                (lineB.first.y + lineB.second.y) / 2
            };

            // Here I want to be able to measure distance between the origin and the center of each line
            auto distanceA = Dimensions::ManhattanDistance(centerA, origin);
            auto distanceB = Dimensions::ManhattanDistance(centerB, origin);

            return distanceA < distanceB;
        });

	// Define ray
	auto x3 = origin.x;
	auto y3 = origin.y;
	auto x4 = origin.x + direction.x;
	auto y4 = origin.y + direction.y;

	for (auto& line : lines)
	{
		auto x1 = line.first.x;
		auto y1 = line.first.y;
		auto x2 = line.second.x;
		auto y2 = line.second.y;

		auto den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
		if (den == 0)
        {
			continue;
		}

		auto t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
		auto u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;

		if (t > 0 && t < 1 && u > 0)
		{
			return std::make_shared<RayIntersection>(
				true,
				sf::Vector2f(
					x1 + t * (x2 - x1),
					y1 + t * (y2 - y1))
            );
		}
	}

	return std::make_shared<RayIntersection>(false);
}