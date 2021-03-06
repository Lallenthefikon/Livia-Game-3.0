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
Animations::Textures mPlayerFallDyingANI;
Animations::Textures mPlayerDyingANI;
Animations::Textures mPlayerDamageANI;
Animations::Textures mPlayerSlideANI;

Animations::Textures mWormDyingANI;
Animations::Textures mWormCrawlingANI;

Animations::Textures mAcidMonsterHorizontalANI;
Animations::Textures mAcidMonsterVerticalANI;

Animations::Textures mGermWalkingANI;
Animations::Textures mGermDamagedANI;

Animations::Textures mAcidMonsterANI;

Animations::Textures mOcto_PiANI;
Animations::Textures mOcto_PiDeathANI;

Animations::Textures mMeatballANI;

Animations::Textures mHeartANI;

Animations::Textures mSpikesANI;

Animations::Textures mDecoration0ANI;
Animations::Textures mDecoration1ANI;
Animations::Textures mDecoration2ANI;
Animations::Textures mDecoration3ANI;
Animations::Textures mDecoration4ANI;
Animations::Textures mDecoration5ANI;
Animations::Textures mDecoration6ANI;
Animations::Textures mDecoration7ANI;
Animations::Textures mDecoration8ANI;
Animations::Textures mDecoration9ANI;
Animations::Textures mDecoration10ANI;
Animations::Textures mDecoration11ANI;
Animations::Textures mDecoration12ANI;
Animations::Textures mDecoration13ANI;
Animations::Textures mDecoration14ANI;
Animations::Textures mDecoration15ANI;
Animations::Textures mDecoration16ANI;
Animations::Textures mDecoration17ANI;
Animations::Textures mDecoration18ANI;
Animations::Textures mDecoration19ANI;
Animations::Textures mDecoration20ANI;
Animations::Textures mDecoration21ANI;
Animations::Textures mDecoration22ANI;
Animations::Textures mDecoration23ANI;
Animations::Textures mDecoration24ANI;
Animations::Textures mDecoration25ANI;
Animations::Textures mDecoration26ANI;
Animations::Textures mDecoration27ANI;
Animations::Textures mDecoration28ANI;
Animations::Textures mDecoration29ANI;

Animations::Textures mTileDecTextures;

Animations::Textures mDialogueLiviaANI; 
Animations::Textures mDialogueMansaANI;
Animations::Textures mDialogueMuhninANI;
Animations::Textures mDialogueTummyANI;

void Animations::loadTextures() {
	int x = 0;
	int y = 0;

	// Player running ANI
	if (mPlayerRunningANI.size() == 0) {
		for (int i = 0; i < 16; i++) {

			mPlayerRunningANI.push_back(new sf::Texture);
			mPlayerRunningANI[i]->loadFromImage(mPlayerIMG, sf::IntRect(100 * x, 140 * y, 100, 140));
			mPlayerRunningANI[i]->setSmooth(true);
			x++;
			if (x == 4) {
				x = 0;
				y++;
			}
		}
		x = 0;
		y = 0;
	}


	// Player jumping ANI
	if (mPlayerJumpingANI.size() == 0) {
		for (int i = 0; i < 8; i++) {

			mPlayerJumpingANI.push_back(new sf::Texture);
			mPlayerJumpingANI[i]->loadFromImage(mPlayerIMG, sf::IntRect(100 * x, (160 * y) + 560, 100, 160));
			mPlayerJumpingANI[i]->setSmooth(true);
			x++;
			if (x == 4) {
				x = 0;
				y++;
			}
		}
		x = 0;
		y = 0;
	}

	// Player idle ANI
	if (mPlayerIdleANI.size() == 0) {
		for (int i = 0; i < 16; i++) {

			mPlayerIdleANI.push_back(new sf::Texture);
			mPlayerIdleANI[i]->loadFromImage(mPlayerIMG, sf::IntRect((70 * x) + 400, (140 * y) + 340, 70, 140));
			mPlayerIdleANI[i]->setSmooth(true);
			x++;
			if (x == 4) {
				x = 0;
				y++;
			}
		}
		x = 0;
		y = 0;
	}

	// Player falling ANI
	if (mPlayerFallingANI.size() == 0) {
		for (int i = 0; i < 8; i++) {
			mPlayerFallingANI.push_back(new sf::Texture);
			mPlayerFallingANI[i]->loadFromImage(mPlayerIMG, sf::IntRect((100 * x) + 400, (160 * y), 100, 160));
			mPlayerFallingANI[i]->setSmooth(true);
			x++;
			if (x == 4) {
				x = 0;
				y++;
			}
		}
		x = 0;
		y = 0;
	}

	// Player FallDying ANI
	if (mPlayerFallDyingANI.size() == 0) {
	for (int i = 0; i < 8; i++) {
		mPlayerFallDyingANI.push_back(new sf::Texture);
			mPlayerFallDyingANI[i]->loadFromImage(mPlayerIMG, sf::IntRect((100 * x) + 970, (160 * y) + 580, 100, 160));
		mPlayerFallDyingANI[i]->setSmooth(true);
		x++;
		if (x == 4) {
			x = 0;
			y++;
		}
	}
	x = 0;
	y = 0;
	}

	// Player Dying ANI
	if (mPlayerDyingANI.size() == 0) {
		for (int i = 0; i < 16; i++) {
			mPlayerDyingANI.push_back(new sf::Texture);
			mPlayerDyingANI[i]->loadFromImage(mPlayerIMG, sf::IntRect((188 * x) + 800, (140 * y), 188, 140));
			mPlayerDyingANI[i]->setSmooth(true);
			x++;
			if (x == 4) {
				x = 0;
				y++;
			}
		}
		x = 0;
		y = 0;
	}

	// Player Damage ANI
	if (mPlayerDamageANI.size() == 0) {
	for (int i = 0; i < 8; i++) {
		mPlayerDamageANI.push_back(new sf::Texture);
		mPlayerDamageANI[i]->loadFromImage(mPlayerIMG, sf::IntRect((80 * x), (140 * y) + 900, 80, 140));
		mPlayerDamageANI[i]->setSmooth(true);
		x++;
		if (x == 4) {
			x = 0;
			y++;
		}
	}
	x = 0;
	y = 0;
	}

	// Player Slide ANI
	if (mPlayerSlideANI.size() == 0) {
		for (int i = 0; i < 8; i++) {
				mPlayerSlideANI.push_back(new sf::Texture);
				mPlayerSlideANI[i]->loadFromImage(mPlayerIMG, sf::IntRect((67 * x) + 700, (140 * y) + 600, 67, 140));
				mPlayerSlideANI[i]->setSmooth(true);
				x++;
			if (x == 4) {
					x = 0;
					y++;
				}
			}
			x = 0;
			y = 0;
	}
	

	// Worm crawling ANI
	if (mWormCrawlingANI.size() == 0) {
		for (int i = 0; i < 16; i++) {
			mWormCrawlingANI.push_back(new sf::Texture);
			mWormCrawlingANI[i]->loadFromImage(mEnemy0IMG, sf::IntRect((75 * x), (35 * y), 75, 35));
			mWormCrawlingANI[i]->setSmooth(true);
			x++;
			if (x == 4) {
				x = 0;
				y++;
			}
		}
		x = 0;
		y = 0;
	}

	// Worm Dying ANI
	if (mWormDyingANI.size() == 0) {
		for (int i = 0; i < 8; i++) {
			mWormDyingANI.push_back(new sf::Texture);
			mWormDyingANI[i]->loadFromImage(mEnemy0IMG, sf::IntRect((75 * x), (35 * y) + 142, 75, 35));
			mWormDyingANI[i]->setSmooth(true);
			x++;
			if (x == 4) {
				x = 0;
				y++;
			}
		}
		x = 0;
		y = 0;
	}

	// Germ Walking ANI
	if (mGermWalkingANI.size() == 0) {
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
	}

	// Germ damaged ANI
	if (mGermDamagedANI.size() == 0) {
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
	}

	// Octo ani
	if (mOcto_PiANI.size() == 0) {
		for (int i = 0; i < 32; i++) {
			mOcto_PiANI.push_back(new sf::Texture);
			mOcto_PiANI[i]->loadFromImage(mEnemy0IMG, sf::IntRect((80 * x) + 700, (120 * y), 80, 120));
			mOcto_PiANI[i]->setSmooth(true);
			x++;
			if (x == 4) {
				x = 0;
				y++;
			}
		}
		x = 0;
		y = 0;
	}

	if (mOcto_PiDeathANI.size() == 0) {
		for (int i = 0; i < 16; i++) {
			mOcto_PiDeathANI.push_back(new sf::Texture);
			mOcto_PiDeathANI[i]->loadFromImage(mEnemy0IMG, sf::IntRect((80 * x) + 333, (120 * y) + 470, 80, 120));
			mOcto_PiDeathANI[i]->setSmooth(true);
			x++;
			if (x == 4) {
				x = 0;
				y++;
			}
		}
		x = 0;
		y = 0;
	}

	// Acidmonster ANI
	if (mAcidMonsterHorizontalANI.size() == 0) {
		for (int i = 0; i < 32; i++) {
			mAcidMonsterHorizontalANI.push_back(new sf::Texture);
			mAcidMonsterHorizontalANI[i]->loadFromImage(mAcidMonsterHorizontalIMG, sf::IntRect((1131 * x), (1200 * y), 1131, 1200));
			mAcidMonsterHorizontalANI[i]->setSmooth(true);
			x++;
			if (x == 4) {
				x = 0;
				y++;
			}
		}
		x = 0;
		y = 0;
	}

	// Acidmonster vertical ANI
	if (mAcidMonsterVerticalANI.size() == 0) {
		for (int i = 0; i < 31; i++) {
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
	}


	// Heart ANI
	if (mHeartANI.size() == 0) {
		for (int i = 0; i < 16; i++) {
			mHeartANI.push_back(new sf::Texture);
			mHeartANI[i]->loadFromImage(mHeartIMG, sf::IntRect((75 * x), (100 * y), 75, 100));
			mHeartANI[i]->setSmooth(true);
			x++;
			if (x == 4) {
				x = 0;
				y++;
			}
		}
		x = 0;
		y = 0;
	}

	// Spikes ANI
	if (mSpikesANI.size() == 0) {
		for (int i = 0; i < 16; i++) {
			mSpikesANI.push_back(new sf::Texture);
			mSpikesANI[i]->loadFromImage(mEnemy0IMG, sf::IntRect((96 * x) + 300, (50 * y), 96, 50));
			mSpikesANI[i]->setSmooth(true);
			x++;
			if (x == 4) {
				x = 0;
				y++;
			}
		}
		x = 0;
		y = 0;
	}

	// Meatball ANI
	if (mMeatballANI.size() == 0) {
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
	}

	// Dialogue ANI

	// Livia
	if (mDialogueLiviaANI.size() == 0) {
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
	}
	// Mansa 
	if (mDialogueMansaANI.size() == 0) {
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
	}

	// Muhnin
	if (mDialogueMuhninANI.size() == 0) {
		for (int i = 0; i < 31; i++) {
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
	}
	// Tummy
	if (mDialogueTummyANI.size() == 0) {
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
	}

	/*mMeatballANI.push_back(new sf::Texture);
	mMeatballANI[0]->loadFromImage(mMeatballIMG, sf::IntRect(0, 0, 400, 251));*/

	// Decoration sprite
	if (mDecoration0ANI.size() == 0) {
		mDecoration0ANI.push_back(new sf::Texture);
		mDecoration0ANI[0]->loadFromImage(mDecorationIMG, sf::IntRect(0, 0, 300, 300));
	}
	if (mDecoration1ANI.size() == 0) {
		mDecoration1ANI.push_back(new sf::Texture);
		mDecoration1ANI[0]->loadFromImage(mDecorationIMG, sf::IntRect(300, 0, 300, 300));
	}
	if (mDecoration2ANI.size() == 0) {
		mDecoration2ANI.push_back(new sf::Texture);
		mDecoration2ANI[0]->loadFromImage(mDecorationIMG, sf::IntRect(600, 0, 300, 300));
	}
	if (mDecoration3ANI.size() == 0) {
		mDecoration3ANI.push_back(new sf::Texture);
		mDecoration3ANI[0]->loadFromImage(mDecorationIMG, sf::IntRect(900, 0, 300, 300));
	}
	if (mDecoration4ANI.size() == 0) {
		mDecoration4ANI.push_back(new sf::Texture);
		mDecoration4ANI[0]->loadFromImage(mDecorationIMG, sf::IntRect(1200, 0, 300, 300));
	}
	if (mDecoration5ANI.size() == 0) {
		mDecoration5ANI.push_back(new sf::Texture);
		mDecoration5ANI[0]->loadFromImage(mDecorationIMG, sf::IntRect(0, 300, 300, 300));
	}
	if (mDecoration6ANI.size() == 0) {
		mDecoration6ANI.push_back(new sf::Texture);
		mDecoration6ANI[0]->loadFromImage(mDecorationIMG, sf::IntRect(300, 300, 300, 300));
	}
	if (mDecoration7ANI.size() == 0) {
		mDecoration7ANI.push_back(new sf::Texture);
		mDecoration7ANI[0]->loadFromImage(mDecorationIMG, sf::IntRect(600, 300, 300, 300));
	}
	if (mDecoration8ANI.size() == 0) {
		mDecoration8ANI.push_back(new sf::Texture);
		mDecoration8ANI[0]->loadFromImage(mDecorationIMG, sf::IntRect(900, 300, 300, 300));
	}
	if (mDecoration9ANI.size() == 0) {
		mDecoration9ANI.push_back(new sf::Texture);
		mDecoration9ANI[0]->loadFromImage(mDecorationIMG, sf::IntRect(1200, 300, 300, 300));
	}
	if (mDecoration10ANI.size() == 0) {
		mDecoration10ANI.push_back(new sf::Texture);
		mDecoration10ANI[0]->loadFromImage(mDecorationIMG, sf::IntRect(0, 600, 300, 300));
	}
	if (mDecoration11ANI.size() == 0) {
		mDecoration11ANI.push_back(new sf::Texture);
		mDecoration11ANI[0]->loadFromImage(mDecorationIMG, sf::IntRect(300, 600, 300, 300));
	}
	if (mDecoration12ANI.size() == 0) {
		mDecoration12ANI.push_back(new sf::Texture);
		mDecoration12ANI[0]->loadFromImage(mDecorationIMG, sf::IntRect(600, 600, 300, 300));
	}
	if (mDecoration13ANI.size() == 0) {
		mDecoration13ANI.push_back(new sf::Texture);
		mDecoration13ANI[0]->loadFromImage(mDecorationIMG, sf::IntRect(900, 600, 300, 300));
	}
	if (mDecoration14ANI.size() == 0) {
		mDecoration14ANI.push_back(new sf::Texture);
		mDecoration14ANI[0]->loadFromImage(mDecorationIMG, sf::IntRect(1200, 600, 300, 300));
	}
	if (mDecoration15ANI.size() == 0) {
		mDecoration15ANI.push_back(new sf::Texture);
		mDecoration15ANI[0]->loadFromImage(mDecorationIMG, sf::IntRect(0, 900, 300, 300));
	}
	if (mDecoration16ANI.size() == 0) {
		mDecoration16ANI.push_back(new sf::Texture);
		mDecoration16ANI[0]->loadFromImage(mDecorationIMG, sf::IntRect(300, 900, 300, 300));
	}
	if (mDecoration17ANI.size() == 0) {
		mDecoration17ANI.push_back(new sf::Texture);
		mDecoration17ANI[0]->loadFromImage(mDecorationIMG, sf::IntRect(600, 900, 300, 300));
	}
	if (mDecoration18ANI.size() == 0) {
		mDecoration18ANI.push_back(new sf::Texture);
		mDecoration18ANI[0]->loadFromImage(mDecorationIMG, sf::IntRect(900, 900, 300, 300));
	}
	if (mDecoration19ANI.size() == 0) {
		mDecoration19ANI.push_back(new sf::Texture);
		mDecoration19ANI[0]->loadFromImage(mDecorationIMG, sf::IntRect(1200, 900, 300, 300));
	}
	if (mDecoration20ANI.size() == 0) {
		mDecoration20ANI.push_back(new sf::Texture);
		mDecoration20ANI[0]->loadFromImage(mDecorationIMG, sf::IntRect(0, 1200, 300, 300));
	}
	if (mDecoration21ANI.size() == 0) {
		mDecoration21ANI.push_back(new sf::Texture);
		mDecoration21ANI[0]->loadFromImage(mDecorationIMG, sf::IntRect(300, 1200, 300, 300));
	}
	if (mDecoration22ANI.size() == 0) {
		mDecoration22ANI.push_back(new sf::Texture);
		mDecoration22ANI[0]->loadFromImage(mDecorationIMG, sf::IntRect(600, 1200, 300, 300));
	}
	if (mDecoration23ANI.size() == 0) {
		mDecoration23ANI.push_back(new sf::Texture);
		mDecoration23ANI[0]->loadFromImage(mDecorationIMG, sf::IntRect(900, 1200, 300, 300));
	}
	if (mDecoration24ANI.size() == 0) {
		mDecoration24ANI.push_back(new sf::Texture);
		mDecoration24ANI[0]->loadFromImage(mDecorationIMG, sf::IntRect(1200, 1200, 300, 300));
	}
	if (mDecoration25ANI.size() == 0) {
		mDecoration25ANI.push_back(new sf::Texture);
		mDecoration25ANI[0]->loadFromImage(mDecorationIMG, sf::IntRect(0, 1500, 300, 300));
	}
	if (mDecoration26ANI.size() == 0) {
		mDecoration26ANI.push_back(new sf::Texture);
		mDecoration26ANI[0]->loadFromImage(mDecorationIMG, sf::IntRect(300, 1500, 300, 300));
	}
	if (mDecoration27ANI.size() == 0) {
		mDecoration27ANI.push_back(new sf::Texture);
		mDecoration27ANI[0]->loadFromImage(mDecorationIMG, sf::IntRect(600, 1500, 300, 300));
	}
	if (mDecoration28ANI.size() == 0) {
		mDecoration28ANI.push_back(new sf::Texture);
		mDecoration28ANI[0]->loadFromImage(mDecorationIMG, sf::IntRect(900, 1500, 300, 300));
	}
	if (mDecoration29ANI.size() == 0) {
		mDecoration29ANI.push_back(new sf::Texture);
		mDecoration29ANI[0]->loadFromImage(mDecorationIMG, sf::IntRect(1200, 1500, 300, 300));
	}
	if (mTileDecTextures.size() == 0) {
		for (int i = 0; i < 24; i++) {
			mTileDecTextures.push_back(new sf::Texture);
			mTileDecTextures[i]->loadFromImage(Toolbox::getTexture(Toolbox::TILEDECSHEET), sf::IntRect((100 * x), (100 * y), 100, 100));
			mTileDecTextures[i]->setSmooth(true);
			x++;
			if (x == 6) {
				x = 0;
				y++;
			}
	}
	}
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

Animations::Textures* Animations::getPlayerHurtANI(){
	return &mPlayerDamageANI;
}

Animations::Textures* Animations::getPlayerFallingANI(){
	return &mPlayerFallingANI;
}

Animations::Textures* Animations::getPlayerDyingANI(){
	return &mPlayerDyingANI;
}

Animations::Textures* Animations::getPlayerFallDyingANI() {
	return &mPlayerFallDyingANI;
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

// Germ ANI
Animations::Textures* Animations::getGermWalkingANI() {
	return &mGermWalkingANI;
}

Animations::Textures* Animations::getGermDamagedANI() {
	return &mGermDamagedANI;
}

// Octo_Pi ANI
Animations::Textures * Animations::getOcto_PiANI(){
	return &mOcto_PiANI;
}

Animations::Textures * Animations::getOcto_PiDeathANI() {
	return &mOcto_PiDeathANI;
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

// Decoration ANI
Animations::Textures* Animations::getDecoration0ANI(){
	return &mDecoration0ANI;
}

Animations::Textures* Animations::getDecoration1ANI() {
	return &mDecoration1ANI;
}

Animations::Textures* Animations::getDecoration2ANI() {
	return &mDecoration2ANI;
}

Animations::Textures* Animations::getDecoration3ANI() {
	return &mDecoration3ANI;
}

Animations::Textures* Animations::getDecoration4ANI() {
	return &mDecoration4ANI;
}

Animations::Textures* Animations::getDecoration5ANI() {
	return &mDecoration5ANI;
}

Animations::Textures* Animations::getDecoration6ANI() {
	return &mDecoration6ANI;
}

Animations::Textures* Animations::getDecoration7ANI() {
	return &mDecoration7ANI;
}

Animations::Textures* Animations::getDecoration8ANI() {
	return &mDecoration8ANI;
}

Animations::Textures* Animations::getDecoration9ANI() {
	return &mDecoration9ANI;
}

Animations::Textures* Animations::getDecoration10ANI() {
	return &mDecoration10ANI;
}

Animations::Textures* Animations::getDecoration11ANI() {
	return &mDecoration11ANI;
}

Animations::Textures* Animations::getDecoration12ANI() {
	return &mDecoration12ANI;
}

Animations::Textures* Animations::getDecoration13ANI() {
	return &mDecoration13ANI;
}

Animations::Textures* Animations::getDecoration14ANI() {
	return &mDecoration14ANI;
}

Animations::Textures* Animations::getDecoration15ANI() {
	return &mDecoration15ANI;
}

Animations::Textures* Animations::getDecoration16ANI() {
	return &mDecoration16ANI;
}

Animations::Textures* Animations::getDecoration17ANI() {
	return &mDecoration17ANI;
}

Animations::Textures* Animations::getDecoration18ANI() {
	return &mDecoration18ANI;
}

Animations::Textures* Animations::getDecoration19ANI() {
	return &mDecoration19ANI;
}

Animations::Textures* Animations::getDecoration20ANI() {
	return &mDecoration20ANI;
}

Animations::Textures* Animations::getDecoration21ANI() {
	return &mDecoration21ANI;
}

Animations::Textures* Animations::getDecoration22ANI() {
	return &mDecoration22ANI;
}

Animations::Textures* Animations::getDecoration23ANI() {
	return &mDecoration23ANI;
}

Animations::Textures* Animations::getDecoration24ANI() {
	return &mDecoration24ANI;
}

Animations::Textures* Animations::getDecoration25ANI() {
	return &mDecoration25ANI;
}

Animations::Textures* Animations::getDecoration26ANI() {
	return &mDecoration26ANI;
}
Animations::Textures* Animations::getTileDecTextures() {
	return &mTileDecTextures;
}

Animations::Textures* Animations::getDecoration27ANI() {
	return &mDecoration27ANI;
}

Animations::Textures* Animations::getDecoration28ANI() {
	return &mDecoration28ANI;
}

Animations::Textures* Animations::getDecoration29ANI() {
	return &mDecoration29ANI;
}