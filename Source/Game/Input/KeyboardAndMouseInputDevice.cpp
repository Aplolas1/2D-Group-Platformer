#include "KeyboardAndMouseInputDevice.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/System/GameState/GameState.h"
#include "../../Engine/Renderer/WindowManager.h"
#include "../../Engine/Core/GameObject.h"
#include "../../Engine/Core/MathHelpers.h"
#include "../../Game/GameObjects/Player.h"

KeyboardAndMouseInputDevice::KeyboardAndMouseInputDevice()
{

}

KeyboardAndMouseInputDevice::~KeyboardAndMouseInputDevice()
{

}

void KeyboardAndMouseInputDevice::ProcessInputs()
{
	m_DigitalInputs[E_DigitalInput_DpadUp].SetPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::W));
	m_DigitalInputs[E_DigitalInput_DpadDown].SetPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::S));
	m_DigitalInputs[E_DigitalInput_DpadLeft].SetPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::A));
	m_DigitalInputs[E_DigitalInput_DpadRight].SetPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::D));

	m_DigitalInputs[E_DigitalInput_B].SetPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::P));
	m_DigitalInputs[E_DigitalInput_Y].SetPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::Q));
	m_DigitalInputs[E_DigitalInput_X].SetPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::E));
	
	m_DigitalInputs[E_DigitalInput_RightShoulder].SetPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::Space));
	sf::Vector2i mouseInput = sf::Mouse::getPosition();

	m_AnalogueInputs[E_AnalogueInput_RightTrigger].SetValue(sf::Mouse::isButtonPressed(sf::Mouse::Left));
	
	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
	GameState* pGameState = pGameStateManager->GetCurrentGameState();
	GameObject* pPlayerObject = pGameState->GetPlayer();
	Player* player = dynamic_cast<Player*>(pPlayerObject);

	if (player)
	{
		WindowManager* pWindowManager = C_SysContext::Get<WindowManager>();
		const sf::RenderWindow* pWindow = pWindowManager->GetWindow();
		const sf::View	   view = pWindow->getView();

		const sf::Vector2f tplypos = player->GetPosition();
		const sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(*pWindow));
		const sf::Vector2f tviewoffset = view.getSize() * 0.5f;
		const sf::Vector2f mouseWorldPos = view.getCenter() + mousePosition - tviewoffset;
		sf::Vector2f distance = mouseWorldPos - tplypos;
		distance = MathHelpers::Normalise(distance);


		m_AnalogueInputs[E_AnalogueInput_ThumbRX].SetValue(distance.x);
		m_AnalogueInputs[E_AnalogueInput_ThumbRY].SetValue(distance.y);
	}
	else
	{
		m_AnalogueInputs[E_AnalogueInput_ThumbRX].SetValue(0.0f);
		m_AnalogueInputs[E_AnalogueInput_ThumbRY].SetValue(0.0f);
	}
}

