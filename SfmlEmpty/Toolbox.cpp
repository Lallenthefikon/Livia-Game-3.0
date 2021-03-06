#include "Toolbox.h"
#include <iostream>

// Player Info
static sf::Sprite mPlayerSprite;
static sf::Vector2f mPlayerVelocity;
static sf::Vector2f mPlayerPosition;
static bool mPlayerAlive;
static int mPlayerHealth;
static float mFrameTime(0);
static float staticFrametime(0.0180);

// Level Info
static std::string mCurrentLevelName;
static std::string mCurrentLevelDirectory;
static sf::Vector2f mGravity(0, 20);
static sf::FloatRect mLevelBounds;


// Textures
static sf::Image mEnemy0sheet;
static sf::Image mBlock0sheet;
static sf::Image mTiledecSheet;
static sf::Image mPlayersheet;
static sf::Image mGoalTexture;
static sf::Image mDialogueTexture;
static sf::Image mMeatballTexture;
static sf::Image mMeatballSpawnerTexture;

// Stomach
static sf::Image mAcidMonsterHorizontalTexture;
static sf::Image mAcidMonsterVerticalTexture;
static sf::Image mStomachBackgroundTexture;
static sf::Image mStomachMiddlegroundTexture;
static sf::Image mAcidBottom;

// Hub
static sf::Image mHubBackground;
static sf::Image mHubMiddleground;

// Throat
static sf::Image mThroatBackground;
static sf::Image mThroatMiddleground;

// Mouth
static sf::Image mMouthBackground;
static sf::Image mMouthMiddleground;

// Intestine
static sf::Image mIntestineBackground;


static sf::Image mLifeTexture;

static sf::Image mTileTexture;
static sf::Image mEditorMenyTexture;

static sf::Image mDecorationTexture;
static sf::Image mDialogueBoxSpriteSheetIMG;
static sf::Image mDialogueSpriteSheetIMG;

// Camera
static sf::Vector2f mWindowSize;
static sf::Vector2f mResolution;
static sf::Vector2f mWindowPos;
static sf::FloatRect mGlobalCameraBounds;

// Sounds
static sf::SoundBuffer mPlayerIdleSound;
static sf::SoundBuffer mPlayerRunSound;
static sf::SoundBuffer mPlayerJumpSound1;
static sf::SoundBuffer mPlayerJumpSound2;
static sf::SoundBuffer mPlayerJumpSound3;
static sf::SoundBuffer mPlayerDamagedSound;
static sf::SoundBuffer mPlayerDeathSound;
static sf::SoundBuffer mPlayerFallDeathSound;
static sf::SoundBuffer mPlayerDrownSound;
static sf::SoundBuffer mPlayerWallSlideSound;
static sf::SoundBuffer mPlayerLandSound;

static sf::SoundBuffer mLiviaDialogueSound1;
static sf::SoundBuffer mLiviaDialogueSound2;
static sf::SoundBuffer mLiviaDialogueSound3;
static sf::SoundBuffer mLiviaDialogueSound4;
static sf::SoundBuffer mLiviaDialogueSound5;

static sf::SoundBuffer mMansaDialogueSound1;
static sf::SoundBuffer mMansaDialogueSound2;
static sf::SoundBuffer mMansaDialogueSound3;
static sf::SoundBuffer mMansaDialogueSound4;
static sf::SoundBuffer mMansaDialogueSound5;
static sf::SoundBuffer mMansaDialogueSound6;

static sf::SoundBuffer mMhuininDialogueSound1;
static sf::SoundBuffer mMhuininDialogueSound2;
static sf::SoundBuffer mMhuininDialogueSound3;
static sf::SoundBuffer mTummyDialogueSound;

static sf::SoundBuffer mWormDeathSound;
static sf::SoundBuffer mGermDeathSound;

static sf::SoundBuffer mTummyRunningSound;

static sf::Music mStomachMusic;
static sf::Music mStomachAmbience;
static sf::Music mThroatMusic;
static sf::Music mHubMusic;
static sf::Music mMouthMusic;
static sf::Music mInestineMusic;
static sf::SoundBuffer mAirHorn;

// Fonts
static sf::Font mGameOverFont;

static bool mPaused;

Toolbox& Toolbox::getInstance(){
	static Toolbox toolbox;
	return toolbox;
}

void Toolbox::loadTextures(std::string levelName) {

	if (mStomachBackgroundTexture.getSize().x <= 0)
		mStomachBackgroundTexture.loadFromFile("resources/images/background/Magsack mork suddig.png");
		
	if (mStomachMiddlegroundTexture.getSize().x <= 0)
		mStomachMiddlegroundTexture.loadFromFile("resources/images/background/mellangrund suddig.png");
		
	if (mAcidBottom.getSize().x <= 0)
		mAcidBottom.loadFromFile("resources/images/background/Magsyra suddig gulare.png");
		
	if (mDecorationTexture.getSize().x <= 0)
		mDecorationTexture.loadFromFile("resources/images/decoration/stomach/decoration_spritesheet.png");

	if (mTiledecSheet.getSize().x <= 0)
		mTiledecSheet.loadFromFile("resources/images/decoration/tiledec sheet.png");

	if (mHubBackground.getSize().x <= 0)
		mHubBackground.loadFromFile("resources/images/background/Hub bakgrund.png");
	
	if (mHubMiddleground.getSize().x <= 0)
		mHubMiddleground.loadFromFile("resources/images/background/moln current.png");
	
	if (mThroatBackground.getSize().x <= 0)
		mThroatBackground.loadFromFile("resources/images/background/strupe back current.png");

	if (mThroatMiddleground.getSize().x <= 0)
		mThroatMiddleground.loadFromFile("resources/images/background/Strupe kant h.png");

	if (mMouthBackground.getSize().x <= 0)
		mMouthBackground.loadFromFile("resources/images/background/mun bakgr suddif 0.2.png");

	if (mMouthMiddleground.getSize().x <= 0)
		mMouthMiddleground.loadFromFile("resources/images/background/T�nder.png");

	if (mIntestineBackground.getSize().x <= 0)
		mIntestineBackground.loadFromFile("resources/images/background/Tarm bakgrund.png");

	if (mEnemy0sheet.getSize().x <= 0)
	mEnemy0sheet.loadFromFile("resources/images/entities/Current_Enemy0_sheet.png");
	
	if (mBlock0sheet.getSize().x <= 0)
	mBlock0sheet.loadFromFile("resources/images/terrain/Current_block0_sheet 2.png");

	if (mGoalTexture.getSize().x <= 0)
	mGoalTexture.loadFromFile("resources/images/terrain/goal.jpg");

	if (mPlayersheet.getSize().x <= 0)
	mPlayersheet.loadFromFile("resources/images/entities/Current_livia_sheet.png");

	if (mAcidMonsterHorizontalTexture.getSize().x <= 0)
		mAcidMonsterHorizontalTexture.loadFromFile("resources/images/entities/tummy/Tummy_Horizontal.png");

	if (mAcidMonsterVerticalTexture.getSize().x <= 0)
	mAcidMonsterVerticalTexture.loadFromFile("resources/images/entities/tummy/Tummy_Vertical.png");

	if (mTileTexture.getSize().x <= 0)
	mTileTexture.loadFromFile("resources/images/map editor/Tile.png");
	
	if (mEditorMenyTexture.getSize().x <= 0)
	mEditorMenyTexture.loadFromFile("resources/images/map editor/EditorMenu.png");
	
	if (mLifeTexture.getSize().x <= 0)
	mLifeTexture.loadFromFile("resources/images/hud/Heart spritesheet.png");

	if (mMeatballTexture.getSize().x <= 0)
	mMeatballTexture.loadFromFile("resources/images/entities/Meatball_projectile_Spritesheet.png");
	
	if (mMeatballSpawnerTexture.getSize().x <= 0)
	mMeatballSpawnerTexture.loadFromFile("resources/images/terrain/meatball_spawner.png");

	if (mDialogueTexture.getSize().x <= 0) {
	mDialogueTexture.loadFromFile("resources/images/dialogue/Dialogue-bubble.png");
	
	if (mDialogueBoxSpriteSheetIMG.getSize().x <= 0)
	mDialogueBoxSpriteSheetIMG.loadFromFile("resources/images/dialogue/TextboxSpritesheet.png");
	mDialogueSpriteSheetIMG.loadFromFile("resources/images/dialogue/DialogueSpritesheet.png");
	}
}

void Toolbox::loadSounds(std::string levelName) {

		// Load Tummy Acid Trip
		mTummyRunningSound.loadFromFile("resources/sounds/effects/tummy/TummyAcidTrip.ogg");
		
		// Music and ambience
		mStomachMusic.openFromFile("resources/sounds/music/stomach/Mage.ogg");
		mStomachAmbience.openFromFile("resources/sounds/music/stomach/Ambient_Stomach.ogg");
		mThroatMusic.openFromFile("resources/sounds/music/stomach/Mage.ogg");
		mHubMusic.openFromFile("resources/sounds/music/hub/Hub.ogg");
	mMouthMusic.openFromFile("resources/sounds/music/mouth/Mouthie.ogg");
	mInestineMusic.openFromFile("resources/sounds/music/intestine/Intestine.ogg");

	// Global effects
	mPlayerRunSound.loadFromFile("resources/sounds/effects/livia/walking/Walkcycle_01.ogg");
	mPlayerJumpSound1.loadFromFile("resources/sounds/effects/livia/jumps/Jump_01.ogg");
	mPlayerJumpSound2.loadFromFile("resources/sounds/effects/livia/jumps/Jump_05.ogg");
	mPlayerJumpSound3.loadFromFile("resources/sounds/effects/livia/jumps/Jump_06.ogg");
	mPlayerDamagedSound.loadFromFile("resources/sounds/effects/livia/damage/Hurt_02.ogg");
	mPlayerDeathSound.loadFromFile("resources/sounds/effects/livia/deaths/Death_01.ogg");
	mPlayerFallDeathSound.loadFromFile("resources/sounds/effects/livia/deaths/Death_Fall_01.ogg");
	mPlayerWallSlideSound.loadFromFile("resources/sounds/effects/livia/wall jump/wall_01.ogg");
	mPlayerLandSound.loadFromFile("resources/sounds/effects/livia/landing/Landing_03.ogg");
	mPlayerDrownSound.loadFromFile("resources/sounds/effects/livia/deaths/Death_Drown_01.ogg");
	
	mLiviaDialogueSound1.loadFromFile("resources/sounds/effects/livia/dialogue/Dialogue_14.ogg");
	mLiviaDialogueSound2.loadFromFile("resources/sounds/effects/livia/dialogue/Dialogue_12.ogg");
	mLiviaDialogueSound3.loadFromFile("resources/sounds/effects/livia/dialogue/Dialogue_02.ogg");
	mLiviaDialogueSound4.loadFromFile("resources/sounds/effects/livia/dialogue/Dialogue_11.ogg");
	mLiviaDialogueSound5.loadFromFile("resources/sounds/effects/livia/dialogue/Dialogue_05.ogg");
	
	mMansaDialogueSound1.loadFromFile("resources/sounds/effects/mansa/dialogue/Dialogue_06.ogg");
	mMansaDialogueSound2.loadFromFile("resources/sounds/effects/mansa/dialogue/Dialogue_17.ogg");
	mMansaDialogueSound3.loadFromFile("resources/sounds/effects/mansa/dialogue/Dialogue_03.ogg");
	mMansaDialogueSound4.loadFromFile("resources/sounds/effects/mansa/dialogue/Dialogue_14.ogg");
	mMansaDialogueSound5.loadFromFile("resources/sounds/effects/mansa/dialogue/Dialogue_18.ogg");
	mMansaDialogueSound6.loadFromFile("resources/sounds/effects/mansa/dialogue/Dialogue_02.ogg");
	
	mTummyDialogueSound.loadFromFile("resources/sounds/effects/tummy/dialogue/Dialogue_01.ogg");
	
	mMhuininDialogueSound1.loadFromFile("resources/sounds/effects/mhuinin/dialogue/Dialogue_01.ogg");
	mMhuininDialogueSound2.loadFromFile("resources/sounds/effects/mhuinin/dialogue/Dialogue_07.ogg");
	mMhuininDialogueSound3.loadFromFile("resources/sounds/effects/mhuinin/dialogue/Dialogue_08.ogg");



	mWormDeathSound.loadFromFile("resources/sounds/effects/worm/Death_01.ogg");
	mGermDeathSound.loadFromFile("resources/sounds/effects/germ/Death_01.ogg");

	mAirHorn.loadFromFile("resources/sounds/effects/Air_Horn_Sound_Effect.ogg");

}

void Toolbox::loadFonts(std::string levelName) {
	mGameOverFont.loadFromFile("resources/fonts/Barokah.ttf");
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

	case ACIDMONSTERVERTICALTEXTURE:
		return mAcidMonsterVerticalTexture;
		break;

	case ACIDMONSTERHORIZONTALTEXTURE:
		return mAcidMonsterHorizontalTexture;
		break;

	case STOMACHBACKGROUND:
		return mStomachBackgroundTexture;
		break;

	case STOMACHMIDDLEGROUND:
		return mStomachMiddlegroundTexture;
		break;

	case HUBBACKGROUND:
		return mHubBackground;
		break;

	case HUBMIDDLEGROUND:
		return mHubMiddleground;
		break;

	case THROATBACKGROUND:
		return mThroatBackground;
		break;

	case THROATMIDDLEGROUNDRIGHT:
		return mThroatMiddleground;
		break;

	case THROATMIDDLEGROUNDLEFT:
		return mThroatMiddleground;
		break;

	case MOUTHBACKGROUND:
		return mMouthBackground;
		break;

	case MOUTHMIDDLEGROUND:
		return mMouthMiddleground;
		break;

	case INTESTINEBACKGROUND:
		return mIntestineBackground;
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

	case DIALOGUEMAPEDITORTEXTURE:
		return mDialogueTexture;
		break;

	case DIALOGUEBOXSHEET:
		return mDialogueBoxSpriteSheetIMG;
		break;

	case DIALOGUETEXTURE:
		return mDialogueSpriteSheetIMG;
		break;

	case MEATBALLTEXTURE:
		return mMeatballTexture;
		break;

	case MEATBALLSPAWNERTEXTURE:
		return mMeatballSpawnerTexture;
		break;

	case TILEDECSHEET:
		return mTiledecSheet;
		break;

	default:
		break;
	}
}

void Toolbox::copyScreenInfo(sf::RenderWindow &window, sf::VideoMode &videoMode){
	mWindowSize = sf::Vector2f(window.getSize());
	mResolution.x = videoMode.width;
	mResolution.y = videoMode.height;
	mWindowPos = sf::Vector2f(window.getPosition());
}

void Toolbox::setWindowSize(sf::RenderWindow &window) {
	mWindowSize = sf::Vector2f(window.getSize());
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

void Toolbox::copyCurrentLevelName(std::string newLevelName){
	mCurrentLevelName = newLevelName;
}

std::string Toolbox::getCurrentLevelName(){
	return mCurrentLevelName;
}

void Toolbox::copyCurrentLevelDirectory(std::string newDirectory) {
	mCurrentLevelDirectory = newDirectory;
}

std::string Toolbox::getCurrentLevelDirectory() {
	return mCurrentLevelDirectory;
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

void Toolbox::copyPlayerHealth(int i) {
	mPlayerHealth = i;
}

int Toolbox::getPlayerHealth() {
	return mPlayerHealth;
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
	case Toolbox::PLAYERJUMP1:
		return mPlayerJumpSound1;
		break;
	case Toolbox::PLAYERJUMP2:
		return mPlayerJumpSound2;
		break;
	case Toolbox::PLAYERJUMP3:
		return mPlayerJumpSound3;
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
	case Toolbox::PLAYERDROWN:
		return mPlayerDrownSound;
		break;
	case Toolbox::SPEAKERLIVIASOUND1:
		return mLiviaDialogueSound1;
		break;
	case Toolbox::SPEAKERLIVIASOUND2:
		return mLiviaDialogueSound2;
		break;
	case Toolbox::SPEAKERLIVIASOUND3:
		return mLiviaDialogueSound3;
		break;
	case Toolbox::SPEAKERLIVIASOUND4:
		return mLiviaDialogueSound4;
		break;
	case Toolbox::SPEAKERLIVIASOUND5:
		return mLiviaDialogueSound5;
		break;
	case Toolbox::SPEAKERMANSASOUND1:
		return mMansaDialogueSound1;
		break;
	case Toolbox::SPEAKERMANSASOUND2:
		return mMansaDialogueSound2;
		break;
	case Toolbox::SPEAKERMANSASOUND3:
		return mMansaDialogueSound3;
		break;
	case Toolbox::SPEAKERMANSASOUND4:
		return mMansaDialogueSound4;
		break;
	case Toolbox::SPEAKERMANSASOUND5:
		return mMansaDialogueSound5;
		break;
	case Toolbox::SPEAKERMANSASOUND6:
		return mMansaDialogueSound6;
		break;
	case Toolbox::SPEAKERTUMMYSOUND:
		return mTummyDialogueSound;
		break;
	case Toolbox::SPEAKERMHUININSOUND1:
		return mMhuininDialogueSound1;
		break;
	case Toolbox::SPEAKERMHUININSOUND2:
		return mMhuininDialogueSound2;
		break;
	case Toolbox::SPEAKERMHUININSOUND3:
		return mMhuininDialogueSound3;
		break;
	case Toolbox::WORMIDLE:
		return mAirHorn;		// Temporary lol (Jk, Final)
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
	case Toolbox::GERMDEATH:
		return mGermDeathSound;
		break;
	case Toolbox::TUMMYRUNNING:
		return mTummyRunningSound;
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
	case Toolbox::THROATMUSIC:
		return mThroatMusic;
		break;
	case Toolbox::MOUTHMUSIC:
		return mMouthMusic;
		break;
	case Toolbox::HUBMUSIC:
		return mHubMusic;
		break;
	case Toolbox::INTESTINEMUSIC:
		return mInestineMusic;
		break;
	default:
		break;
	}
}

sf::Font& Toolbox::getFont(FONTKEY fontKey) {
	switch (fontKey) {
	case Toolbox::GAMEOVER:
		return mGameOverFont;
		break;
	case Toolbox::DIALOGUE:
		return mGameOverFont;
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
	//return mFrameTime;
	return staticFrametime;
}

void Toolbox::copyGravity(sf::Vector2f &gravity) {
	mGravity = gravity;
}

sf::Vector2f& Toolbox::getGravity() {
	return mGravity;
	//std::cout << "Gravity Y: " << mGravity.y << std::endl;
}

void Toolbox::setGamePaused(bool isPaused) {
	mPaused = isPaused;
}

bool Toolbox::getGamePaused() {
	return mPaused;
}