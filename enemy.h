#pragma once

#include <iostream>
#include <vector>

class Enemy {

private:
	//attributes
	std::string name;
	int healthPoints;
	int damage;
	std::vector<std::string> image;

public:

	//constructors
	Enemy(const std::string& nameIn, const int healthPointsIn, const int damageIn, const std::vector<std::string> &imageIn);

	//getters
	std::string getName() const;
	int getHealthPoints() const;
	int getDamage() const;
	std::vector<std::string> getImage() const;

	//setters
	void setName(const std::string& nameIn);
	void setHealthPoints(const int healthPointsIn);
	void setDamage(const int damageIn);
	void setImage(const std::vector<std::string>& imageIn);

	//methods
	void takeDamage(const int damageIn);

};