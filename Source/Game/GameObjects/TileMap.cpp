#include "TileMap.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/Assets/AssetManager.h"
#include "../../Engine/Renderer/RenderManager.h"
#include "../GameData/GameDataManager.h"
#include <iostream>
#include "../../Engine/System/GameState/GameStateManager.h"


/**
 * \brief Constructor for this class.
 * Uses Initialiser Lists Constructors as standard
 */
TileMap::TileMap()
{

}

/**
 * \brief Destructor for our Text Game Object
 * No dynamic memory is used in this class currently.
 */
TileMap::~TileMap()
{

	C_SysContext::Get<RenderManager>()->RemoveRenderObject(this);

}








/**
 * \brief Get the Position as separate variables via References
 * \param  px - the current x position
 * \param  py - the current y position
 */
void TileMap::GetPosition(float& px, float& py)
{
	px = this->GetPosition().x;

	py = this->GetPosition().y;

}

/**
 * \brief Get the Position as a 2D Vector via Return
 * \return the current position as a 2D Vector
 */
sf::Vector2f TileMap::GetPosition()
{
	return this->GetPosition();
}


bool TileMap::LoadFromSpritesheetDef(SpritesheetDef* pSpritesheetDef, const int* tiles, unsigned int width, unsigned int height)
{

	if (!pSpritesheetDef)
		return false;

	auto* pAssetManager = C_SysContext::Get<AssetManager>();
	m_pTileSet = &pAssetManager->GetTexture(pSpritesheetDef->m_Filename.c_str());

	std::vector<sf::IntRect> frames;
	for (auto& m_pSpriteDef : pSpritesheetDef->m_pSpriteDefs)
	{
		sf::IntRect rect(m_pSpriteDef.m_PosX, m_pSpriteDef.m_PosY, m_pSpriteDef.m_Width, m_pSpriteDef.m_Height);
		frames.push_back(rect);
	}

	int numTiles = 0;

	for (unsigned int i = 0; i < width * height; i++)
	{

		const unsigned int tileNumber = tiles[i];
		if (tileNumber < 0 || tileNumber >= frames.size())
			continue;

		numTiles++;

	}

	m_Vertices.setPrimitiveType(sf::Quads);
	m_Vertices.resize(numTiles * 4);


	int quadNum = 0;
	for (unsigned int i = 0; i < width; ++i)
	{

		for (unsigned int j = 0; j < height; ++j)
		{

			//get current tile number
			const unsigned int tileNo = tiles[i + j * width];

			//if tile number is outside the range of valid tiles, leave it blank
			if (tileNo < 0 || tileNo >= frames.size())
				continue;

			const int tu1 = frames[tileNo].left;
			const int tv1 = frames[tileNo].top;
			const int tu2 = tu1 + frames[tileNo].width;
			const int tv2 = tv1 + frames[tileNo].height;

			const int tstartvertindex = quadNum * 4;
			sf::Vertex* quad = &m_Vertices[tstartvertindex];

			//define the 4 corners (geometric position)
			quad[0].position = sf::Vector2f(sf::Vector2i(i * frames[tileNo].width, j * frames[tileNo].height));
			quad[1].position = sf::Vector2f(sf::Vector2i((i + 1) * frames[tileNo].width, j * frames[tileNo].height));
			quad[2].position = sf::Vector2f(sf::Vector2i((i + 1) * frames[tileNo].width, (j + 1) * frames[tileNo].height));
			quad[3].position = sf::Vector2f(sf::Vector2i(i * frames[tileNo].width, (j + 1) * frames[tileNo].height));

			//quad[0].position = sf::Vector2f(sf::Vector2i(i, j));
			//quad[1].position = sf::Vector2f(sf::Vector2i(i + 1, j));
			//quad[2].position = sf::Vector2f(sf::Vector2i(i+1, j+1));
			//quad[3].position = sf::Vector2f(sf::Vector2i(i, j+1));

			//define the 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(sf::Vector2i(tu1, tv1));
			quad[1].texCoords = sf::Vector2f(sf::Vector2i(tu2, tv1));
			quad[2].texCoords = sf::Vector2f(sf::Vector2i(tu2, tv2));
			quad[3].texCoords = sf::Vector2f(sf::Vector2i(tu1, tv2));

			//add to the total number of tiles
			quadNum++;

		}



	}

	//add this game object to the render manager (object is subclass of drawable)
	C_SysContext::Get<RenderManager>()->AddRenderObject(this);

	return true;
}

/**
 * \brief Update the position the tilesheet is rendered at
 * \param px - the x position to move to
 * \param py - the y position to move to
 */
void TileMap::SetPosition(float px, float py)
{
	this->SetPosition(px, py);
}

/**
 * \brief Update the position the tilesheet is rendered at
 * \param ppos - the position to move to
 */
void TileMap::SetPosition(sf::Vector2f ppos)
{
	this->SetPosition(ppos);
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	//apply the transform (to position the tile map)
	states.transform *= getTransform();

	//apply the tile set texture (to the shader)
	states.texture = m_pTileSet;

	//draw the vertex array
	target.draw(m_Vertices, states);
}

void TileMap::Initialise()
{
	//Tile map is initialized when it's created
}

void TileMap::Update()
{
	//Tile map is static so it has no need for updating.
}

void TileMap::LoadFromFile(std::string level, std::string background)
{





	auto* pGDM = C_SysContext::Get<GameDataManager>();
	SpritesheetDef* pSSDef = pGDM->GetSpritesheetDef(level.c_str());
	//read the file and store the value into our map
	std::ifstream file{};
	file.open(background.c_str());
	if (file.is_open())
	{
		int* pMap = new int[t_mapW * t_mapH];
		int tileinput;
		for (int i = 0; i < t_mapW * t_mapH; i++)
		{
			file >> tileinput;
			pMap[i] = tileinput;
		}
		file.close();
		LoadFromSpritesheetDef(pSSDef, pMap, t_mapW, t_mapH);
		delete[] pMap;
	}
	else
	{
		char message[1024];
		strerror_s(message, 1024, errno);
		std::cerr << "Error: " << message;
	}

}


void TileMap::onCollision(Collider2D* pCollider2D)
{
	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
	GameState* pCurrentGameState = pGameStateManager->GetCurrentGameState();

	pCurrentGameState->RemoveGameObject(this);
}

int TileMap::TileIndexAtPosition(int posx, int posy, std::string background)
{

	float playerPosX = posx;
	float playerPosY = posy;

	int playerTilePosX = floor(playerPosX / 50);
	int playerTilePosY = floor(playerPosY / 64);

	tileIndex = 16 * (playerTilePosY - 1) + playerTilePosX;

	std::ifstream file{};
	file.open(background.c_str());
	if (file.is_open())
	{
		int* pMap = new int[t_mapW * t_mapH];
		int tileinput;
		for (int i = 0; i < t_mapW * t_mapH; i++)
		{
			file >> tileinput;
			pMap[i] = tileinput;

		}

		file.close();

		tileValue = pMap[tileIndex];

	}

	return tileValue;
}

//int TileMap::GetTileValue(std::string background)
//{
//
//
//
//}