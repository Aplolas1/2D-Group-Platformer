#pragma once
#include "../../Engine/Core/GameObject.h"
#include "../../Engine/Renderer/AnimatedSprite.h"

class WeaponBase: public GameObject
{
public:
	WeaponBase();
	virtual ~WeaponBase() {};


	
	//GameObject Overrided
	virtual void Initialise() override;
	void Update() override;

	void GetPosition(float& px, float& py) override;
	sf::Vector2f GetPosition() override;
	void SetPosition(sf::Vector2f ppos) override;
	void SetPosition(float px, float py) override;

	//Weapons Functions
	virtual void Reload();
	virtual void Fire();

	void SetScale(float scaleX, float scaleY);
	void SetRotation(float angle);
	bool canFire();

protected:
	AnimatedSprite m_AnimatedSprite;
	int m_ammo;
	float m_fireRate;
	float m_fireTimer;
};

