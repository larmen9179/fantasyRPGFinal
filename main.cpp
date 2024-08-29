#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <chrono>
#include <thread>
#include "main.h"
#include "player.h"
#include "enemy.h"

//declaring global game map
std::vector<std::vector<std::string>> dungeon = 
{   
    //room 3 - possible to encounter (3) enemies
    {"-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1"},
    {"-1", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "-1"},
    {"-1", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "-1"},
    {"-1", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "-1"},
    {"-1", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "-1"},
    {"-1", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "-1"},
    {"-1", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "-1"},
    
    //room 2 - possible to encounter (2) enemies
    {"-1", "2", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1"},
    {"-1", "2", "2", "2", "2", "2", "2", "2", "2", "2", "2", "-1"},
    {"-1", "2", "2", "2", "2", "2", "2", "2", "2", "2", "2", "-1"},
    {"-1", "2", "2", "2", "2", "2", "2", "2", "2", "2", "2", "-1"},
    {"-1", "2", "2", "2", "2", "2", "2", "2", "2", "2", "2", "-1"},

    //room 1 encounters just one enemy
    {"-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "1", "-1"},
    {"-1", "-1", "c", "1", "1", "1", "1", "1", "1", "1", "1", "-1"},
    {"-1", "1", "1", "-1", "w", "1", "-1", "m", "1", "c", "t", "-1"},
    {"-1", "s", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1"}


 };

//global player object
Player player("Roghbradden", dungeon);

//clonable enemy objects
std::vector<Enemy> enemies;

//rate for enemy encounters at each dungeon location that's not a specified room
int enemyEncounter{};

//tells if the player actually switched rooms last turn
bool transition = false;

int main()
{
    //giving the player their first weapon (fists)
    std::string firstWeapon = "Fists";


    //-------------TESTING-------------------------------

    //giving the player the map early to test print map functionality
    player.setHasMap(true);

    //--------------------------------------------
    

    //adding the weapon to the player's inventory
    player.addWeapon(firstWeapon, 1, 2);

    //setting the player's current weapon to the first weapon
    player.setCurrentWeapon(firstWeapon);


    //----------TESTING---------------------------
    //Testing logic for magic attacks

    std::string firstMagic = "Fireball";
    player.addMagic(firstMagic, 1, 3);
    
    player.setCurrentMagic(firstMagic);

    //--------------------------------------------
   

    //creating enemies to clone for encounters
    enemies.push_back(Enemy("Goblin", 5, 1));
    enemies.push_back(Enemy("Hivemind", 10, 2));
    enemies.push_back(Enemy("Drake", 8, 1));

    //calling the main game loop
    gameLoop();
    return 0;
}

int getRand(int min, int max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min, max);

	return dis(gen);
}

void gameLoop() {

    

    //user input for commands
    std::string userInput;
    //storing the player's starting position
    //this will be used to update the player's position
    //passed by reference to the moveHandler function
    //passed by reference to the printDungeon function
    //passed by reference to the inputHandler function
    std::vector<int> playerPosition = playerStart();

    while (true) {

        //clearing terminal screen
        clearScreen();

        if (!eventRoom(playerPosition)) {
            

            if (transition) {
                std::cout << "You have switched rooms...\n";
                std::cout << "You could encounter an enemy in this room...\n";
                int randNumber = getRand(0, 50);

                std::cout << randNumber << '\n';
                std::cout << enemyEncounter << '\n';

                if (randNumber <= enemyEncounter) {
                    std::cout << "You have encountered an enemy...\n";

                    fight(playerPosition);

                    std::cout << "enemy encounter rate is reset\n";

                    enemyEncounter = 0;
                }
                else {
					std::cout << "You have not encountered an enemy...\n";
                    std::cout << "enemy encounter rate is increased\n";
                    enemyEncounter++;
				}
            }
            else {
                std::cout << "You are still in the same room...\n";
                std::cout << "you wont encounter an enemy...\n";
            }
        }
		else {
			std::cout << "You are in an event room...\n";
		}

        transition = false;

        //printing the dungeon map
        printDungeon(playerPosition);

        std::vector<bool> possibleMoves = moveFinder(playerPosition);

        //printing player stats
        std::cout << "Current Health: " << player.getHealthPoints() << '\n';

        //prompting for user input
        std::cout << "Enter a command or type 'help' for a list of commands...\n";
        std::cout << ">";

        //reading user input
        std::cin >> userInput;

        //handling user input commands
        inputHandler(userInput, playerPosition, possibleMoves);

    }
}

void fight(std::vector<int> &playerPosition) {
    
    bool ran = false;
    //removing the previous screen showing dungeon map
    clearScreen();

    //empty vector of enemies for the player to fight
    std::vector<Enemy> enemiesToFight;

    //getting the number of enemies to fight in the room
    int enemyCount = std::stoi(dungeon[playerPosition[0]][playerPosition[1]]);

    //cloning a random enemy from the enemies vector and adding it to the enemiesToFight vector
    for(int i = 0;i < enemyCount; i++) {
        int enemyChoice = getRand(0, enemyCount - 1);

        std::cout << "You have encountered a " << enemies[enemyChoice].getName() << "...\n";

        enemiesToFight.push_back(Enemy(enemies[enemyChoice].getName(), enemies[enemyChoice].getHealthPoints(), enemies[enemyChoice].getDamage()));
	}

    std::cout << '\n';

    int aliveEnemies{countEnemies(enemiesToFight)};
    int turnsLeft{2};

	while (aliveEnemies > 0) {
        //drawing the ascii enemies
        drawEnemies(enemiesToFight);

        //checking if the player has any turns left
        //if not, then all the enemies attack the player
        //terminal messages will be enemy attacking and damage amount dealt
        
        std::cout << "Current Health: " << player.getHealthPoints() << '\n';
		std::string userInput;
		std::cout << "Enter a command or type 'help' for a list of commands...\n";
		std::cout << ">";

		std::cin >> userInput;

		if (userInput == "help") {
			std::cout << "Commands: \n";
			std::cout << "a - attack\n";
            std::cout << "u - use item\n";
            std::cout << "i - inventory\n";
            std::cout << "c - change equipment\n";
			std::cout << "r - run\n";
			

			std::cout << '\n';
			std::cout << "Type \"Enter\" to continue...\n";

			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.get();
		}

		else if (userInput == "a") {

            int enemyToAttack{};
			
            attackEnemy:

                //prompt message for the user to attack an enemy
                std::cout << '\n';
                std::cout << "Attack what? Type in your option number...";
                std::cout << '\n';

                int i{};

                //listing the possible enemies to attack(fixed)
                for(auto &enemy : enemiesToFight) {
					if(enemy.getHealthPoints() > 0) {
						std::cout << i + 1 << " - " << enemy.getName() << '\n';
						i++;
					}
				}

                //giving the user a go back option
                i++;
                std::cout << i << " - Go back...\n";
                std::cout << '\n';

                //grabbing user option
                std::cin >> userInput;

                std::vector<int> enemyOptions;

                int j = 1;
                //storing the options for the user to attack based off of the enemies that are still alive(fixed)
                for (auto& enemy : enemiesToFight) {
                    if (enemy.getHealthPoints() > 0) {
                        enemyOptions.push_back(j);
                        j++;
                    }
                }
                
                //checking if the user wants to go back
                if(userInput == std::to_string(i)) {
                    std::cout << '\n';
                    std::cout << "Going back to battle menu...";

                    std::cout << '\n';
                    std::cout << "Type \"Enter\" to continue...\n";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin.get();

				    goto clear;
			    }

                else if(userInput.length() == 1 && std::isdigit(userInput[0])){
                    if (std::find(enemyOptions.begin(), enemyOptions.end(), std::stoi(userInput)) != enemyOptions.end()) {
                        enemyToAttack = std::stoi(userInput) - 1;

                        std::cout << "You have chosen to attack the " << enemiesToFight[enemyToAttack].getName() << "...\n";

                        goto attackType;
                    }
                    else {
                        std::cout << "Invalid option. Please try again...\n";
                        std::cout << "Type \"Enter\" to continue...\n";
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cin.get();

                        clearScreen();
                        drawEnemies(enemiesToFight);

                        goto attackEnemy;
                    }
                }
                else {
					std::cout << "Invalid option. Please try again...\n";
					std::cout << "Type \"Enter\" to continue...\n";
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cin.get();
                    
                    clearScreen();
                    drawEnemies(enemiesToFight);

					goto attackEnemy;
				}
            
            //label for the user to choose the type of attack they want to use
            attackType:

                //prompt message for the user to choose the type of attack
                std::cout << '\n';
                std::cout << "Attack with current weapon or magic? Type in your option number...\n";

                std::cout << "1 - Weapon\n";
                std::cout << "2 - Magic\n";
                std::cout << "3 - Go back...\n";

                std::cout << '\n';

                //grabbing the users choice
                std::cin >> userInput;

                //allowing the user to go back to menu to choose a different enemy
                if (userInput == "3") {
                    std::cout << '\n';
					std::cout << "Going back to enemy menu...";

					std::cout << '\n';
					std::cout << "Type \"Enter\" to continue...\n";
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cin.get();

                    clearScreen();
                    drawEnemies(enemiesToFight);

                    goto attackEnemy;
                }
                else if (userInput == "1") {

                    turnsLeft--;

                    std::cout << "You attack the " << enemiesToFight[enemyToAttack].getName() << " with " << player.getWeapon(player.getCurrentWeapon()).name;

                    int attackDamage = getRand(player.getWeapon(player.getCurrentWeapon()).minDmg, player.getWeapon(player.getCurrentWeapon()).maxDmg);

                    enemiesToFight[enemyToAttack].takeDamage(attackDamage);

                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    std::cout << '\n';

                    std::cout << "You have dealt " << attackDamage << " damage to the " << enemiesToFight[enemyToAttack].getName() << '\n';

                    std::this_thread::sleep_for(std::chrono::seconds(2));

                }
                else if (userInput == "2") {
                    if (!player.hasMagic()) {
                        std::cout << "You don't have any magic yet...\n";
                        std::cout << "Going back to attack menu...\n";

                        std::cout << '\n';

                        std::cout << "Type \"Enter\" to continue...\n";
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cin.get();
                        clearScreen();
                        drawEnemies(enemiesToFight);

                        goto attackType;
                    }

                    turnsLeft--;

                    std::cout << "You attack the " << enemiesToFight[enemyToAttack].getName() <<  " with " << player.getMagic(player.getCurrentMagic()).name;

                    int attackDamage = getRand(player.getMagic(player.getCurrentMagic()).minDmg, player.getMagic(player.getCurrentMagic()).maxDmg);

                    enemiesToFight[enemyToAttack].takeDamage(attackDamage);

                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    std::cout << '\n';

                    std::cout << "You have dealt " << attackDamage << " damage to the " << enemiesToFight[enemyToAttack].getName() << '\n';

                    std::this_thread::sleep_for(std::chrono::seconds(2));
                }
                else {

                    std::cout << "Invalid option. Please try again...\n";
					std::cout << "Type \"Enter\" to continue...\n";
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cin.get();

					clearScreen();
					drawEnemies(enemiesToFight);

					goto attackType;
                }
                    
		}
		else if (userInput == "r") {
			std::cout << "You have successfully ran away!\n";
            ran = true;
			break;
		}
		else if (userInput == "i") {
			showInventory();
		}
        else if (userInput == "c") {
            std::cout << "Change Equipment: \n";
            std::cout << "Enter a command to change equipment: \n";
        }
        else {
            std::cout << '\n';
            std::cout << "Invalid option. Please try again...\n";
            std::cout << "Type \"Enter\" to continue...\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }

        std::cout << '\n';

        if (turnsLeft == 0) {

            turnsLeft = 2;

            for (auto& enemy : enemiesToFight) {
                if (enemy.getHealthPoints() > 0) {

                    int enemyDamage = getRand(1, enemy.getDamage());

                    player.takeDamage(enemyDamage);
                    std::cout << enemy.getName() << " has attacked you for " << enemyDamage << " damage...\n";
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                }
            }

        }

        clear:
            clearScreen();

        aliveEnemies = countEnemies(enemiesToFight);

        if (player.getHealthPoints() <= 0) {
            std::cout << "You have been defeated... The game has ended!\n";

            std::cout << '\n';

            std::cout << "Type \"Enter\" to continue...\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();

            exit(0);
        }
        

    }

    if (ran) {
        std::cout << '\n';

        std::cout << "Type \"Enter\" to continue...\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();

        clearScreen();

        return;
    }

    std::cout << "All enemies have been defeated...\n";

    std::cout << '\n';
    std::cout << "Type \"Enter\" to continue...\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();


    clearScreen();


}

int countEnemies(std::vector<Enemy>& enemiesToFightIn) {
    int count{};

    for (int i = 0; i < enemiesToFightIn.size(); i++) {
        if (enemiesToFightIn[i].getHealthPoints() > 0) {
            count++;
        }
    }

    return count;
}

void drawEnemies(std::vector<Enemy> &enemiesToFight) {
    
    for (int i = 0; i < dungeon.size() * 2; i++) {
        std::cout << "-";
    }

    std::cout << '\n';
    std::cout << "ascii enemies go here \n";
    std::cout << '\n';

    for(int i = 0; i < enemiesToFight.size(); i++) {
        if(enemiesToFight[i].getHealthPoints() > 0)
		    std::cout << enemiesToFight[i].getName() << " - " << enemiesToFight[i].getHealthPoints() << "     ";
	}

    std::cout << '\n';

    for (int i = 0; i < dungeon.size() * 2; i++) {
        std::cout << "-";
    }

    std::cout << '\n';

}

std::vector<int> playerStart() {

    std::vector<int> playerPostion;

    //finding the
    for (int i = 0; i < dungeon.size(); i++) {
		for (int j = 0; j < dungeon[i].size(); j++) {
			if (dungeon[i][j] == "s") {
				playerPostion.push_back(i);
				playerPostion.push_back(j);
			}
		}
	}

    return playerPostion;
}

bool eventRoom(std::vector<int> &playerPosition) {
    if(dungeon[playerPosition[0]][playerPosition[1]] == "s") {
		return true;
	}
    return false;
}

void inputHandler(std::string& userInput, std::vector<int>& playerPosition, std::vector<bool>& possibleMoves) {

    std::cout << '\n';

    if (userInput == "help") {
        std::cout << "Commands: \n";
        std::cout << "w - move up\n";
        std::cout << "s - move down\n";
        std::cout << "a - move left\n";
        std::cout << "d - move right\n";
        std::cout << "i - inventory\n";
        std::cout << "c - change equipment\n";
        std::cout << "e - exit program\n";

        std::cout << '\n';
        std::cout << "Type \"Enter\" to continue...\n";

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }
    else if (userInput == "w") {
        if (possibleMoves[0]) {
            playerPosition[0] -= 1;
            player.updateHasBeen(playerPosition[0], playerPosition[1]);
            transition = true;
        }
        else {
            std::cout << "You can't move up right now...\n";
            std::cout << '\n';
            std::cout << "Type \"Enter\" to continue...\n";

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
    }
    else if (userInput == "s") {
        if (possibleMoves[1]) {
            playerPosition[0] += 1;
            player.updateHasBeen(playerPosition[0], playerPosition[1]);
            transition = true;
        }
        else {
            std::cout << "You can't move down right now...\n";
            std::cout << '\n';
            std::cout << "Type \"Enter\" to continue...\n";

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
    }
    else if (userInput == "a") {
        if (possibleMoves[2]) {
            playerPosition[1] -= 1;
            player.updateHasBeen(playerPosition[0], playerPosition[1]);
            transition = true;
        }
        else {
            std::cout << "You can't move left right now...\n";
            std::cout << '\n';
            std::cout << "Type \"Enter\" to continue...\n";

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
    }
    else if (userInput == "d") {
        if (possibleMoves[3]) {
            playerPosition[1] += 1;
            player.updateHasBeen(playerPosition[0], playerPosition[1]);
            transition = true;
        }
        else {
            std::cout << "You can't move right right now...\n";
            std::cout << '\n';
            std::cout << "Type \"Enter\" to continue...\n";

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
    }
    
    else if (userInput == "i") {

        showInventory();
    }
    else if (userInput == "c") {
        std::cout << "Change Equipment: \n";
        std::cout << "Enter a command to change equipment: \n";
        std::cout << "w - change weapon";
        std::cout << "m - change magic";
    }
    else if (userInput == "e") {
        std::cout << "Exiting program...\n";
        exit(0);
    }
    
    else {
        std::cout << "Invalid command. Please try again...\n";
        std::cout << "Type \"Enter\" to continue...\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }
    std::cout << '\n';

}

void showInventory() {

    std::cout << '\n';
    std::cout << "Inventory: \n";

    std::cout << '\n';

    std::cout << "Current Weapon: " << player.getCurrentWeapon() << '\n';

    std::cout << '\n';

    std::cout << "Current Magic: " << player.getCurrentMagic() << '\n';

    std::cout << '\n';

    std::cout << "Weapons: \n";
    player.showWeapons();
    
    std::cout << '\n';

    std::cout << "Magic: \n";
    player.showMagic();

    std::cout << '\n';

    std::cout << "Items: \n";
    player.showItems();

    std::cout << '\n';
    std::cout << "Type \"Enter\" to continue...\n";

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

std::vector<bool> moveFinder(std::vector<int> &playerPosition) {

    std::vector<bool> possibleMoves;

    if(playerPosition[0] - 1 >= 0 && dungeon[playerPosition[0] - 1][playerPosition[1]] != "-1" && dungeon[playerPosition[0] - 1][playerPosition[1]] != "0") {
		possibleMoves.push_back(true);
	}
	else {
		possibleMoves.push_back(false);
	}

    if (playerPosition[0] + 1 < dungeon.size() && dungeon[playerPosition[0] + 1][playerPosition[1]] != "-1" && dungeon[playerPosition[0] + 1][playerPosition[1]] != "0") {
        possibleMoves.push_back(true);
    }
    else {
        possibleMoves.push_back(false);
    }

    if (playerPosition[1] - 1 >= 0 && dungeon[playerPosition[0]][playerPosition[1] - 1] != "-1" && dungeon[playerPosition[0]][playerPosition[1] - 1] != "0") {
        possibleMoves.push_back(true);
    }
    else {
		possibleMoves.push_back(false);
	}

    if (playerPosition[1] + 1 < dungeon[0].size() && dungeon[playerPosition[0]][playerPosition[1] + 1] != "-1" && dungeon[playerPosition[0]][playerPosition[1] + 1] != "0") {
		possibleMoves.push_back(true);
	}
	else {
		possibleMoves.push_back(false);
	}

	return possibleMoves;
}

//functional methods
void clearScreen() {
    // Call the system function to execute the "cls" command
    system("cls");
}

void printDungeon(std::vector<int> &playerPosition) {

    for (int i = 0; i < dungeon.size() * 2; i++) {
        std::cout << "-";
    }

	if (player.getHasMap()) {
        for (int i = 0; i < dungeon.size(); i++) {
            for (int j = 0; j < dungeon[i].size(); j++) {
                if (dungeon[i][j] == "-1") {
                    std::cout << "  ";
                }
                else if (i == playerPosition[0] && j == playerPosition[1]) {
                    std::cout << "p ";
                }
                else if (dungeon[i][j] == "1" || dungeon[i][j] == "2" || dungeon[i][j] == "3"){
                    std::cout << "- ";
                }
                else {
                    std::cout << dungeon[i][j] << " ";
                }
            }
            std::cout << '\n';
        }
	}
    else {
        for (int i = 0; i < dungeon.size(); i++) {
            for (int j = 0; j < dungeon[i].size(); j++) {
                if (dungeon[i][j] == "-1") {
                    std::cout << "  ";
                }
				else if (i == playerPosition[0] && j == playerPosition[1]) {
					std::cout << "p ";
				}
                else {
                    if (player.hasBeenSpot(i, j)) {
						if (dungeon[i][j] == "1" || dungeon[i][j] == "2" || dungeon[i][j] == "3")
                            std::cout << "- ";
                        else
							std::cout << dungeon[i][j] << " ";
                    }
                    else {
                        std::cout << "  ";
                    }
                }
            }
            std::cout << '\n';
        }
    }

    

    for (int i = 0; i < dungeon.size() * 2; i++) {
        std::cout << "-";
    }

    std::cout << '\n';

}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
