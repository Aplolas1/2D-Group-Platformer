#include "GameStateTitleScreen.h"
#include "../GameObjects/GameObjectWithText.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "GameStateMainMenu.h"
GameStateTitleScreen::GameStateTitleScreen() = default;

GameStateTitleScreen::~GameStateTitleScreen()
{
}

GameObject* GameStateTitleScreen::GetPlayer()
{
	//TODO:  We don't have a Player Object yet to use!
	return nullptr;
}

/**
 * \brief Called when the State is first loaded.
 * Sets up the Initial State of the Screen.
 */
void GameStateTitleScreen::Initialise()
{
	//Add a Text Object
	GameObjectWithText* tText = new GameObjectWithText();
	GameObjectWithText* tText2 = new GameObjectWithText();
	tText2->SetCharSize(50);
	tText2->SetDisplayText("Welcome to Relic Shooter - (BTEC EDITION)");
	tText2->SetColour(sf::Color::Blue);
	tText2->SetFontFile("fonts/wendy.ttf");
	tText2->SetPosition(sf::Vector2f(200.f, 200.f));
	tText->SetCharSize(30);
	tText->SetDisplayText("Press Space Bar To Continue...");
	tText->SetColour(sf::Color::Red);
	tText->SetFontFile("fonts/wendy.ttf");
	tText->SetPosition(sf::Vector2f(200.f, 250.f));

	//Add it to the Renderer
	tText->Initialise();
	tText2->Initialise();


}

/**
 * \brief Update the Game State Once per Frame
 */
void GameStateTitleScreen::Update()
{

	GameState::Update();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		C_SysContext::Get<GameStateManager>();
		GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
		GameStateMainMenu* bgamestate = new GameStateMainMenu();
		pGameStateManager->QueueGameState(bgamestate);
	}
}