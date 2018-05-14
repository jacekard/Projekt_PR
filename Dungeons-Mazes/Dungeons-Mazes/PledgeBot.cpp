#include "PledgeBot.hpp"
#include "Artifact.hpp"

////////////////////////////////////////////////////////////
/// Function move
/// @brief bot's position translates by his direction vector
///		based on Pledge conditions
////////////////////////////////////////////////////////////
void PledgeBot::move() {
	m_Timer.tick();

	Pledge();
	Point next = m_Position + m_Vector;
	if (m_pMaze->m_pMap[next.x][next.y].artifact != nullptr) {
		//cout << "ZEBRALES ARTEFAKT!" << endl;
		m_ArtifactsObtained++;
		m_pMaze->m_Artifacts.erase(std::find(m_pMaze->m_Artifacts.begin(), m_pMaze->m_Artifacts.end(),
			m_pMaze->m_pMap[next.x][next.y].artifact));
		m_pMaze->m_pMap[m_Position.x][m_Position.y].NPC = nullptr;
		m_pMaze->m_pMap[next.x][next.y].artifact = nullptr;
		m_pMaze->m_pMap[next.x][next.y].NPC = this;
		m_Position = next;
	}
	else if (m_pMaze->m_pMap[next.x][next.y].NPC != nullptr) {
		//cout << endl << endl << "SPOTKALISMY SIE. NIE MOGE PRZEJSC DALEJ";
	}
	else {
		m_pMaze->m_pMap[m_Position.x][m_Position.y].NPC = nullptr;
		m_pMaze->m_pMap[next.x][next.y].NPC = this;
		m_Position = next;
	}

	m_Timer.tock();
}

////////////////////////////////////////////////////////////
/// Function Pledge
/// @brief At the start direction vector is random, then bot 
///		moves along that direction. If it spots the wall, it 
///		turns left and substracts 90° from the 'special value' 
///		and keeps hand on the right wall. Then, he turns right, 
///		when the wall ends and adds 90°, or left, when spots 
///		another obstacle, and substracts 90°. When 'special value'
///		equals 0, the bot stops tracking the wall, which means
///		the direction vetor is same as at the beggining. It 
///		prevents from infinite loops.
////////////////////////////////////////////////////////////
void PledgeBot::Pledge() {
	static int degrees = 0;
	Point next = m_Position + m_Vector;
	if (degrees != 0) {
		next = m_Position + m_Vector.turnRight();
		if ((m_pMaze->ifCoordExist(next.x, m_pMaze->m_MapSizeX) && m_pMaze->ifCoordExist(next.y, m_pMaze->m_MapSizeY) && !m_pMaze->m_pMap[next.x][next.y].cell->m_IsWall)) {
			m_Vector = m_Vector.turnRight();
			degrees += 90;
			//Pledge();
		}
	}
	if ((!m_pMaze->ifCoordExist(next.x, m_pMaze->m_MapSizeX) || !m_pMaze->ifCoordExist(next.y, m_pMaze->m_MapSizeY) || m_pMaze->m_pMap[next.x][next.y].cell->m_IsWall)) {
		m_Vector = m_Vector.turnLeft();
		degrees -= 90;
		Pledge();
	}

}

void PledgeBot::show() {
	#if defined(CONSOLE_VIEW_BUILD)
	cout << "P";
	#endif
}

PledgeBot::PledgeBot(Point p, string name, Maze* maze) : AbstractPlayer(p, name, maze) {
	m_Vector = randomVector();
}

PledgeBot::~PledgeBot() {}