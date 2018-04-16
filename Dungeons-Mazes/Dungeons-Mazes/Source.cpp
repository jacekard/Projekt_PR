#include <conio.h>
#include "Maze.hpp"
#include "AStarBot.hpp"
#include "Artifact.hpp"
#include "Console.hpp"


#if defined(CONSOLE_VIEW_BUILD)
int main() {
	HideCursor();

	//Maze* maze = new Maze(20, 20, 5, 1); //(maxX, maxY, maxArtifacts, scale)
	Maze* maze = new Maze("mapaTestowa", 8, 1);  //(mazeName, maxArtifacts, scale)
	//maze->spawnBot("Dijkstra");
	maze->spawnBot("A*");
	Timer mainTimer = Timer();
	mainTimer.start();
	
	for (auto character : maze->m_Characters) {
		character->m_Timer.start();
	}

	maze->Print();
	Sleep(2000);
	
	while (true) {
		
		maze->spawnArtifact(1.0);
		for (auto character : maze->m_Characters) {
			character->move();
		}
		maze->Print();

		if (maze->m_Artifacts.size() == 0) {
			maze->Print();
			maze->endSimulation();
			break;
		}
	}
	
	cout << "Simulation ended with total time of " << mainTimer.end() / 1000.0 << "s" << endl;
	for (auto character : maze->m_Characters) {
		cout << *character;
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