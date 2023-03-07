#pragma once

#include "../../Engine/System/GameState/GameState.h"
#include "../../Game/GameObjects/GameObjectWithSprite.h"
#include "../../Game/GameObjects/GameObjectWithAnimatedSprite.h"
#include "../../Game/GameObjects/Player.h"
#include "../../Game/Weapons/WeaponBase.h"

class GameStateTitleScreen : public GameState
{
public:
	GameStateTitleScreen();
	~GameStateTitleScreen() override;

public:
	GameObject* GetPlayer() override;
	void Initialise() override;
	void Update() override;

};

