#include "Bullet.h"

#include "../../Engine/Renderer/FrameTimer.h"
#include "../GameData/GameDataManager.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/GameState/GameState.h"
#include "../../Engine/System/GameState/GameStateManager.h"

Bullet::Bullet()
{
	
}

Bullet::~Bullet()
{
	
}

void Bullet::Initialise()
{
	GameDataManager* pGameDataManager = C_SysContext::Get<GameDataManager>();
	SpritesheetDef* pSpriteSheetDef;
	pSpriteSheetDef = pGameDataManager->GetSpritesheetDef("sprites/bullets/spr_bullet.xml");
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(0, pSpriteSheetDef, "spr_bullet", 24, false);
	m_AnimatedSprite.SetCurrentAnimation(0);

	m_velocity = 1500.0f;
	m_lifetime = 1.0f;

	m_collisionRect = m_AnimatedSprite.getGlobalBounds();
}

void Bullet::Update()
{
	m_AnimatedSprite.Animate();

	//don't move until we are passed the flash
	if (m_AnimatedSprite.GetCurrentFrame() == 0)
		return;

	//Grab the frame timer
	FrameTimer* pFrameTimer = C_SysContext::Get<FrameTimer>();

	//create a forward vector
	sf::Vector2f movement(1.0f, 0.0f);

	//modify magnitude based on velocity
	movement *= (m_velocity * pFrameTimer->DeltaTime());

	//rotate and scale it to face the correct direction
	sf::Transform transform;
	transform.rotate(m_AnimatedSprite.getRotation());
	transform.scale(m_AnimatedSprite.getScale());
	movement = transform.transformPoint(movement);

	//tarnsform the bullet position
	m_AnimatedSprite.move(movement);

	m_lifetime -= pFrameTimer->DeltaTime();
	if (m_lifetime <= 0.0f)
	{
		GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
		GameState* pGameState = pGameStateManager->GetCurrentGameState();
		//remove from the current game state
		if (pGameState)
			pGameState->RemoveGameObject(this);
	}

	m_collisionRect = m_AnimatedSprite.getGlobalBounds();
}

void Bullet::GetPosition(float& px, float& py)
{
	px = m_AnimatedSprite.getPosition().x;
	py = m_AnimatedSprite.getPosition().y;
}

sf::Vector2f Bullet::GetPosition()
{
	return m_AnimatedSprite.getPosition();
}

void Bullet::SetPosition(float px, float py)
{
	m_AnimatedSprite.setPosition(px, py);
}

void Bullet::SetPosition(sf::Vector2f ppos)
{
	m_AnimatedSprite.setPosition(ppos);
}

void Bullet::SetRotation(float angle)
{
	m_AnimatedSprite.setRotation(angle);
}

void Bullet::SetScale(float scaleX, float scaleY)
{
	m_AnimatedSprite.setScale(scaleX, scaleY);
}

void Bullet::onCollision(Collider2D* pCollider2D)
{
	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
	GameState* pCurrentGameState = pGameStateManager->GetCurrentGameState();

	pCurrentGameState->RemoveGameObject(this);
}


