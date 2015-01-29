#include "FadeInState.hpp"
#include <iostream>

FadeInState::FadeInState(StateStack& stack, Context context)
:	State(stack, context),
	mBackground(context.window->getView().getSize()),
	mEffectTime(sf::Time::Zero),
	mCallback(nullptr)
{
	mBackground.setFillColor(sf::Color(0, 0, 0, 255));
}

void FadeInState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	window.draw(mBackground);
}

bool FadeInState::update(sf::Time dt)
{
	mEffectTime += dt;
	unsigned int alpha = mBackground.getFillColor().a;
	unsigned int step = 10;

	if(alpha <= step) {
		requestStackPop();
		return false;
	}

	if(mEffectTime >= sf::milliseconds(10)) {
		mBackground.setFillColor(sf::Color(0, 0, 0, alpha - step));
		mEffectTime = sf::Time::Zero;
	}

	// Don't update the underlaying state
	return false;
}

bool FadeInState::handleEvent(const sf::Event &event)
{
	// Don't send event deeper in the state stack
	return false;
}

void FadeInState::setCallback(Callback callback)
{
	mCallback = std::move(callback);
}

void FadeInState::setColor(sf::Color color)
{
	mColor = color;
}
