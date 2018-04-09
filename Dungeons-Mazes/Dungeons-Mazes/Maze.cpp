#include "Maze.hpp"
#include "Cell.hpp"
#include "AStarBot.hpp"
#include "Player.hpp"
#include "Artifact.hpp"

Maze::Maze(uint8_t mapSizeX, uint8_t mapSizeY, uint8_t maxArtifactCount)
	: m_MapSizeX(mapSizeX), m_MapSizeY(mapSizeY), m_MaxArtifactCount(maxArtifactCount) {
	assert(mapSizeX > 0);
	assert(mapSizeY > 0);

	m_pMap = new Node*[m_MapSizeX];
	for (int i = 0; i < m_MapSizeX; i++) {
		m_pMap[i] = new Node[m_MapSizeY];
	}
	for (int i = 0; i < m_MapSizeX; i++) {
		for (int j = 0; j < m_MapSizeY; j++) {
			m_pMap[i][j].cell = new Cell(Point(i, j), this);
			m_pMap[i][j].NPC = nullptr;
			m_pMap[i][j].artifact = nullptr;
			m_Cells.push_back(m_pMap[i][j].cell);
		}
	}

	for (auto cell : m_Cells) {
		cell->addNeighbors();
	}

	initializeRandomMaze(0.2);
	//initializeIsleMaze(m_MapSizeX*m_MapSizeY/random(2,20), 0.2);
	//initializeProceduralMaze();

	spawnArtifact(1.0);
	spawnBot("A*");
}

Maze::~Maze() {
	for (size_t i = 0; i < m_MapSizeY; i++) {///XD
		for (size_t j = 0; j < m_MapSizeY; j++) {
			//delete m_pMap[i][j].cell;
			//delete m_pMap[i][j].NPC;
		}
	}
}

void Maze::initializeRandomMaze(double randomFactor) {
	//randomFactor is floating point number between 0 and 1.0
	for (int i = 0; i < m_MapSizeX; i++) {
		for (int j = 0; j < m_MapSizeY; j++) {
			if (random() < randomFactor) {
				m_pMap[i][j].cell->m_IsWall = true;
			}
			else
				m_pMap[i][j].cell->m_IsWall = false;
		}
	}
}

void Maze::initializeIsleMaze(int isleCount, double randomFactor) {
	//randomFactor is floating point number between 0 and 1.0
	Point r;
	Cell *cell;
	for (int i = 0; i < isleCount; i++) {
		r = Point(random(0, m_MapSizeX - 1), random(0, m_MapSizeY - 1));
		cell = m_pMap[r.x][r.y].cell;
		cell->m_IsWall = true;
		recursiveWallPlacing(cell, randomFactor);
	}
}

void Maze::recursiveWallPlacing(Cell *cell, double randomFactor) {
	for (auto neighbor : cell->m_pNeighbors) {
		if(random() < randomFactor)
		neighbor->m_IsWall = true;
		if (random() < randomFactor && randomFactor >= 0.0000001)
			recursiveWallPlacing(neighbor, randomFactor - 0.05);
	}
}

void Maze::Print() {
	for (size_t i = 0; i < m_MapSizeX; i++) {
		for (size_t j = 0; j < m_MapSizeY; j++) {
			if (m_pMap[i][j].artifact != nullptr)
				(m_pMap[i][j].artifact)->show();
			else if (m_pMap[i][j].NPC != nullptr)
				(m_pMap[i][j].NPC)->show();
			else
				(m_pMap[i][j].cell)->show();
		}
		cout << endl;
	}
}

bool Maze::ifCoordExist(int p, int mapSize) {
	return (p >= 0 && p < mapSize) ? true : false;
}

void Maze::spawnArtifact(double randomFactor) {
	if (m_Artifacts.size() >= m_MaxArtifactCount
		|| random() > randomFactor)
		return;
	Point p = Point(random(0, m_MapSizeX - 1), random(0, m_MapSizeY - 1));
	Artifact* artifact = new Artifact(p, "", this);
	m_pMap[p.x][p.y].artifact = artifact;
	m_pMap[p.x][p.y].cell->m_IsWall = false;
	m_Artifacts.push_back(artifact);
}

void Maze::spawnBot(string type) {
	AbstractPlayer* bot;
	Point p = Point(random(0, m_MapSizeX - 1), random(0, m_MapSizeY - 1));
	if (type == "A*")
		bot = new AStarBot(p, "A* Bot", this);
	else if (type == "different")
		;///...
	this->m_Characters.push_back(bot);
	m_pMap[p.x][p.y].NPC = bot;
	m_pMap[p.x][p.y].cell->m_IsWall = false; 
	//usuwa ewentualna sciane na miejscu bota
}