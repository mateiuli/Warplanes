#include "SettingsState.hpp"

SettingsState::SettingsState(StateStack &stack, Context context)
:	State(stack, context),
	mGUIContainer()
{
	mBackground.setTexture(context.textures->get(TextureID::TitleScreen2));

	// Build the key binding buttons and labels
	addButtonLabel(Player::Action::MoveLeft,	150.f, "Move Left", context);
	addButtonLabel(Player::Action::MoveRight,	200.f, "Move Right", context);
	addButtonLabel(Player::Action::MoveUp,		250.f, "Move Up", context);
	addButtonLabel(Player::Action::MoveDown,	300.f, "Move Down", context);

	this->updateLabels();

	auto backButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	backButton->setPosition(100.f, 375.f);
	backButton->setText("Back");
	// Instead of lambda
	backButton->setCallback(std::bind(&SettingsState::requestStackPop, this));

	mGUIContainer.pack(backButton);
	mGUIContainer.createBackground(270.f, 295.f);
}

void SettingsState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());
	window.draw(mBackground);
	window.draw(mGUIContainer);
}

bool SettingsState::update(sf::Time dt)
{
	return true;
}

bool SettingsState::handleEvent(const sf::Event& event)
{
	bool isKeyBinding = false;

	// Iterate through all key binding buttons to see if they are being pressed
	// and wait for user input to specify a custom key for each action
	for(int action = 0; action < static_cast<int>(Player::Action::Count); ++action) {
		if(mBindingButtons[action]->isActive()) {
			isKeyBinding = true;
			if(event.type == sf::Event::KeyPressed) {
				getContext().player->assignKey(static_cast<Player::Action>(action), event.key.code);
				mBindingButtons[action]->deactivate();
			}
			break;
		}
	}

	if(isKeyBinding)
		this->updateLabels();
	else
		mGUIContainer.handleEvent(event);

	return false;
}

void SettingsState::updateLabels()
{
	Player& player = *getContext().player;

	for(int i = 0; i < static_cast<int>(Player::Action::Count); ++i) {
		// Grab the assigned key
		sf::Keyboard::Key key = player.getAssignedKey(static_cast<Player::Action>(i));
		// Print it
		mBindingLabels[i]->setText(toString(key));
		mBindingLabels[i]->alignText(GUI::Label::Align::Right);
	}
}

void SettingsState::addButtonLabel(Player::Action action, float y, const std::string& text, Context context)
{
	// The button
	mBindingButtons[static_cast<int>(action)] = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	mBindingButtons[static_cast<int>(action)]->setPosition(100.f, y);
	mBindingButtons[static_cast<int>(action)]->setText(text);
	mBindingButtons[static_cast<int>(action)]->setToggle(true);

	// The label
	mBindingLabels[static_cast<int>(action)] = std::make_shared<GUI::Label>("", *context.fonts);
	mBindingLabels[static_cast<int>(action)]->setPosition(330.f, y + 10.f);

	mGUIContainer.pack(mBindingButtons[static_cast<int>(action)]);
	mGUIContainer.pack(mBindingLabels[static_cast<int>(action)]);
}
