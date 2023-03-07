#include "Camera.h"

#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/Renderer/WindowManager.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/System/GameState/GameState.h"
#include "../../Engine/Core/GameObject.h"

Camera::Camera()
{
	m_followPlayer = false;
}

Camera::~Camera()
{

}

void Camera::Initialise()
{
	WindowManager* m_WindowManager = C_SysContext::Get<WindowManager>();
	this->m_view = m_WindowManager->GetWindow()->getDefaultView();
}

void Camera::Update()
{
	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
	GameState* m_currentGameState = pGameStateManager->GetCurrentGameState();
	GameObject* m_player = m_currentGameState->GetPlayer();

	if (m_player)
	{
		this->SetPosition(m_player->GetPosition());
	}
	if (this->m_followPlayer)
	{
		this->SetCamera();
	}
}

sf::Vector2f Camera::GetPosition()
{
	return m_view.getCenter();
}

void Camera::SetPosition(float px, float py)
{
	m_view.setCenter(px, py);
}

void Camera::SetPosition(sf::Vector2f ppos)
{
	m_view.setCenter(ppos);
}

void Camera::GetPosition(float& px, float& py)
{
	px = m_view.getCenter().x;
	py = m_view.getCenter().y;
}

void Camera::SetCamera()
{
	m_followPlayer = true;
	WindowManager* m_windowManager = C_SysContext::Get<WindowManager>();
	m_windowManager->GetWindow()->setView(m_view);
}


