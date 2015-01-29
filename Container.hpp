#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include "Component.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <vector>
#include <memory>

namespace GUI
{

class Container : public Component {
public:
	using Ptr = std::shared_ptr<Container>;

public:
					Container();
	void			pack(Component::Ptr component);
	virtual bool	isSelectable() const;
	virtual void	handleEvent(const sf::Event& event);

	/* Create a backgrounds that wraps up all the components */
	void 			createBackground(sf::Vector2f size);
	void 			createBackground(float width, float height);

private:
	/* From 'Drawable' class */
	virtual void	draw(sf::RenderTarget& target, sf::RenderStates states) const;
	bool			hasSelection() const;
	void			select(int index);
	void			selectNext();
	void			selectPrevious();

private:
	std::vector<Component::Ptr>	mChildren;
	int mSelectedChild;
	sf::RectangleShape	mBackground;
};

}

#endif
