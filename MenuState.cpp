#include "MenuState.hpp"

MenuState::MenuState(StateStack& stack, Context context)
: State(stack, context),
	mBackground(),
	mGUIContainer()
{
	sf::Texture& texture = context.textures->get(TextureID::TitleScreen3);

	// Play
	auto playButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	playButton->setPosition(100, 250);
	playButton->setText("Play");
	playButton->setCallback([this] () {
		requestStackPop();
		requestStackPush(StateID::Game);
	});

	// Settings
	auto settingsButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	settingsButton->setPosition(100, 300);
	settingsButton->setText("Settings");
	settingsButton->setCallback([this] () {
		requestStackPush(StateID::Settings);
	});

	// Exit
	auto exitButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	exitButton->setPosition(100, 350);
	exitButton->setText("Exit");
	exitButton->setCallback([this] () {
		// stack clear - debug pop
		requestStackPop();
	});

	mGUIContainer.pack(playButton);
	mGUIContainer.pack(settingsButton);
	mGUIContainer.pack(exitButton);
	mGUIContainer.createBackground(sf::Vector2f(270.f, 170.f));
	mBackground.setTexture(texture);
}

void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());
	window.draw(mBackground);
	window.draw(mGUIContainer);
}

bool MenuState::update(sf::Time dt)
{
	// no update needed
	return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
	mGUIContainer.handleEvent(event);
	return false;
}














