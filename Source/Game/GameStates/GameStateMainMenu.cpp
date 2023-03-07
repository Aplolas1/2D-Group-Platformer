#include "GameStateMainMenu.h"
#include "../GameObjects/GameObjectWithText.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "GameStateTest.h"
#include "GameStateTitleScreen.h"
GameStateMainMenu::GameStateMainMenu() = default;

GameStateMainMenu ::~GameStateMainMenu()
{

}

GameObject* GameStateMainMenu::GetPlayer()
{
	//TODO:  We don't have a Player Object yet to use!
	return nullptr;
}

/**
 * \brief Called when the State is first loaded.
 * Sets up the Initial State of the Screen.
 */
void GameStateMainMenu::Initialise()
{

	//Add a Text Object
	GameObjectWithText* tText = new GameObjectWithText();
	GameObjectWithText* tText2 = new GameObjectWithText();
	tText3 = std::make_unique<GameObjectWithText>();
	GameObjectWithText* tText4 = new GameObjectWithText();
	tText2->SetCharSize(50);
	tText2->SetDisplayText("Start Game");
	tText2->SetColour(sf::Color::Blue);
	tText2->SetFontFile("fonts/wendy.ttf");
	tText2->SetPosition(sf::Vector2f(200.f, 200.f));

	tText->SetCharSize(50);
	tText->SetDisplayText("Exit Game");
	tText->SetColour(sf::Color::Blue);
	tText->SetFontFile("fonts/wendy.ttf");
	tText->SetPosition(sf::Vector2f(200.f, 250.f));

	tText3->SetCharSize(50);
	tText3->SetDisplayText("<----");
	tText3->SetColour(sf::Color::Red);
	tText3->SetFontFile("fonts/wendy.ttf");
	tText3->SetPosition(sf::Vector2f(700.f, 200.f));

	tText4->SetCharSize(30);
	tText4->SetDisplayText("Instructions:\nUSE WASD for the players movement \nHold Space bar to sprint \nUse P for Hit Animation \nQ will load the blitz weapon and E will load the rifle \nUse Left click to fire the weapon \nUse the Dpad to move the enemy \nTo Pause the game use the ESC key \nto initiate Lost state press V \nHitPoints Are in Magenta and current weapon is in Cyan \nPress ENTER to start or exit the game \npress 5 to change the games Level");
	tText4->SetColour(sf::Color::Green);
	tText4->SetFontFile("fonts/wendy.ttf");
	tText4->SetPosition(sf::Vector2f(200.f, 400.f));

	tText->Initialise();
	tText2->Initialise();
	tText3->Initialise();
	tText4->Initialise();
}
/**
 * \brief Update the Game State Once per Frame
 */
void GameStateMainMenu::Update()
{
	int menuIndex = 0;

	GameState::Update();


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		tText3->SetPosition(sf::Vector2f(700.f, 200.f));
		menuIndex = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		tText3->SetPosition(sf::Vector2f(700.f, 250.f));
		menuIndex = 1;
	}
	switch (menuIndex)
	{
	case 0:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			C_SysContext::Get<GameStateManager>();
			GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
			GameStateTest* agamestate = new GameStateTest();
			pGameStateManager->QueueGameState(agamestate);
		}
	case 1:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			C_SysContext::Get<GameStateManager>();
			GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
			pGameStateManager->QueuePop();
		}
	default:
		break;
	}
}