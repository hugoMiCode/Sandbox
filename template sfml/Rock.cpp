#include "Rock.h"

Rock::Rock(sf::Vector2f sizeParticle) : Matter(sizeParticle)
{
	type = Type::Rock;

	gravityFreq = 0.f;
	interactionFreq = 0.f;

	sf::Uint8 g{ sf::Uint8(32 * rand() / RAND_MAX) };
	grain.setFillColor(sf::Color(104 - g, 104 - g, 104 - g));
}

void Rock::loop(std::vector<std::vector<Matter*>>& grid, int i, int j)
{
}

void Rock::show(sf::RenderWindow* window)
{
	window->draw(grain);
}
