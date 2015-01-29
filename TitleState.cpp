#include "TitleState.hpp"
#include <iostream>

TitleState::TitleState(StateStack& stack, Context context)
:	State(stack, context),
	mText(),
	mTitle(),
	mShowText(true),
	mTextEffectTime(sf::Time::Zero)
{
	mBackground.setTexture(context.textures->get(TextureID::TitleScreen1));
	sf::Vector2f windowSize = context.window->getView().getSize();

	// Game title
	mTitle.setFont(context.fonts->get(FontID::Armalite));
	mTitle.setString("The Crap Bomber");
	mTitle.setCharacterSize(90);
	centerOrigin(mTitle);
	mTitle.setColor(sf::Color(25, 60, 80));
	mTitle.setPosition(windowSize.x / 2.f, 100.f);

	// Press key to continue
	mText.setFont(context.fonts->get(FontID::Main));
	mText.setString("Press SPACE to continue");\
	centerOrigin(mText);
	mText.setColor(sf::Color::White);
	mText.setPosition(windowSize.x / 2.f, windowSize.y / 2.f + 150.f);
}

void TitleState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());
	window.draw(mBackground);
	window.draw(mTitle);

	if(mShowText)
		window.draw(mText);
}

bool TitleState::handleEvent(const sf::Event& event)
{
	if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space) {
		requestStackPop();
		//requestStackPush(StateID::TransitionFadeOut);
		requestStackPush(StateID::Menu);
	}

	return false;
}

bool TitleState::update(sf::Time dt)
{
	mTextEffectTime += dt;

	if(mTextEffectTime >= sf::seconds(.6)) {
		mShowText = !mShowText;
		mTextEffectTime = sf::Time::Zero;
	}
	return true;
}
