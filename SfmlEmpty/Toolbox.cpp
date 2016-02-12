#include "Toolbox.h"

static sf::Sprite mPlayerSprite;

// Textures
static sf::Image mEnemy0sheet;
static sf::Image mBlock0sheet;
static sf::Image mPlayersheet;
static sf::Image mPlayerIdlesheet;
static sf::Image mAcidMonsterTexture;

static sf::Image mTileTexture;
static sf::Image mEditorMenyTexture;

// Camera edit
static sf::Vector2f mWindowSize;
static sf::Vector2f mResolution;
static sf::Vector2f mWindowPos;

// Sounds
static sf::SoundBuffer mPlayerSound;
static sf::SoundBuffer mPlayerSoundExtra;
static sf::SoundBuffer mWormSound;
static sf::SoundBuffer mWormSoundExtra;

Toolbox& Toolbox::getInstance(){
	static Toolbox toolbox;
	return toolbox;
}

void Toolbox::loadTextures(){
	mEnemy0sheet.loadFromFile("resources/images/Mask.png");
	mBlock0sheet.loadFromFile("resources/images/TileSheet_6.png");

	mPlayersheet.loadFromFile("resources/images/Livia_spritesheet_placeholder LR-Comb v.2.1.fw.png");
	mPlayerIdlesheet.loadFromFile("resources/images/livia_idle_spritesheet_dubble.png");

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

	case PLAYERTEXTURE:
		return mPlayersheet;
		break;

	case PLAYERIDLETEXTURE:
		return mPlayerIdlesheet;
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

sf::SoundBuffer& Toolbox::getSoundExtra(SOUNDKEY soundKey) {
	switch (soundKey) {
	case Toolbox::PLAYERIDLE:
		mPlayerSoundExtra.loadFromFile("resources/sounds/Jump_03.ogg");
		return mPlayerSoundExtra;
		break;
	case Toolbox::PLAYERRUN:
		break;
	case Toolbox::PLAYERJUMP:
		mPlayerSoundExtra.loadFromFile("resources/sounds/Jump_01.ogg");
		return mPlayerSoundExtra;
		break;
	case Toolbox::PLAYERLAND:
		break;
	case Toolbox::PLAYERDAMAGED:
		mPlayerSoundExtra.loadFromFile("resources/sounds/Jump_02.ogg");
		return mPlayerSoundExtra;
		break;
	case Toolbox::WORMIDLE:
		return mWormSoundExtra;
		break;
	case Toolbox::WORMRUN:
		return mWormSoundExtra;
		break;
	case Toolbox::WORMJUMP:
		return mWormSoundExtra;
		break;
	case Toolbox::WORMLAND:
		return mWormSoundExtra;
		break;
	default:
		return mPlayerSoundExtra;
		break;
	}
}