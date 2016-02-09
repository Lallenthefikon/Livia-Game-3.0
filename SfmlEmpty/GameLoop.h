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
	void switchState();
	void updateState();
	GameState* mCurrentState;
	sf::RenderWindow mWindow;
	std::string mCurrentMap;
	sf::CircleShape shape;
	sf::SoundBuffer mAmbienceBuffer;
	sf::Sound mAmbienceSound;
	float mTimeElapsed;
	int FPS;
	bool gameRunning = true, mapEditing; // States
};

