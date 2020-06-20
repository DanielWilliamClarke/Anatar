#ifndef I_ENTITY_BUILDER_H
#define I_ENTITY_BUILDER_H
#pragma once

#include <memory>
#include <map>
#include <string>

class EntityObject;

typedef std::map<std::string, std::shared_ptr<EntityObject>> EntityManifest;

class IEntityObjectBuilder
{
public:
	IEntityObjectBuilder() = default;
	virtual ~IEntityObjectBuilder() = default;
	virtual EntityManifest Build() const = 0;
};

#endif //I_ENTITY_BUILDER_H