#ifndef I_PLAYER_ATTRBUTE_COMPONENT_H
#define I_PLAYER_ATTRBUTE_COMPONENT_H


#include "i_attribute_component.h"

class IPlayerAttributeComponent: public IAttributeComponent
{
public:
	IPlayerAttributeComponent() = default;
	~IPlayerAttributeComponent() override = default;
	virtual void Update(float dt) = 0;
};

#endif
