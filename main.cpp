#include <iostream>
#include <thread>
#include <vector>

using worldType = std::vector<std::vector<char> >;

void clearScreen();

void drawWorld(const worldType &world);

int getNeighboursNumber(const int &xPos, const int &yPos, const worldType &world);

bool isWithinRange(const int &number, const int &max);

worldType updateWorld(const worldType &currentWorld);

const char aliveCell = 'X';
const char deadCell = ' ';
const int width = 10;
const int height = 10;

int main()
{
    worldType world(width, std::vector<char>(height, deadCell));
    std::chrono::milliseconds refreshTime(100);
    world[0][2] = aliveCell;
    world[1][2] = aliveCell;
    world[2][2] = aliveCell;
    world[1][0] = aliveCell;
    world[2][1] = aliveCell;
    std::cout << getNeighboursNumber(0,3, world);



    for (int i = 0; i < 100; i++)
    {
        system("clear");
        drawWorld(world);
        world = updateWorld(world);
        std::this_thread::sleep_for(refreshTime);
    }
}

void clearScreen()
{
    for (int i = 0; i < 100; i++)
    {
        std::cout << "\n";
    }
}

void drawWorld(const std::vector<std::vector<char> > &world)
{
    std::cout << "______________________" << std::endl;
    for (int i = 0; i < world.size(); i++)
    {
        for (int j = 0; j < world[i].size(); j++)
        {
            std::cout << world[i][j];
        }
        std::cout << std::endl;
    }
}

worldType updateWorld(const worldType &currentWorld)
{
    worldType newWorld(width, std::vector<char>(height, deadCell));
    for (int i = 0; i < currentWorld.size(); i++)
    {
        for (int j = 0; j < currentWorld[i].size(); j++)
        {
            int neighboursNumber = getNeighboursNumber(i, j, currentWorld);
            bool isAlive = currentWorld[i][j] == aliveCell ? true : false;
            if (isAlive)
            {
                if (neighboursNumber == 2 || neighboursNumber == 3)
                {
                    newWorld[i][j] = aliveCell;
                } else
                {
                    newWorld[i][j] = deadCell;
                }
            } else
            {
                if (neighboursNumber == 3)
                {
                    newWorld[i][j] = aliveCell;
                }
            }
        }
    }
    return newWorld;
}

int getNeighboursNumber(const int &xPos, const int &yPos, const worldType &world)
{
    int neighboursNumber = 0;
    for (int i = xPos - 1; i <= xPos + 1; i++)
    {
        if (isWithinRange(i, world.size() - 1))
        {
            for (int j = yPos - 1; j <= yPos + 1; j++)
            {
                if (isWithinRange(j, world[i].size() - 1))
                {
                    if (!(i == xPos && j == yPos))
                    {
                        if (world[i][j] == aliveCell)
                        {
                            neighboursNumber++;
                        }
                    }
                }
            }
        }
    }
    return neighboursNumber;
}

bool isWithinRange(const int &number, const int &max)
{
    if (number < 0)
    {
        return false;
    } else if (number > max)
    {
        return false;
    } else
    {
        return true;
    }
}