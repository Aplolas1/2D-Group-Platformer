#pragma once

#include "../../Engine/Core//GameObject.h"
#include "../../Engine/Renderer/Sprite.h"
#include "../../Engine/Physics/BoxCollider2D.h"

class GameObjectWithSprite : public GameObject//, public BoxCollider2D
{
public:
	GameObjectWithSprite();
	~GameObjectWithSprite();

	void Initialise() override;
	void Update() override;
	void GetPosition(float& px, float& py) override;
	sf::Vector2f GetPosition() override;
	void SetPosition(float px, float py) override;
	void SetPosition(sf::Vector2f ppos) override;
	void move(float offsetX, float offsetY);
	void rotate(float angle);
	//float GetRotation() const;
	void scale(float factorX, float factorY);

	void onCollision(Collider2D* pCollider2D);

	Sprite m_sprite;
};

