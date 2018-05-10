#include <conio.h>
#include "Maze.hpp"
#include "AStarBot.hpp"
#include "Artifact.hpp"
#include "Console.hpp"


#if defined(CONSOLE_VIEW_BUILD)
int main() {
	HideCursor();
	///height, width, maximum artifacts at once, scale 
	Maze* maze = new Maze(20, 40, 5, 1);
	
	double simulationTime = 20.0; /// in seconds
	double artifactChance = 1.0; /// initial chance of spawning
	double decreaseArtifactChance = 0.05; /// decrease a chance of spawning

	/// Maze generation examples:
	maze->MazeEmpty1(); 
	//maze->MazeEmpty2();
	//maze->MazeEmpty3();
	//maze->MazeETI();
	//maze->MazeFromFile("serduszko");
	//maze->MazeWeighted();

	/// Bots options:
	/// Bots(A*, Dijkstra, Tremaux)
	//maze->Bots(1,1,0); 


	Timer mainTimer = Timer();
	mainTimer.start();
	
	for (auto character : maze->m_Characters) {
		character->m_Timer.start();
	}

	maze->Print();
	Sleep(2000);
	
	while (true) {
		
		maze->spawnArtifact(artifactChance, decreaseArtifactChance);
		for (auto character : maze->m_Characters) {
			character->move();
		}
		maze->Print();

		if (simulationTime != 0.0) {
			if (mainTimer.getSecondsFromStart() >= simulationTime) {
				maze->endSimulation();
				break;
			}
		} else if (maze->m_Artifacts.size() == 0) {
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