#ifndef I_ENTITY_BUILDER_H
#define I_ENTITY_BUILDER_H


#include <memory>
#include <unordered_map>
#include <string>

class EntityObject;

template<typename T>
using EntityManifest = std::unordered_map<T, std::shared_ptr<EntityObject>>;

template<typename T>
class IEntityObjectBuilder
{
public:
	IEntityObjectBuilder() = default;
	virtual ~IEntityObjectBuilder() = default;
	virtual EntityManifest<T> Build() = 0;
};

#endif //I_ENTITY_BUILDER_H