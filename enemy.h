#pragma once

#include <iostream>
#include <vector>

class Enemy {

private:
	//attributes
	std::string name;
	int healthPoints;
	int minDamage;
	int maxDamage;
	std::vector<std::string> image;

public:

	//constructors
	Enemy(const std::string& nameIn, const int healthPointsIn, const int minDamageIn, const int maxDamageIn, const std::vector<std::string> &imageIn);

	//getters
	std::string getName() const;
	int getHealthPoints() const;
	int getMinDamage() const;
	int getMaxDamage() const;
	std::vector<std::string> getImage() const;

	//setters
	void setName(const std::string& nameIn);
	void setHealthPoints(const int healthPointsIn);
	void setMinDamage(const int minDamageIn);
	void setMaxDamage(const int maxDamageIn);
	void setImage(const std::vector<std::string>& imageIn);

	//methods
	void takeDamage(const int damageIn);

};