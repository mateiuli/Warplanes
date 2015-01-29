#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "State.hpp"
#include "World.hpp"
#include "Player.hpp"
#include "CommandQueue.hpp"

class StateStack;

class GameState : public State {
public:
					GameState(StateStack& stack, Context context);
	virtual void	draw();
	virtual bool	update(sf::Time dt);
	virtual bool	handleEvent(const sf::Event &event);

private:
	World	mWorld;
	Player	mPlayer;
};

#endif
