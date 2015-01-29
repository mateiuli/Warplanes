#include "SceneNode.hpp"

SceneNode::SceneNode()
:	mParent(nullptr)
{

}

void SceneNode::attachChild(Ptr child)
{
	child->mParent = this;
	mChildren.push_back(std::move(child));
}

/* Search for the specified SceneNode and delete it */
SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{	
	// found is an vector::iterator that stores a smart pointer
	// to the element searched for
	auto found = std::find_if(mChildren.begin(), mChildren.end(), 
		[&] (Ptr& p) -> bool { 
			return p.get() == &node; 
	});

	assert(found != mChildren.end());
	Ptr result = std::move(*found);

	// delete the node
	result->mParent = nullptr;
	mChildren.erase(found);

	return result;
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	// draw the scene
	drawCurrent(target, states);
	drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	// do nothing
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
	for(const SceneNode::Ptr& child : mChildren) {
		child->draw(target, states);
	}
}

void SceneNode::update(sf::Time dt)
{
	updateCurrent(dt);
	updateChildren(dt);
}

void SceneNode::updateCurrent(sf::Time dt)
{

}

void SceneNode::updateChildren(sf::Time dt)
{
	for(SceneNode::Ptr& child : mChildren)
		child->update(dt);
}

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;
	
	for(const SceneNode* node = this; node != nullptr; node = node->mParent)
		transform *= node->getTransform();

	return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}

unsigned int SceneNode::getCategory() const
{
	// default is Scene
	return Category::Scene;
}

/* Executes and forwards the command */
void SceneNode::onCommand(const Command& command, sf::Time dt)
{
	if(command.category & getCategory()) {
		command.action(*this, dt);
	}

	std::cout << "\n";

	for(auto& child : mChildren)
		child->onCommand(command, dt);
}

sf::FloatRect	SceneNode::getBoundingRect() const
{
	return sf::FloatRect();
}
