#include "GameLoop.h"
#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow){

	GameLoop gameloop;
	gameloop.run();
	return 0;
}