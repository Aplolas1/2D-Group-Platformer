#include "Collectible.h"

#include "../GameData/GameDataManager.h"
#include "../GameData/SpritesheetDef.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/System/GameState/GameState.h"


Collectible::Collectible()
{
}

Collectible::~Collectible()
{
}

void Collectible::Initialise()
{
    GameDataManager* pGameDataManager = C_SysContext::Get<GameDataManager>();

    SpritesheetDef* pSpriteSheetDef = pGameDataManager->GetSpritesheetDef("sprites/characters/spr_buckler.xml");

    m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_dash, pSpriteSheetDef, "spr_buckler_dash", 10, true);
    m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_hit, pSpriteSheetDef, "spr_buckler_hit", 10, true);
    m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_idle, pSpriteSheetDef, "spr_buckler_idle", 10, true);
    m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_melee, pSpriteSheetDef, "spr_buckler_melee", 10, true);
    m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_sprint, pSpriteSheetDef, "spr_buckler_sprint", 10, true);
    m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_walk, pSpriteSheetDef, "spr_buckler_walk", 10, true);

    m_AnimatedSprite.setPosition(1200, 800);
    m_AnimatedSprite.SetCurrentAnimation(E_AnimationState_idle);
    Update();
}

void Collectible::Update()
{
    m_AnimatedSprite.Animate();
    m_coinMoving == false;

    switch (m_AnimatedSprite.GetCurrentAnimation())
    {
    case E_AnimationState_idle:
    {
        if (m_coinMoving == true)
        {
            m_AnimatedSprite.SetCurrentAnimation(E_AnimationState_walk);
        }
    }
    break;

    case E_AnimationState_walk:
    {
        if (m_coinMoving == false)
        {
            m_AnimatedSprite.SetCurrentAnimation(E_AnimationState_idle);
        }
    }
    break;
    }
}

void Collectible::GetPosition(float& px, float& py)
{
    m_AnimatedSprite.getPosition().x;
    m_AnimatedSprite.getPosition().y;
}

sf::Vector2f Collectible::GetPosition()
{
    return m_AnimatedSprite.getPosition();
}

void Collectible::SetPosition(float px, float py)
{
    m_AnimatedSprite.setPosition(px, py);

}

void Collectible::SetPosition(sf::Vector2f ppos)
{
    m_AnimatedSprite.setPosition(ppos);
}

void Collectible::onCollision(Collider2D* pCollider2D)
{
    GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
    GameState* pCurrentGameState = pGameStateManager->GetCurrentGameState();

    pCurrentGameState->RemoveGameObject(this);
}
