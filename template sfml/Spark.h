#pragma once
#include "Matter.h"


class Spark : public Matter
{
public:
	Spark(sf::Vector2f sizeParticle);

	float getSparkClockElapsedTime();
	float getSparkTime();

	bool toDelete();
	void loop(std::vector<std::vector<Matter*>>& grid, int i, int j);
	void show(sf::RenderWindow* window);

private:
	sf::Clock sparkClock;
	float sparkTime;
	bool wet{ false };
};

