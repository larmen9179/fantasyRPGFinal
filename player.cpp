#include "player.h"

//weapon struct
Weapon::Weapon(const std::string& nameIn, const int minDmgIn, const int maxDmgIn)
	: name(nameIn), minDmg(minDmgIn), maxDmg(maxDmgIn)
{}

Weapon::Weapon() {}

//item struct
Item::Item(const std::string& nameIn, const int amountIn, const int damageIn, const int healAmountIn)
	: name(nameIn), amount(amountIn), damage(damageIn), healAmount(healAmountIn)
{}

Item::Item() {}

//constructors
Player::Player(const std::string &nameIn, const std::vector<std::vector<std::string>> &dungeonIn)
	
	: name(nameIn), 
	attackLevel(1), 
	maxHealth(10), 
	healthPoints(10), 
	keys(0), 
	hasMap(false), 
	hasBeen(dungeonIn.size(), std::vector<bool>(dungeonIn[0].size(), false))
	
{}

//methods
void Player::updateHasBeen(int i, int j) {
	hasBeen[i][j] = true;
}

//getters
std::string Player::getName() const {
	return this->name;
}

int Player::getAttackLevel() const {
	return this->attackLevel;
}

int Player::getMaxHealth() const {
	return this->maxHealth;
}

int Player::getHealthPoints() const {
	return this->healthPoints;
}

int Player::getKeys() const {
	return this->keys;
}

bool Player::getHasMap() const {
	return this->hasMap;
}

std::vector<std::vector<bool>> Player::getHasBeen() const {
	return this->hasBeen;
}

Weapon Player::getWeapon(const std::string &nameIn){
	return this->weapons[nameIn];
}

Weapon Player::getMagic(const std::string &nameIn){
	return this->magic[nameIn];
}

std::string Player::getCurrentWeapon() const {
	return this->currentWeapon;
}

std::string Player::getCurrentMagic() const {
	
	if(this->currentMagic.empty()){
		return "You can't equip any magic...";
	}
	
	return this->currentMagic;
}

//setters
void Player::setName(const std::string &nameIn) {
	this->name = nameIn;
}

void Player::setAttackLevel(const int &attackLevelIn) {
	this->attackLevel = attackLevelIn;
}

void Player::setMaxHealth(const int &maxHealthIn) {
	this->maxHealth = maxHealthIn;
}

void Player::setHealthPoints(const int &healthPointsIn) {
	this->healthPoints = healthPointsIn;
}

void Player::setKeys(const int &keysIn) {
	this->keys = keysIn;
}

void Player::setHasMap(const bool &hasMapIn) {
	this->hasMap = hasMapIn;
}

void Player::setHasBeen(const std::vector<std::vector<bool>> &hasBeenIn) {
	this->hasBeen = hasBeenIn;
}

void Player::showWeapons(){
	
	if (this->weapons.empty()) {
				std::cout << "You have no weapons...\n";
	}
	else{
		for (auto& weapon : this->weapons) {
			std::cout << weapon.first << " - Damage: " << weapon.second.minDmg << " To " << weapon.second.maxDmg << '\n';
		}
	}
}

void Player::setCurrentWeapon(const std::string &currentWeaponIn){
	
	this->currentWeapon = currentWeaponIn;
}

void Player::setCurrentMagic(const std::string &currentMagicIn){
	
	this->currentMagic = currentMagicIn;
}

void Player::showMagic(){
	
	if (this->magic.empty()) {
				std::cout << "You have no magic...\n";
	}
	else{
		for (auto& magicItem : this->magic) {
			std::cout << magicItem.first << " - Damage: " << magicItem.second.minDmg << " To " << magicItem.second.maxDmg << '\n';
		}
	}
}

void Player::showItems(){
	
	if (this->items.empty()) {
				std::cout << "You have no items...\n";
	}
	else{
		std::cout << "Items: \n";
		for (auto& item : this->items) {
			std::cout << item.first << " - Amount: " << item.second.amount << '\n';
		}
	}
}

bool Player::hasMagic() {
	if (this->magic.empty()) {
		return false;
	}
	else {
		return true;
	}
}

void Player::addWeapon(std::string &nameIn, int minDmgIn, int maxDmgIn){
	
	this->weapons[nameIn] = Weapon(nameIn, minDmgIn, maxDmgIn);
}

void Player::addMagic(std::string &nameIn, int minDmgIn, int maxDmgIn){
	
	this->magic[nameIn] = Weapon(nameIn, minDmgIn, maxDmgIn);
}

void Player::takeDamage(int damageIn){
	
	this->healthPoints -= damageIn;
}

