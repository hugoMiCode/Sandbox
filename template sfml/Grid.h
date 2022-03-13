#pragma once
#include "Vacuum.h"
#include "Sand.h"
#include "Water.h"
#include "Rock.h"
#include "Powder.h"
#include "Spark.h"

class Grid
{
public:
	Grid(sf::Vector2f initSizeParticle, sf::Vector2u sizeWindow);

	void changeSizeNewDeleteMatter(int offset);

	int getSizeNewDeleteMatter();
	sf::Vector2u getSize();

	void newMatter(sf::Vector2f pos, Type typeToAdd);
	bool newable(Type type);
	void restartClockNew(Type type);

	void deleteMatter(sf::Vector2f pos, Type typeToDelete);
	bool deleteable(Type type);
	void restartClockDelete(Type type);

	std::vector<int> bijection(int n);

	void show(sf::RenderWindow* window);
	void loop();

private:
	sf::Vector2u sizeGrid;
	sf::Vector2f sizeParticle;
	std::vector<std::vector<Matter*>> grid;

	int sizeNewDeleteMatter;

	sf::Clock newSandClock;
	sf::Clock newWaterClock;
	sf::Clock newPowderClock;
	sf::Clock newFireClock;

	sf::Clock deleteSandClock;
	sf::Clock deleteWaterClock;
	sf::Clock deletePowderClock;

	float freqNewSand;
	float freqNewWater;
	float freqNewPowder;
	float freqNewFire;

	float freqDeleteSand;
	float freqDeleteWater;
	float freqDeletePowder;
};

