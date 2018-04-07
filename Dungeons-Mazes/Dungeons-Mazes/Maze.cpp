#include "Maze.hpp"
#include "Cell.hpp"
#include "Bot.hpp"
#include "Player.hpp"
#include "Artifact.hpp"

Maze::Maze(int mapSizeX, int mapSizeY) : m_MapSizeX(mapSizeX), m_MapSizeY(mapSizeY) {
	assert(mapSizeX > 0);
	assert(mapSizeY > 0);
	m_pMap = new Node*[mapSizeY];
	for (int i = 0; i < mapSizeY; i++) {
		m_pMap[i] = new Node[mapSizeX];
	}
	for (int i = 0; i < mapSizeY; i++) {
		for (int j = 0; j < mapSizeX; j++) {
			m_pMap[i][j].cell = new Cell(Point(i,j), this);
			m_pMap[i][j].NPC = nullptr;
			m_pMap[i][j].artifact = nullptr;
			m_pMap[i][j].cell->addNeighbors();
		}
	}

	////ADDING OBJECTS
	Bot* bot = new Bot(Point(10, 10), "KUPA NA GLOWIE", this);
	Artifact* coin = new Artifact(Point(8, 8), "a", this);
	this->m_Characters.push_back(bot);
	this->m_Artifacts.push_back(coin);
	m_pMap[10][10].NPC = bot;
	m_pMap[8][8].artifact = coin;
	/////
}

Maze::~Maze() {
	for (size_t i = 0; i < m_MapSizeY; i++) {
		for (size_t j = 0; j < m_MapSizeY; j++) {
			//delete m_pMap[i][j].cell;
			//delete m_pMap[i][j].NPC;
		}
	}
}

void Maze::Print() {
	for (size_t i = 0; i < m_MapSizeY; i++) {
		for (size_t j = 0; j < m_MapSizeX; j++) {
			if(m_pMap[i][j].artifact!=nullptr)
				(m_pMap[i][j].artifact)->show();
			if (m_pMap[i][j].NPC != nullptr)
				(m_pMap[i][j].NPC)->show();
			else
				(m_pMap[i][j].cell)->show();
		}
		cout << endl;
	}
}

bool Maze::ifCoordExist(int p, int mapSize) {
	if (p >= 0 && p < mapSize) return true;
	else return false;
}