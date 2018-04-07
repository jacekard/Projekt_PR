////////////////////////////////////////////////////////////////////////////////
// Filename: main.cpp
////////////////////////////////////////////////////////////////////////////////
#include "Config.hpp"
#include <conio.h>]

int main() {
	Maze* maze = new Maze(20, 20);
	//AbstractPlayer* bot;
	while (_getch() != 'q') {
		system("cls");
		maze->Print();
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