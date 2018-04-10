////////////////////////////////////////////////////////////////////////////////
// Filename: main.cpp
////////////////////////////////////////////////////////////////////////////////
#include <conio.h>
#include "Maze.hpp"
#include "AStarBot.hpp"
#include "Artifact.hpp"

//TODO:
//jak AStarBot dojdzie do end, to jego start = end;


//Optymalizacje:
//A* nie trzeba zerowaæ wag komórek
//ale trzeba za ka¿dym razem resetowaæ pole Cell.m_pPrevious = nullptr;
//Do przemyœlenia.

int main() {

	Maze* maze = new Maze(10, 10, 2); //(maxX, maxY, maxArtifacts)
	maze->spawnArtifact(1.0);
	//maze->spawnBot("A*");
	maze->spawnBot("Mouse");
	maze->Print();
	Sleep(2000);


	int i = 0;
	while (i < 200) {
		system("cls");
		maze->Print();
		maze->spawnArtifact(0.3);
		for (auto character : maze->m_Characters) {
			character->move();
		}
		i++;
		Sleep(250);
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