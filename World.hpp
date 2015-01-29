#ifndef WORLD_HPP
#define WORLD_HPP

#include <iostream>
#include <array>

#include <SFML/Graphics.hpp>
#include <SFML/System/NonCopyable.hpp>

#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"
#include "SpriteNode.hpp"
#include "Aircraft.hpp"
#include "CommandQueue.hpp"

class World : private sf::NonCopyable {
public:
	struct SpawnPoint {
		SpawnPoint(Aircraft::Type type, float x, float y);

		Aircraft::Type type;
		float x;
		float y;
	};

public:
	explicit			World(sf::RenderWindow& window, FontHolder& fonts);
	void					update(sf::Time dt);
	void					draw();
	CommandQueue& getCommandQueue();

private:
	void loadTextures();
	void buildScene();

	sf::FloatRect	getViewBounds() const;
	sf::FloatRect	getBattlefieldPoints() const;

	void addEnemy(Aircraft::Type type, float relX, float relY);
	void addEnemies();
	void spawnEnemies();

private:
	enum class Layer : int {
		Background,
		Air,
		Count,
	};

	sf::RenderWindow&	mWindow;
	sf::View					mWorldView;

	/* Resources managers */
	TextureHolder		mTextures;
	FontHolder&			mFonts;

	/* The root of the scene graph */
	SceneNode				mSceneGraph;

	/* Pointers to the root's children - the layers*/
	std::array<SceneNode*, 
		static_cast<int>(Layer::Count)>	mSceneLayers;

	/* Spawn positions for enemys */
	std::vector<SpawnPoint> mEnemySpawnPoints;

	sf::FloatRect		mWorldBounds;
	sf::Vector2f		mSpawnPosition;
	float 					mScrollSpeed;
	Aircraft*				mPlayerAircraft;
	CommandQueue		mCommandQueue;
};

#endif
