template <typename T>
void StateStack::registerState(StateID stateID)
{
	mFactories[stateID] = [this] () {
		return State::Ptr(new T(*this, mContext));
	};
}
