
#include "enemy.h"

//constructors
Enemy::Enemy(const std::string& nameIn, const int healthPointsIn, const int damageIn) {
	this->name = nameIn;
	this->healthPoints = healthPointsIn;
	this->damage = damageIn;
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

//methods
void Enemy::takeDamage(const int damageIn) {
	this->healthPoints -= damageIn;
}