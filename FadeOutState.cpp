#include "FadeOutState.hpp"

FadeOutState::FadeOutState(StateStack& stack, Context context)
:	State(stack, context),
	mBackground(context.window->getView().getSize()),
	mEffectTime(sf::Time::Zero),
	mCallback(nullptr)
{
	mBackground.setFillColor(sf::Color(0, 0, 0, 0));
}

void FadeOutState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	window.draw(mBackground);
}

bool FadeOutState::update(sf::Time dt)
{
	mEffectTime += dt;
	unsigned int alpha = mBackground.getFillColor().a;
	unsigned int step = 30;

	if(alpha >= 255 - step) {
		requestStackPop();
		requestStackPush(StateID::TransitionFadeIn);
		return false;
	}

	if(mEffectTime >= sf::milliseconds(10)) {
		mBackground.setFillColor(sf::Color(0, 0, 0, alpha + step));
		mEffectTime = sf::Time::Zero;
	}

	// Don't update the underlaying state
	return false;
}

bool FadeOutState::handleEvent(const sf::Event &event)
{
	// Don't send event deeper in the state stack
	return false;
}

void FadeOutState::setCallback(Callback callback)
{
	mCallback = std::move(callback);
}

void FadeOutState::setColor(sf::Color color)
{
	mColor = color;
}
