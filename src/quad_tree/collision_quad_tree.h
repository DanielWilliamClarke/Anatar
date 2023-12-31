#ifndef ANNATAR_COLLISION_QUAD_TREE_H
#define ANNATAR_COLLISION_QUAD_TREE_H

#include <memory>

struct Collision;
struct CollisionMediators;

template <typename C, typename P>
class QuadTree;

using CollisionQuadTree = std::shared_ptr<QuadTree<Collision, CollisionMediators>>;

#endif
