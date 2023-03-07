#pragma once
#include "GameObjectWithAnimatedSprite.h"
#include "../Input/KeyboardAndMouseInputDevice.h"
#include "../../../Source/Engine/Core/GameObject.h"
#include "../../Engine/Physics/BoxCollider2D.h"

class EnemyObject : public GameObject
{
public:
	EnemyObject();
	~EnemyObject();

	void Initialise()override;
	void Update()override;
	void GetPosition(float& px, float& py)override;
	sf::Vector2f GetPosition() override;
	void SetPosition(float px, float py)override;
	void SetPosition(sf::Vector2f ppos) override;
	void onCollision(Collider2D* pCollider2D);


protected:
	AnimatedSprite m_AnimatedSprite;
	bool m_enemyMoving;
	int _direction;
	float _strafe_speed;
	enum AnimationState
	{
		E_AnimationState_Idle,
		E_AnimationState_Walk,
		E_AnimationState_egg_start,
		E_AnimationState_egg_idle,
		E_AnimationState_egg_crack,
		E_AnimationState_death,
		E_AnimationState_hit

	};
};
