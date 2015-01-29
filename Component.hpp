#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/NonCopyable.hpp>

#include <memory>

namespace GUI
{
class Component : 	public sf::Drawable,
					public sf::Transformable,
					private sf::NonCopyable {
public:
	using Ptr = std::shared_ptr<Component>;

public:
					Component();
	virtual			~Component();
	virtual bool	isSelectable() const = 0;
	bool			isSelected() const;
	virtual void	select();
	virtual void	deselect();
	virtual bool	isActive() const;
	virtual void	activate();
	virtual void	deactivate();
	virtual void	handleEvent(const sf::Event& event) = 0;

private:
	bool	mIsSelected;
	bool	mIsActive;

};
}

#endif
