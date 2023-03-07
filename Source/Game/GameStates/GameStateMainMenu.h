#pragma once

#include "../../Engine/System/GameState/GameState.h"
#include "../../Game/GameObjects/GameObjectWithSprite.h"
#include "../../Game/GameObjects/GameObjectWithAnimatedSprite.h"
#include "../../Game/GameObjects/GameObjectWithText.h"
#include "../../Game/GameObjects/Player.h"
#include "../../Game/Weapons/WeaponBase.h"

class GameStateMainMenu : public GameState
{
public:
	GameStateMainMenu();
	~GameStateMainMenu() override;
	std::unique_ptr<GameObjectWithText> tText3;
protected:
	GameObject* GetPlayer() override;
	void Initialise() override;
	void Update() override;

};

