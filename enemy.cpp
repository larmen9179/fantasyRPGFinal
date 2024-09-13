#include "enemy.h"

//constructors
Enemy::Enemy(const std::string& nameIn, const int healthPointsIn, const int minDamageIn, const int maxDamageIn, const std::vector<std::string> &imageIn) {
	this->name = nameIn;
	this->healthPoints = healthPointsIn;
	this->minDamage = minDamageIn;
	this->maxDamage = maxDamageIn;
	this->image = imageIn;
}

//getters
std::string Enemy::getName() const{
	return this->name;
}

int Enemy::getHealthPoints() const {
	return this->healthPoints;
}

int Enemy::getMinDamage() const {
	return this->minDamage;
}

int Enemy::getMaxDamage() const {
	return this->maxDamage;
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

void Enemy::setMinDamage(const int minDamageIn) {
	this->minDamage = minDamageIn;
}

void Enemy::setMaxDamage(const int maxDamageIn) {
	this->maxDamage = maxDamageIn;
}

void Enemy::setImage(const std::vector<std::string> &imageIn) {
	this->image = imageIn;
}

//methods
void Enemy::takeDamage(const int damageIn) {
	this->healthPoints -= damageIn;
}