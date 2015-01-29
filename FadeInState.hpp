#ifndef FADEINSTATE
#define FADEINSTATE

#include "State.hpp"
#include <functional>

class StateStack;

class FadeInState : public State {
public:
	using Callback = std::function<void()>;

public:
					FadeInState(StateStack& stack, Context context);
	virtual void	draw();
	virtual bool	update(sf::Time dt);
	virtual bool	handleEvent(const sf::Event& event);

	/* Action to do when the transition is done */
	void setCallback(Callback callback);
	/* Default color is black */
	void setColor(sf::Color color);

private:
	sf::RectangleShape	mBackground;
	sf::Time			mEffectTime;
	Callback			mCallback;
	sf::Color			mColor;
};

#endif
