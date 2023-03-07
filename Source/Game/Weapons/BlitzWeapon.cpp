#include "BlitzWeapon.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../GameData/GameDataManager.h"
#include "../../Engine/System/GameState/GameState.h"

BlitzWeapon::BlitzWeapon()
{

}

BlitzWeapon::~BlitzWeapon()
{

}

void BlitzWeapon::Initialise()
{
	WeaponBase::Initialise();
	m_barellOffsetX = 50;
	m_barrelOffsetY = 5;

	m_ammo = 100;
	m_fireRate = 7.0f;

	GameDataManager* pGameDataManager = C_SysContext::Get<GameDataManager>();
	SpritesheetDef* pSpriteSheetDef;
	pSpriteSheetDef = pGameDataManager->GetSpritesheetDef("sprites/weapons/spr_blitz.xml");
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(0, pSpriteSheetDef, "spr_blitz", 10, false);
	m_AnimatedSprite.SetCurrentAnimation(0);
	m_AnimatedSprite.Pause();
}

void BlitzWeapon::Update()
{
	WeaponBase::Update();
}

void BlitzWeapon::Reload()
{

}

void BlitzWeapon::Fire()
{
	//generate bullet
	Bullet* bullet = new Bullet();
	bullet->Initialise();

	if (!canFire())
		return;

	WeaponBase::Fire();

	//create a bullet spawn offset
	sf::Vector2f bulletSpawnOffset(sf::Vector2i(m_barellOffsetX, m_barrelOffsetY));

	//rotate it to face the correct direction
	sf::Transform transform;
	transform.rotate(m_AnimatedSprite.getRotation());
	transform.scale(m_AnimatedSprite.getScale());
	bulletSpawnOffset = transform.transformPoint(bulletSpawnOffset);

	bullet->SetPosition(m_AnimatedSprite.getPosition().x + bulletSpawnOffset.x + 5,
		m_AnimatedSprite.getPosition().y + bulletSpawnOffset.y - 35);
	bullet->SetRotation(m_AnimatedSprite.getRotation());
	bullet->SetScale(m_AnimatedSprite.getScale().x, m_AnimatedSprite.getScale().y);

	//Adding the bullet to the gameState
	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
	GameState* pGameState = pGameStateManager->GetCurrentGameState();
	if (pGameState)
		pGameState->AddGameObject(bullet);

}
