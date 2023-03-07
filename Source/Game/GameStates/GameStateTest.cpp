#include "GameStateTest.h"
#include "../GameObjects/GameObjectWithText.h"
#include "../GameData/GameDataManager.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Game/GameObjects/TileMap.h"
#include "../../Game/GameObjects/Player.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "GameStatePause.h"
#include "GameStateGameLoss.h"
#include <string>
GameStateTest::GameStateTest() = default;

GameStateTest::~GameStateTest()
{
}

GameObject* GameStateTest::GetPlayer()
{
	return this->tPlayerCharacter;
}

/**
 * \brief Called when the State is first loaded.
 * Sets up the Initial State of the Screen.
 */
void GameStateTest::Initialise()
{
	//Tile map created -- level 1
	this->pTileMap1 = new TileMap();
	//Tile map initialised
	pTileMap1->Initialise();
	//Tile map loaded from a file
	pTileMap1->LoadFromFile(level2, background2);
	//Since tilemap inherits from game object we can add it to the game state
	m_GameObjects.push_back(pTileMap1);
	//Add a Text Object
	GameObjectWithText* tText = new GameObjectWithText();
	GameObjectWithText* tText2 = new GameObjectWithText();
	hpText = std::make_unique<GameObjectWithText>();
	weaponText = std::make_unique<GameObjectWithText>();
	tText2->SetCharSize(50);
	tText2->SetDisplayText("");
	tText2->SetColour(sf::Color::Blue);
	tText2->SetFontFile("fonts/wendy.ttf");
	tText2->SetPosition(sf::Vector2f(100.f,100.f));
	

	GameObjectWithSprite* tSprite = new GameObjectWithSprite();
	tSprite->Initialise();
	
	tPlayerCharacter = new Player();
	tPlayerCharacter->Initialise();

	hpText->SetCharSize(40);
	auto s = std::to_string(hpVal);
	hpText->SetDisplayText(s);
	hpText->SetColour(sf::Color::Magenta);
	hpText->SetFontFile("fonts/wendy.ttf");
	hpText->SetPosition(sf::Vector2f(50.f, 50.f));

	weaponText->SetCharSize(40);
	weaponText->SetDisplayText("");
	weaponText->SetColour(sf::Color::Cyan);
	weaponText->SetFontFile("fonts/wendy.ttf");
	weaponText->SetPosition(sf::Vector2f(50.f, 50.f));


	/*GameObjectWithAnimatedSprite* tAnimatedSprite = new GameObjectWithAnimatedSprite();
	tAnimatedSprite->Initialise();*/
	EnemyObject* tEnemy = new EnemyObject();
	tEnemy->Initialise();
	tEnemy->Update();

	Collectible* tCollectible = new Collectible();
	tCollectible->Initialise();
	//Add it to the Renderer
	tText->Initialise();
	tText2->Initialise();
	hpText->Initialise();
	weaponText->Initialise();
	Camera* m_camera = new Camera();
	m_camera->Initialise();
	m_camera->SetCamera();

	//Add it to the Game Objects
	this->m_GameObjects.push_back(tText);
	this->m_GameObjects.push_back(tSprite);
	//this->m_GameObjects.push_back(tAnimatedSprite);
	this->m_GameObjects.push_back(tPlayerCharacter);
	this->m_GameObjects.push_back(tEnemy);
	this->m_GameObjects.push_back(tCollectible);
	this->m_GameObjects.push_back(m_camera);
	
}


/**
 * \brief Update the Game State Once per Frame
 */
void GameStateTest::Update()
{
	sf::Vector2f hpPos = tPlayerCharacter->GetPosition();
	hpText->SetPosition(hpPos.x - 100, hpPos.y - 100);

	sf::Vector2f wepPos = tPlayerCharacter->GetPosition();
	weaponText->SetPosition(wepPos.x, wepPos.y - 100);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		weaponText->SetDisplayText("Blitz");
		weaponText->Initialise();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		weaponText->SetDisplayText("Rifle");
		weaponText->Initialise();
	}
	GameState::Update();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		C_SysContext::Get<GameStateManager>();
		GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
		GameStatePause* pgamestate = new GameStatePause();
		pGameStateManager->QueueGameState(pgamestate);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		
		hpVal = hpVal - 10;
		auto s = std::to_string(hpVal);
		hpText->SetDisplayText(s);
		hpText->Initialise();
		
	}
	GameState::Update();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
	{
		C_SysContext::Get<GameStateManager>();
		GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
		GameStateGameLoss* agamestate = new GameStateGameLoss();
		pGameStateManager->QueueGameState(agamestate);
	}
	int tileCheck = pTileMap1->TileIndexAtPosition(tPlayerCharacter->GetPosition().x, tPlayerCharacter->GetPosition().y, background1);
	if (tileCheck >= 0)
	{
		Collider2D CollidesWisth(TileMap * pTileMap1);

		Collider2D OnCollision();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
	{
		pTileMap1->LoadFromFile(level1, background1);
		m_GameObjects.push_back(pTileMap1);
	}
}
