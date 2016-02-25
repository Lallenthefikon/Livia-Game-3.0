#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

struct Toolbox {


	enum TEXTUREKEY { 
		WORMTEXTURE, 
		BLOCK0TEXTURE, 
		ACIDMONSTERTEXTURE,
		RUNNINGPLAYERTEXTURE, PLAYERJUMPTEXTURE, PLAYERIDLETEXTURE, PLAYERHURTTEXTURE, PLAYERSLIDETEXTURE,
		TILETEXTURE, EDITORMENY,  STOMACHBACKGROUND, STOMACHACID, LIFETEXTURE, GOALTEXTURE };

	enum SOUNDKEY { PLAYERIDLE, PLAYERRUN, PLAYERJUMP, PLAYERLAND, PLAYERDAMAGED, PLAYERDEATH, PLAYERFALLDEATH, PLAYERWALLSLIDE, WORMIDLE, WORMRUN, WORMJUMP, WORMLAND, WORMDEATH, STOMACHMUSIC, STOMACHAMBIENCE };
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
	static sf::Sprite getPlayerSprite();
	static sf::Vector2f getPlayerVelocity();
	static bool getPlayerIsAlive();

	static sf::Vector2f findCoordPos(sf::Vector2i &pixelPos,sf::RenderWindow &window);

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

