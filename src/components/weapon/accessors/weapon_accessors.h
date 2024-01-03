#ifndef ANNATAR_WEAPON_ACCESSORS_H
#define ANNATAR_WEAPON_ACCESSORS_H

#include <memory>

#include "bullet/i_bullet_system.h"
#include "bullet/i_bullet_factory.h"
#include "ui/i_player_hud.h"

enum WeaponSlot : unsigned int {
    NONE = 999,
    ONE = 1,
    TWO = 2,
    THREE = 3,
    FOUR = 4,
};

class WeaponSlotAccess
{
public:
    void setSlot(WeaponSlot s)
    {
        this->slot = s;
    }
protected:
    WeaponSlot slot;
};

class WeaponBulletSystemAccess
{
public:
    void setBulletSystem(const std::shared_ptr<IBulletSystem>& bs)
    {
        this->bulletSystem = bs;
    }
protected:
    std::shared_ptr<IBulletSystem> bulletSystem;
};

class WeaponBulletFactoryAccess
{
public:
    void setBulletFactory(const std::shared_ptr<IBulletFactory>& bf)
    {
        this->bulletFactory = bf;
    }
protected:
    std::shared_ptr<IBulletFactory> bulletFactory;
};

class WeaponHudAccess
{
public:
    void setHud(const std::shared_ptr<IPlayerHud>& h)
    {
        this->hud = h;
    };
protected:
    std::shared_ptr<IPlayerHud> hud;
};

#endif
