#include "GameStatePause.h"
#include "../GameObjects/GameObjectWithText.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "GameStateMainMenu.h"
GameStatePause::GameStatePause() = default;

GameStatePause::~GameStatePause()
{
}

GameObject* GameStatePause::GetPlayer()
{
	//TODO:  We don't have a Player Object yet to use!
	return nullptr;
}

/**
 * \brief Called when the State is first loaded.
 * Sets up the Initial State of the Screen.
 */
void GameStatePause::Initialise()
{
	//Add a Text Object
	GameObjectWithText* tText = new GameObjectWithText();
	GameObjectWithText* tText2 = new GameObjectWithText();
	tText2->SetCharSize(50);
	tText2->SetDisplayText("You Have Paused The Game");
	tText2->SetColour(sf::Color::Blue);
	tText2->SetFontFile("fonts/wendy.ttf");
	tText2->SetPosition(sf::Vector2f(200.f, 200.f));
	tText->SetCharSize(30);
	tText->SetDisplayText("Press Space to continue or E to exit the game");
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
void GameStatePause::Update()
{

	GameState::Update();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		C_SysContext::Get<GameStateManager>();
		GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
		pGameStateManager->QueuePop();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		C_SysContext::Get<GameStateManager>();
		GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
		GameStateMainMenu* bgamestate = new GameStateMainMenu();
		pGameStateManager->QueueGameState(bgamestate);
		
	}
}