#ifndef SCENE_NODE_HPP
#define SCENE_NODE_HPP

#include <iostream>
#include <vector>
#include <memory>
#include <cassert>
#include <algorithm>

#include <SFML/Graphics.hpp>
#include <SFML/System/NonCopyable.hpp>

#include "Command.hpp"

class SceneNode : 	public sf::Transformable,
					public sf::Drawable,
					private sf::NonCopyable {
public:
	using Ptr = std::unique_ptr<SceneNode>;

public:
	SceneNode();

	/* insert/remove nodes */
	void	attachChild(Ptr child);
	Ptr 	detachChild(const SceneNode& node);

	/* Update the game logic */
	void	update(sf::Time dt);
	
private:
	/* Render the whole scene node */
	void			draw(sf::RenderTarget&, sf::RenderStates) const;
	/* Render only this object */
	virtual void	drawCurrent(sf::RenderTarget&, sf::RenderStates) const;
	/* Render only the children */
	void			drawChildren(sf::RenderTarget&, sf::RenderStates) const;

	/* Update game logic */
	virtual void	updateCurrent(sf::Time dt);
	void			updateChildren(sf::Time dt);

public:
	/* Get absolute transforms */
	sf::Transform 	getWorldTransform() const;
	sf::Vector2f	getWorldPosition() const;
	sf::FloatRect	getBoundingRect() const;

	/* Command category */
	virtual unsigned int getCategory() const;

	/* Execute command on this object */
	void	onCommand(const Command&, sf::Time);

private:
	std::vector<Ptr>	mChildren;
	SceneNode*			mParent;
};

#endif
