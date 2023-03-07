#pragma once

#include "../../Engine/Core/GameObject.h"
#include "../../Engine/Renderer/AnimatedSprite.h"
#include "../Input/KeyboardAndMouseInputDevice.h"

class GameObjectWithAnimatedSprite : public GameObject
{
public:
	GameObjectWithAnimatedSprite();
	~GameObjectWithAnimatedSprite();

	void Initialise() override;
	void Update() override;
	void GetPosition(float& px, float& py) override;
	sf::Vector2f GetPosition() override;
	void SetPosition(float px, float py) override;
	void SetPosition(sf::Vector2f ppos) override;


private:
	AnimatedSprite m_AnimatedSprite;
};

