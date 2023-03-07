#pragma once

#include "../../Engine/System/GameState/GameState.h"
#include "../../Game/GameObjects/GameObjectWithSprite.h"
#include "../../Game/GameObjects/GameObjectWithAnimatedSprite.h"
#include "../../Game/GameObjects/GameObjectWithText.h"
#include "../../Game/GameObjects/Player.h"
#include "../../Game/Weapons/WeaponBase.h"
#include "../../Game/GameObjects/Camera.h"
#include "../../Game/GameObjects/TileMap.h"
#include "../../Game/GameObjects/EnemyObject.h"
#include "../../Game/GameObjects/Collectible.h"
class GameStateTest : public GameState
{
public:
	GameStateTest();
	~GameStateTest() override;
	Player* tPlayerCharacter;
	std::unique_ptr<GameObjectWithText>  hpText;
	std::unique_ptr<GameObjectWithText>  weaponText;
public: 
	GameObject* GetPlayer() override;
	void Initialise() override;
	void Update() override;

	//TileMap* TileIndexAtPosition(int posx, int posy, std::string background);
	TileMap* pTileMap1;
	Player* GetPosition();

	//Player GUI
	int hpVal = 100;

	
	std::string level1 = "backgrounds/bg_desert.xml";
	std::string background1 = "levels/BackGroundMap.txt";
	std::string level2 = "backgrounds/bg_ship.xml";
	std::string background2 = "levels/BackGroundMap2.txt";
};
const int desertLevel0[] =
{

	0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
	0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
	0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
	0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
	0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
	0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
	0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
	0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,

};

const int desertLevel1[] =
{

	17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,
	17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,
	17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,
	17, 2, 4, 6, 8, 13, 23, 4, 6, 8, 10, 17, 22, 6, 8, 17,
	17, 3, 5, 7, 9, 10, 2, 5, 7, 9, 11, 15, 24, 7, 9, 17,
	24, -1, -1, -1, -1, 11, 3, -1, -1, -1, -1, 2, 4, -1, -1, 13,
	22, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 3, 5, -1, -1, 17,
	23, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 15,
	24, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 14,
	22, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 17,
	23, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 15,
	24, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 13,
	22, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 14,
	23, -1, -1, -1, -1, -1, -1, -1, -1, -1, 12, 21, -1, -1, -1, 17,
	23, -1, -1, -1, -1, -1, -1, -1, -1, 12, 17, 20, 21, -1, -1, 13,
	17, 16, 17, 18, 17, 19, 20, 17, 18, 17, 17, 17, 17, 16, 18, 17,

};

