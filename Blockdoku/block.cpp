// block.cpp

#include "block.h"

Block::Block()
	: Entity()
{
	this->addSprite("assets/blockSprite.tga");
	this->sprite()->color = BLUE;
}

void Block::spawnBlock()
{

	grid = std::vector<Cell *>();

	for (size_t y = 0; y < 3; y++)
	{
		for (size_t x = 0; x < 3; x++)
		{
			Cell *c;

			c = new Cell(WHITE);

			c->position = Vector2(x * 64 + 0, y * 64 + 0);
			this->addChild(c);
			grid.push_back(c);
		}
	}

}

Block::~Block()
{

}

void Block::update(float deltaTime)
{

}