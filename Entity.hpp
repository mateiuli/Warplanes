#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "SceneNode.hpp"
#include <SFML/Graphics.hpp>

class Entity : public SceneNode {
public:
					Entity(int hitPoints);
	void			setVelocity(sf::Vector2f velocity);
	void			setVelocity(float vx, float vy);
	void			accelerate(sf::Vector2f velocity);
	void			accelerate(float vx, float vy);
	sf::Vector2f	getVelocity() const;
	virtual void	updateCurrent(sf::Time dt);

	void			repair(int points);
	void			damage(int points);
	void			destroy();
	int				getHitpoints() const;
	bool			isDestroyed() const;

private:
	sf::Vector2f	mVelocity;
	int				mHitpoints;
};

#endif
