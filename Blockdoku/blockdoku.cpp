#include "blockdoku.h"
#include <rt2d/timer.h>

Blockdoku::Blockdoku()
{
    /*
    - TODO: Live score count (text)
    - TODO: Add to score count (depending on how many cells are busy)
    - TODO: Make tetris blocks (collection of cells, needs to be draggable)
    - TODO: Make blocks cells busy on placement (replacing current clicksystem)
    - TODO: Knows when you can't place a block > game over > show score/highscore
    */

    grid = std::vector<Cell*>();

    for (size_t y = 0; y < 9; y++) {
        for (size_t x = 0; x < 9; x++) 
        {
            Cell* c;
            if (
                ((x >= 3 && x < 6) && (y < 3 || y >= 6))
                || ((x < 3 || x >= 6) && (y >= 3 && y < 6))
            ) 
            {
                c = new Cell(GRAY);
            } 
            else 
            {
                c = new Cell(WHITE);
            }   
        
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
    if (input()->getMouseDown(0) && !isAnimPlaying)
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
            clickedCell->isBusy = true;
        }
    }
    
    std::vector<std::vector<size_t>> busyHorizontal{checkHorizontalLines()};
    std::vector<std::vector<size_t>> busyVertical{checkVerticalLines()};
    std::vector<std::vector<size_t>> busyThrees{checkThrees()};

    if(!isAnimPlaying && (busyHorizontal.size() || busyVertical.size() || busyThrees.size()))
    {
        timer->start();
        isAnimPlaying = true;
        solveLines(busyHorizontal);
        solveLines(busyVertical);
        solveThrees(busyThrees);
    }
    

    if(timer->seconds()>= 1)
    {
        solveLines(busyHorizontal, true);
        solveLines(busyVertical, true);
        solveThrees(busyThrees, true);
        timer->stop();
        isAnimPlaying = false;
    }

    
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

void Blockdoku::solveLines(std::vector<std::vector<size_t>> busyCells, const bool endTransition)
{
    for (const std::vector<size_t> & busyCell:busyCells)
    {
        if (endTransition)
        {
            grid[busyCell[1] * 9 + busyCell[0]]->sprite()->color =  grid[busyCell[1] * 9 + busyCell[0]]->defaultColor;
            grid[busyCell[1] * 9 + busyCell[0]]->isBusy = false;
        }
        else
        {
            grid[busyCell[1] * 9 + busyCell[0]]->sprite()->color = GREEN;
        }
    }
}

void Blockdoku::solveThrees(std::vector<std::vector<size_t>> busyCells, const bool endTransition)
{
    for (const std::vector<size_t> & busyCell:busyCells)
    {
        for (size_t y{busyCell[1]}; y < busyCell[1] + 3; y++) 
        {
            // Iterate rows in sets of 3.
            for (size_t x{busyCell[0]}; x < busyCell[0] + 3; x++) 
            {
                if (endTransition)
                {
                    grid[y * 9 + x]->sprite()->color = grid[y * 9 + x]->defaultColor;
                    grid[y * 9 + x]->isBusy = false;
                }
                else
                {
                   grid[y * 9 + x]->sprite()->color = GREEN; 
                }
            }
        }
    }
}

std::vector<std::vector<size_t>> Blockdoku::checkThrees() 
{
  std::vector<std::vector<size_t>> busyCells{};

  // Iterate columns in sets of 3.
  for (size_t y{0}; y < 9; y += 3) {
    // Iterate rows in sets of 3.
    for (size_t x{0}; x < 9; x += 3) {
      bool isLineBusy{true};

      // Iterate columns within the current set of 3.
      for (size_t currentCol{y}; currentCol < y + 3; ++currentCol) 
      {
        // Iterate rows within the current set of 3.
        for (size_t currentRow{x}; currentRow < x + 3; ++currentRow) 
        {
          Cell* currentCell = grid[currentCol * 9 + currentRow];

            // Check if the cell is not busy
            if (!currentCell->isBusy)
            {
                isLineBusy = false;
                break;  // Break the loop if a non-busy cell is found
            }
        }

        if (!isLineBusy) break;
      }
      
      if (isLineBusy) {
        busyCells.push_back(std::vector<size_t>{x, y});
      }
    }
  }
  
  return busyCells;
}