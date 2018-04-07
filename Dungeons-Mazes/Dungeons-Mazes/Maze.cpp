#include "Maze.hpp"
#include "Cell.hpp"
#include "Bot.hpp"
#include "Player.hpp"

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
			dynamic_cast<Cell*>(m_pMap[i][j].cell)->addNeighbors();
		}
	}
	Bot* bot = new Bot(Point(10, 10), "KUPA NA GLOWIE", this);
	this->m_List.push_back(bot);
	this->bots.push_back(bot);
	m_pMap[10][10].NPC = bot;
	
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
			if (m_pMap[i][j].NPC == nullptr)
				(m_pMap[i][j].cell)->show();
			else 
				(m_pMap[i][j].NPC)->show();
		}
		cout << endl;
	}
}

bool Maze::ifCoordExist(int p, int mapSize) {
	if (p >= 0 && p < mapSize) return true;
	else return false;
}