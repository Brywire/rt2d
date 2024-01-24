// block.cpp

#include "block.h"

Block::Block()
	: Entity()
{
	//this->addSprite("assets/blockSprite.tga");
	//this->sprite()->color = BLUE;
	this->position = Vector2(700, 292);
}

void Block::spawnBlock()
{
	//TODO draw cells from the middle
	grid = std::vector<Cell *>();

	for (size_t y = 0; y < 3; y++)
	{
		for (size_t x = 0; x < 3; x++)
		{
			Cell *c;

			c = new Cell(WHITE);

			c->position = Vector2(x * 64, y * 64);
			this->addChild(c);
			grid.push_back(c);
			
			c->gridPos.x = x;
            c->gridPos.y = y;
		}
	}

}

Block::~Block()
{

}

void Block::update(float deltaTime)
{

}