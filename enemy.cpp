
#include "enemy.h"

//constructors
Enemy::Enemy(const std::string& nameIn, const int healthPointsIn, const int damageIn, const std::vector<std::string> &imageIn) {
	this->name = nameIn;
	this->healthPoints = healthPointsIn;
	this->damage = damageIn;
	this->image = imageIn;
}

//getters
std::string Enemy::getName() const{
	return this->name;
}

int Enemy::getHealthPoints() const {
	return this->healthPoints;
}

int Enemy::getDamage() const {
	return this->damage;
}

std::vector<std::string> Enemy::getImage() const {
	return this->image;
}

//setters
void Enemy::setName(const std::string& nameIn) {
	this->name = nameIn;
}

void Enemy::setHealthPoints(const int healthPointsIn) {
	this->healthPoints = healthPointsIn;
}

void Enemy::setDamage(const int damageIn) {
	this->damage = damageIn;
}

void Enemy::setImage(const std::vector<std::string> &imageIn) {
	this->image = imageIn;
}

//methods
void Enemy::takeDamage(const int damageIn) {
	this->healthPoints -= damageIn;
}