#include "Projectile.hpp"
#include "DataTables.hpp"
#include "Utility.hpp"
#include "Command.hpp"

#include <cassert>
#include <map>

namespace
{
	std::map<Projectile::Type, ProjectileData> Table = initializeProjectileData();
}

Projectile::Projectile(Type type, TextureHolder& textures)
:	Entity(1), // 1 hit point
	mType(type),
	mSprite(textures.get(Table[type].texture)),
	mTargetDirection()
{
	centerOrigin(mSprite);
}


void Projectile::guideTowards(sf::Vector2f position)
{
	assert(isGuided());
	mTargetDirection = unitVector(position - getWorldPosition());
}

bool Projectile::isGuided() const
{
	return mType == Projectile::Type::Missile;
}

void Projectile::updateCurrent(sf::Time dt, CommandQueue& commands)
{
	if(isGuided()) {
		const float approachRate = 200.f;

		// Adjust the velocity based on the direction vector to
		// maintain a constant speed of the missile during turnings
		sf::Vector2f newVelocity = unitVector(getVelocity() + approachRate * dt.asSeconds() * mTargetDirection);
		newVelocity *= getMaxSpeed();
		float angle = std::atan2(newVelocity.y, newVelocity.x);

		setRotation(toDegree(angle) + 90.f);
		setVelocity(newVelocity);
	}

	Entity::updateCurrent(dt);
}

void Projectile::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

unsigned int Projectile::getCategory() const
{
	if(mType == Projectile::Type::EnemyBullet)
		return Category::EnemyProjectile;

	return Category::AlliedProjectile;
}

sf::FloatRect Projectile::getBoundingRect() const
{
	return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

float Projectile::getMaxSpeed() const
{
	return Table[mType].speed;
}

int Projectile::getDamage() const
{
	return Table[mType].damage;
}
