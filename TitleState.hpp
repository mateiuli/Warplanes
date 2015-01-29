#ifndef TITLE_STATE_HPP
#define TITLE_STATE_HPP

#include "State.hpp"

class StateStack;

class TitleState : public State {
public:
					TitleState(StateStack& stack, Context context);
	virtual void	draw();
	virtual bool	update(sf::Time dt);
	virtual bool	handleEvent(const sf::Event& event);

private:
	sf::Sprite	mBackground;
	sf::Text	mText;
	sf::Text	mTitle;
	bool		mShowText;
	sf::Time	mTextEffectTime;
};

#endif // TITLESCREEN_HPP
