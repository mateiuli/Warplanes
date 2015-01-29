#include "World.hpp"

World::SpawnPoint::SpawnPoint(Aircraft::Type type, float x, float y)
:	type(type), x(x), y(y)
{
}

World::World(sf::RenderWindow& window, FontHolder& fonts)
:	mWindow(window),
	mWorldView(window.getDefaultView()),
	mFonts(fonts),
	mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 10000.f),
	mSpawnPosition(	mWorldView.getSize().x / 2.f,  					// x
					mWorldBounds.height - mWorldView.getSize().y),	// y

	mScrollSpeed(-15.f),
	mPlayerAircraft(nullptr),
	mCommandQueue()
{
	loadTextures();
	buildScene();

	mWorldView.setCenter(mSpawnPosition);
}

void World::loadTextures()
{
	// Backgrounds
	mTextures.load(TextureID::Desert,	"Media/Textures/Terrain/terrain_2_blur.png");

	// Aircrafts
	mTextures.load(TextureID::Eagle,	"Media/Textures/Aircraft/Eagle.png");
	mTextures.load(TextureID::Raptor,	"Media/Textures/Aircraft/Raptor.png");
	mTextures.load(TextureID::Avenger,	"Media/Textures/Aircraft/Avenger.png");

	// Projectiles
	mTextures.load(TextureID::Bullet,	"Media/Textures/Weapons/Bullet.png");
	mTextures.load(TextureID::Missile,	"Media/Textures/Weapons/Missile.png");
}

/* Build up the scene, initialize different scene layers */
void World::buildScene()
{
	for(int i = 0; i < static_cast<int>(Layer::Count); i++) {
		// new SceneNode for every layer
		SceneNode::Ptr layer(new SceneNode());
		
		// copy raw pointer. no ownership transfer
		mSceneLayers[i] = layer.get();

		// move layer into SceneGraph
		mSceneGraph.attachChild(std::move(layer));
	}

	// set up the background texture
	sf::Texture& texture = mTextures.get(TextureID::Desert);
	texture.setRepeated(true);
	// background's bounds
	sf::IntRect textureRect(mWorldBounds);
	// prepare the node sprite
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	// add it to the layer's children
	mSceneLayers[static_cast<int>(Layer::Background)]->attachChild(std::move(backgroundSprite));

	// set up the airplanes
	std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Type::Eagle, mTextures, mFonts));
	// raw pointer
	mPlayerAircraft = leader.get();
	mPlayerAircraft->setPosition(mSpawnPosition);	mPlayerAircraft->setVelocity(40.f, mScrollSpeed);
	// atach the plane to the coresponding layer
	mSceneLayers[static_cast<int>(Layer::Air)]->attachChild(std::move(leader));

	// escort planes
	//std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::Type::Raptor, mTextures, mFonts));
	//std::unique_ptr<Aircraft>	rightEscort(new Aircraft(Aircraft::Type::Raptor, mTextures, mFonts));
	// relative positions to the leader
	//leftEscort->setPosition(-80.f, 50.f);
	//rightEscort->setPosition(80.f, 50.f);
	// atach them to the leader
	//mPlayerAircraft->attachChild(std::move(leftEscort));
	//mPlayerAircraft->attachChild(std::move(rightEscort));

	addEnemies();
}

void World::draw()
{
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}

void World::update(sf::Time dt)
{
	// move the view
	mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());
	// player not moving at all
	mPlayerAircraft->setVelocity(0.f, 0.f);

	// forward commands to the scene graph
	while(!mCommandQueue.isEmpty())
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);

	sf::Vector2f velocity = mPlayerAircraft->getVelocity();

	// check for diagonal velocity
	if(velocity.x != 0.f && velocity.y != 0.f)
		mPlayerAircraft->setVelocity(velocity / std::sqrt(2.f));

	// move aircraft with the view
	mPlayerAircraft->accelerate(0.f, mScrollSpeed);
	
	// regular update step
	mSceneGraph.update(dt);

	// stick to the visible area
	sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());

	// leave some space to the screen's border
	const float borderDistance = 40.f;

	// current position
	sf::Vector2f position = mPlayerAircraft->getPosition();

	// left border
	position.x = std::max(position.x, viewBounds.left + borderDistance);	
	// right border
	position.x = std::min(position.x, viewBounds.width - borderDistance);
	// top border
	position.y = std::max(position.y, viewBounds.top + borderDistance);
	// bottom border
	position.y = std::max(position.y, viewBounds.height - borderDistance);

	mPlayerAircraft->setPosition(position);

	spawnEnemies();
}

/**
 * @brief World::addEnemy
 * @param type Aircraft type
 * @param relX Relative X position to the player's spawn point
 * @param relY Relative Y position
 */
void World::addEnemy(Aircraft::Type type, float relX, float relY)
{
	SpawnPoint spawn(type, mSpawnPosition.x + relX, mSpawnPosition.y - relY);
	mEnemySpawnPoints.push_back(spawn);
}

/**
 * @brief World::addEnemies Add enemies to the spawn point container
 */
void World::addEnemies()
{
	addEnemy(Aircraft::Type::Raptor,		0.f,	500.f);
	addEnemy(Aircraft::Type::Raptor,		0.f,	1000.f);
	addEnemy(Aircraft::Type::Raptor, +100.f,	1100.f);
	addEnemy(Aircraft::Type::Raptor, -100.f,	1100.f);
	addEnemy(Aircraft::Type::Avenger,	-70.f,	1400.f);
	addEnemy(Aircraft::Type::Avenger,	-70.f,	1600.f);
	addEnemy(Aircraft::Type::Avenger,	 70.f,	1400.f);
	addEnemy(Aircraft::Type::Avenger,	 70.f,	1600.f);

	// Sort all the enemies according to their y value
	std::sort(mEnemySpawnPoints.begin(), mEnemySpawnPoints.end(),
		[] (SpawnPoint lhs, SpawnPoint rhs) {
			return lhs.y < rhs.y;
		});
}

void World::spawnEnemies()
{
	while(!mEnemySpawnPoints.empty() && mEnemySpawnPoints.back().y > getBattlefieldPoints().top) {
		// grab the coordinates
		SpawnPoint spawn = mEnemySpawnPoints.back();
		std::cout << "[spawn]";

		// create a new enemy aircraft at this position
		std::unique_ptr<Aircraft> enemy(new Aircraft(spawn.type, mTextures, mFonts));
		enemy->setPosition(spawn.x, spawn.y);
		enemy->setRotation(180.f);

		// add the enemy to the scene graph
		mSceneLayers[static_cast<int>(Layer::Air)]->attachChild(std::move(enemy));

		mEnemySpawnPoints.pop_back();
	}
}

CommandQueue& World::getCommandQueue()
{
	return mCommandQueue;
}

sf::FloatRect World::getViewBounds() const
{
	return sf::FloatRect(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
}

sf::FloatRect World::getBattlefieldPoints() const
{
	sf::FloatRect bounds = getViewBounds();
	bounds.top -= 100.f;
	bounds.height += 100.f;

	return bounds;
}
