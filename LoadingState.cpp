#include "LoadingState.hpp"

LoadingState::LoadingState(StateStack& stack, Context context)
:	State(stack, context),
	mLoadingText(),
	mProgressBarBackground(),
	mProgressBar(),
	mLoadingTask()
{
	sf::RenderWindow& window = *context.window;

	// Set up the text
	mLoadingText.setFont(context.fonts->get(FontID::Main));
	mLoadingText.setString("Loading resources...");
	centerOrigin(mLoadingText);
	mLoadingText.setPosition(window.getSize().x / 2u, window.getSize().y / 2u + 50);

	// Set up the progress bar's background
	mProgressBarBackground.setFillColor(sf::Color::White);
	mProgressBarBackground.setSize(sf::Vector2f(window.getSize().x - 20, 10));
	mProgressBarBackground.setPosition(10, mLoadingText.getPosition().y + 40);

	// Set up the progress bar
	mProgressBar.setFillColor(sf::Color(100, 100, 100));
	mProgressBar.setSize(sf::Vector2f(200, 10));
	mProgressBar.setPosition(10, mLoadingText.getPosition().y + 40);

	this->setCompletion(0.f);
	this->mLoadingTask.execute();
}

void LoadingState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	window.draw(mLoadingText);
	window.draw(mProgressBarBackground);
	window.draw(mProgressBar);
}

bool LoadingState::update(sf::Time dt)
{
	// Update the progress bar from the remote task or finish it
	if(mLoadingTask.isFinished()) {
		requestStackPop();
		requestStackPush(StateID::Game);
	}
	else {
		this->setCompletion(mLoadingTask.getCompletion());
	}

	return true;
}

bool LoadingState::handleEvent(const sf::Event& event)
{
	// Send events deeper in the state stack
	return true;
}

void LoadingState::setCompletion(float percent)
{
	if(percent > 1.f)
		percent = 1.f;

	mProgressBar.setSize(sf::Vector2f(mProgressBarBackground.getSize().x * percent,
									  mProgressBar.getSize().y));
}

