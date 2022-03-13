#include "Sand.h"
#include "Vacuum.h"
#include "Water.h"

Sand::Sand(sf::Vector2f sizeParticle) : Matter(sizeParticle)
{
	type = Type::Sand;

	gravityFreq = 300.f;
	interactionFreq = 100.f;

	sf::Uint8 g{ sf::Uint8(100 * rand() / RAND_MAX) };
	grain.setFillColor(sf::Color(255, 255 - g, 0));
}

void Sand::loop(std::vector<std::vector<Matter*>>& grid, int i, int j)
{
	if (gravityClock.getElapsedTime().asSeconds() > 1.f / gravityFreq && j != int(grid.size()) - 1) {
		gravityClock.restart();

		for (int c{ 0 }; c < 2; c++) {
			if (grid[j + 1][i]->isVoid()) { // bas
				delete grid[j + 1][i];
				grid[j + 1][i] = grid[j][i];
				grid[j][i] = new Vacuum(grain.getSize());
			}
			else if (grid[j + 1][i]->isFluid() && rand() / float(RAND_MAX) < 0.2f) { // bas
				Type typeFluid{ grid[j + 1][i]->getType() };
				delete grid[j + 1][i];
				grid[j + 1][i] = grid[j][i];

				if (i != 0 && i != int(grid[0].size()) - 1) {
					if (grid[j][i - 1]->isVoid() && grid[j][i + 1]->isVoid()) { // gauche | droite
						if (rand() / float(RAND_MAX) < 0.5f) {
							grid[j][i] = grid[j][i - 1];
							grid[j][i - 1] = newMatter(typeFluid);
						}
						else {
							grid[j][i] = grid[j][i + 1];
							grid[j][i + 1] = newMatter(typeFluid);
						}
					}
					else if (grid[j][i - 1]->isVoid() && !grid[j][i + 1]->isVoid()) { // gauche | droite
						grid[j][i] = grid[j][i - 1];
						grid[j][i - 1] = newMatter(typeFluid);
					}
					else if (!grid[j][i - 1]->isVoid() && grid[j][i + 1]->isVoid()) { // gauche | droite
						grid[j][i] = grid[j][i + 1];
						grid[j][i + 1] = newMatter(typeFluid);
					}
					else {
						grid[j][i] = newMatter(typeFluid);
					}
				}
				else if (i == 0) {
					if (grid[j][i + 1]->isVoid()) { // droite
						grid[j][i] = grid[j][i + 1];
						grid[j][i + 1] = newMatter(typeFluid);
					}
					else {
						grid[j][i] = newMatter(typeFluid);
					}
				}
				else {
					if (grid[j][i - 1]->isVoid()) { // gauche
						grid[j][i] = grid[j][i - 1];
						grid[j][i - 1] = newMatter(typeFluid);
					}
					else {
						grid[j][i] = newMatter(typeFluid);
					}
				}
			}
		}
	}

	if (interactionClock.getElapsedTime().asSeconds() > 1.f / interactionFreq && j != int(grid.size()) - 1) {
		interactionClock.restart();

		if (grid[j + 1][i]->isSolide()) { // bas
			if (i != 0 && i != int(grid[0].size()) - 1) {
				if (grid[j + 1][i - 1]->isSolide()) { // bas gauche
					if (grid[j + 1][i + 1]->isVoid()) { // bas droite
						delete grid[j + 1][i + 1];
						grid[j + 1][i + 1] = grid[j][i];
						grid[j][i] = new Vacuum(grain.getSize());
					}
					else if (grid[j + 1][i + 1]->isFluid()) { // bas droite
						Type typeFluid{ grid[j + 1][i + 1]->getType() };
						delete grid[j + 1][i + 1];
						grid[j + 1][i + 1] = grid[j][i];

						if (grid[j][i + 1]->isVoid()) { // droite
							grid[j][i] = grid[j][i + 1];
							grid[j][i + 1] = newMatter(typeFluid);
						}
						else {
							grid[j][i] = newMatter(typeFluid);
						}
					}
				}
				else if (grid[j + 1][i + 1]->isSolide()) { // bas droite
					if (grid[j + 1][i - 1]->isVoid()) { // bas gauche
						delete grid[j + 1][i - 1];
						grid[j + 1][i - 1] = grid[j][i];
						grid[j][i] = new Vacuum(grain.getSize());
					}
					else if (grid[j + 1][i - 1]->isFluid()) { // bas gauche
						Type typeFluid{ grid[j + 1][i - 1]->getType() };
						delete grid[j + 1][i - 1];
						grid[j + 1][i - 1] = grid[j][i];

						if (grid[j][i - 1]->isVoid()) {
							grid[j][i] = grid[j][i - 1];
							grid[j][i - 1] = newMatter(typeFluid);
						}
						else
							grid[j][i] = newMatter(typeFluid);
					}
				}
				else if (grid[j + 1][i - 1]->isVoid() && grid[j + 1][i + 1]->isVoid()) { // bas gauche | bas droite
					if (rand() / float(RAND_MAX) < 0.5f) {
						delete grid[j + 1][i - 1];
						grid[j + 1][i - 1] = grid[j][i];
						grid[j][i] = new Vacuum(grain.getSize());
					}
					else {
						delete grid[j + 1][i + 1];
						grid[j + 1][i + 1] = grid[j][i];
						grid[j][i] = new Vacuum(grain.getSize());
					}
				}
				else if (grid[j + 1][i - 1]->isFluid() && grid[j + 1][i + 1]->isFluid()) { // bas gauche | bas droite
					if (rand() / float(RAND_MAX) < 0.5f) {
						Type typeFluid{ grid[j + 1][i - 1]->getType() };
						delete grid[j + 1][i - 1];
						grid[j + 1][i - 1] = grid[j][i];

						if (grid[j][i - 1]->isVoid()) { // gauche
							grid[j][i] = grid[j][i - 1];
							grid[j][i - 1] = newMatter(typeFluid);
						}
						else {
							grid[j][i] = newMatter(typeFluid);
						}
					}
					else {
						Type typeFluid{ grid[j + 1][i + 1]->getType() };
						delete grid[j + 1][i + 1];
						grid[j + 1][i + 1] = grid[j][i];

						if (grid[j][i + 1]->isVoid()) { // droite
							grid[j][i] = grid[j][i + 1];
							grid[j][i + 1] = newMatter(typeFluid);
						}
						else {
							grid[j][i] = newMatter(typeFluid);
						}
					}
				}
			}
			else if (i == 0) {
				if (grid[j + 1][i + 1]->isVoid()) { // bas droite
					delete grid[j + 1][i + 1];
					grid[j + 1][i + 1] = grid[j][i];
					grid[j][i] = new Vacuum(grain.getSize());
				}
				else if (grid[j + 1][i + 1]->isFluid()) { // bas droite
					Type typeFluid{ grid[j + 1][i + 1]->getType() };
					delete grid[j + 1][i + 1];
					grid[j + 1][i + 1] = grid[j][i];
					grid[j][i] = newMatter(typeFluid);
				}
			}
			else {
				if (grid[j + 1][i - 1]->isVoid()) { // bas gauche
					delete grid[j + 1][i - 1];
					grid[j + 1][i - 1] = grid[j][i];
					grid[j][i] = new Vacuum(grain.getSize());
				}
				else if (grid[j + 1][i - 1]->isFluid()) { // bas gauche
					Type typeFluid{ grid[j + 1][i - 1]->getType() };
					delete grid[j + 1][i - 1];
					grid[j + 1][i - 1] = grid[j][i];
					grid[j][i] = newMatter(typeFluid);
				}
			}
		}
	}
}

void Sand::show(sf::RenderWindow* window)
{
	window->draw(grain);
}
