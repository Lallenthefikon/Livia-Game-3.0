#include "Animations.h"

static sf::Image& mPlayerRunningIMG(Toolbox::getTexture(Toolbox::PLAYERTEXTURE));
static sf::Image& mPlayerJumpingIMG(Toolbox::getTexture(Toolbox::BLOCK0TEXTURE));
static sf::Image& mPlayerIdleIMG(Toolbox::getTexture(Toolbox::WORMTEXTURE));

static sf::Image& mWormCrawlingIMG(Toolbox::getTexture(Toolbox::WORMTEXTURE));

Animations::Textures mPlayerRunningLeftANI;
Animations::Textures mPlayerRunningRightANI;
Animations::Textures mPlayerJumpingANI;
Animations::Textures mPlayerIdleANI;
	
Animations::Textures mWormCrawlingANI;

void Animations::loadTextures(){
	int x = 0;
	int y = 0;

	// Player running ANI
	for (int i = 0; i < 16; i++){
	
		mPlayerRunningLeftANI.push_back(new sf::Texture);
		mPlayerRunningLeftANI[i]->loadFromImage(mPlayerRunningIMG, sf::IntRect(100 * x, 140 * y, 100, 139));
		x++;
		if (x == 4){
			x = 0;
			y++;
		}
	}
	x = 0;
	y = 0;

	for (int i = 0; i < 16; i++){
		mPlayerRunningRightANI.push_back(new sf::Texture);
		mPlayerRunningRightANI[i]->loadFromImage(mPlayerRunningIMG, sf::IntRect((100 * x) + 400, 140 * y, 100, 139));
		x++;
		if (x == 4){
			x = 0;
			y++;
		}
	}

	// Player jumping ANI
	for (int i = 0; i < 16; i++){

		mPlayerJumpingANI.push_back(new sf::Texture);
		mPlayerJumpingANI[i]->loadFromImage(mPlayerJumpingIMG, sf::IntRect(70 * x, 70 * y, 70, 70));
		x++;
		if (x == 4){
			x = 0;
			y++;
		}
	}
	x = 0;
	y = 0;

	// Player idle ANI
	mPlayerIdleANI.push_back(new sf::Texture);
	mPlayerIdleANI[0]->loadFromImage(mPlayerIdleIMG);


	// Worm crawling
	mWormCrawlingANI.push_back(new sf::Texture);
	mWormCrawlingANI[0]->loadFromImage(mWormCrawlingIMG);
}

// Player ANI

Animations::Textures* Animations::getPlayerRunningLeftANI(){
	return &mPlayerRunningLeftANI;
}

Animations::Textures* Animations::getPlayerRunningRightANI(){
	return &mPlayerRunningRightANI;
}


Animations::Textures* Animations::getPlayerJumpingANI(){
	return &mPlayerJumpingANI;
}

Animations::Textures* Animations::getPlayerIdleANI(){
	return &mPlayerIdleANI;
}


// Worm ANI
Animations::Textures* Animations::getWormCrawlingRightANI(){
	return &mWormCrawlingANI;
}

Animations::Textures* Animations::getWormCrawlingLeftANI(){
	return &mWormCrawlingANI;
}