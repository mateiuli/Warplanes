#include "Entity.hpp"
#include <cassert>

Entity::Entity(int hitPoints)
:	mVelocity({0, 0}),
	mHitpoints(hitPoints)
{
}

void Entity::setVelocity(sf::Vector2f velocity)
{
	mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy)
{
	mVelocity.x = vx;
	mVelocity.y = vy;
}

sf::Vector2f Entity::getVelocity() const
{
	return mVelocity;
}

void Entity::updateCurrent(sf::Time dt)
{
	move(mVelocity * dt.asSeconds());
}

void Entity::accelerate(sf::Vector2f velocity)
{
	mVelocity += velocity;
}

void Entity::accelerate(float vx, float vy)
{
	mVelocity.x += vx;
	mVelocity.y += vy;
}

void Entity::repair(int points)
{
	assert(points > 0);
	mHitpoints += points;
}

void Entity::damage(int points)
{
	assert(points > 0);
	mHitpoints -= points;
}

void Entity::destroy()
{
	mHitpoints = 0;
}

int Entity::getHitpoints() const
{
	return mHitpoints;
}

bool Entity::isDestroyed() const
{
	return mHitpoints <= 0;
}
