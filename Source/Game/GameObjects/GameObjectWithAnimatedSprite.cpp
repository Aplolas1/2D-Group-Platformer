#include "GameObjectWithAnimatedSprite.h"

#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/Input/InputManager.h"
#include "../../Engine/Input/InputDevice.h"

GameObjectWithAnimatedSprite::GameObjectWithAnimatedSprite()
{
	
}

GameObjectWithAnimatedSprite::~GameObjectWithAnimatedSprite()
{
	
}

void GameObjectWithAnimatedSprite::Initialise()
{
	int frameWidth = 256;
	sf::IntRect frame;
	frame.height = 256;
	frame.width = 256;
	frame.left = 0;
	frame.top = 0;
	std::vector<sf::IntRect>listOfFrames;
	sf::Vector2f origin;
	std::vector<sf::Vector2f>ListOfOrigin;
	origin.x = 0;
	origin.y = 0;
	listOfFrames.push_back(frame);
	ListOfOrigin.push_back(origin);

	for (int i = 0; i < 6; i++)
	{
		frame.left = frameWidth * i;
		
		listOfFrames.push_back(frame);
		ListOfOrigin.push_back(origin);
	}

	m_AnimatedSprite.AddAnimation(0, "sprites/spritesheet_test.png", listOfFrames, ListOfOrigin, 30, true);
	m_AnimatedSprite.SetCurrentAnimation(0);
}

void GameObjectWithAnimatedSprite::Update()
{
	m_AnimatedSprite.Animate();

	InputManager* pInputManager = C_SysContext::Get<InputManager>();
	InputDevice* pInputDevice = pInputManager->GetInputDevice();
	sf::Vector2f inputMovement;

	/*if (pInputDevice->GetButtonInput(E_DigitalInput_DpadRight).IsDown())
	{
		inputMovement.x = 1.0f;
	}
	if (pInputDevice->GetButtonInput(E_DigitalInput_DpadLeft).IsDown())
	{
		inputMovement.x = -1.0f;
	}
	if (pInputDevice->GetButtonInput(E_DigitalInput_DpadUp).IsDown())
	{
		inputMovement.y = -1.0f;
	}
	if (pInputDevice->GetButtonInput(E_DigitalInput_DpadDown).IsDown())
	{
		inputMovement.y = 1.0f;
	}*/
	m_AnimatedSprite.move(inputMovement);

	float x_pos = pInputDevice->GetAnalogueInput(E_AnalogueInput_ThumbLX).GetValue();

	float y_pos = pInputDevice->GetAnalogueInput(E_AnalogueInput_ThumbRX).GetValue();

}

void GameObjectWithAnimatedSprite::GetPosition(float& px, float& py)
{
	m_AnimatedSprite.getPosition().x;
	m_AnimatedSprite.getPosition().y;
}

sf::Vector2f GameObjectWithAnimatedSprite::GetPosition()
{
	return m_AnimatedSprite.getPosition();
}

void GameObjectWithAnimatedSprite::SetPosition(float px, float py)
{
	m_AnimatedSprite.setPosition(px, py);
}

void GameObjectWithAnimatedSprite::SetPosition(sf::Vector2f ppos)
{
	m_AnimatedSprite.setPosition(ppos);
}









