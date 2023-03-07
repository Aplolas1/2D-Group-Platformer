#pragma once
#include "../../../Source/Engine/Core/GameObject.h"
#include "../../../Source/Engine/Renderer/AnimatedSprite.h"
#include "../../Engine/Physics/BoxCollider2D.h"


class Collectible;

class Collectible : public GameObject
{
public:
	Collectible();
	~Collectible();

	void Initialise() override;
	void Update() override;
	void GetPosition(float& px, float& py) override;
	sf::Vector2f GetPosition() override;
	void SetPosition(float px, float py) override;
	void SetPosition(sf::Vector2f ppos) override;
	void onCollision(Collider2D* pCollider2D);

private:
	AnimatedSprite m_AnimatedSprite;

	bool m_coinMoving;

	enum AnimationState
	{
		E_AnimationState_dash,
		E_AnimationState_hit,
		E_AnimationState_idle,
		E_AnimationState_melee,
		E_AnimationState_sprint,
		E_AnimationState_walk
	};
};


