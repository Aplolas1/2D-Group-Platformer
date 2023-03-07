#pragma once

#include "../../../Source/Engine/Renderer/AnimatedSprite.h"
#include "../../../Source/Engine/Core/GameObject.h"
#include "../../Engine/Physics/BoxCollider2D.h"
#include "../Input/KeyboardAndMouseInputDevice.h"

class WeaponBase;

class Player : public GameObject
{
public:
	Player();
	~Player();

	void Initialise() override;
	void Update() override;
	void GetPosition(float& px, float& py) override;
	sf::Vector2f GetPosition() override;
	void SetPosition(float px, float py) override;
	void SetPosition(sf::Vector2f ppos) override;

	void PlayerWeaponInput();
	void UpdateWeapon();
	void Fire();
	void Reload();
	void OnCollision(Collider2D* pCollider2d);
	void HitByEnemy();
	void PlayerDeath();
	int m_health = 100;
	void GetHp(int val);
	bool blitzEquipped = true;
private:
	AnimatedSprite m_AnimatedSprite;

	bool m_playerMoving;
	

	WeaponBase* m_pWeapon;
	float m_weaponOffsetX;
	float m_weaponOffsetY;

	

	enum E_AnimationState
	{
		E_AnimationState_Idle,
		E_AnimationState_Walk,
		E_AnimationState_Sprint,
		E_AnimationState_Dash,
		E_AnimationState_Death,
		E_AnimationState_Dig,
		E_AnimationState_Holo,
		E_AnimationState_Melee,
		E_AnimationState_Teleport_In,
		E_AnimationState_Teleport_Out,
		E_AnimationState_Hit
	};
};

