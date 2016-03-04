#include "Toolbox.h"
#include <iostream>

// Player Info
static sf::Sprite mPlayerSprite;
static sf::Vector2f mPlayerVelocity;
static sf::Vector2f mPlayerPosition;
static bool mPlayerAlive;

static float mFrameTime(0);

// Level Info
static sf::Vector2f mGravity(0, 125);
static sf::FloatRect mLevelBounds;


// Textures
static sf::Image mEnemy0sheet;
static sf::Image mBlock0sheet;
static sf::Image mPlayersheet;
static sf::Image mGoalTexture;
static sf::Image mDialogueTexture;
static sf::Image mMeatballTexture;
static sf::Image mMeatballSpawnerTexture;

static sf::Image mAcidMonsterHorizontalTexture;
static sf::Image mAcidMonsterVerticalTexture;
static sf::Image mStomachBackgroundTexture;
static sf::Image mAcidBottom;
static sf::Image mLifeTexture;

static sf::Image mTileTexture;
static sf::Image mEditorMenyTexture;

static sf::Image mDecorationTexture;

// Camera
static sf::Vector2f mWindowSize;
static sf::Vector2f mResolution;
static sf::Vector2f mWindowPos;
static sf::FloatRect mGlobalCameraBounds;

// Sounds
static sf::SoundBuffer mPlayerIdleSound;
static sf::SoundBuffer mPlayerRunSound;
static sf::SoundBuffer mPlayerJumpSound;
static sf::SoundBuffer mPlayerDamagedSound;
static sf::SoundBuffer mPlayerDeathSound;
static sf::SoundBuffer mPlayerFallDeathSound;
static sf::SoundBuffer mPlayerWallSlideSound;
static sf::SoundBuffer mPlayerLandSound;
static sf::SoundBuffer mWormDeathSound;
static sf::Music mStomachMusic;
static sf::Music mStomachAmbience;
static sf::SoundBuffer mAirHorn;

// Fonts
static sf::Font mGameOverFont;

Toolbox& Toolbox::getInstance(){
	static Toolbox toolbox;
	return toolbox;
}

void Toolbox::loadTextures(std::string levelName){
	if (levelName == "Stomach"){
		mStomachBackgroundTexture.loadFromFile("resources/images/background/Magsack mork suddig.png");
		mAcidBottom.loadFromFile("resources/images/background/Magsyra suddig gulare.png");
		mDecorationTexture.loadFromFile("resources/images/decoration/decoration_spritesheet.png");
	}

	mEnemy0sheet.loadFromFile("resources/images/entities/Current_Enemy0_sheet.png");
	mBlock0sheet.loadFromFile("resources/images/terrain/Current_block0_sheet 2.png");
	mGoalTexture.loadFromFile("resources/images/terrain/goal.jpg");

	mPlayersheet.loadFromFile("resources/images/entities/Current_livia_sheet.png");

	//mAcidMonsterHorizontalTexture.loadFromFile("resources/images/entities/tummy/Tummy.png");
	mAcidMonsterVerticalTexture.loadFromFile("resources/images/entities/tummy/Tummy upp.png");

	mTileTexture.loadFromFile("resources/images/map editor/Tile.png");
	mEditorMenyTexture.loadFromFile("resources/images/map editor/EditorMenu.png");
	
	mLifeTexture.loadFromFile("resources/images/hud/Heart spritesheet.png");

	mMeatballTexture.loadFromFile("resources/images/entities/Meatball_projectile_Spritesheet.png");
	mMeatballSpawnerTexture.loadFromFile("resources/images/terrain/meatball_spawner.png");
	mDialogueTexture.loadFromFile("resources/images/dialogue/Dialogue-bubble.png");
}

void Toolbox::loadSounds(std::string levelName) {

	if (levelName == "Stomach") {
		// Load Tummy Acid Trip

		// Music and ambience
		mStomachMusic.openFromFile("resources/sounds/music/stomach/Mage.ogg");
		mStomachAmbience.openFromFile("resources/sounds/music/stomach/Ambient_Stomach.ogg");
	}

	// Global effects
	//mPlayerIdleSound.loadFromFile("resources/sounds/effects/livia/jump_02.ogg");
	mPlayerRunSound.loadFromFile("resources/sounds/effects/livia/walking/Walkcycle_01.ogg");
	mPlayerJumpSound.loadFromFile("resources/sounds/effects/livia/jumps/Jump_01.ogg");
	mPlayerDamagedSound.loadFromFile("resources/sounds/effects/livia/damage/Hurt_02.ogg");
	mPlayerDeathSound.loadFromFile("resources/sounds/effects/livia/deaths/Death_01.ogg");
	mPlayerFallDeathSound.loadFromFile("resources/sounds/effects/livia/deaths/Death_Fall_01.ogg");
	mPlayerWallSlideSound.loadFromFile("resources/sounds/effects/livia/wall jump/wall_01.ogg");
	mPlayerLandSound.loadFromFile("resources/sounds/effects/livia/landing/Landing_03.ogg");

	mWormDeathSound.loadFromFile("resources/sounds/effects/worm/Death_01.ogg");

	mAirHorn.loadFromFile("resources/sounds/effects/Air_Horn_Sound_Effect.ogg");

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

	case PLAYERRUNNINGTEXTURE:
		return mPlayersheet;
		break;

	case TILETEXTURE:
		return mTileTexture;
		break;

	case EDITORMENY:
		return mEditorMenyTexture;
		break;

	case ACIDMONSTERTEXTURE:
		//return mAcidMonsterVerticalTexture;
		return mAcidMonsterHorizontalTexture;
		break;

	case STOMACHBACKGROUND:
		return mStomachBackgroundTexture;
		break;

	case LIFETEXTURE:
		return mLifeTexture;
		break;

	case GOALTEXTURE:
		return mGoalTexture;
		break;

	case STOMACHACID:
		return mAcidBottom;
		break;

	case DECORATIONTEXTURE:
		return mDecorationTexture;
		break;

	case DIALOGUETEXTURE:
		return mDialogueTexture;
		break;

	case MEATBALLTEXTURE:
		return mMeatballTexture;
		break;

	case MEATBALLSPAWNERTEXTURE:
		return mMeatballSpawnerTexture;
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

void Toolbox::copyCameraInfo(sf::Vector2f &globalCameraCenter, sf::Vector2f &localCameraBounds){
	mGlobalCameraBounds.left = globalCameraCenter.x - mWindowSize.x/2;
	mGlobalCameraBounds.width = globalCameraCenter.x + mWindowSize.x/2;
	mGlobalCameraBounds.top = globalCameraCenter.y - mWindowSize.x/2;
	mGlobalCameraBounds.height = globalCameraCenter.y + mWindowSize.y/2;
}

sf::FloatRect Toolbox::getGlobalCameraBounds(){
	return mGlobalCameraBounds;
}

void Toolbox::copyLevelBounds(sf::FloatRect &levelBounds){
	mLevelBounds = levelBounds;
}

sf::FloatRect Toolbox::getLevelBounds(){
	 return mLevelBounds;
}

void Toolbox::copyPlayerSprite(sf::Sprite &playerSprite){
	mPlayerSprite = playerSprite;
}

void Toolbox::copyPlayerVelocity(sf::Vector2f &playerVelocity){
	mPlayerVelocity = playerVelocity;
}

void Toolbox::copyPlayerPosition(sf::Vector2f playerPosition) {
	mPlayerPosition = playerPosition;
}

void Toolbox::copyPlayerIsAlive(bool isAlive){
	mPlayerAlive = isAlive;
}

sf::Sprite Toolbox::getPlayerSprite(){
	return mPlayerSprite;
}

sf::Vector2f Toolbox::getPlayerVelocity(){
	return mPlayerVelocity;
}

sf::Vector2f Toolbox::getPlayerPosition() {
	return mPlayerPosition;
}

bool Toolbox::getPlayerIsAlive(){
	return mPlayerAlive;
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
		return mPlayerLandSound;
		break;
	case Toolbox::PLAYERDAMAGED:
		return mPlayerDamagedSound;
		break;
	case Toolbox::PLAYERDEATH:
		return mPlayerDeathSound;
		break;
	case Toolbox::PLAYERFALLDEATH:
		return mPlayerFallDeathSound;
		break;
	case Toolbox::PLAYERWALLSLIDE:
		return mPlayerWallSlideSound;
		break;
	case Toolbox::WORMIDLE:
		return mAirHorn;		// Temporary lol
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

void Toolbox::copyFrameTime(float &frameTime) {
	mFrameTime = frameTime;
	if (mFrameTime > 0.032) {
		mFrameTime = 0.032;
	}
	//std::cout << "Frame time: " << mFrameTime << std::endl;
}

float& Toolbox::getFrameTime() {
	return mFrameTime;
}

void Toolbox::copyGravity(sf::Vector2f &gravity) {
	mGravity = gravity;
}

sf::Vector2f& Toolbox::getGravity() {
	return mGravity;
	//std::cout << "Gravity Y: " << mGravity.y << std::endl;
}