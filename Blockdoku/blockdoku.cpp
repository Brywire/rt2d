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
    //Getting the mouse input on click
    if (input()->getMouse(0))
        {
            // Get the mouse position
            int mouseX = input()->getMouseX();
            int mouseY = input()->getMouseY();

            //Convert mouse position to grid coordinates
            int gridX = (mouseX - 100) / 64;
            int gridY = (mouseY - 100) / 64;

            //Print debug information
            std::cout << "Mouse Position: (" << mouseX << ", " << mouseY << ") ";
            std::cout << "Grid Coordinates: (" << gridX << ", " << gridY << ")" << std::endl;

            //Ensure the coordinates are within the valid range
            if (gridX >= 0 && gridX < 9 && gridY >= 0 && gridY < 9)
            {
                //Get the clicked cell
                Cell* clickedCell = grid[gridY * 9 + gridX];

                //Change the color to blue
                clickedCell->sprite()->color = BLUE;

                //Toggle the isBusy bool value
                clickedCell->isBusy = !clickedCell->isBusy;
            } 
        }
}