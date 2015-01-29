#include "StateStack.hpp"

StateStack::StateStack(State::Context context)
:	mContext(context)
{
}

StateStack::PendingChange::PendingChange(StateStack::Action action)
:	action(action)
{
}

StateStack::PendingChange::PendingChange(StateStack::Action action, StateID stateID)
:	action(action),
	stateID(stateID)
{
}

void StateStack::pushState(StateID stateID)
{
	mPendingList.push_back(PendingChange(StateStack::Action::Push, stateID));
}

void StateStack::popState()
{
	mPendingList.push_back(PendingChange(StateStack::Action::Pop));
}

void StateStack::clearState()
{
	mPendingList.push_back(PendingChange(StateStack::Action::Clear));
}

State::Ptr StateStack::createState(StateID stateID)
{
	// get the factory for this state
	auto found = mFactories.find(stateID);
	assert(found != mFactories.end());

	// second() is the function that creates the state
	// and returns a unique_pointer to it
	return found->second();
}

void StateStack::handleEvent(const sf::Event& event)
{
	// Iterate from the highest state to the lowest and
	// if a state recognize the event, break;
	for(auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr) {
		if(!(*itr)->handleEvent(event))
			break;
	}

	// After all the events are handled,
	// it's safe to modify the stack
	applyPendingChanges();
}

void StateStack::update(sf::Time dt)
{
	// Same order as in eventHandle()
	for(auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr) {
		if(!(*itr)->update(dt))
			break;
	}

	applyPendingChanges();
}

void StateStack::draw()
{
	// The first state to be drawn is the lowest,
	// this way it is posible to overlay multiple states
	for(auto& state : mStack) {
		state->draw();
	};
}

bool StateStack::isEmpty() const
{
	return mStack.empty();
}

void StateStack::applyPendingChanges()
{
	for(StateStack::PendingChange& change : mPendingList) {
		switch(change.action) {
		case StateStack::Action::Push:
			mStack.push_back(createState(change.stateID));
			break;

		case StateStack::Action::Pop:
			mStack.pop_back();
			break;

		case StateStack::Action::Clear:
			mStack.clear();
			break;

		default:
			break;
		}
	}

	mPendingList.clear();
}
