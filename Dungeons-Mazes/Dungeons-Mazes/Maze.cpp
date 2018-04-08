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
			m_Cells.push_back(m_pMap[i][j].cell);
		}
	}

	for (auto cell : m_Cells) {
		cell->addNeighbors();
	}

	////ADDING OBJECTS
	Bot* bot = new Bot(Point(14, 14), "KUPA NA GLOWIE", this);
	Artifact* coin = new Artifact(Point(0, 0), "a", this);
	this->m_Characters.push_back(bot);
	this->m_Artifacts.push_back(coin);
	m_pMap[bot->m_Position.x][bot->m_Position.y].NPC = bot;
	m_pMap[bot->m_Position.x][bot->m_Position.y].cell->m_IsWall = false; //usuwa ewentualna sciane na miejscu bota

	//DEBUG Gdy zablokujemy œciany wokó³ bota program nie wywala sie!
	m_pMap[13][13].cell->m_IsWall = false;
	m_pMap[14][13].cell->m_IsWall = false;
	m_pMap[13][14].cell->m_IsWall = false;
	//DEBUG

	m_pMap[coin->m_Position.x][coin->m_Position.y].artifact = coin;
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