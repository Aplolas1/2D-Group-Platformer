#pragma once
#include "../../Engine/Core/GameObject.h"
#include "../../Engine/Renderer/AnimatedSprite.h"
#include "../../Engine/Physics/BoxCollider2D.h"

class Bullet : public GameObject
{
public:
	Bullet();
	~Bullet();

	virtual void Initialise() override;
	virtual void Update() override;
	virtual void GetPosition(float& px, float& py) override;
	virtual sf::Vector2f GetPosition();
	virtual void SetPosition(float px, float py) override;
	virtual void SetPosition(sf::Vector2f ppos) override;

	void SetRotation(float angle);
	void SetScale(float scaleX, float scaleY);
	//virtual void OnCollision(Collider2D* pCollider);

	/*bool collidesWith(Collider2D* pCollider2D);
	bool collidesWith(BoxCollider2D* pBoxCollider);
	bool collidesWith(CircleCollider2D* pCircle);*/
	void onCollision(Collider2D* pCollider2D);

protected:
	AnimatedSprite m_AnimatedSprite;
	float m_velocity;
	float m_lifetime;

	sf::FloatRect m_collisionRect;
};

