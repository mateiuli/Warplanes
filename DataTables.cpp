#include "DataTables.hpp"

std::map<Aircraft::Type, AircraftData> initializeAircraftData()
{
	std::map<Aircraft::Type, AircraftData> data;

	data[Aircraft::Type::Eagle].hitpoints = 100;
	data[Aircraft::Type::Eagle].speed = 200.f;
	data[Aircraft::Type::Eagle].texture = TextureID::Eagle;
	data[Aircraft::Type::Eagle].fireInterval = sf::seconds(1);

	data[Aircraft::Type::Raptor].hitpoints = 30;
	data[Aircraft::Type::Raptor].speed = 80.f;
	data[Aircraft::Type::Raptor].texture = TextureID::Raptor;
	data[Aircraft::Type::Raptor].fireInterval = sf::Time::Zero;
	data[Aircraft::Type::Raptor].directions.push_back(Direction(45,		80));
	data[Aircraft::Type::Raptor].directions.push_back(Direction(-45,	160));
	data[Aircraft::Type::Raptor].directions.push_back(Direction(45,		80));

	data[Aircraft::Type::Avenger].hitpoints = 20;
	data[Aircraft::Type::Avenger].speed = 60.f;
	data[Aircraft::Type::Avenger].texture = TextureID::Avenger;
	data[Aircraft::Type::Avenger].fireInterval = sf::seconds(2);
	data[Aircraft::Type::Avenger].directions.push_back(Direction(45,	50));
	data[Aircraft::Type::Avenger].directions.push_back(Direction(0,		50));
	data[Aircraft::Type::Avenger].directions.push_back(Direction(-45, 100));
	data[Aircraft::Type::Avenger].directions.push_back(Direction(0,		50));
	data[Aircraft::Type::Avenger].directions.push_back(Direction(+45, 50));

	return data;
}

std::map<Projectile::Type, ProjectileData> initializeProjectileData()
{
	std::map<Projectile::Type, ProjectileData> data;

	data[Projectile::Type::AlliedBullet].damage = 10;
	data[Projectile::Type::AlliedBullet].speed = 300.f;
	data[Projectile::Type::AlliedBullet].texture = TextureID::Bullet;

	data[Projectile::Type::EnemyBullet].damage = 10;
	data[Projectile::Type::EnemyBullet].speed = 300.f;
	data[Projectile::Type::EnemyBullet].texture = TextureID::Bullet;

	data[Projectile::Type::Missile].damage = 200;
	data[Projectile::Type::Missile].speed = 150.f;
	data[Projectile::Type::Missile].texture = TextureID::Missile;

	// taking advantage of move constructor (C++11)
	return data;
}
