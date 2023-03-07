#include "WeaponBase.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/Renderer/FrameTimer.h"
#include "../../Game/GameData/GameDataManager.h"
#include "../../Engine/System/GameState/GameState.h"
#include "../../Engine/System/GameState/GameStateManager.h"


WeaponBase::WeaponBase()
{

}

void WeaponBase::GetPosition(float& px, float& py)
{
	px = m_AnimatedSprite.getPosition().x;
	py = m_AnimatedSprite.getPosition().y;
}

sf::Vector2f WeaponBase::GetPosition()
{
	return m_AnimatedSprite.getPosition();
}

void WeaponBase::SetPosition(sf::Vector2f ppos)
{
	m_AnimatedSprite.setPosition(ppos);
}

void WeaponBase::Initialise()
{
	
}

void WeaponBase::Reload()
{

}

void WeaponBase::Update()
{
	m_AnimatedSprite.Animate();
	if (m_AnimatedSprite.AnimationFinished())
	{
		m_AnimatedSprite.SetCurrentAnimation(0);
		m_AnimatedSprite.Pause();
	}
	if (m_fireTimer >= 0.0f)
	{
		FrameTimer* pFrameTimer = C_SysContext::Get<FrameTimer>();
		m_fireTimer -= pFrameTimer->DeltaTime();
	}
}

void WeaponBase::Fire()
{
	if (m_fireRate > 0.0f)
	{
		m_fireTimer = 1.0f / m_fireRate;
	}
}

bool WeaponBase::canFire()
{
	if (m_ammo > 0)
	{
		return m_fireTimer <= 0.0f;
	}
	return false;
}

void WeaponBase::SetPosition(float px, float py)
{
	m_AnimatedSprite.setPosition(px, py);
}

void WeaponBase::SetScale(float scaleX, float scaleY)
{

	m_AnimatedSprite.setScale(scaleX, scaleY);
}

void WeaponBase::SetRotation(float angle)
{
	m_AnimatedSprite.setRotation(angle);
}
