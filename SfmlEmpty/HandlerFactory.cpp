#include "HandlerFactory.h"
#include "Entityhandler.h"
#include "Terrainhandler.h"

Abstracthandler* HandlerFactory::getEntityHandlerInstance() {
	return Entityhandler::getInstance();
}

Abstracthandler* HandlerFactory::getTerrainHandlerInstance() {
	return Terrainhandler::getInstance();
}