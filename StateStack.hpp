#ifndef STATE_STACK_HPP
#define STATE_STACK_HPP

#include <vector>
#include <map>
#include <functional>
#include <cassert>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

#include "StateIdentifiers.hpp"
#include "State.hpp"

namespace sf {
	class Event;
};

class StateStack : private sf::NonCopyable {
public:
	enum class Action {
		Push,
		Pop,
		Clear,
	};

private:
	struct PendingChange {
		PendingChange(Action action, StateID stateID);
		PendingChange(Action action);

		Action 	action;
		StateID stateID;
	};

public:
	explicit	StateStack(State::Context context);
	
	template <typename T>
	void		registerState(StateID stateID);
	void 		pushState(StateID stateID);
	void 		popState();
	void 		clearState();
	
	void 		update(sf::Time dt);
	void 		draw();
	void		handleEvent(const sf::Event& event);
	//State::Ptr getActiveState();

	bool 		isEmpty() const;

private:
	State::Ptr 	createState(StateID stateID);
	void		applyPendingChanges();

private:
	/* Active states */
	std::vector<State::Ptr>			mStack;
	/* Operation on stack are done only when it's safe*/
	std::vector<PendingChange>	mPendingList;
	/* Holds the RenderTarget, ResourceManager, etc. */
	State::Context							mContext;
	/* Holds functions that generate each state */
	std::map<StateID, std::function<State::Ptr()>> mFactories;

};

/*
 * struct Transition;
 * class Effect : public State {
 *	std::function<void()> callback;
 *	Effect(statestack, context)
 *	setCallback();
 *	// virtual update(); draw(); handleEvent();
 * }
 *
 * class FadeIn : public Effect {
 *	Effect()
 *	update, draw, event;
 *
 * }
 *
 *  La fel ca la State: registerEffect();
	Transition transition;
	// the transition has two effects
	// one that closes the current state,
	// and another one that start the requested state
	transition.first	= StateID::TransitionFadeOut;
	transition.second	= StateID::TransitionFadeIn;
	requstStackPush(StateID::Menu, transition)
	{
		// out
		requestStackPush(StateID::TransitionFadeOut);
	}

*/

#include "StateStack.inl"

#endif
