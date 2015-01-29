#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "State.hpp"
#include "Container.hpp"
#include "Button.hpp"
#include "Label.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>

class StateStack;

class MenuState : public State {
public:
					MenuState(StateStack& stack, Context context);
	virtual void	draw();
	virtual bool	update(sf::Time dt);
	virtual bool  	handleEvent(const sf::Event& event);

private:
	enum class Option : unsigned int {
		Play,
		Exit,
	};

private:
	sf::Sprite		mBackground;
	GUI::Container	mGUIContainer;

};

#endif
