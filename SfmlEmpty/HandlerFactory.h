#pragma once

class Abstracthandler;

struct HandlerFactory {
	static Abstracthandler* getEntityHandlerInstance();
	static Abstracthandler* getTerrainHandlerInstance();
};

