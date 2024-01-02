#include "i_weapon_component.h"
#include "ui/i_player_hud.h"

IWeaponComponent::IWeaponComponent(
    std::shared_ptr<IPlayerHud> hud,
    WeaponSlot slot
)
    : hud(hud), slot(slot)
{}

WeaponSlot IWeaponComponent::getSlot() const
{
    return this->slot;
}

void IWeaponComponent::Update(WeaponTriggerState& triggerState)
{
    if (this->hud)
    {
        auto weaponState = this->getWeaponState();
        this->hud->Update(triggerState, weaponState);
    }
}

void IWeaponComponent::Cease()
{
}