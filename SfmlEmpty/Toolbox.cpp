#include "Toolbox.h"

static sf::Sprite mPlayerSprite;

// Textures
static sf::Image mEnemy0sheet;
static sf::Image mBlock0sheet;
static sf::Image mRunningPlayersheet;
static sf::Image mIdlePlayersheet;
static sf::Image mJumpingPlayersheet;
static sf::Image mHurtPlayersheet;
static sf::Image mAcidMonsterTexture;
static sf::Image mIntestineBackgroundTexture;

static sf::Image mTileTexture;
static sf::Image mEditorMenyTexture;

// Camera edit
static sf::Vector2f mWindowSize;
static sf::Vector2f mResolution;
static sf::Vector2f mWindowPos;

// Sounds
static sf::SoundBuffer mPlayerSound;
static sf::SoundBuffer mWormSound;

Toolbox& Toolbox::getInstance(){
	static Toolbox toolbox;
	return toolbox;
}

void Toolbox::loadTextures(std::string levelName){
	if (levelName == "Intestine"){
		mIntestineBackgroundTexture.loadFromFile("resources/images/Tarm_BG");
	}

	mEnemy0sheet.loadFromFile("resources/images/Mask.png");
	mBlock0sheet.loadFromFile("resources/images/Current_block0_sheet.png");

	mRunningPlayersheet.loadFromFile("resources/images/Livia_spritesheet_placeholder1.2(100,140).png");
	mIdlePlayersheet.loadFromFile("resources/images/Livia_idle_spritesheet.png");

	mAcidMonsterTexture.loadFromFile("resources/images/AcidMonster.png");

	mTileTexture.loadFromFile("resources/images/Tile.png");
	mEditorMenyTexture.loadFromFile("resources/images/EditorMenu.png");
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

	case INTESTINEBACKGROUND:
		return mIntestineBackgroundTexture;
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

void Toolbox::copyPlayerInfo(sf::Sprite &playerSprite){
	mPlayerSprite = playerSprite;
}

sf::Sprite Toolbox::getPlayerSprite(){
	return mPlayerSprite;
}

// Sounds
sf::SoundBuffer& Toolbox::getSound(SOUNDKEY soundKey) {
	switch (soundKey) {
	case Toolbox::PLAYERIDLE:
		mPlayerSound.loadFromFile("resources/sounds/Jump_03.ogg");
		return mPlayerSound;
		break;
	case Toolbox::PLAYERRUN:
		break;
	case Toolbox::PLAYERJUMP:
		mPlayerSound.loadFromFile("resources/sounds/Jump_01.ogg");
		return mPlayerSound;
		break;
	case Toolbox::PLAYERLAND:
		break;
	case Toolbox::PLAYERDAMAGED:
		mPlayerSound.loadFromFile("resources/sounds/Jump_02.ogg");
		return mPlayerSound;
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
		return mPlayerSound;
		break;
	}
}