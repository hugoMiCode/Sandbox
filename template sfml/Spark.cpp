#include "Spark.h"
#include "Vacuum.h"

Spark::Spark(sf::Vector2f sizeParticle) : Matter(sizeParticle)
{
	type = Type::Spark;

	sparkTime = 0.5f * rand() / float(RAND_MAX);

	gravityFreq = 0.f;
	interactionFreq = 0.f;

	sf::Uint8 g{ sf::Uint8(80 * rand() / RAND_MAX) };
	grain.setFillColor(sf::Color(153, g, 0));
}

float Spark::getSparkClockElapsedTime()
{
	return sparkClock.getElapsedTime().asSeconds();
}

float Spark::getSparkTime()
{
	return sparkTime;
}

bool Spark::toDelete()
{
	return sparkClock.getElapsedTime().asSeconds() > sparkTime || wet;
}

void Spark::loop(std::vector<std::vector<Matter*>>& grid, int i, int j)
{
	for (int i0{ -1 }; i0 <= 1; i0++) {
		for (int j0{ -1 }; j0 <= 1; j0++) {
			if (i + i0 >= 0 && j + j0 >= 0 && i + i0 < grid[0].size() && j + j0 < grid.size()) {
				if (grid[j + j0][i + i0]->getType() == Type::Water) {
					wet = true;
					break;
				}
			}
		}
		if (wet)
			break;
	}
}

void Spark::show(sf::RenderWindow* window)
{
	window->draw(grain);
}
