#ifndef I_ENTITY_BUILDER_H
#define I_ENTITY_BUILDER_H
#pragma once

#include <memory>
#include <map>
#include <string>

class EntityObject;

using ObjectID = unsigned int;
using EntityManifest = std::map<ObjectID, std::shared_ptr<EntityObject>>;

class IEntityObjectBuilder
{
public:
	IEntityObjectBuilder() = default;
	virtual ~IEntityObjectBuilder() = default;
	virtual EntityManifest Build() = 0;
};

#endif //I_ENTITY_BUILDER_H