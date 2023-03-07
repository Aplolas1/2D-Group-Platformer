#pragma once

#include <SFML/Graphics.hpp>
#include "../../Engine/Core/GameObject.h"
class Camera : public GameObject
{
public: 
	Camera();
	~Camera();

	void Initialise();
	void Update();
	sf::Vector2f GetPosition();
	void GetPosition(float& px, float& py);
	void SetPosition(float px, float py);
	void SetPosition(sf::Vector2f ppos);

	void SetCamera();

private: 
	bool m_followPlayer;
	sf::View m_view;
};

