#include "Animations.h"

static sf::Image& mPlayerIMG(Toolbox::getTexture(Toolbox::RUNNINGPLAYERTEXTURE));
//static sf::Image& mPlayerIdleIMG(Toolbox::getTexture(Toolbox::WORMTEXTURE));

static sf::Image& mWormCrawlingIMG(Toolbox::getTexture(Toolbox::WORMTEXTURE));

static sf::Image& mAcidMonsterIMG(Toolbox::getTexture(Toolbox::ACIDMONSTERTEXTURE));

Animations::Textures mPlayerRunningANI;
Animations::Textures mPlayerFallingANI;
Animations::Textures mPlayerJumpingANI;
Animations::Textures mPlayerIdleANI;
	
Animations::Textures mWormCrawlingANI;

Animations::Textures mAcidMonsterANI;

void Animations::loadTextures(){
	int x = 0;
	int y = 0;

	// Player running ANI
	for (int i = 0; i < 16; i++){

		mPlayerRunningANI.push_back(new sf::Texture);
		mPlayerRunningANI[i]->loadFromImage(mPlayerIMG, sf::IntRect(100 * x, 140 * y, 100, 140));
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
		mPlayerIdleANI[i]->loadFromImage(mPlayerIMG, sf::IntRect((70 * x) + 400, (140 * y) + 640, 70, 140));
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
		mPlayerFallingANI[i]->loadFromImage(mPlayerIMG, sf::IntRect((100 * x) + 400, (160* y), 100, 160));
		x++;
		if (x == 4){
			x = 0;
			y++;
		}
	}
	x = 0;
	y = 0;


	/*mPlayerIdleANI.push_back(new sf::Texture);
	mPlayerIdleANI[0]->loadFromImage(mPlayerIdleIMG);*/
	

	// Worm crawling
	mWormCrawlingANI.push_back(new sf::Texture);
	mWormCrawlingANI[0]->loadFromImage(mWormCrawlingIMG);

	// Acidmonster

	mAcidMonsterANI.push_back(new sf::Texture);
	mAcidMonsterANI[0]->loadFromImage(mAcidMonsterIMG);
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




// Worm ANI
Animations::Textures* Animations::getWormCrawlingANI(){
	return &mWormCrawlingANI;
}

Animations::Textures* Animations::getAcidMonster(){
	return &mAcidMonsterANI;
}

