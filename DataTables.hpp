#ifndef DATATABLES_HPP
#define DATATABLES_HPP

#include "Aircraft.hpp"
#include "Projectile.hpp"
#include "ResourceIdentifiers.hpp"

#include <map>
#include <vector>

struct Direction {
	Direction(float angle, float distance) : angle(angle), distance(distance) {};
	float angle;
	float distance;
};

struct AircraftData {
	int			hitpoints;
	float		speed;
	TextureID	texture;
	sf::Time	fireInterval;
	std::vector<Direction> directions;
};

struct ProjectileData {
	int			damage;
	float		speed;
	TextureID	texture;
};

/* Creates a Data Table that holds the properties for each Aircraft type */
std::map<Aircraft::Type, AircraftData> initializeAircraftData();

/* Properties for projectiles */
std::map<Projectile::Type, ProjectileData> initializeProjectileData();

#endif
