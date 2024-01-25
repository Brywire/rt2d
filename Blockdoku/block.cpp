// block.cpp

#include "block.h"

Block::Block()
	: Entity()
{
	//this->addSprite("assets/blockSprite.tga");
	//this->sprite()->color = BLUE;
	this->position = Vector2(700, 292);
	this->initialBlockPosition = position;
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

void Block::Boundry()
{
    if (this->position.x > SWIDTH + 64 || 
	this->position.y > SHEIGHT + 64 || 
	this->position.x < -64 || 
	this->position.y < -64)
    {
    position = initialBlockPosition;
    }
}