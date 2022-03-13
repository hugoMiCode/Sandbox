#include "Grid.h"

Grid::Grid(sf::Vector2f initSizeParticle, sf::Vector2u sizeWindow)
{
	sizeNewDeleteMatter = 4;

	freqNewSand = 120.f;
	freqNewWater = 120.f;
	freqNewPowder = 120.f;
	freqNewFire = 120.f;

	freqDeleteSand = 80.f;
	freqDeleteWater = 80.f;
	freqDeletePowder = 80.f;

	sizeParticle = initSizeParticle;
	sizeGrid.x = sizeWindow.x / sizeParticle.x;
	sizeGrid.y = sizeWindow.y / sizeParticle.y;

	for (unsigned int j{ 0 }; j < sizeGrid.y; j++) {
		std::vector<Matter*> line{};
		for (unsigned int i{ 0 }; i < sizeGrid.x; i++)
			line.push_back(new Vacuum(initSizeParticle));
		grid.push_back(line);
	}
}

void Grid::changeSizeNewDeleteMatter(int offset)
{
	sizeNewDeleteMatter += offset;

	if (sizeNewDeleteMatter < 2)
		sizeNewDeleteMatter = 2;
	else if (sizeNewDeleteMatter > 8)
		sizeNewDeleteMatter = 8;
}

int Grid::getSizeNewDeleteMatter()
{
	return sizeNewDeleteMatter;
}

sf::Vector2u Grid::getSize()
{
	return sf::Vector2u(grid[0].size(), grid.size());
}

void Grid::newMatter(sf::Vector2f pos, Type typeToAdd)
{
	if (newable(typeToAdd)) {
		restartClockNew(typeToAdd);

		int i{ int(pos.x / sizeParticle.x) };
		int j{ int(pos.y / sizeParticle.y) };

		for (int i0{ -sizeNewDeleteMatter }; i0 <= sizeNewDeleteMatter; i0++) {
			for (int j0{ -sizeNewDeleteMatter }; j0 <= sizeNewDeleteMatter; j0++) {
				if (int(sqrt(pow(i0, 2) + pow(j0, 2))) < sizeNewDeleteMatter && i + i0 >= 0 && j + j0 >= 0 && i + i0 < sizeGrid.x && j + j0 < sizeGrid.y) {
					if (grid[j + j0][i + i0]->getType() == Type::Vacuum) {
						switch (typeToAdd)
						{
						case Type::Sand:
							if (rand() / float(RAND_MAX) < 0.1f) {
								delete grid[j + j0][i + i0];
								grid[j + j0][i + i0] = new Sand(sizeParticle);
							}
							break;
						case Type::Water:
							if (rand() / float(RAND_MAX) < 0.1f) {
								delete grid[j + j0][i + i0];
								grid[j + j0][i + i0] = new Water(sizeParticle);
							}
							break;
						case Type::Rock:
							delete grid[j + j0][i + i0];
							grid[j + j0][i + i0] = new Rock(sizeParticle);
							break;
						case Type::Powder:
							if (rand() / float(RAND_MAX) < 0.1f) {
								delete grid[j + j0][i + i0];
								grid[j + j0][i + i0] = new Powder(sizeParticle);
							}
							break;
						case Type::Spark:
							if (rand() / float(RAND_MAX) < 0.02f) {
								delete grid[j + j0][i + i0];
								grid[j + j0][i + i0] = new Spark(sizeParticle);
							}
							break;
						default:
							break;
						}
					}
				}
			}
		}
	}
}

bool Grid::newable(Type type)
{
	switch (type)
	{
	case Type::Vacuum:
		return false;
		break;
	case Type::Sand:
		return newSandClock.getElapsedTime().asSeconds() > 1.f / freqNewSand;
		break;
	case Type::Water:
		return newWaterClock.getElapsedTime().asSeconds() > 1.f / freqNewWater;
		break;
	case Type::Rock:
		return true;
		break;
	case Type::Powder:
		return newPowderClock.getElapsedTime().asSeconds() > 1.f / freqNewPowder;
		break;
	case Type::Spark:
		return newFireClock.getElapsedTime().asSeconds() > 1.f / freqNewFire;
		break;
	default:
		break;
	}
	return false;
}

void Grid::restartClockNew(Type type)
{
	switch (type)
	{
	case Type::Vacuum:
		break;
	case Type::Sand:
		newSandClock.restart();
		break;
	case Type::Water:
		newWaterClock.restart();
		break;
	case Type::Rock:
		break;
	case Type::Powder:
		newPowderClock.restart();
		break;
	case Type::Spark:
		newFireClock.restart();
		break;
	default:
		break;
	}
}

void Grid::deleteMatter(sf::Vector2f pos, Type typeToDelete)
{
	if (deleteable(typeToDelete)) {
		restartClockDelete(typeToDelete);

		int i{ int(pos.x / sizeParticle.x) };
		int j{ int(pos.y / sizeParticle.y) };


		for (int i0{ -sizeNewDeleteMatter }; i0 <= sizeNewDeleteMatter; i0++) {
			for (int j0{ -sizeNewDeleteMatter }; j0 <= sizeNewDeleteMatter; j0++) {
				if (int(sqrt(pow(i0, 2) + pow(j0, 2))) < sizeNewDeleteMatter && i + i0 >= 0 && j + j0 >= 0 && i + i0 < sizeGrid.x && j + j0 < sizeGrid.y) {
					if (grid[j + j0][i + i0]->getType() == typeToDelete) {
						delete grid[j + j0][i + i0];
						grid[j + j0][i + i0] = new Vacuum(sizeParticle);
					}
				}
			}
		}
	}
}

bool Grid::deleteable(Type type)
{
	switch (type)
	{
	case Type::Vacuum:
		return false;
		break;
	case Type::Sand:
		return deleteSandClock.getElapsedTime().asSeconds() > 1.f / freqDeleteSand;
		break;
	case Type::Water:
		return deleteWaterClock.getElapsedTime().asSeconds() > 1.f / freqDeleteWater;
		break;
	case Type::Rock:
		return true;
		break;
	case Type::Powder:
		return deletePowderClock.getElapsedTime().asSeconds() > 1.f / freqDeletePowder;
		break;
	default:
		break;
	}

	return false;
}

void Grid::restartClockDelete(Type type)
{
	switch (type)
	{
	case Type::Vacuum:
		break;
	case Type::Sand:
		deleteSandClock.restart();
		break;
	case Type::Water:
		deleteWaterClock.restart();
		break;
	case Type::Rock:
		break;
	case Type::Powder:
		deletePowderClock.restart();
		break;
	default:
		break;
	}
}

std::vector<int> Grid::bijection(int n)
{
	std::vector<int> idSort{};
	std::vector<int> idRand{};

	for (int i{ 0 }; i < n; i++)
		idSort.push_back(i);


	for (int i{ 0 }; i < n; i++) {
		int j{ int(idSort.size() * rand() / float(RAND_MAX + 1))};
		idRand.push_back(idSort[j]);
		idSort.erase(idSort.begin() + j);
	}

	return idRand;
}

void Grid::show(sf::RenderWindow* window)
{
	for (unsigned int j{ 0 }; j < sizeGrid.y; j++)
		for (unsigned int i{ 0 }; i < sizeGrid.x; i++) {
			grid[j][i]->setPosition(sf::Vector2f(i * sizeParticle.x, j * sizeParticle.y));
			grid[j][i]->show(window);
		}
}

void Grid::loop()
{
	std::vector<int> idRand{ bijection(sizeGrid.x) };
	for (int j{ int(sizeGrid.y) - 1 }; j >= 0; j--)
		for (int i : idRand) {
			if (grid[j][i]->getType() == Type::Spark && grid[j][i]->toDelete()) {
				delete grid[j][i];
				grid[j][i] = new Vacuum(sizeParticle);
			}
			else
				grid[j][i]->loop(grid, i, j);

			if (grid[j][i]->getType() == Type::Powder && grid[j][i]->toDelete()) {
				delete grid[j][i];
				grid[j][i] = new Spark(sizeParticle);
			}
		}
}
