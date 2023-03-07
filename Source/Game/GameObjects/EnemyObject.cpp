#include "EnemyObject.h"

#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Game/GameData/GameDataManager.h"
#include "../GameData/SpritesheetDef.h"
#include "../../Engine/Input/InputDevice.h"
#include "../../Engine/Input/InputManager.h"
#include "../../Engine/Utils/Utils.h"
#include "../../Engine/System/GameState/GameState.h"
#include "../../Engine/System/GameState/GameStateManager.h"


EnemyObject::EnemyObject()
{
}

EnemyObject::~EnemyObject()
{
}

void EnemyObject::Initialise()
{
	GameDataManager* pGameDataManager = C_SysContext::Get<GameDataManager>();


	SpritesheetDef* pSpriteSheetDef = pGameDataManager->GetSpritesheetDef("sprites/characters/spr_boss.xml");

	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Idle, pSpriteSheetDef, "spr_boss_idle", 10, true);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Walk, pSpriteSheetDef, "spr_boss_walk", 10, true);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_egg_start, pSpriteSheetDef, "spr_boss_egg_start", 10, true);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_egg_idle, pSpriteSheetDef, "spr_boss_egg_idle", 10, true);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_egg_crack, pSpriteSheetDef, "spr_boss_egg_crack", 10, true);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_death, pSpriteSheetDef, "spr_boss_death", 10, false);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_hit, pSpriteSheetDef, "spr_boss_hit", 10, false);

	m_enemyMoving = false;
	m_AnimatedSprite.setPosition(1400, 500);

	m_AnimatedSprite.SetCurrentAnimation(E_AnimationState_egg_start);

}

void EnemyObject::Update()
{
	m_AnimatedSprite.Animate();
	float movementSpeed = 150.0f;

	InputManager* pInputManager = C_SysContext::Get<InputManager>();
	InputDevice* pInputDevice = pInputManager->GetInputDevice();
	sf::Vector2f inputMovement;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		inputMovement.x = -1.0f;
		m_enemyMoving = true;

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		inputMovement.x = 1.0f;
		m_enemyMoving = true;


	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		inputMovement.y = 1.0f;
		m_enemyMoving = true;
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		inputMovement.y = -1.0f;
		m_enemyMoving = true;
	}


	m_AnimatedSprite.move(inputMovement);

	float x_pos = pInputDevice->GetAnalogueInput(E_AnalogueInput_ThumbLX).GetValue();

	float y_pos = pInputDevice->GetAnalogueInput(E_AnalogueInput_ThumbRX).GetValue();


	switch (m_AnimatedSprite.GetCurrentAnimation())
	{
	case E_AnimationState_egg_idle:
	{

		if (m_enemyMoving == true && pInputDevice->GetButtonInput(E_DigitalInput_DpadRight).IsDown()) {
			m_AnimatedSprite.SetCurrentAnimation(E_AnimationState_Walk);
		}
	}
	break;

	case E_AnimationState_egg_start:
	{
		if (m_enemyMoving == false) {
			m_AnimatedSprite.SetCurrentAnimation(E_AnimationState_egg_idle);

		}

	}
	break;

	}



}

void EnemyObject::GetPosition(float& px, float& py)
{
	m_AnimatedSprite.getPosition().x;
	m_AnimatedSprite.getPosition().y;
}

sf::Vector2f EnemyObject::GetPosition()
{
	return m_AnimatedSprite.getPosition();
}

void EnemyObject::SetPosition(float px, float py)
{
	m_AnimatedSprite.setPosition(px, py);
}

void EnemyObject::SetPosition(sf::Vector2f ppos)
{
	m_AnimatedSprite.setPosition(ppos);
}


void EnemyObject::onCollision(Collider2D* pCollider2D)
{
	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
	GameState* pCurrentGameState = pGameStateManager->GetCurrentGameState();

	pCurrentGameState->RemoveGameObject(this);
}

