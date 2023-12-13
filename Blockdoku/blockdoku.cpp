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
    if (input()->getMouseDown(0) && timer->seconds()== 0)
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
            
        
        }
    }
    
    std::vector<std::vector<size_t>> busyHorizontal{checkHorizontalLines()};
    std::vector<std::vector<size_t>> busyVertical{checkVerticalLines()};
    //checkThreeByThree

    if(timer->seconds()== 0 && (busyHorizontal.size() || busyVertical.size()))
    {
        timer->start();
        transitionSolveLines(busyHorizontal);
        transitionSolveLines(busyVertical);
    }
    

    if(timer->seconds()>= 1)
    {
        solveLines(busyHorizontal);
        solveLines(busyVertical);
        timer->stop();
    }
    //solveThreeByThree
}

std::vector<std::vector<size_t>> Blockdoku::checkHorizontalLines()
{
    std::vector<std::vector<size_t>> busyCells{};

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
        
        //If line is busy, add to Vector
        if (isLineBusy)
        {
            for (size_t x = 0; x < 9; x++)
            {
                busyCells.push_back(std::vector<size_t>{x,y});
            }
        }
    }

    return busyCells;
}

std::vector<std::vector<size_t>> Blockdoku::checkVerticalLines()
{
    std::vector<std::vector<size_t>> busyCells{};
    
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
                busyCells.push_back(std::vector<size_t>{x,y});
            }
            
        }
    }

    return busyCells;
}

void Blockdoku::solveLines(std::vector<std::vector<size_t>> busyCells)
{
    for (const std::vector<size_t> & busyCell:busyCells)
    {
        grid[busyCell[1] * 9 + busyCell[0]]->sprite()->color = WHITE;
        grid[busyCell[1] * 9 + busyCell[0]]->isBusy = false;
    }
}

void Blockdoku::transitionSolveLines(std::vector<std::vector<size_t>> busyCells)
{
    for (const std::vector<size_t> & busyCell:busyCells)
    {
        grid[busyCell[1] * 9 + busyCell[0]]->sprite()->color = GREEN;
    }
}