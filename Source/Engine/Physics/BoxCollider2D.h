#ifndef _BOX_COLLIDER_2D
#define _BOX_COLLIDER_2D

#include "Collider2D.h"
#include <SFML/Graphics.hpp>
//#include "../../Game/GameObjects/TileMap.h"

class BoxCollider2D : public Collider2D
{
public:
	BoxCollider2D();
	virtual ~BoxCollider2D();

	virtual bool CollidesWith(Collider2D* pCollider2D);
	virtual bool CollidesWith(BoxCollider2D* pBoxCollider2D);
	virtual bool CollidesWith(CircleCollider2D* pCircleCollider2D);
//	virtual bool CollidesWith(TileMap* pTileMap);
//protected:

	sf::FloatRect m_CollisionRect;
};

#endif

