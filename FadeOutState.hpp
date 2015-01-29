#ifndef FADEOUTSTATE
#define FADEOUTSTATE

#include "State.hpp"
#include <functional>

class StateStack;

class FadeOutState : public State {
public:
	using Callback = std::function<void()>;

public:
					FadeOutState(StateStack& stack, Context context);
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
