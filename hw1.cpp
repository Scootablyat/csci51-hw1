#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/*
    PLAYER POSITION IS DENOTED BY 'O' IN THE GRID
    ENEMY'S POSITION IS DENOTED BY 'X IN THE GRID

    Settings.txt file:
    grid_size - determines size of the grid, input any number to display a grid of that size
    p_x and p_y - determines player x and y position respectively (cannot be larger than grid_size - 1)
    e_x and e_y - determines enemy x and y position respectively (cannot be larger than grid_size - 1)
    
*/

struct player
{
    int x;
    int y;
};

struct enemy
{
    int x;
    int y;
};

struct cell
{
    bool isOccupied;
    std::string content;
    int x;
    int y;
};

int getSettings(std::string setting)
{
    int grid_size;
    int p_x;
    int p_y;
    int e_x;
    int e_y;
    std::fstream settingsFile;
    settingsFile.open("settings.txt", std::ios::in);
    std::string line;

    if (settingsFile.is_open())
    {
        while (std::getline(settingsFile, line))
        {
            // std::cout << line << std::endl;
            if (line.find("grid_size = ") == 0 && setting == "gridSize")
            {
                return grid_size = std::stoi(line.erase(0, 11));
            }
            if (line.find("p_x = ") == 0 && setting == "playerPos-x")
            {
                return p_x = std::stoi(line.erase(0, 6));
            }
            if (line.find("p_y = ") == 0 && setting == "playerPos-y")
            {
                return p_y = std::stoi(line.erase(0, 6));
            }
            if (line.find("e_x = ") == 0 && setting == "enemyPos-x")
            {
                return e_x = std::stoi(line.erase(0, 6));
            }
            if (line.find("e_y = ") == 0 && setting == "enemyPos-y")
            {
                return e_y = std::stoi(line.erase(0, 6));
            }
        }
    }
    return 0;
}

std::vector<std::vector<cell>> createGrid(int grid_size, player p, enemy e)
{
    std::vector<std::vector<cell>> grid(grid_size);
    // cell grid[grid_size][grid_size];
    for (size_t i = 0; i < grid_size; i++)
    {
        grid[i] = std::vector<cell>(grid_size);
        for (size_t k = 0; k < grid_size; k++)
        {
            grid[i][k].content = '#';
            grid[i][k].isOccupied = false;
            grid[i][k].x = i;
            grid[i][k].y = k;
        }
    }
    for (size_t i = 0; i < grid_size; i++)
    {
        for (size_t j = 0; j < grid_size; j++)
        {
            if (e.x == i && e.y == j)
            {
                grid[i][j].content = 'x';
                grid[i][j].isOccupied = true;
            }
            if (p.x == i && p.y == j)
            {
                if (grid[i][j].isOccupied == true)
                {
                    grid[i][j].content += 'O';
                }
                else
                {
                    grid[i][j].content = 'O';
                    grid[i][j].isOccupied = true;
                }
            }
        }
    }
    return grid;
}

void displayGrid(std::vector<std::vector<cell>> grid)
{
    for (size_t i = 0; i < grid.size(); i++)
    {
        for (size_t j = 0; j < grid.size(); j++)
        {
            // std::cout << grid[i][j].content << " [" << i << ", " << j << "] ";
            std::cout << grid[i][j].content << "  ";
        }
        std::cout << std::endl;
    }
}

void movePlayer(std::string control, std::vector<std::vector<cell>> *grid, player *p1)
{
    if (control == "north" || control == "n")
    {
        if (p1->x < 1)
        {
            p1->x = getSettings("gridSize") - 1;
        }
        else
        {
            p1->x -= 1;
        }
    }
    else if (control == "south" || control == "s")
    {
        if (p1->x > getSettings("gridSize") - 2)
        {
            p1->x = 0;
        }
        else
        {
            p1->x += 1;
        }
    }
    else if (control == "east" || control == "e")
    {
        if (p1->y > getSettings("gridSize") - 2)
        {
            p1->y = 0;
        }
        else
        {
            p1->y += 1;
        }
    }
    else if (control == "west" || control == "w")
    {
        if (p1->y < 1)
        {
            p1->y = getSettings("gridSize") - 1;
        }
        else
        {
            p1->y -= 1;
        }
    }
    else
    {
        std::cout << "Invalid input, try again\n";
    }
}

int main()
{
    player p1;
    enemy e1;
    std::string control;
    p1.x = getSettings("playerPos-x");
    p1.y = getSettings("playerPos-y");
    e1.x = getSettings("enemyPos-x");
    e1.y = getSettings("enemyPos-y");

    std::vector<std::vector<cell>> playGrid = createGrid(getSettings("gridSize"), p1, e1);
    while (true)
    {
        displayGrid(playGrid);
        std::cout << "Enter command: ";
        std::cin >> control;
        if (control == "exit")
        {
            std::cout << "Exiting game\n";
            break;
        }
        else if (control == "attack" || control == "a")
        {
            if (p1.x == e1.x && p1.y == e1.y)
            {
                std::cout << "ENEMY KILLED. YOU WON!\n";
                std::cout << "Exiting game\n";
                break;
            }
            else
            {
                std::cout << "Miss!\n";
            }
        }
        else
        {
            movePlayer(control, &playGrid, &p1);
            playGrid = createGrid(getSettings("gridSize"), p1, e1);
        }
    }

    return 0;
}

// Terminal: g++ hw1.cpp -o hw1
// ./hw1