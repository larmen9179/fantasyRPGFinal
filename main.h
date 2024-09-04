#pragma once
#include <random>
#include <iostream>
#include "enemy.h"

void clearScreen();
void showInventory();
void printDungeon(std::vector<int> &playerPosition);
void eventHandler(const std::vector<int>& playerPosition);
void gameLoop();
void inputHandler(std::string& userInput, std::vector<int>& playerPosition, std::vector<bool> &possibleMoves);
void fight(std::vector<int> &playerPosition);
void drawEnemies(std::vector<Enemy> &enemiesToFight);
void printPlayerStats();

//------------------------
std::vector<int> playerStart();
std::vector<bool> moveFinder(std::vector<int> &playerPosition);
bool eventRoom(std::vector<int>& playerPosition);
int getRand(int min, int max);
int countEnemies(std::vector<Enemy> &enemiesToFightIn);
