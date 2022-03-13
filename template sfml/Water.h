#pragma once
#include "Matter.h"


class Water : public Matter
{
public:
	Water(sf::Vector2f sizeParticle);

	void loop(std::vector<std::vector<Matter*>>& grid, int i, int j);
	void show(sf::RenderWindow* window);

private:
	sf::Clock colorChangeClock;

	float colorChangeFreq;
	float offsetColorChange;
};

// toujours avoir un offset -> rand() au lieu de = 0
