#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>

//weapon struct
//this will be used for weapons and magic
//they both have just a name and a damage amount
struct Weapon {
	std::string name;
	int minDmg;
	int maxDmg;

	Weapon(const std::string& nameIn, const int minDmgIn, const int maxDmgIn);
	Weapon();
};

//item struct
struct Item {
	std::string name;
	int amount;
	int damage;
	int healAmount;

	Item(const std::string& nameIn, const int amountIn, const int damageIn, const int healAmountIn);
	Item();
};

class Player {

private:
	//attributes
	std::string name;
	int attackLevel;
	int maxHealth;
	int healthPoints;
	int keys;
	bool hasMap;
	std::vector<std::vector<bool>> hasBeen;

	//players inventory
	std::unordered_map<std::string, Weapon> weapons;
	std::unordered_map<std::string, Weapon> magic;
	std::unordered_map<std::string, Item> items;
	
	//storing the player's currently equipped items
	std::string currentWeapon;
	std::string currentMagic;

public:
	//constructors
	Player(const std::string& nameIn, const std::vector<std::vector<std::string>> &dungeonIn);

	//------------------------
	//getters
	std::string getName() const;
	int getAttackLevel() const;
	int getMaxHealth() const;
	int getHealthPoints() const;
	int getKeys() const;
	bool getHasMap() const;
	std::vector<std::vector<bool>> getHasBeen() const;
	Weapon getWeapon(const std::string &nameIn);
	Weapon getMagic(const std::string &nameIn);
	std::string getCurrentWeapon() const;
	std::string getCurrentMagic() const;

	//------------------------
	//setters
	void setName(const std::string &nameIn);
	void setAttackLevel(const int &attackLevelIn);
	void setMaxHealth(const int &maxHealthIn);
	void setHealthPoints(const int &healthPointsIn);
	void setKeys(const int &keysIn);
	void setHasMap(const bool &hasMapIn);
	void setHasBeen(const std::vector<std::vector<bool>> &hasBeenIn);
	void setCurrentWeapon(const std::string &currentWeaponIn);
	void setCurrentMagic(const std::string &currentMagicIn);

	//------------------------
	//methods
	void updateHasBeen(int i, int j);
	void showWeapons();
	void showMagic();
	void showItems();

	bool hasMagic();

	void addWeapon(std::string &nameIn, int minDmgIn, int maxDmgIn);
	void addMagic(std::string &nameIn, int minDmgIn, int maxDmgIn);

	void takeDamage(int damageIn);
	
};