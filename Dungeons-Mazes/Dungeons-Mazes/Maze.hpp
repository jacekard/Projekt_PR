#pragma once
#include "Config.hpp"

enum PlayerType;
class GameObject;
class AbstractPlayer;
class Artifact;
class Cell;

struct Node {
	Cell* cell;
	AbstractPlayer* NPC;
	Artifact * artifact;
    bool isWall;
};

class Maze {
public:
	int m_MapSizeX, m_MapSizeY;
	int m_MaxArtifactCount;
	Node **m_pMap;
	vector<Cell*> m_Cells;
	vector<Artifact*> m_Artifacts;
	vector<AbstractPlayer*> m_Characters;
	bool artifactHasJustSpawned;
	int m_Scale;
	Maze();
	Maze(int mapSizeX, int mapSizeY, int m_MaximumArtifactCount, int scale);
	Maze(string mazeName, int m_MaximumArtifactCount, int scale);
	~Maze();
	void initializeMap(bool isWall);
	void initializeRandomMaze(double randomFactor);
	void initializeIsleMaze(int isleCount, double randomFactor);
	void initializeProceduralMaze();
	void initializeMazeFromFile(string mazeName);
	void scaleMaze();
	void makeOurMazeNotPerfectAgain();
	bool ifCoordExist(int p, int mapSize);
	void recursiveWallPlacing(Cell *cell, double randomFactor);
	void spawnArtifact(int MaxArtifactCountOnMap, double randomFactor, double decreasingFactor);
	void spawnBot(PlayerType type);
	void endSimulation();
	void Print();
	void save();

    void WAForFuckedUpLinkingToDisplayWalls();

#pragma region Examples
	void MazeEmpty1();
	void MazeEmpty2();
	void MazeEmpty3();
	void MazeFromFile(string mazeName);
	void MazeETI();
	void MazeWeighted();
	void Bots(PlayerType bots[]);
#pragma endregion Examples
};