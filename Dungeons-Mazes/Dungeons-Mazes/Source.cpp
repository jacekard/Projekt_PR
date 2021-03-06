﻿#include <conio.h>
#include "Maze.hpp"
#include "AStarBot.hpp"
#include "Artifact.hpp"

#if defined(CONSOLE_VIEW_BUILD)

#include "Console.hpp"

int main() {
	HideCursor();

	///MapSizeX, MapSizeY, MaximumArtifactCount, Scale
	Maze* maze = new Maze(10, 10, 4, 1);

	double simulationTime = 0.0; /// in seconds
	int MaxArtifactsCountOnMap = 1; ///maximum artifacts available at once
	double artifactChance = 1.0; /// initial chance of spawning
	double decreaseArtifactChance = 0.00; /// decrease a chance of spawning

	/// Maze generation examples:
	maze->MazeEmpty1();
	//maze->MazeEmpty2();
	//maze->MazeEmpty3();
	//maze->MazeETI();
	//maze->MazeFromFile("serduszko");
	//maze->MazeWeighted();


	/// Bots options:
	/// Bots(A*, Dijkstra, Pledge)
	PlayerType bots[] = { ASTAR, ASTAR, ASTAR };
	maze->Bots(bots);

	Timer mainTimer = Timer();
	mainTimer.start();

	for (auto character : maze->m_Characters) {
		character->m_Timer.start();
	}

	//maze->Print();
	//Sleep(2000);


	while (true) {
		maze->spawnArtifact(MaxArtifactsCountOnMap, artifactChance, decreaseArtifactChance);

		for (auto character : maze->m_Characters) {
			character->move();
		}
		maze->Print();
		Sleep(100);

		if (simulationTime > 0.0) {
			if (mainTimer.getSecondsFromStart() >= simulationTime) {
				maze->endSimulation();
				break;
			}
		}
		if (maze->m_MaxArtifactCount == 0 && maze->m_Artifacts.size() == 0) {
			maze->endSimulation();
			break;
		}
	}

	cout << "Simulation ended with total time of " << mainTimer.end() / 1000.0 << "s" << endl;
	for (auto pl : maze->m_Characters) {
		cout << *pl;
	}

	system("pause");
	return 0;
}
#endif

#if defined(DIRECTX_VIEW_BUILD)
#include "SystemClass.hpp"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
    SystemClass* System;
    bool result;


    // Create the system object.
    System = new SystemClass;
    if (!System)
    {
        return 0;
    }

    // Initialize and run the system object.
    result = System->Initialize();
    if (result)
    {
        System->Run();
    }

    // Shutdown and release the system object.
    System->Shutdown();
    delete System;
    System = 0;

    return 0;
}
#endif