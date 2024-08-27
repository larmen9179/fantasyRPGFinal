#pragma once

#include <iostream>

class Enemy {

private:
	//attributes
	std::string name;
	int healthPoints;
	int damage;

public:

	//constructors
	Enemy(const std::string& nameIn, const int healthPointsIn, const int damageIn);

	//getters
	std::string getName() const;
	int getHealthPoints() const;
	int getDamage() const;

	//setters
	void setName(const std::string& nameIn);
	void setHealthPoints(const int healthPointsIn);
	void setDamage(const int damageIn);

	//methods
	void takeDamage(const int damageIn);

};