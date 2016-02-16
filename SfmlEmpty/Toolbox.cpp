#include "Toolbox.h"

static sf::Sprite mPlayerSprite;
static sf::Vector2f mPlayerVelocity;

// Textures
static sf::Image mEnemy0sheet;
static sf::Image mBlock0sheet;
static sf::Image mRunningPlayersheet;
static sf::Image mIdlePlayersheet;
static sf::Image mJumpingPlayersheet;
static sf::Image mHurtPlayersheet;
static sf::Image mAcidMonsterTexture;
static sf::Image mStomachBackgroundTexture;
static sf::Image mLifeTexture;

static sf::Image mTileTexture;
static sf::Image mEditorMenyTexture;

// Camera edit
static sf::Vector2f mWindowSize;
static sf::Vector2f mResolution;
static sf::Vector2f mWindowPos;

// Sounds
static sf::SoundBuffer mPlayerIdleSound;
static sf::SoundBuffer mPlayerRunSound;
static sf::SoundBuffer mPlayerJumpSound;
static sf::SoundBuffer mPlayerDamagedSound;
static sf::SoundBuffer mWormSound;
static sf::Music mStomachMusic;
static sf::Music mStomachAmbience;

Toolbox& Toolbox::getInstance(){
	static Toolbox toolbox;
	return toolbox;
}

void Toolbox::loadTextures(std::string levelName){
	if (levelName == "Stomach"){
		mStomachBackgroundTexture.loadFromFile("resources/images/Tarm_BG.jpg");
	}

	mEnemy0sheet.loadFromFile("resources/images/Mask.png");
	mBlock0sheet.loadFromFile("resources/images/Current_block0_sheet.png");

	mRunningPlayersheet.loadFromFile("resources/images/Livia_spritesheet_placeholder1.2(100,140).png");
	mIdlePlayersheet.loadFromFile("resources/images/Livia_idle_spritesheet.png");

	mAcidMonsterTexture.loadFromFile("resources/images/AcidMonster.png");

	mTileTexture.loadFromFile("resources/images/Tile.png");
	mEditorMenyTexture.loadFromFile("resources/images/EditorMenu.png");
	
	mLifeTexture.loadFromFile("resources/images/Livia_life.png");
}

void Toolbox::loadSounds(std::string levelName) {

	if (levelName == "Stomach") {
		// Load Tummy Acid Trip

		// Music and ambience
		mStomachMusic.openFromFile("resources/sounds/music/stomach/SML - ex4.ogg");
		mStomachAmbience.openFromFile("resources/sounds/music/stomach/Ambient_Stomach.ogg");
	}

	// Global effects
	mPlayerIdleSound.loadFromFile("resources/sounds/effects/livia/jump_02.ogg");
	mPlayerRunSound.loadFromFile("resources/sounds/effects/livia/Jump_03.ogg");
	mPlayerJumpSound.loadFromFile("resources/sounds/effects/livia/Jump_01.ogg");
	mPlayerDamagedSound.loadFromFile("resources/sounds/effects/livia/Hurt_03.aif");

}

sf::Image& Toolbox::getTexture(TEXTUREKEY textureKey){

	switch (textureKey){

	case WORMTEXTURE:
		return mEnemy0sheet;
		break;

	case BLOCK0TEXTURE:
		return mBlock0sheet;
		break;

	case RUNNINGPLAYERTEXTURE:
		return mRunningPlayersheet;
		break;

	case PLAYERJUMPTEXTURE:
		return mJumpingPlayersheet;
		break;

	case PLAYERIDLETEXTURE:
		return mIdlePlayersheet;
		break;

	case PLAYERHURTTEXTURE:
		return mHurtPlayersheet;
		break;
		
	case TILETEXTURE:
		return mTileTexture;
		break;

	case EDITORMENY:
		return mEditorMenyTexture;
		break;

	case ACIDMONSTERTEXTURE:
		return mAcidMonsterTexture;
		break;

	case STOMACHBACKGROUND:
		return mStomachBackgroundTexture;
		break;

	case LIFETEXTURE:
		return mLifeTexture;
		break;

	default:
		break;
	}
}

// Camera Edit
void Toolbox::copyScreenInfo(sf::RenderWindow &window, sf::VideoMode &videoMode){
	mWindowSize = sf::Vector2f(window.getSize());
	mResolution.x = videoMode.width;
	mResolution.y = videoMode.height;
	mWindowPos = sf::Vector2f(window.getPosition());
}

sf::Vector2f Toolbox::getWindowSize(){
	return mWindowSize;
}

sf::Vector2f Toolbox::getResolution(){
	return mResolution;
}

sf::Vector2f Toolbox::getWindowPos(){
	return mWindowPos;
}

void Toolbox::copyPlayerSprite(sf::Sprite &playerSprite){
	mPlayerSprite = playerSprite;
}

void Toolbox::copyPlayerVelocity(sf::Vector2f &playerVelocity){
	mPlayerVelocity = playerVelocity;
}

sf::Sprite Toolbox::getPlayerSprite(){
	return mPlayerSprite;
}

sf::Vector2f Toolbox::getPlayerVelocity(){
	return mPlayerVelocity;
}

// Sound and music
sf::SoundBuffer& Toolbox::getSound(SOUNDKEY soundKey) {
	switch (soundKey) {
	case Toolbox::PLAYERIDLE:
		return mPlayerIdleSound;
		break;
	case Toolbox::PLAYERRUN:
		return mPlayerRunSound;
		break;
	case Toolbox::PLAYERJUMP:
		return mPlayerJumpSound;
		break;
	case Toolbox::PLAYERLAND:
		break;
	case Toolbox::PLAYERDAMAGED:
		return mPlayerDamagedSound;
		break;
	case Toolbox::WORMIDLE:
		break;
	case Toolbox::WORMRUN:
		break;
	case Toolbox::WORMJUMP:
		break;
	case Toolbox::WORMLAND:
		break;
	default:
		break;
	}
}

sf::Music& Toolbox::getMusic(SOUNDKEY soundKey) {
	switch (soundKey) {
	case Toolbox::STOMACHAMBIENCE:
		return mStomachAmbience;
		break;
	case Toolbox::STOMACHMUSIC:
		return mStomachMusic;
		break;
	default:
		break;
	}
}