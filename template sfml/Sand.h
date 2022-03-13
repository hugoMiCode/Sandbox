#pragma once
#include "Matter.h"


class Sand : public Matter
{
public:
	Sand(sf::Vector2f sizeParticle);
	
	void loop(std::vector<std::vector<Matter*>>& grid, int i, int j);
	void show(sf::RenderWindow* window);

private:

};

