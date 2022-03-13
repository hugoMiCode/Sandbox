#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>

enum class Type {
	Vacuum = -1,
	Sand = 0,
	Water = 1,
	Rock = 2,
	Powder = 3,
	Spark = 4
};

class Matter
{
public:
	Matter(sf::Vector2f sizeParticle);

	float getFrequency();
	float getTimeAnimationClock();

	void setPosition(sf::Vector2f pos);
	void restartClock();

	Type getType();

	bool isSolide();
	bool isVoid();
	bool isFluid();

	Matter* newMatter(Type type);

	virtual bool toDelete() { return false; };
	virtual void loop(std::vector<std::vector<Matter*>>& grid, int i, int j) = 0; // peut etre non utile
	virtual void show(sf::RenderWindow* window) = 0;

protected:
	Type type; 
	sf::RectangleShape grain;

	sf::Clock gravityClock;
	sf::Clock interactionClock;

	float gravityFreq{ 0 }; // a suppr
	float fallingSpeed{ 40.f }; // case / second
	float interactionFreq{ 0 };
};

