#ifndef STATE_HPP
#define STATE_HPP

#include "ResourceIdentifiers.hpp"
#include "StateIdentifiers.hpp"
#include "Utility.hpp"

#include <memory>

namespace sf {
	class Time;
	class Event;
	class RenderWindow;
}

class Player;
class StateStack;

class State {
public:
	/* Holder of shared objects between all states */
	struct Context {
		Context(sf::RenderWindow&, TextureHolder&, FontHolder&, Player&);

		sf::RenderWindow*	window;
		TextureHolder*		textures;
		FontHolder*			fonts;
		Player*				player;
	};

	using Ptr = std::unique_ptr<State>;

public:
					State(StateStack& stack, Context context);
	virtual			~State();

	virtual void	draw() = 0;
	virtual bool 	update(sf::Time dt) = 0;
	virtual bool 	handleEvent(const sf::Event& event) = 0;

protected:
	void	requestStackPush(StateID stateID);
	void 	requestStackPop();
	void	requestStackClear();
	Context getContext() const;

private:
	StateStack*	mStack;
	Context 	mContext;
};

#endif
