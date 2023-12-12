#include "blockdoku.h"
#include "cell.h"
#include "block.h"

Blockdoku::Blockdoku()
{
    grid = std::vector<Cell*>();

    for (size_t y = 0; y < 9; y++) {
        for (size_t x = 0; x < 9; x++) {
            Cell* c = new Cell();
            c->position = Vector2(x*64+100, y*64+100);
            this->addChild(c);
            grid.push_back(c);
        }
        
    }
    
}

Blockdoku::~Blockdoku()
{
    
}

void Blockdoku::update(float deltaTime)
{

}