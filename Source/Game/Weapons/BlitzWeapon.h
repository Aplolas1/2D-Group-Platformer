#pragma once

#include "WeaponBase.h"

#include "../GameObjects/Bullet.h"

class BlitzWeapon : public WeaponBase
{
public:
	BlitzWeapon();
	~BlitzWeapon() override;

	virtual void Initialise() override;
	virtual void Update() override;
	virtual void Reload() override;
	virtual void Fire() override;

private:
	int m_barellOffsetX;
	int m_barrelOffsetY;

	int damage = 10;
};

