#include "State.hpp"
#include "StateStack.hpp"

State::Context::Context(sf::RenderWindow& window,  TextureHolder& textures, 
								FontHolder& fonts, Player& player)
:	window(&window),
	textures(&textures),
	fonts(&fonts),
	player(&player)
{
}

State::State(StateStack& stack, Context context)
:	mStack(&stack),
	mContext(context)
{
}

State::~State()
{
}

void State::requestStackPush(StateID stateID)
{
	mStack->pushState(stateID);
}

void State::requestStackPop()
{
	mStack->popState();
}

void State::requestStackClear()
{
	mStack->clearState();
}

State::Context State::getContext() const
{
	return mContext;
}



