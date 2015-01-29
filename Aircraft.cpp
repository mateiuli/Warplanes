#include "Aircraft.hpp"
#include "DataTables.hpp"
#include "TextNode.hpp"
#include "Utility.hpp"

namespace
{
	std::map<Aircraft::Type, AircraftData> Table = initializeAircraftData();
}

/* Maps an aircraft type to the corresponding texture id */
TextureID toTextureID(Aircraft::Type type)
{
	switch(type) {
	case Aircraft::Type::Eagle:
		return TextureID::Eagle;

	case Aircraft::Type::Raptor:
		return TextureID::Raptor;

	case Aircraft::Type::Avenger:
		return TextureID::Avenger;

	default:
		break;
	}

	return TextureID::NoTexture;
}

Aircraft::Aircraft(Type type, TextureHolder& textures, FontHolder& fonts)
: Entity(Table[type].hitpoints),
	mType(type),
	mSprite(textures.get(toTextureID(type))),
	mTravelledDistance(0.f),
	mDirectionIndex(0),
	mIsFiring(false),
	mIsLaunchingMissile(false),
	mMissileAmmo(0)
{
	// center the origin of the sprite
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	// Create Health Bar
	std::unique_ptr<TextNode> healthDisplay(new TextNode(fonts, ""));
	// raw pointer to the text node
	mHealthDisplay = healthDisplay.get();
	// rvalue reference produced by std::move
	this->attachChild(std::move(healthDisplay));
	mHealthDisplay->setPosition(0.f, 50.f);
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

void Aircraft::updateCurrent(sf::Time dt)
{
	Entity::updateCurrent(dt);

	mHealthDisplay->setString(toString(getHitpoints()) + " HP");
	//mHealthDisplay->setPosition(0.f, 50.f);
	mHealthDisplay->setRotation(-getRotation());

	updateMovementPattern(dt);
}

float Aircraft::getMaxSpeed()
{
	return Table[mType].speed;
}

void Aircraft::updateMovementPattern(sf::Time dt)
{
	// grab the specific pattern for this aircraft type
	std::vector<Direction>& directions = Table[mType].directions;

	if(directions.empty())
		return;

	float distanceToTravel = directions[mDirectionIndex].distance;

	// If moved long enough in current direction then change direction
	if(mTravelledDistance > distanceToTravel) {
		mDirectionIndex = (mDirectionIndex + 1) % directions.size();
		mTravelledDistance = 0;
	}

	// Compute velocity from direction
	// By default, 0 degrees means movement to right.
	// Adding 90 more degrees will make it move down.
	float radians = toRadian(directions[mDirectionIndex].angle + 90.f);
	float vx = getMaxSpeed() * std::cos(radians);
	float vy = getMaxSpeed() * std::sin(radians);

	this->setVelocity(vx, vy);
	mTravelledDistance += getMaxSpeed() * dt.asSeconds();
}

unsigned int Aircraft::getCategory() const
{
	switch(mType) {
	case Aircraft::Type::Eagle:
		return Category::PlayerAircraft;

	case Aircraft::Type::Raptor:
		return Category::AlliedAircraft;

	case Aircraft::Type::Avenger:
		return Category::EnemyAircraft;

	default:
		break;
	}

	return Category::None;
}

void Aircraft::fire()
{
	// only ships with fire interval != 0 are able to fire
	if(Table[mType].fireInterval != sf::Time::Zero)
		mIsFiring = true;
}

void Aircraft::launchMissile()
{
	if(mMissileAmmo > 0) {
		mIsLaunchingMissile = true;
		mMissileAmmo--;
	}
}
