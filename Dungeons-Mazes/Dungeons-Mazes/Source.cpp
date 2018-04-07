////////////////////////////////////////////////////////////////////////////////
// Filename: main.cpp
////////////////////////////////////////////////////////////////////////////////
#include <conio.h>
#include "Maze.hpp"
#include "Bot.hpp"
int main() {
	Maze* maze = new Maze(20, 20);
	int i = 0;
	while (i < 100000000000) {
		system("cls");
		for(auto character : maze->m_List) {
			dynamic_cast<AbstractPlayer*>(character)->move();
		}
		maze->Print();
		i++;
		Sleep(100);
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