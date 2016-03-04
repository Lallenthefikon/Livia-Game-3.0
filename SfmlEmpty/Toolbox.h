#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

struct Toolbox {


	enum TEXTUREKEY { 
		// Player
		PLAYERRUNNINGTEXTURE, PLAYERJUMPTEXTURE, PLAYERIDLETEXTURE, PLAYERHURTTEXTURE, PLAYERSLIDETEXTURE,
		// Enemies
		WORMTEXTURE,
		ACIDMONSTERTEXTURE,
		// Blocks
		BLOCK0TEXTURE, 
		// Other Entities
		MEATBALLTEXTURE, MEATBALLSPAWNERTEXTURE,
		// Editor
		TILETEXTURE,
		EDITORMENY,
		GOALTEXTURE,
		// UI
		LIFETEXTURE,
		// Stomach
		STOMACHBACKGROUND, STOMACHMIDDLEGROUND, STOMACHACID,
		// Hub
		HUBBACKGROUND,
		DECORATIONTEXTURE,
		// Dialogue
		DIALOGUETEXTURE
	};

	enum SOUNDKEY {
		// Player
		PLAYERIDLE, PLAYERRUN, PLAYERJUMP, PLAYERLAND, PLAYERDAMAGED, PLAYERDEATH, PLAYERFALLDEATH, PLAYERWALLSLIDE,
		// Worm
		WORMIDLE, WORMRUN, WORMJUMP, WORMLAND, WORMDEATH,
		// Stomach
		STOMACHMUSIC, STOMACHAMBIENCE
	};

	enum FONTKEY { GAMEOVER, DIALOGUE };

	static Toolbox& getInstance();
	static void loadTextures(std::string levelName);
	static void loadSounds(std::string levelName);
	static void loadFonts(std::string levelName);
	static sf::Image& getTexture(TEXTUREKEY textureKey);

	// Screen Info
	static void copyScreenInfo(sf::RenderWindow &window, sf::VideoMode &videoMode);
	static sf::Vector2f getWindowSize();
	static sf::Vector2f getResolution();
	static sf::Vector2f getWindowPos();

	// Camera Info
	static void copyCameraInfo(sf::Vector2f &globalCameraBounds, sf::Vector2f &localCameraBounds);
	static sf::FloatRect getGlobalCameraBounds();

	// Level Info
	static void copyLevelBounds(sf::FloatRect &levelBounds);
	static sf::FloatRect getLevelBounds();

	// Player Info 
	static void copyPlayerSprite(sf::Sprite &playerSprite);
	static void copyPlayerVelocity(sf::Vector2f &playerVelocity);
	static void copyPlayerIsAlive(bool isAlive);
	static void copyPlayerPosition(sf::Vector2f playerPosition);
	
	static sf::Sprite getPlayerSprite();
	static sf::Vector2f getPlayerVelocity();
	static sf::Vector2f getPlayerPosition();
	static bool getPlayerIsAlive();

	static sf::Vector2f findCoordPos(sf::Vector2i &pixelPos, sf::RenderWindow &window);

	// Sounds
	static sf::SoundBuffer& getSound(SOUNDKEY soundKey);
	static sf::Music& getMusic(SOUNDKEY soundKey);

	// Fonts
	static sf::Font& getFont(FONTKEY fontKey);

	// Frame time
	static void copyFrameTime(float &frameTime);
	static float& getFrameTime();

	// Gravity
	static void copyGravity(sf::Vector2f &gravity);
	static sf::Vector2f& getGravity();
};

