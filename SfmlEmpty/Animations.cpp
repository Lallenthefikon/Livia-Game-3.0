#include "Animations.h"

static sf::Image& mPlayerIMG(Toolbox::getTexture(Toolbox::PLAYERRUNNINGTEXTURE));
//static sf::Image& mPlayerIdleIMG(Toolbox::getTexture(Toolbox::WORMTEXTURE));

static sf::Image& mEnemy0IMG(Toolbox::getTexture(Toolbox::WORMTEXTURE));

static sf::Image& mAcidMonsterHorizontalIMG(Toolbox::getTexture(Toolbox::ACIDMONSTERHORIZONTALTEXTURE));
static sf::Image& mAcidMonsterVerticalIMG(Toolbox::getTexture(Toolbox::ACIDMONSTERVERTICALTEXTURE));

static sf::Image& mMeatballIMG(Toolbox::getTexture(Toolbox::MEATBALLTEXTURE));

static sf::Image& mHeartIMG(Toolbox::getTexture(Toolbox::LIFETEXTURE));

static sf::Image& mDialogueSpritesheetIMG(Toolbox::getTexture(Toolbox::DIALOGUETEXTURE));

static sf::Image& mDecorationIMG(Toolbox::getTexture(Toolbox::DECORATIONTEXTURE));

Animations::Textures mPlayerRunningANI;
Animations::Textures mPlayerFallingANI;
Animations::Textures mPlayerJumpingANI;
Animations::Textures mPlayerIdleANI;
Animations::Textures mPlayerDyingANI;
Animations::Textures mPlayerSlideANI;

Animations::Textures mWormDyingANI;
Animations::Textures mWormCrawlingANI;

Animations::Textures mAcidMonsterHorizontalANI;
Animations::Textures mAcidMonsterVerticalANI;
Animations::Textures mGermWalkingANI;
Animations::Textures mGermDamagedANI;

Animations::Textures mAcidMonsterANI;

Animations::Textures mMeatballANI;

Animations::Textures mHeartANI;

Animations::Textures mSpikesANI;

Animations::Textures mDecoration0ANI;
Animations::Textures mDecoration1ANI;

Animations::Textures mDialogueLiviaANI; 
Animations::Textures mDialogueMansaANI;
Animations::Textures mDialogueMuhninANI;
Animations::Textures mDialogueTummyANI;

void Animations::loadTextures(){
	int x = 0;
	int y = 0;

	// Player running ANI
	for (int i = 0; i < 16; i++){

		mPlayerRunningANI.push_back(new sf::Texture);
		mPlayerRunningANI[i]->loadFromImage(mPlayerIMG, sf::IntRect(100 * x, 140 * y, 100, 140));
		mPlayerRunningANI[i]->setSmooth(true);
		x++;
		if (x == 4){
			x = 0;
			y++;
		}
	}
	x = 0;
	y = 0;

	// Player jumping ANI
	for (int i = 0; i < 8; i++){

		mPlayerJumpingANI.push_back(new sf::Texture);
		mPlayerJumpingANI[i]->loadFromImage(mPlayerIMG, sf::IntRect(100 * x, (160 * y) + 560, 100, 160));
		mPlayerJumpingANI[i]->setSmooth(true);
		x++;
		if (x == 4){
			x = 0;
			y++;
		}
	}
	x = 0;
	y = 0;

	// Player idle ANI
	for (int i = 0; i < 16; i++){

		mPlayerIdleANI.push_back(new sf::Texture);
		mPlayerIdleANI[i]->loadFromImage(mPlayerIMG, sf::IntRect((70 * x) + 400, (140 * y) + 340, 70, 140));
		mPlayerIdleANI[i]->setSmooth(true);
		x++;
		if (x == 4){
			x = 0;
			y++;
		}
	}
	x = 0;
	y = 0;

	// Player falling ANI
	for (int i = 0; i < 8; i++){
		mPlayerFallingANI.push_back(new sf::Texture);
		mPlayerFallingANI[i]->loadFromImage(mPlayerIMG, sf::IntRect((100 * x) + 400, (160 * y), 100, 160));
		mPlayerFallingANI[i]->setSmooth(true);
		x++;
		if (x == 4){
			x = 0;
			y++;
		}
	}
	x = 0;
	y = 0;

	// Player Dying ANI
	for (int i = 0; i < 16; i++){
		mPlayerDyingANI.push_back(new sf::Texture);
		mPlayerDyingANI[i]->loadFromImage(mPlayerIMG, sf::IntRect((188 * x) + 800, (140* y), 188, 140));
		mPlayerDyingANI[i]->setSmooth(true);
		x++;
		if (x == 4){
			x = 0;
			y++;
		}
	}
	x = 0;
	y = 0;

	// Player Slide ANI
	for (int i = 0; i < 8; i++){
		mPlayerSlideANI.push_back(new sf::Texture);
		mPlayerSlideANI[i]->loadFromImage(mPlayerIMG, sf::IntRect((67 * x) + 700, (140 * y) + 600, 67, 140));
		mPlayerSlideANI[i]->setSmooth(true);
		x++;
		if (x == 4){
			x = 0;
			y++;
		}
	}
	x = 0;
	y = 0;

	// Worm crawling ANI
	for (int i = 0; i < 16; i++){
		mWormCrawlingANI.push_back(new sf::Texture);
		mWormCrawlingANI[i]->loadFromImage(mEnemy0IMG, sf::IntRect((75 * x), (35 * y), 75, 35));
		mWormCrawlingANI[i]->setSmooth(true);
		x++;
		if (x == 4){
			x = 0;
			y++;
		}
	}
	x = 0;
	y = 0;

	// Worm Dying ANI
	for (int i = 0; i < 8; i++){
		mWormDyingANI.push_back(new sf::Texture);
		mWormDyingANI[i]->loadFromImage(mEnemy0IMG, sf::IntRect((75 * x), (35 * y) + 140, 75, 35));
		mWormDyingANI[i]->setSmooth(true);
		x++;
		if (x == 4){
			x = 0;
			y++;
		}
	}
	x = 0;
	y = 0;

	// Germ Walking ANI
	for (int i = 0; i < 16; i++) {
		mGermWalkingANI.push_back(new sf::Texture);
		mGermWalkingANI[i]->loadFromImage(mEnemy0IMG, sf::IntRect((80 * x), (130 * y) + 216, 80, 130));
		mGermWalkingANI[i]->setSmooth(true);
		x++;
		if (x == 4) {
			x = 0;
			y++;
		}
	}
	x = 0;
	y = 0;

	// Germ damaged ANI
	for (int i = 0; i < 8; i++) {
		mGermDamagedANI.push_back(new sf::Texture);
		mGermDamagedANI[i]->loadFromImage(mEnemy0IMG, sf::IntRect((65 * x) + 333, (130 * y) + 200, 65, 130));
		mGermDamagedANI[i]->setSmooth(true);
		x++;
		if (x == 4) {
			x = 0;
			y++;
		}
	}
	x = 0;
	y = 0;

	// Acidmonster ANI
	for (int i = 0; i < 32; i++){
	mAcidMonsterHorizontalANI.push_back(new sf::Texture);
		mAcidMonsterHorizontalANI[i]->loadFromImage(mAcidMonsterHorizontalIMG, sf::IntRect((1131 * x), (1200 * y), 1131, 1200));
		mAcidMonsterHorizontalANI[i]->setSmooth(true);
		x++;
		if (x == 4){
			x = 0;
			y++;
		}
	}
	x = 0;
	y = 0;

	// Acidmonster vertical ANI
	for (int i = 0; i < 32; i++) {
		mAcidMonsterVerticalANI.push_back(new sf::Texture);
		mAcidMonsterVerticalANI[i]->loadFromImage(mAcidMonsterVerticalIMG, sf::IntRect((1920 * x), (1212 * y), 1920, 1212));
		mAcidMonsterVerticalANI[i]->setSmooth(true);
		x++;
		if (x == 4) {
			x = 0;
			y++;
		}
	}
	x = 0;
	y = 0;


	// Heart ANI
	for (int i = 0; i < 16; i++){
		mHeartANI.push_back(new sf::Texture);
		mHeartANI[i]->loadFromImage(mHeartIMG, sf::IntRect((75 * x), (100 * y), 75, 100));
		mHeartANI[i]->setSmooth(true);
		x++;
		if (x == 4){
			x = 0;
			y++;
		}
	}
	x = 0;
	y = 0;

	// Spikes ANI
	for (int i = 0; i < 16; i++){
		mSpikesANI.push_back(new sf::Texture);
		mSpikesANI[i]->loadFromImage(mEnemy0IMG, sf::IntRect((96 * x) + 300, (50 * y), 96, 50));
		mSpikesANI[i]->setSmooth(true);
		x++;
		if (x == 4){
			x = 0;
			y++;
		}
	}
	x = 0;
	y = 0;

	// Meatball ANI
	for (int i = 0; i < 16; i++) {
		mMeatballANI.push_back(new sf::Texture);
		mMeatballANI[i]->loadFromImage(mMeatballIMG, sf::IntRect((200 * x), (200 * y), 200, 200));
		mMeatballANI[i]->setSmooth(true);
		x++;
		if (x == 4) {
			x = 0;
			y++;
		}
	}
	x = 0;
	y = 0;

	// Dialogue ANI

	// Livia

	for (int i = 0; i < 32; i++) {
		mDialogueLiviaANI.push_back(new sf::Texture);
		mDialogueLiviaANI[i]->loadFromImage(mDialogueSpritesheetIMG, sf::IntRect((400 * x), (500 * y), 400, 500));
		mDialogueLiviaANI[i]->setSmooth(true);
		x++;
		if (x == 4) {
			x = 0;
			y++;
		}
	}
	x = 0;
	y = 0;

	// Mansa 

	for (int i = 0; i < 32; i++) {
		mDialogueMansaANI.push_back(new sf::Texture);
		mDialogueMansaANI[i]->loadFromImage(mDialogueSpritesheetIMG, sf::IntRect((400 * x) + 1600, (500 * y), 400, 500));
		mDialogueMansaANI[i]->setSmooth(true);
		x++;
		if (x == 4) {
			x = 0;
			y++;
		}
	}
	x = 0;
	y = 0;

	// Muhnin

	for (int i = 0; i < 32; i++) {
		mDialogueMuhninANI.push_back(new sf::Texture);
		mDialogueMuhninANI[i]->loadFromImage(mDialogueSpritesheetIMG, sf::IntRect((400 * x) + 4800, (500 * y), 400, 500));
		mDialogueMuhninANI[i]->setSmooth(true);
		x++;
		if (x == 4) {
			x = 0;
			y++;
		}
	}
	x = 0;
	y = 0;

	// Tummy

	for (int i = 0; i < 32; i++) {
		mDialogueTummyANI.push_back(new sf::Texture);
		mDialogueTummyANI[i]->loadFromImage(mDialogueSpritesheetIMG, sf::IntRect((400 * x) + 3200, (500 * y), 400, 500));
		mDialogueTummyANI[i]->setSmooth(true);
		x++;
		if (x == 4) {
			x = 0;
			y++;
		}
	}
	x = 0;
	y = 0;


	/*mMeatballANI.push_back(new sf::Texture);
	mMeatballANI[0]->loadFromImage(mMeatballIMG, sf::IntRect(0, 0, 400, 251));*/

	// Decoration sprite
	mDecoration0ANI.push_back(new sf::Texture);
	mDecoration0ANI[0]->loadFromImage(mDecorationIMG, sf::IntRect(0, 0, 100, 100));

	mDecoration1ANI.push_back(new sf::Texture);
	mDecoration1ANI[0]->loadFromImage(mDecorationIMG, sf::IntRect(100, 0, 100, 200));

}
// Player ANI

Animations::Textures* Animations::getPlayerRunningANI(){
	return &mPlayerRunningANI;
}

Animations::Textures* Animations::getPlayerJumpingANI(){
	return &mPlayerJumpingANI;
}

Animations::Textures* Animations::getPlayerIdleANI(){
	return &mPlayerIdleANI;
}

Animations::Textures* Animations::getPlayerFallingANI(){
	return &mPlayerFallingANI;
}

Animations::Textures* Animations::getPlayerDyingANI(){
	return &mPlayerDyingANI;
}

Animations::Textures* Animations::getPlayerSlideANI(){
	return &mPlayerSlideANI;
}

// Worm ANI
Animations::Textures* Animations::getWormCrawlingANI(){
	return &mWormCrawlingANI;
}

Animations::Textures* Animations::getWormDyingANI(){
	return &mWormDyingANI;
}

// Germ Walking ANI
Animations::Textures* Animations::getGermWalkingANI() {
	return &mGermWalkingANI;
}

Animations::Textures* Animations::getGermDamagedANI() {
	return &mGermDamagedANI;
}



// Acid Monster ANI
Animations::Textures* Animations::getAcidMonsterHorizontal(){
	return &mAcidMonsterHorizontalANI;
}

Animations::Textures* Animations::getAcidMonsterVertical() {
	return &mAcidMonsterVerticalANI;
}

// Meatball ANI
Animations::Textures* Animations::getMeatballANI() {
	return &mMeatballANI;
}

Animations::Textures* Animations::getHeartANI(){
	return &mHeartANI;
}

Animations::Textures* Animations::getSpikesANI(){
	return &mSpikesANI;
}

// Decoration ANI
Animations::Textures* Animations::getDecoration0ANI(){
	return &mDecoration0ANI;
}

Animations::Textures* Animations::getDecoration1ANI() {
	return &mDecoration1ANI;
}

// Dialogue ANI
Animations::Textures* Animations::getDialogueLiviaANI() {
	return &mDialogueLiviaANI;
}

Animations::Textures* Animations::getDialogueMansaANI() {
	return &mDialogueMansaANI;
}

Animations::Textures* Animations::getDialogueMuhninANI(){
	return &mDialogueMuhninANI;
}

Animations::Textures* Animations::getDialogueTummyANI() {
	return &mDialogueTummyANI;
}