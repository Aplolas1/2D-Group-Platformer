#include "GameObjectWithSprite.h"
#include "../GameData/GameDataManager.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/GameState/GameState.h"
#include "../../Engine/System/GameState/GameStateManager.h"

#include "../../Game/GameObjects/Bullet.h"

GameObjectWithSprite::GameObjectWithSprite()
{
	
}

GameObjectWithSprite::~GameObjectWithSprite()
{
	
}

void GameObjectWithSprite::Initialise()
{
	m_sprite.Initialise("sprites/spr_hud_face_raff_0.png");
	//sf::FloatRect m_CollisionRect = m_sprite.getGlobalBounds();
}

void GameObjectWithSprite::Update()
{
	sf::FloatRect m_CollisionRect = m_sprite.getGlobalBounds();
	/*m_sprite.move(8, 8);

	m_sprite.rotate(90);

	m_sprite.scale(1, 1);*/
}

void GameObjectWithSprite::GetPosition(float& px, float& py)
{
	m_sprite.getPosition().x;
	m_sprite.getPosition().y;
}

sf::Vector2f GameObjectWithSprite::GetPosition()
{
	return m_sprite.getPosition();
}

void GameObjectWithSprite::SetPosition(float px, float py)
{
	m_sprite.setPosition(px, py);
}

void GameObjectWithSprite::SetPosition(sf::Vector2f ppos)
{
	m_sprite.setPosition(ppos);
}

void GameObjectWithSprite::move(float offsetX, float offsetY)
{
	sf::Vector2f ppos = m_sprite.getPosition();
	m_sprite.setPosition(ppos.x + offsetX, ppos.y + offsetY);
}

void GameObjectWithSprite::rotate(float angle)
{
	m_sprite.setRotation(m_sprite.getRotation() + angle);
}

void GameObjectWithSprite::scale(float factorX, float factorY)
{
	sf::Vector2f scale = m_sprite.getScale();
	m_sprite.setScale(scale.x * factorX, scale.y * factorY);
}

void GameObjectWithSprite::onCollision(Collider2D* pCollider2D)
{
	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
	GameState* pCurrentGameState = pGameStateManager->GetCurrentGameState();

	if(dynamic_cast<Bullet*>(pCollider2D))
		pCurrentGameState->RemoveGameObject(this);
}
