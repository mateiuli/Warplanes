#include "Container.hpp"

namespace GUI
{

Container::Container()
:	mChildren(),
	mSelectedChild(-1),
	mBackground()
{
}

void Container::pack(Component::Ptr component)
{
	mChildren.push_back(component);
	if(!hasSelection() && component->isSelectable())
		select(mChildren.size() - 1);
}

bool Container::isSelectable() const
{
	return false;
}

void Container::handleEvent(const sf::Event& event)
{
	if(this->hasSelection() && mChildren[mSelectedChild]->isActive()) {
		mChildren[mSelectedChild]->handleEvent(event);
	}
	else if(event.type == sf::Event::KeyPressed) {
		if(event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
			this->selectPrevious();
		else if(event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
			this->selectNext();
		else if(event.key.code == sf::Keyboard::Return)
			if(this->hasSelection())
				mChildren[mSelectedChild]->activate();
	}
}

void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Bind to local coordinates/scale
	states.transform *= this->getTransform();

	// Draw the background
	target.draw(mBackground, states);

	for(auto& component : mChildren)
		target.draw(*component, states);
}

bool Container::hasSelection() const
{
	return mSelectedChild >= 0;
}

void Container::select(int index)
{
	if(mChildren[index]->isSelectable()) {
		if(this->hasSelection())
			mChildren[mSelectedChild]->deselect();

		mChildren[index]->select();
		mSelectedChild = index;
	}
}

void Container::selectNext()
{
	if(!this->hasSelection())
		return;

	// Search next component that is selectable
	int next = mSelectedChild;
	do {
		next = (next + 1) % mChildren.size();
	} while(!mChildren[next]->isSelectable());

	// Select that component
	this->select(next);
}

void Container::selectPrevious()
{
	if(!this->hasSelection())
		return;

	// Search previous component that is selectable
	int prev = mSelectedChild;
	do {
		prev = (prev - 1 + mChildren.size()) % mChildren.size();
	} while(!mChildren[prev]->isSelectable());

	// Select that component
	this->select(prev);
}

void Container::createBackground(sf::Vector2f size)
{
	if(mChildren.size() < 1)
		return;

	// margin distance
	float offset = 15.f;
	sf::Vector2f pos = mChildren[0]->getPosition();

	mBackground.setSize(size);
	mBackground.setFillColor(sf::Color(40, 40, 40, 100));
	mBackground.setPosition(pos.x - offset, pos.y - offset);
}

void Container::createBackground(float width, float height)
{
	createBackground(sf::Vector2f(width, height));
}

}
