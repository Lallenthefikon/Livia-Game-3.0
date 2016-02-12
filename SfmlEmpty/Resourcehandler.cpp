#include "Resourcehandler.h"

std::map<sf::Image&, int> mTextures;
std::map<sf::SoundBuffer&, int> mSoundBuffers;

std::map<sf::Image&, int>& Resourcehandler::getTextures(LEVELKEY levelKey) {
	return mTextures;
}

std::map<sf::SoundBuffer&, int>& Resourcehandler::getSounds(LEVELKEY levelKey) {
	return mSoundBuffers;
}

Resourcehandler& Resourcehandler::getInstance() {
	static Resourcehandler resourceHandler;
	return resourceHandler;
}