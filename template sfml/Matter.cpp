#include "Matter.h"
#include "Vacuum.h"
#include "Sand.h"
#include "Water.h"
#include "Rock.h"
#include "Powder.h"
#include "Spark.h"

Matter::Matter(sf::Vector2f sizeParticle)
{
	grain.setSize(sizeParticle);
}

float Matter::getFrequency()
{
	return gravityFreq;
}

float Matter::getTimeAnimationClock()
{
	return gravityClock.getElapsedTime().asSeconds();
}

void Matter::setPosition(sf::Vector2f pos)
{
	grain.setPosition(pos);
}

void Matter::restartClock()
{
	gravityClock.restart();
}

Type Matter::getType()
{
	return type;
}

bool Matter::isSolide()
{
	return type == Type::Sand || type == Type::Rock || type == Type::Powder;
}

bool Matter::isVoid()
{
	return type == Type::Vacuum || type == Type::Spark;
}

bool Matter::isFluid()
{
	return type == Type::Water;
}

Matter* Matter::newMatter(Type type)
{
	switch (type)
	{
	case Type::Vacuum:
		return new Vacuum(grain.getSize());
		break;
	case Type::Sand:
		return new Sand(grain.getSize());
		break;
	case Type::Water:
		return new Water(grain.getSize());
		break;
	case Type::Rock:
		return new Rock(grain.getSize());
		break;
	case Type::Powder:
		return new Powder(grain.getSize());
		break;
	case Type::Spark:
		return new Spark(grain.getSize());
		break;
	default:
		break;
	}

	return nullptr;
}
