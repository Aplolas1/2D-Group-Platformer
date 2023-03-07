#pragma once

#include <SFML\Graphics.hpp>
#include "../../Engine/Core/GameObject.h"
#include "../GameData/SpritesheetDef.h"
#include "../../Engine/UI/Text.h"
#include "../../Engine/System/GameState/GameState.h"
#include "../../Engine/Physics/Collider2D.h"
#include "Player.h"
#include <fstream>


class TileMap : public sf::Drawable, public sf::Transformable, public GameObject, public Player
{

protected:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:

	//zero parameter constructor
	TileMap();

	//Destructor
	~TileMap() override;

	void Initialise() override;
	void Update() override;

	void GetPosition(float& px, float& py) override;
	sf::Vector2f GetPosition() override;
	void SetPosition(float px, float py) override;
	void SetPosition(sf::Vector2f ppos) override;

	//spritesheet driven tilemap
	bool LoadFromSpritesheetDef(SpritesheetDef* pSpritesheetDef, const int* tiles, unsigned int width, unsigned int height);

	void LoadFromFile(std::string level, std::string background);

	void onCollision(Collider2D* pCollider2D);
	Collider2D CollidesWith(TileMap* pTileMap);

	int TileIndexAtPosition(int posx, int posy, std::string background);

	//int GetTileValue(std::string background);

private:

	sf::VertexArray m_Vertices;
	sf::Texture* m_pTileSet;
	const int t_mapW = 16; // width of the map
	const int t_mapH = 16; // height of the map
	std::string background1 = "backgrounds/bg_desert.xml";
	std::string level1 = "levels/BackGroundMap.txt";
	std::string background2 = "backgrounds/bg_ship.xml";
	std::string level2 = "levels/BackGroundMap2.txt";
	int tileIndex, tileValue;

};

