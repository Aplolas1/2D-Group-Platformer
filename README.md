# 2D-Group-Platformer
2D platform prototype made by me and a few freinds.

This Programmer is ran using The extenstion of SFML.
and using Visual Studio as our base IDE.

When making this platformer we divided the roles of creating the platformer up with each other, 
i was making the stack that the game would run off to store the game scenes and make the game run with a main menu and title screen 
as well as being able to leave the game if the user wants to do so
This is how the program looks and the various stages that the game has
![2DTitle](https://user-images.githubusercontent.com/127206949/223427055-2fa09063-09c4-4386-b21e-80779d7bfe8d.PNG)
![image](https://user-images.githubusercontent.com/127206949/223427227-904609ff-cbd3-4906-8d57-9152d7711175.png)
I used a simple stack solution to configir the scenes and the code i have been using to make such things happens looks like this
```void GameStateManager::Update()
{
	for (std::vector<GameState*>::reverse_iterator iter = m_GameStates.rbegin(); iter != m_GameStates.rend(); ++iter)
	{
		(*iter)->Update();

		if ((*iter)->SwallowUpdate())
			break;
	}

	if (m_bPopGameState)
	{
		PopGameState();
	}

	//process the queued game states
	for (std::vector<GameState*>::iterator iter = m_GameStateQueue.begin(); iter != m_GameStateQueue.end(); ++iter)
	{
		PushGameState(*iter);
	}
	m_GameStateQueue.clear();
}

void GameStateManager::PushGameState(GameState* pGameState)
{
	if (!pGameState)
		return;

	RenderManager* pRenderManager = C_SysContext::Get<RenderManager>();
	pRenderManager->PushRenderGroup();

	m_GameStates.push_back(pGameState);
	m_GameStates.back()->Initialise();
}

void GameStateManager::PopGameState()
{
	RenderManager* pRenderManager = C_SysContext::Get<RenderManager>();
	pRenderManager->PopRenderGroup();

	if (m_GameStates.size() > 0)
	{
		SAFE_DELETE_PTR(m_GameStates.back());
		m_GameStates.pop_back();
	}

	m_bPopGameState = false;
}

void GameStateManager::QueueGameState(GameState* pGameState)
{
	if (!pGameState)
		return;

	if (m_GameStates.size() == 0)
	{
		PushGameState(pGameState);
	}
	else
	{
		m_GameStateQueue.push_back(pGameState);
	}
}

void GameStateManager::QueuePop()
{
	m_bPopGameState = true;
}
```
These functions are fairly self explanitary so i wont go into much detail but this is the basic set of functions i used to initialise a queue using the QueueGameState Function
the reason i used a stack method like this is because i feel like it can be read easier than some other ways, it may not be the most efficient but i also wanted the other
programmers to understand what actions it is undertaking. the stack functions in a FILO setup making sure that the main menu and title screen can always be accessed but the other scene need to be popped to be able to do so.

![image](https://user-images.githubusercontent.com/127206949/223427331-20a12e5c-7341-46d3-8b56-63c1f411e072.png)

This is what the main game state looked like once we had finished off the prototype with a generated map and a player object, i was also in charge of creating a somewhat basic hud,
to do this as you can see i have shown the hp of the charcter on the left of him and also what current weapon the character has equipped.


As you can see there is not a lot going on but it has the basic properties of a prototype which we were looking for.
