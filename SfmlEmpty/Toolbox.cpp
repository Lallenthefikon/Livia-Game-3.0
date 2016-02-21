#include "Toolbox.h"

static sf::Sprite mPlayerSprite;
static sf::Vector2f mPlayerVelocity;

// Textures
static sf::Image mEnemy0sheet;
static sf::Image mBlock0sheet;
static sf::Image mPlayersheet;
static sf::Image mIdlePlayersheet;
static sf::Image mJumpingPlayersheet;
static sf::Image mHurtPlayersheet;
static sf::Image mSlidePlayersheet;

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
static sf::SoundBuffer mPlayerDeathSound;
static sf::SoundBuffer mWormDeathSound;
static sf::Music mStomachMusic;
static sf::Music mStomachAmbience;

// Fonts
static sf::Font mGameOverFont;

Toolbox& Toolbox::getInstance(){
	static Toolbox toolbox;
	return toolbox;
}

void Toolbox::loadTextures(std::string levelName){
	if (levelName == "Stomach"){
		mStomachBackgroundTexture.loadFromFile("resources/images/magsäck.jpg");
	}

	mEnemy0sheet.loadFromFile("resources/images/Mask spritesheet.png");
	mBlock0sheet.loadFromFile("resources/images/Current_block0_sheet.png");

	mPlayersheet.loadFromFile("resources/images/Current_livia_sheet.png");
	//mIdlePlayersheet.loadFromFile("resources/images/Livia_idle_spritesheet.png");

	mAcidMonsterTexture.loadFromFile("resources/images/Acid Monster.png");

	mTileTexture.loadFromFile("resources/images/Tile.png");
	mEditorMenyTexture.loadFromFile("resources/images/EditorMenu.png");
	
	mLifeTexture.loadFromFile("resources/images/Heart spritesheet.png");
}

void Toolbox::loadSounds(std::string levelName) {

	if (levelName == "Stomach") {
		// Load Tummy Acid Trip

		// Music and ambience
		//mStomachMusic.openFromFile("resources/sounds/music/stomach/SML - ex4.ogg");
		//mStomachAmbience.openFromFile("resources/sounds/music/stomach/Ambient_Stomach.ogg");
	}

	// Global effects
	//mPlayerIdleSound.loadFromFile("resources/sounds/effects/livia/jump_02.ogg");
	mPlayerRunSound.loadFromFile("resources/sounds/effects/livia/Walkcycle_01.ogg");
	mPlayerJumpSound.loadFromFile("resources/sounds/effects/livia/Jump_01.ogg");
	mPlayerDamagedSound.loadFromFile("resources/sounds/effects/livia/Hurt_02.ogg");
	mPlayerDeathSound.loadFromFile("resources/sounds/effects/livia/Death_01.ogg");

	mWormDeathSound.loadFromFile("resources/sounds/effects/worm/Death_01.ogg");

}

void Toolbox::loadFonts(std::string levelName) {
	mGameOverFont.loadFromFile("resources/fonts/ComicSansMSRegular.ttf");
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
		return mPlayersheet;
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

	case PLAYERSLIDETEXTURE:
		return mSlidePlayersheet;
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

sf::Vector2f Toolbox::findCoordPos(sf::Vector2i &pixelPos, sf::RenderWindow &window){
	sf::Vector2i pixel_pos = pixelPos;
	sf::Vector2f coord_pos = window.mapPixelToCoords(pixel_pos);
	return coord_pos;
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
	case Toolbox::PLAYERDEATH:
		return mPlayerDeathSound;
		break;
	case Toolbox::WORMIDLE:
		break;
	case Toolbox::WORMRUN:
		break;
	case Toolbox::WORMJUMP:
		break;
	case Toolbox::WORMLAND:
		break;
	case Toolbox::WORMDEATH:
		return mWormDeathSound;
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

sf::Font & Toolbox::getFont(FONTKEY fontKey) {
	switch (fontKey) {
	case Toolbox::GAMEOVER:
		return mGameOverFont;
		break;
	case Toolbox::DIALOGUE:
		break;
	default:
		break;
	}
}
