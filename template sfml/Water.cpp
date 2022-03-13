#include "Water.h"
#include "Vacuum.h"
#include "Sand.h"

Water::Water(sf::Vector2f sizeParticle) : Matter(sizeParticle)
{
	type = Type::Water;

	gravityFreq = 300.f;
	interactionFreq = 300.f;
	colorChangeFreq = 1.f;

	offsetColorChange = (1.f / colorChangeFreq) * rand() / float(RAND_MAX);

	sf::Uint8 b{ sf::Uint8(80 * rand() / RAND_MAX) };
	grain.setFillColor(sf::Color(0, 50, 255 - b));
}

void Water::loop(std::vector<std::vector<Matter*>>& grid, int i, int j)
{
	if (j != int(grid.size()) - 1 && grid[j + 1][i]->isVoid()) {
		int fallenCell{ int(fallingSpeed * gravityClock.getElapsedTime().asSeconds()) };
	
		if (fallenCell > 0) {
			gravityClock.restart();
	
			for (int c{ 1 }; c <= fallenCell; c++) {
				if (grid[j + c][i]->isVoid()) { // j + c < grid.size()
					delete grid[j + c][i];
					grid[j + c][i] = grid[j + c - 1][i];
					grid[j][i] = new Vacuum(grain.getSize());
				}
			}
		}
	}

	
	if (gravityClock.getElapsedTime().asSeconds() > 1.f / gravityFreq && j != int(grid.size()) - 1) {
		gravityClock.restart();
	
		if (grid[j + 1][i]->isVoid()) { // bas
			delete grid[j + 1][i];
			grid[j + 1][i] = grid[j][i];
			grid[j][i] = new Vacuum(grain.getSize());
		}
	}

	if (interactionClock.getElapsedTime().asSeconds() > 1.f / gravityFreq && j != int(grid.size()) - 1) { // ici j peut etre egale a la derniere valeur !!!!!!
		interactionClock.restart();

		if (grid[j + 1][i]->isSolide() || grid[j + 1][i]->isFluid()) { // bas
			if (i != 0 && i != int(grid[0].size()) - 1) {
				if ((grid[j + 1][i - 1]->isSolide() || grid[j + 1][i - 1]->isFluid())		// bas gauche
					&& (grid[j + 1][i + 1]->isSolide() || grid[j + 1][i + 1]->isFluid())	// bas droite
					&& grid[j][i - 1]->isVoid()												// gauche
					&& grid[j][i + 1]->isVoid()) {											// droite
					if (i != 1 && i != int(grid[0].size()) - 2) {
						if (grid[j][i - 2]->isVoid() && (grid[j][i + 2]->isSolide() || grid[j][i + 2]->isFluid())) { // gauche gauche | droite droite
							delete grid[j][i - 1];
							grid[j][i - 1] = grid[j][i];
							grid[j][i] = new Vacuum(grain.getSize());
						}
						else if ((grid[j][i - 2]->isSolide() || grid[j][i - 2]->isFluid()) && grid[j][i + 2]->isVoid()) { // gauche gauche | droite droite
							delete grid[j][i + 1];
							grid[j][i + 1] = grid[j][i];
							grid[j][i] = new Vacuum(grain.getSize());
						}
					}
				}
				else if ((grid[j + 1][i - 1]->isSolide() || grid[j + 1][i - 1]->isFluid()) && grid[j + 1][i + 1]->isVoid()) { // bas gauche | bas droite
					delete grid[j + 1][i + 1];
					grid[j + 1][i + 1] = grid[j][i];
					grid[j][i] = new Vacuum(grain.getSize());
				}
				else if (grid[j + 1][i - 1]->isVoid() && (grid[j + 1][i + 1]->isSolide() || grid[j + 1][i + 1]->isFluid())) { // bas gauche | bas droite
					delete grid[j + 1][i - 1];
					grid[j + 1][i - 1] = grid[j][i];
					grid[j][i] = new Vacuum(grain.getSize());
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
				else if ((grid[j][i - 1]->isSolide() || grid[j][i - 1]->isFluid()) && grid[j][i + 1]->isVoid()) { // gauche | droite
					delete grid[j][i + 1];
					grid[j][i + 1] = grid[j][i];
					grid[j][i] = new Vacuum(grain.getSize());
				}
				else if (grid[j][i - 1]->isVoid() && (grid[j][i + 1]->isSolide() || grid[j][i + 1]->isFluid())) { // gauche | droite
					delete grid[j][i - 1];
					grid[j][i - 1] = grid[j][i];
					grid[j][i] = new Vacuum(grain.getSize());
				}
			}
			else if (i == 0) {
				if (grid[j + 1][i + 1]->isVoid()) { // bas droite
					delete grid[j + 1][i + 1];
					grid[j + 1][i + 1] = grid[j][i];
					grid[j][i] = new Vacuum(grain.getSize());
				}
				else if (grid[j][i + 1]->isVoid()) { // droite
					delete grid[j][i + 1];
					grid[j][i + 1] = grid[j][i];
					grid[j][i] = new Vacuum(grain.getSize());
				}
			}
			else {
				if (grid[j + 1][i - 1]->isVoid()) { // bas gauche
					delete grid[j + 1][i - 1];
					grid[j + 1][i - 1] = grid[j][i];
					grid[j][i] = new Vacuum(grain.getSize());
				}
				else if (grid[j][i - 1]->isVoid()) { // gauche
					delete grid[j][i - 1];
					grid[j][i - 1] = grid[j][i];
					grid[j][i] = new Vacuum(grain.getSize());
				}
			}
		}
	}
}

void Water::show(sf::RenderWindow* window)
{
	if (colorChangeClock.getElapsedTime().asSeconds() - offsetColorChange > 1.f / colorChangeFreq) {
		colorChangeClock.restart();
		offsetColorChange = rand() / float(RAND_MAX);
		sf::Uint8 b{ sf::Uint8(80 * rand() / RAND_MAX) };

		grain.setFillColor(sf::Color(grain.getFillColor().r, grain.getFillColor().g, 255 - b));
	}

	window->draw(grain);
}
