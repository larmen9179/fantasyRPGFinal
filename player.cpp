#include "player.h"

//weapon struct
Weapon::Weapon(const std::string& nameIn, const int minDmgIn, const int maxDmgIn, std::vector<std::string> imageIn)
	: name(nameIn), minDmg(minDmgIn), maxDmg(maxDmgIn), image(imageIn)
{}

Weapon::Weapon() {}

//item struct
Item::Item(const std::string& nameIn, int amountIn, int damageIn, int healAmountIn, std::vector<std::string> imageIn)
	: name(nameIn), amount(amountIn), damage(damageIn), healAmount(healAmountIn), image(imageIn)
{}

Item::Item() {}

//constructors
Player::Player(const std::string &nameIn, const std::vector<std::vector<std::string>> &dungeonIn)
	
	: name(nameIn), 
	attackLevel(1), 
	maxHealth(18), 
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

std::vector<Item> & Player::getItems(){
	return this->items;
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

std::unordered_map<std::string, Weapon> & Player::getWeapons(){
	return this->weapons;
}

std::unordered_map<std::string, Weapon>& Player::getSpells() {
	return this->magic;
}

Item & Player::getItem(const std::string &nameIn){

	int i;
	for (i = 0; i < this->items.size(); i++) {
		if (this->items[i].name == nameIn) {
			break;
		}
	}
	return items[i];
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
		for (auto& item : this->items) {
			std::cout << item.name << " - Amount: " << item.amount << '\n';
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

void Player::addWeapon(std::string& nameIn, int minDmgIn, int maxDmgIn, std::vector<std::string> imageIn) {
	
	this->weapons[nameIn] = Weapon(nameIn, minDmgIn, maxDmgIn, imageIn);
}

void Player::addMagic(std::string &nameIn, int minDmgIn, int maxDmgIn, std::vector<std::string> imageIn){
	
	this->magic[nameIn] = Weapon(nameIn, minDmgIn, maxDmgIn, imageIn);
}

void Player::addItem(std::string &nameIn, int amountIn, int damageIn, int healAmountIn, std::vector<std::string> imageIn){
	this->items.push_back(Item(nameIn, amountIn, damageIn, healAmountIn, imageIn));
}

void Player::heal(int healAmountIn){
	this->healthPoints += healAmountIn;

	if(this->healthPoints > this->maxHealth)
		this->healthPoints = this->maxHealth;
}

void Player::takeDamage(int damageIn){
	
	this->healthPoints -= damageIn;
}

bool Player::hasBeenSpot(int i, int j) {
	return this->hasBeen[i][j];
}