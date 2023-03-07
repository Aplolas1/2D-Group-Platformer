#pragma once

#include "WeaponBase.h"
#include "../GameObjects/Bullet.h"

class RifleWeapon : public WeaponBase
{
public:
	RifleWeapon();
	~RifleWeapon();


	virtual void Initialise() override;
	virtual void Update() override;
	virtual void Reload() override;
	virtual void Fire() override;

private:
	int m_barellOffsetX;
	int m_barrelOffsetY;

	int damage = 5;
};

