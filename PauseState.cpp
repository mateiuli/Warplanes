#include "PauseState.hpp"

PauseState::PauseState(StateStack& stack, Context context)
:	State(stack, context),
	mPausedText(),
	mInstructionText()
{
	sf::Font& font = context.fonts->get(FontID::Main);
	sf::Vector2f viewSize = context.window->getView().getSize();

	mPausedText.setFont(font);
	mPausedText.setString("Game Paused");
	mPausedText.setCharacterSize(70);
	centerOrigin(mPausedText);
	mPausedText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

	mInstructionText.setFont(font);
	mInstructionText.setCharacterSize(25);
	mInstructionText.setString("{Press Backspace to return to Main Menu}");
	centerOrigin(mInstructionText);
	mInstructionText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);
}

void PauseState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(sf::Vector2f(window.getSize()));

	window.draw(backgroundShape);
	window.draw(mPausedText);
	window.draw(mInstructionText);
}

bool PauseState::update(sf::Time dt)
{
	return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{
	if(event.type != sf::Event::KeyPressed)
		return false;

	// continue
	if(event.key.code == sf::Keyboard::Escape) {
		// remove itself to return th the game
		requestStackPop();
	}

	// go back to menu
	if(event.key.code == sf::Keyboard::BackSpace) {
		requestStackClear();
		requestStackPush(StateID::Menu);
	}

	return false;
}
