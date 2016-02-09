#include "Toolbox.h"

static sf::Sprite mPlayerSprite;

// Textures
static sf::Image mEnemy0sheet;
static sf::Image mBlock0sheet;
static sf::Image mPlayersheet;

static sf::Image mTileTexture;
static sf::Image mEditorMenyTexture;

// Camera edit
static sf::Vector2f mWindowSize;
static sf::Vector2f mResolution;
static sf::Vector2f mWindowPos;

Toolbox& Toolbox::getInstance(){
	static Toolbox toolbox;
	return toolbox;
}

void Toolbox::loadTextures(){
	mEnemy0sheet.loadFromFile("resources/images/Mask.png");
	mBlock0sheet.loadFromFile("resources/images/TileSheet.png");
	mPlayersheet.loadFromFile("resources/images/Livia_spritesheet_placeholder1.2(100,140).png");

	mTileTexture.loadFromFile("resources/images/Tile.png");
	mEditorMenyTexture.loadFromFile("resources/images/EditorMeny.png");
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
		
	case TILETEXTURE:
		return mTileTexture;
		break;

	case EDITORMENY:
		return mEditorMenyTexture;
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