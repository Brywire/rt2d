#include "blockdoku.h"
#include <rt2d/timer.h>

Blockdoku::Blockdoku()
{
    
    grid = std::vector<Cell*>();

    for (size_t y = 0; y < 9; y++) {
        for (size_t x = 0; x < 9; x++) {
            Cell* c = new Cell();
            c->position = Vector2(x*64+100, y*64+100);
            this->addChild(c);
            grid.push_back(c);
            timer = new Timer;
        }
        
    }

    
    
}

Blockdoku::~Blockdoku()
{
    
}

void Blockdoku::update(float deltaTime)
{
    //Getting the mouse input on click
    if (input()->getMouseDown(0))
    {
        //Getting mouse position and converting into grid coordinates
        int mouseX = input()->getMouseX();
        int mouseY = input()->getMouseY();

        int gridX = (mouseX - 100 + 32) / 64;
        int gridY = (mouseY - 100 + 32) / 64;
        
        //Making sure coordinates are on the grid
        if (gridX >= 0 && gridX < 9 && gridY >= 0 && gridY < 9)
        {
            //Get the clicked cell
            Cell* clickedCell = grid[gridY * 9 + gridX];

            //Change the color to blue
            clickedCell->sprite()->color = BLUE;

            //Make the cell busy
            clickedCell->isBusy = !clickedCell->isBusy;

            //Call the solve function after a click
            
            //checkThreeByThree
        }
    }
    checkHorizontalLines();
    checkVerticalLines();
}

void Blockdoku::checkHorizontalLines()
{
    // Check for busy horizontal lines
    for (size_t y = 0; y < 9; y++)
    {
        bool isLineBusy = true;

        for (size_t x = 0; x < 9; x++)
        {
            Cell* currentCell = grid[y * 9 + x];

            // Check if the cell is not busy
            if (!currentCell->isBusy)
            {
                isLineBusy = false;
                break;  // Break the loop if a non-busy cell is found
            }
        }
        
        // If the entire line is busy, set the color back to white
        if (isLineBusy)
        {
            for (size_t x = 0; x < 9; x++)
            {
                grid[y * 9 + x]->sprite()->color = WHITE;
                grid[y * 9 + x]->isBusy = false;
            }
        }
    }
}

void Blockdoku::checkVerticalLines()
{
    // Check for busy vertical lines
    for (size_t x = 0; x < 9; x++)
    {
        bool isLineBusy = true;

        for (size_t y = 0; y < 9; y++)
        {
            Cell* currentCell = grid[y * 9 + x];

            // Check if the cell is not busy
            if (!currentCell->isBusy)
            {
                isLineBusy = false;
                break;  // Break the loop if a non-busy cell is found
            }
        }

        // If the entire line is busy, set the color back to white
        if (isLineBusy)
        {
            for (size_t y = 0; y < 9; y++)
            {
                grid[y * 9 + x]->sprite()->color = WHITE;
                grid[y * 9 + x]->isBusy = false;
            }
        }
    }
}
