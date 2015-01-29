#ifndef AIRCRAFT_HPP
#define AIRCRAFT_HPP

#include "Entity.hpp"
#include "ResourceIdentifiers.hpp"
#include "Command.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

#include <memory>

// forward declaration
class TextNode;

class Aircraft : public Entity {
public:
	/* Different types of aircrafts */
	enum class Type {
		Eagle,
		Raptor,
		Avenger,
		Count,
	};

public:
	/* No need for explicit because of the enum class */
	explicit Aircraft(Type type, TextureHolder&, FontHolder&);

	virtual void drawCurrent(sf::RenderTarget&, sf::RenderStates) const;
	virtual void updateCurrent(sf::Time dt);
	virtual unsigned int getCategory() const;

	void	fire();
	void	launchMissile();

	float	getMaxSpeed();
	void	updateMovementPattern(sf::Time dt);

private:
	Type		mType;
	sf::Sprite	mSprite;
	TextNode*	mHealthDisplay;

	/* direction, movement patterns */
	float		mTravelledDistance;
	int			mDirectionIndex;

	bool		mIsFiring;
	bool		mIsLaunchingMissile;
	int			mMissileAmmo;
	sf::Time 	mFireCountdown;
};

#endif
