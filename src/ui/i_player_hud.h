#ifndef I_PLAYER_HUD
#define I_PLAYER_HUD

#include <SFML/Graphics.hpp>
#include <memory>

class IRenderer;

struct PlayerAttributeUpdate;
struct WeaponTriggerState;
struct WeaponState;

class IPlayerHud
{
public:
	IPlayerHud() = default;
	virtual ~IPlayerHud() = default;

	virtual void Update(PlayerAttributeUpdate& attributeUpdate) = 0;
	virtual void Update(WeaponTriggerState& triggerState, WeaponState& weaponState) = 0;
	virtual void Draw(const std::shared_ptr<IRenderer>& renderer) const = 0;
};

#endif // I_PLAYER_HUD