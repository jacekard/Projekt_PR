////////////////////////////////////////////////////////////////////////////////
// Filename: main.cpp
////////////////////////////////////////////////////////////////////////////////
#include <conio.h>
#include "Maze.hpp"
#include "AStarBot.hpp"
#include "Artifact.hpp"
#include "Console.hpp"



int main() {
	HideCursor();

	Maze* maze = new Maze(40, 50, 25); //(maxX, maxY, maxArtifacts)
	maze->spawnArtifact(1.0); //to jest wazne, zeby bylo przed Botem, bo sie pewnie wyjebie
	maze->spawnBot("A*");
	maze->spawnBot("A*");
	//maze->spawnBot("Mouse");

	maze->Print();
	Sleep(2000);
	double i = 0.0;
	while (true) {
		maze->Print();
		maze->spawnArtifact(1.0 - i);
		for (auto character : maze->m_Characters) {
			character->move();
		}
		i += 0.1;
		Sleep(20);
	}
	cout << endl;
	system("pause");
	return 0;
}

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
//{
//    SystemClass* System;
//    bool result;
//
//
//    // Create the system object.
//    System = new SystemClass;
//    if (!System)
//    {
//        return 0;
//    }
//
//    // Initialize and run the system object.
//    result = System->Initialize();
//    if (result)
//    {
//        System->Run();
//    }
//
//    // Shutdown and release the system object.
//    System->Shutdown();
//    delete System;
//    System = 0;
//
//    return 0;
//}