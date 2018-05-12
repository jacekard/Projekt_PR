#pragma once

#include "Config.hpp"
#include "Maze.hpp"
#include "AbstractPlayer.hpp"
#include "GraphicsClass.hpp"

class InputClass;
class GraphicsClass;
class Maze;
class Cell;

class SystemClass
{
public:
    SystemClass();
    SystemClass(const SystemClass&);
    ~SystemClass();

    bool Initialize();
    void Shutdown();
    void Run();

    LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
    bool Frame();
    void InitializeWindows(int&, int&);
    void ShutdownWindows();

private:
    LPCSTR m_applicationName;
    HINSTANCE m_hinstance;
    HWND m_hwnd;

   InputClass* m_Input;
   GraphicsClass* m_Graphics;
   int screenWidth, screenHeight;

   //Maze related
   Maze* maze;

   double simulationTime; /// in seconds
   int MaxArtifactsCountOnMap;
   double artifactChance; /// initial chance of spawning
   double decreaseArtifactChance; /// decrease a chance of spawning
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

static SystemClass* ApplicationHandle = 0;

