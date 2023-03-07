#pragma once

#include "../../Engine/System/GameState/GameState.h"
#include "../../Game/GameObjects/GameObjectWithSprite.h"
#include "../../Game/GameObjects/GameObjectWithAnimatedSprite.h"
#include "../../Game/GameObjects/Player.h"
#include "../../Game/Weapons/WeaponBase.h"

class GameStatePause : public GameState
{
public:
	GameStatePause();
	~GameStatePause() override;

public:
	GameObject* GetPlayer() override;
	void Initialise() override;
	void Update() override;

};
