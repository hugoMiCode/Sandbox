#pragma once
#include "Matter.h"


class Powder : public Matter
{
public:
	Powder(sf::Vector2f sizeParticle);

	bool toDelete();
	bool isWet(std::vector<std::vector<Matter*>>& grid, int i, int j);

	void loop(std::vector<std::vector<Matter*>>& grid, int i, int j);
	void show(sf::RenderWindow* window);

private:
	sf::Clock burnClock;
	sf::Clock propagationFireClock;

	float timeToBurn;
	float freqPropagationFire;

	bool burnt{ false };
	bool burning{ false };
};

