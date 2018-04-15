#include "Maze.hpp"
#include "Cell.hpp"
#include "AStarBot.hpp"
#include "MouseBot.hpp"
#include "DijkstraBot.hpp"
#include "Player.hpp"
#include "Artifact.hpp"

Maze::Maze(uint8_t mapSizeX, uint8_t mapSizeY, uint8_t maxArtifactCount, int scale)
	: m_MapSizeX(mapSizeX), m_MapSizeY(mapSizeY), m_MaxArtifactCount(maxArtifactCount) {
	assert(mapSizeX > 0);
	assert(mapSizeY > 0);

	artifactHasJustSpawned = false;

	//initializeRandomMaze(1.0);
	//initializeIsleMaze(random((int)m_MapSizeX / 3, m_MapSizeX - random(m_MapSizeX)), 0.1);
	initializeProceduralMaze();
}

Maze::Maze(string mazeName, uint8_t maxArtifactCount, int scale) : m_MaxArtifactCount(maxArtifactCount) {
	artifactHasJustSpawned = false;

	fstream file;
	file.open("Mazes/"+mazeName+".txt", ios::in);
	assert(file.good());

	int mapSizeX, mapSizeY, offset;
	file >> mapSizeX;
	file >> mapSizeY;
	file >> offset;

	m_MapSizeX = mapSizeX+offset*2;
	m_MapSizeY = mapSizeY+offset*2;
	initializeMap(false);

	while (!file.eof()) {
		int x, y;
		file >> y;
		file >> x;
		y += offset;
		x += offset;
		m_pMap[x][y].cell->m_IsWall = true;
	}

	file.close();

	scaleMaze(scale);
}

void Maze::initializeMap(bool isWall) {
	m_pMap = new Node*[m_MapSizeX];
	for (int i = 0; i < m_MapSizeX; i++) {
		m_pMap[i] = new Node[m_MapSizeY];
	}

	for (int i = 0; i < m_MapSizeX; i++) {
		for (int j = 0; j < m_MapSizeY; j++) {
			m_pMap[i][j].cell = new Cell(Point(i, j), this, isWall);
			m_pMap[i][j].NPC = nullptr;
			m_pMap[i][j].artifact = nullptr;
			m_Cells.push_back(m_pMap[i][j].cell);
		}
	}

	for (auto cell : m_Cells) {
		cell->addNeighbors(m_pMap);
	}
}

void Maze::initializeProceduralMaze() {
	initializeMap(true);
	//Print();
	Cell * tmp = m_Cells[random(0, m_Cells.size() - 1)];
	tmp->m_IsWall = false;
	//Print();
	vector<Cell*> walls;
	for (auto wall : tmp->m_pNeighbors)
		if (wall->m_IsWall) {
			wall->m_Vector = wall->m_Position - tmp->m_Position;
			if (wall->m_Vector.x*wall->m_Vector.y == 0)
				walls.push_back(wall);

		}

	while (walls.size() != 0) {
		Cell * wall = walls[random(0, walls.size() - 1)];
		Point next = wall->m_Position + wall->m_Vector;
		if (ifCoordExist(next.x, m_MapSizeX) && ifCoordExist(next.y, m_MapSizeY))
			if (!m_pMap[next.x][next.y].cell->m_IsWall) {
				walls.erase(std::find(walls.begin(), walls.end(), wall));
				continue;
			}
		wall->m_IsWall = false;
		//Print();
		walls.erase(std::find(walls.begin(), walls.end(), wall));
		if (ifCoordExist(next.x, m_MapSizeX) && ifCoordExist(next.y, m_MapSizeY)) {
			wall = m_pMap[next.x][next.y].cell;
			wall->m_IsWall = false;
			//Print();
			for (auto neighbor : wall->m_pNeighbors) {
				if (neighbor->m_IsWall) {
					//coord exist nie bedzie tu ptozrebmny
					neighbor->m_Vector = Point(neighbor->m_Position - wall->m_Position);
					if (neighbor->m_Vector.x*neighbor->m_Vector.y == 0)
						walls.push_back(neighbor);
				}
			}
		}
	}

	//makeOurMazeNotPerfectAgain();
}

void Maze::scaleMaze(int scale) {
	if (scale == 1) return;
	Node **m_pScaleMap = new Node*[m_MapSizeX*scale];
	for (int i = 0; i < m_MapSizeX*scale; i++) {
		m_pScaleMap[i] = new Node[m_MapSizeY*scale];
	}

	m_Cells.clear();

	for (int i = 0; i < m_MapSizeX*scale; i++) {
		for (int j = 0; j < m_MapSizeY*scale; j++) {
			m_pScaleMap[i][j].cell = new Cell(Point(i, j), this, false);
			m_pScaleMap[i][j].NPC = nullptr;
			m_pScaleMap[i][j].artifact = nullptr;
			m_Cells.push_back(m_pScaleMap[i][j].cell);
		}
	}

	for (int i = 0; i < m_MapSizeX; i++) {
		for (int j = 0; j < m_MapSizeY; j++) {
			if (m_pMap[i][j].cell->m_IsWall) {
				for (int h = 0; h < scale; h++) {
					for (int l = 0; l < scale; l++) {
						m_pScaleMap[i*scale+h][j*scale+l].cell->m_IsWall = true;
					}
				}
			}
		}
	}

	m_MapSizeX *= scale;
	m_MapSizeY *= scale;
	m_pMap = m_pScaleMap; //wyciek xDDD

	for (auto cell : m_Cells) {
		cell->addNeighbors(m_pMap);
	}
}

////////////////////////////////////////////////////////////
/// Function makeOurMazeNotPerfectAgain
/// @brief Ensures that there is more than one way to move
///         in the maze
////////////////////////////////////////////////////////////
void Maze::makeOurMazeNotPerfectAgain() {
	for (auto cell : m_Cells) {
		if (cell->m_IsWall) {
			int neigborsCount = 0;
			for (auto neighbor : cell->m_pNeighbors) {
				if (neighbor->m_IsWall)
					neigborsCount++;
			}
			if (neigborsCount == 3) {
				if (random(100) < 50)
					cell->m_IsWall = false;
			}
		}
	}
}


////////////////////////////////////////////////////////////
/// Function initializeRandomMaze
/// @brief Initializes maze
/// @in randomFactor - value between 0 and 1 determining
///     number of walls
////////////////////////////////////////////////////////////
void Maze::initializeRandomMaze(double randomFactor) {
	initializeMap(false);

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

////////////////////////////////////////////////////////////
/// Function initializeIsleMaze
/// @brief Initializes maze containing "isles" of walls
/// @in isleCount - number of isles generated
/// @in randomFactor - value between 0 and 1 determining
///     number of walls
////////////////////////////////////////////////////////////
void Maze::initializeIsleMaze(int isleCount, double randomFactor) {
	initializeMap(false);

	Point r;
	Cell *cell;
	for (int i = 0; i < isleCount; i++) {
		r = Point(random(0, m_MapSizeX - 1), random(0, m_MapSizeY - 1));
		cell = m_pMap[r.x][r.y].cell;
		cell->m_IsWall = true;
		recursiveWallPlacing(cell, randomFactor);
	}
}

////////////////////////////////////////////////////////////
/// Function recursiveWallPlacing
/// @brief recursively places wall
/// @in cell - cell ...
/// @in randomFactor - value between 0 and 1 determining
///     chance of spawning walls
////////////////////////////////////////////////////////////
void Maze::recursiveWallPlacing(Cell *cell, double randomFactor) {
	for (auto neighbor : cell->m_pNeighbors) {
		if (random() < randomFactor)
			neighbor->m_IsWall = true;
		if (random() < randomFactor && randomFactor >= 0.0000001)
			recursiveWallPlacing(neighbor, randomFactor - 0.05);
	}
}

void Maze::Print() {
#if defined(CONSOLE_VIEW_BUILD)
	gotoxy(0, 0);

	for (int i = 0; i < m_MapSizeX; i++) {
		for (int j = 0; j < m_MapSizeY; j++) {
			gotoxy(j + 1, i + 1);
			if (m_pMap[i][j].artifact != nullptr)
				(m_pMap[i][j].artifact)->show();
			else if (m_pMap[i][j].NPC != nullptr)
				(m_pMap[i][j].NPC)->show();
			else
				(m_pMap[i][j].cell)->show();
		}
		cout << endl;
	}
	for (int i = 0; i < m_MapSizeX + 2; i++) {
		for (int j = 0; j < m_MapSizeY + 2; j++) {
			if (i == 0 || j == 0 || i == m_MapSizeX + 1 || j == m_MapSizeY + 1) {
				gotoxy(j, i);
				cout << (char)178;
			}

		}
		cout << endl;
	}
#endif
}

bool Maze::ifCoordExist(int p, int mapSize) {
	return (p >= 0 && p < mapSize) ? true : false;
}

void Maze::spawnArtifact(double randomFactor) {
	artifactHasJustSpawned = false;

	static double i = 0.00;
	if (m_Artifacts.size() >= m_MaxArtifactCount
		|| random() > randomFactor - i)
		return;
	Point p = Point(random(0, m_MapSizeX - 1), random(0, m_MapSizeY - 1));
	if (m_pMap[p.x][p.y].cell->m_IsWall || m_pMap[p.x][p.y].NPC != nullptr || m_pMap[p.x][p.y].artifact != nullptr) {
		spawnArtifact(randomFactor - i);
		return;
	}
	Artifact* artifact = new Artifact(p, "", this);
	m_pMap[p.x][p.y].artifact = artifact;
	m_pMap[p.x][p.y].cell->m_IsWall = false;
	m_Artifacts.push_back(artifact);
	i += 0.05;

	artifactHasJustSpawned = true;

}

void Maze::spawnBot(string type) {
	AbstractPlayer* bot;
	Point p = Point(random(0, m_MapSizeX - 1), random(0, m_MapSizeY - 1));
	if (m_pMap[p.x][p.y].cell->m_IsWall || m_pMap[p.x][p.y].NPC != nullptr || m_pMap[p.x][p.y].artifact != nullptr) {
		spawnBot(type);
		return;
	}
	if (type == "A*")
		bot = new AStarBot(p, "A* Bot", this);
	else if (type == "Mouse") {
		bot = new MouseBot(p, "Mouse Bot", this);
	}
	else if (type == "Dijkstra") {
		bot = new DijkstraBot(p, "Dijkstra Bot", this);
	}
	else if (type == "different")
		;///...
	this->m_Characters.push_back(bot);
	m_pMap[p.x][p.y].NPC = bot;
	m_pMap[p.x][p.y].cell->m_IsWall = false;
	//usuwa ewentualna sciane na miejscu bota
}

void Maze::endSimulation() {
	for (auto character : m_Characters) {
		character->m_Timer.countResults();
	}
}

Maze::~Maze() {
	for (int i = 0; i < m_MapSizeY; i++) {///XD
		for (int j = 0; j < m_MapSizeY; j++) {
			delete m_pMap[i][j].cell;
			delete m_pMap[i][j].NPC;
			delete m_pMap[i][j].artifact;
		}
	}
}