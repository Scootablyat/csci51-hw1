#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int grid_size;
int p_x;
int p_y;
int e_x;
int e_y;

/*
    PLAYER POSITION IS DENOTED BY 'O' IN THE GRID
    ENEMY'S POSITION IS DENOTED BY 'X IN THE GRID
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


struct cell{
    bool isOccupied;
    char content;
    int x;
    int y;
};

void getSettings(){
    std::fstream settingsFile;
    settingsFile.open("settings.txt", std::ios::in);
    std::string line;
    
    if(settingsFile.is_open()){
        while(std::getline(settingsFile, line)){
            //std::cout << line << std::endl;
            if(line.find("grid_size = ") == 0){
                grid_size = std::stoi(line.erase(0,11));
            }
            if(line.find("p_x = ") == 0){
                p_x = std::stoi(line.erase(0,6));
            }
            if(line.find("p_y = ") == 0){
                p_y = std::stoi(line.erase(0,6));
            }
            if(line.find("e_x = ") == 0){
                e_x = std::stoi(line.erase(0,6));
            }
            if(line.find("e_y = ") == 0){
                e_y = std::stoi(line.erase(0,6));
            }
        }
    }
}

std::vector<std::vector<cell>> createGrid(int grid_size, player p, enemy e){
    std::vector<std::vector<cell>> grid(grid_size);
    //cell grid[grid_size][grid_size];
    for (size_t i = 0; i < grid_size; i++){
        grid[i] = std::vector<cell>(grid_size);
        for (size_t k = 0; k < grid_size; k++){
            grid[i][k].content = '#';
            grid[i][k].isOccupied = false;
            grid[i][k].x = i;
            grid[i][k].y = k;
        }
    }
    for (size_t i = 0; i < grid_size; i++){
        for (size_t j = 0; j < grid_size; j++){
            if(p.x == i && p.y == j){
                grid[i][j].content = 'O';
                grid[i][j].isOccupied = true;
            }
            if(e.x == i && e.y == j){
                grid[i][j].content = 'x';
                grid[i][j].isOccupied = true;
            }
        }
    }
    return grid;
}



void displayGrid(std::vector<std::vector<cell>> grid){
    for (size_t i = 0; i < grid_size; i++){
        for (size_t j = 0; j < grid_size; j++){
            std::cout << grid[i][j].content << " [" << i << ", " << j << "] ";
        }
        std::cout << std::endl;
    }
}

int main(){
    getSettings();
    player p1;
    enemy e1;
    p1.x = p_x;
    p1.y = p_y;
    e1.x = e_x;
    e1.y = e_y;

    std::vector<std::vector<cell>> playGrid = createGrid(grid_size, p1, e1);
    displayGrid(playGrid);
    return 0;   
}