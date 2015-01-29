#include "Player.hpp"

struct AircraftMover {
	AircraftMover(float vx, float vy)
	: velocity(vx, vy) 
	{
	}

	void operator()(Aircraft& aircraft, sf::Time dt) const 
	{
		aircraft.accelerate(velocity * dt.asSeconds());
	}

	sf::Vector2f velocity;
};

Player::Player()
{
	// set initial key bindings
	mKeyBinding[sf::Keyboard::Left] 	= Player::Action::MoveLeft;
	mKeyBinding[sf::Keyboard::Right]	= Player::Action::MoveRight;
	mKeyBinding[sf::Keyboard::Up]			= Player::Action::MoveUp;
	mKeyBinding[sf::Keyboard::Down]		= Player::Action::MoveDown;
	mKeyBinding[sf::Keyboard::Space]	= Player::Action::Fire;
	mKeyBinding[sf::Keyboard::M]			= Player::Action::LaunchMissile;

	// set initial action bindings
	initializeActions();

	// send all commands to PlayerAircraft
	for(auto &pair : mActionBinding) {
		pair.second.category = Category::PlayerAircraft;
	}
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	if(event.type == sf::Event::KeyPressed) {
		// check if key appears in the binding and trigger command
		auto found = mKeyBinding.find(event.key.code);

		if(found != mKeyBinding.end() && !isRealTimeAction(found->second))
			commands.push(mActionBinding[found->second]);
	}
}

void Player::handleRealTimeInput(CommandQueue& commands)
{	
	// traverse all assigned keys and check if they are pressed
	for(auto pair : mKeyBinding) {
		// if key is pressed, lookup action and trigger corrsepoding command
		if(sf::Keyboard::isKeyPressed(pair.first))
			if(isRealTimeAction(pair.second))
				commands.push(mActionBinding[pair.second]);
	}
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
	// remove all keys that already map to this action
	for(auto it = mKeyBinding.begin(); it != mKeyBinding.end(); ++it) {
		if(it->second == action)
			mKeyBinding.erase(it);
	}

	// insert new binding
	mKeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
	for(auto& pair : mKeyBinding) {
		if(pair.second == action)
			return pair.first;
	}

	return sf::Keyboard::Unknown;
}

void Player::initializeActions()
{
	using namespace std::placeholders;

	// playerSpeed
	const float ps = 5000.f;

	mActionBinding[Action::MoveLeft].action 	= derivedAction<Aircraft>(AircraftMover(-ps, 0.f));
	mActionBinding[Action::MoveRight].action 	= derivedAction<Aircraft>(AircraftMover(ps, 0.f));
	mActionBinding[Action::MoveUp].action 		= derivedAction<Aircraft>(AircraftMover(0.f, -ps));
	mActionBinding[Action::MoveDown].action 	= derivedAction<Aircraft>(AircraftMover(0.f, ps)); 

	mActionBinding[Action::Fire].action						= derivedAction<Aircraft>(std::bind(&Aircraft::fire, _1));
	mActionBinding[Action::LaunchMissile].action 	= derivedAction<Aircraft>(std::bind(&Aircraft::launchMissile, _1));
}

bool Player::isRealTimeAction(Action action)
{
	switch(action) {
	case Action::MoveLeft:
	case Action::MoveRight:
	case Action::MoveUp:
	case Action::MoveDown:
		return true;

	default:
		return false;
	}

	return false;
}
