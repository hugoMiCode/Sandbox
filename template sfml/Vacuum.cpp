#include "Vacuum.h"

Vacuum::Vacuum(sf::Vector2f sizeParticle) : Matter(sizeParticle)
{
	type = Type::Vacuum;
}

void Vacuum::loop(std::vector<std::vector<Matter*>>& grid, int i, int j)
{
}

void Vacuum::show(sf::RenderWindow* window)
{
}
