#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Abstractgame.h"
#include "Entityhandler.h"
#include "MapGenerator.h"
#include "Toolbox.h"
#include "GameRun.h"
#include "MapEditor.h"
#include "MapEditMaploader.h"

class GameLoop : public Abstractgame{
public:
	GameLoop();
	virtual ~GameLoop();
	void run();
	void update();
	void render();
private:
	void calcTimeElapsedAndFPS(sf::Clock &clock);
	void manualStateChange(int &i);
	void manualFPSChange(int &i);
	void manualMapDirectoryChange(int &i);
	std::string getLevelFilename(int i);
	std::string getMapName(int i);
	void switchFPS();
	void updateFPS();
	void switchState();
	void updateState();

	GameState* mCurrentState;
	sf::RenderWindow mWindow;
	
	std::string mCurrentLevelDirectory,
		mCurrentLevelName;

	int mCurrentLvlIndex,
		clickOnce0 = 0,
		clickOnce1 = 0,
		clickOnce2 = 0;
	
	float mFrameTime;
	int FPS;
	bool gameRunning = true, mapEditing; // States
	bool lowFPS, highFPS = true;
};

