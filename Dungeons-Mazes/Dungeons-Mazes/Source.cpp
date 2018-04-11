#include <conio.h>
#include "Maze.hpp"
#include "AStarBot.hpp"
#include "Artifact.hpp"
#include "Console.hpp"


#if defined(CONSOLE_VIEW_BUILD)
int main() {
	HideCursor();

	Maze* maze = new Maze(50, 50, 25); //(maxX, maxY, maxArtifacts)

	maze->spawnBot("Dijkstra");
	//maze->spawnBot("A*");
	
	Timer timer = Timer();
	timer.start();
	
	maze->Print();
	timer.end();
	cout << timer.getResultMillis();
	Sleep(2000);
	double i = 0.0;
	while (true) {
		maze->spawnArtifact(1.0 - i);

		for (auto character : maze->m_Characters) {
			character->move();
			cout << character->m_timer.getCycleMillis() << endl;
		}
		maze->Print();
		i += 0.05;
		if (maze->m_Artifacts.size() == 0)
			break;
	}
	
	Sleep(3000);
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