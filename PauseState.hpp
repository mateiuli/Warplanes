#ifndef PAUSESTATE_HPP
#define PAUSESTATE_HPP

#include "State.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class StateStack;

class PauseState : public State {
public:
					PauseState(StateStack& stack, Context context);
	virtual void	draw();
	virtual bool	update(sf::Time dt);
	virtual bool	handleEvent(const sf::Event& event);

private:
	sf::Text mPausedText;
	sf::Text mInstructionText;
};

#endif
