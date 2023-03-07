#include "Player.h"

#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Game/GameData/GameDataManager.h"
#include "../GameData/SpritesheetDef.h"
#include "../../Engine/Input/InputDevice.h"
#include "../../Engine/Input/InputManager.h"
#include "../../Engine/Utils/Utils.h"
#include "../../Engine/System/GameState/GameState.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/Core/MathHelpers.h"

#include "../Weapons/WeaponBase.h"
#include "../Weapons/BlitzWeapon.h"
#include "../Weapons/RifleWeapon.h"

Player::Player()
{
	
}

Player::~Player()
{
	SAFE_DELETE_PTR(m_pWeapon);
}

void Player::Initialise()
{
	GameDataManager* pGameDataManager = C_SysContext::Get<GameDataManager>();
	SpritesheetDef* pSpriteSheetDef;

	pSpriteSheetDef = pGameDataManager->GetSpritesheetDef("sprites/characters/spr_biu.xml");

	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Idle, pSpriteSheetDef, "spr_biu_idle", 10, true);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Walk, pSpriteSheetDef, "spr_biu_walk", 10, true);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Sprint, pSpriteSheetDef, "spr_biu_sprint", 10, true);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Dash, pSpriteSheetDef, "spr_biu_dash", 10, true);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Death, pSpriteSheetDef, "spr_biu_death", 10, false);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Dig, pSpriteSheetDef, "spr_biu_dig", 10, true);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Holo, pSpriteSheetDef, "spr_biu_holo", 10, true);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Melee, pSpriteSheetDef, "spr_biu_melee", 10, true);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Teleport_In, pSpriteSheetDef, "spr_biu_teleport_in", 10, true);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Teleport_Out, pSpriteSheetDef, "spr_biu_teleport_out", 10, true);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Hit, pSpriteSheetDef, "spr_biu_hit", 10, false);

	m_AnimatedSprite.setPosition(250, 250);
	m_AnimatedSprite.SetCurrentAnimation(E_AnimationState_Idle);
	if (blitzEquipped == true)
	{
		m_pWeapon = new BlitzWeapon();
		//m_pWeapon->Initialise();
	}
	else {
		m_pWeapon = new RifleWeapon();
		//m_pWeapon->Initialise();
	}
	/*if (rifleEquipped = true)
	{
		m_pWeapon = new RifleWeapon();
		m_pWeapon->Initialise();
	}*/
	//UpdateWeapon();

	sf::FloatRect m_CollisionRect = m_AnimatedSprite.getGlobalBounds();
}

void Player::Update()
{
	m_AnimatedSprite.Animate();
	m_playerMoving = false;
	float movementSpeed = 50.0f;

	InputManager* pInputManager = C_SysContext::Get<InputManager>();
	InputDevice* pInputDevice = pInputManager->GetInputDevice();
	sf::Vector2f inputMovement;

	if (pInputDevice->GetButtonInput(E_DigitalInput_DpadRight).IsDown())
	{
		inputMovement.x = 1.0f;
		m_playerMoving = true;

if (pInputDevice->GetButtonInput(E_DigitalInput_RightShoulder).IsDown())
{
	movementSpeed = movementSpeed * 2;
}
	}
	if (pInputDevice->GetButtonInput(E_DigitalInput_DpadLeft).IsDown())
	{
		inputMovement.x = -1.0f;
		m_playerMoving = true;

		if (pInputDevice->GetButtonInput(E_DigitalInput_RightShoulder).IsDown())
		{
			movementSpeed = movementSpeed * 2;
		}
	}
	if (pInputDevice->GetButtonInput(E_DigitalInput_DpadUp).IsDown())
	{
		inputMovement.y = -1.0f;
		m_playerMoving = true;

		if (pInputDevice->GetButtonInput(E_DigitalInput_RightShoulder).IsDown())
		{
			movementSpeed = movementSpeed * 2;
		}
	}
	if (pInputDevice->GetButtonInput(E_DigitalInput_DpadDown).IsDown())
	{
		inputMovement.y = 1.0f;
		m_playerMoving = true;

		if (pInputDevice->GetButtonInput(E_DigitalInput_RightShoulder).IsDown())
		{
			movementSpeed = movementSpeed * 2;
		}
	}
	if (pInputDevice && pInputDevice->GetAnalogueInput(E_AnalogueInput_ThumbRX).GetValue() > 0.0f)
	{
		m_AnimatedSprite.setScale(1.0f, 1.0f);
	}
	else if (pInputDevice && pInputDevice->GetAnalogueInput(E_AnalogueInput_ThumbRX).GetValue() < 0.0f)
	{
		m_AnimatedSprite.setScale(-1.0f, 1.0f);
	}
	m_AnimatedSprite.move(inputMovement);

	float x_pos = pInputDevice->GetAnalogueInput(E_AnalogueInput_ThumbLX).GetValue();

	float y_pos = pInputDevice->GetAnalogueInput(E_AnalogueInput_ThumbRX).GetValue();

	switch (m_AnimatedSprite.GetCurrentAnimation())
	{
	case E_AnimationState_Idle:
	{
		if (m_playerMoving == true) {
			m_AnimatedSprite.SetCurrentAnimation(E_AnimationState_Walk);
		}
		if (m_playerMoving == true && (pInputDevice->GetButtonInput(E_DigitalInput_RightShoulder).IsDown())) {
			m_AnimatedSprite.SetCurrentAnimation(E_AnimationState_Sprint);
		}
		if (m_playerMoving == false && pInputDevice->GetButtonInput(E_DigitalInput_B).IsDown()) {
			HitByEnemy();
		}
	}
	break;

	case E_AnimationState_Walk:
	{
		if (m_playerMoving == false) {
			m_AnimatedSprite.SetCurrentAnimation(E_AnimationState_Idle);
		}
		if (m_playerMoving == true && (pInputDevice->GetButtonInput(E_DigitalInput_RightShoulder).IsDown())) {
			m_AnimatedSprite.SetCurrentAnimation(E_AnimationState_Sprint);
		}
	}
	break;
	case E_AnimationState_Sprint:
	{
		if (m_playerMoving == false) {
			m_AnimatedSprite.SetCurrentAnimation(E_AnimationState_Idle);
		}
		if (m_playerMoving == true && (pInputDevice->GetButtonInput(E_DigitalInput_RightShoulder).IsUp())) {
			m_AnimatedSprite.SetCurrentAnimation(E_AnimationState_Walk);
		}
	}
	break;
	case E_AnimationState_Death:
	{
		if (m_AnimatedSprite.AnimationFinished())
		{
			//m_AnimatedSprite.RemoveGameObject(this);
		}
	}
	break;
	}

	if (pInputDevice->GetButtonInput(E_DigitalInput_Y).IsDown())
	{
		delete m_pWeapon;
		m_pWeapon = new BlitzWeapon();
		m_pWeapon->Initialise();
	}
	if (pInputDevice->GetButtonInput(E_DigitalInput_X).IsDown())
	{
		delete m_pWeapon;
		m_pWeapon = new RifleWeapon();
		m_pWeapon->Initialise();
	}

	float offsetYDiff = 25;
	//Get the player position and add the weapon offset to it (accounting for scale)
	sf::Vector2f tweaponpos = m_AnimatedSprite.getPosition();
	tweaponpos.x += m_weaponOffsetX * m_AnimatedSprite.getScale().x;
	tweaponpos.y += m_weaponOffsetY * m_AnimatedSprite.getScale().y + offsetYDiff;
	m_pWeapon->SetScale(m_AnimatedSprite.getScale().x, m_AnimatedSprite.getScale().y);
	m_pWeapon->SetPosition(tweaponpos);

	PlayerWeaponInput();

	UpdateWeapon();

	
}

void Player::HitByEnemy()
{
	m_AnimatedSprite.SetCurrentAnimation(E_AnimationState_Hit);
	m_health - 10;

	PlayerDeath();

	if (m_AnimatedSprite.AnimationFinished())
	{
		m_AnimatedSprite.SetCurrentAnimation(E_AnimationState_Idle);
	}
}

void Player::PlayerDeath()
{
	if (m_health <= 0)
	{
		m_AnimatedSprite.SetCurrentAnimation(E_AnimationState_Death);
	}
	if (m_AnimatedSprite.AnimationFinished())
	{
		GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
		GameState* pGameState = pGameStateManager->GetCurrentGameState();
		//remove from the current game state
		if (pGameState)
			pGameState->RemoveGameObject(this);
	}
}

void Player::GetPosition(float& px, float& py)
{
	m_AnimatedSprite.getPosition().x;
	m_AnimatedSprite.getPosition().y;
}
void Player::GetHp(int val)
{
	val = m_health;
}
sf::Vector2f Player::GetPosition()
{
	return m_AnimatedSprite.getPosition();
}

void Player::SetPosition(float px, float py)
{
	m_AnimatedSprite.setPosition(px, py);
}

void Player::SetPosition(sf::Vector2f ppos)
{
	m_AnimatedSprite.setPosition(ppos);
}

void Player::PlayerWeaponInput()
{
	InputManager* pInputManager = C_SysContext::Get<InputManager>();
	InputDevice* pInputDevice = pInputManager->GetInputDevice();

	if (pInputDevice && pInputDevice->GetAnalogueInput(E_AnalogueInput_RightTrigger).GetValue())
	{
		Fire();
	}
}

void Player::Fire()
{
	if (m_pWeapon)
	{
		m_pWeapon->Fire();
	}
}

void Player::Reload()
{
	if (m_pWeapon)
	{
		m_pWeapon->Reload();
	}
}
void Player::OnCollision(Collider2D* pCollider2d)
{

}

void Player::UpdateWeapon()
{
	InputManager* pInputManager = C_SysContext::Get<InputManager>();
	InputDevice* pInputDevice = pInputManager->GetInputDevice();
	
	float angle = 0.0f;

		if (pInputDevice)
		{
			const float thumbXPos = pInputDevice->GetAnalogueInput(E_AnalogueInput_ThumbRX).GetValue();
			const float thumbYPos = pInputDevice->GetAnalogueInput(E_AnalogueInput_ThumbRY).GetValue();

			const sf::Vector2f up(0.0f, -1.0f);
			const sf::Vector2f forwards(thumbXPos, thumbYPos);
			if (MathHelpers::Length(forwards) > 0.0f)
			angle = MathHelpers::AngleBetweenVectors(up, forwards) - 90.0f;
		}
		angle = m_AnimatedSprite.getScale().x < 0.0f ? -angle : angle;

		m_pWeapon->SetPosition(m_AnimatedSprite.getPosition().x + m_weaponOffsetX * m_AnimatedSprite.getScale().x,
			m_AnimatedSprite.getPosition().y + m_weaponOffsetY * m_AnimatedSprite.getScale().y);
		m_pWeapon->SetRotation(angle);
		m_pWeapon->SetScale(m_AnimatedSprite.getScale().x, m_AnimatedSprite.getScale().y);
		m_pWeapon->Update();
}

