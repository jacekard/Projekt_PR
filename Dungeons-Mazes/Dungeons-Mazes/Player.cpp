#include "Player.hpp"
#include "Maze.hpp"

void Player::checkInputStatus() {
	//if (m_SystemClas.m_Input->IsKeyDown('W')) {
	//	m_Direction = UP;
	//}
	//else if (m_SystemClas.m_Input->IsKeyDown('S')) {
	//	m_Direction = DOWN;
	//}
	//else if (m_SystemClas.m_Input->IsKeyDown('A')) {
	//	m_Direction = LEFT;
	//}
	//else if (m_SystemClas.m_Input->IsKeyDown('D')) {
	//	m_Direction = RIGHT;
	//}
	//else {
	//	m_Direction = CENTER;
	//}
}

void Player::move() {
	m_Timer.tick();

	if (m_Direction != CENTER) {
		Point next = m_Position + m_Direction;
		//if(m_pMaze->ifCoordExist(next.x)) zrob to 
		if (m_pMaze->m_pMap[next.x][next.y].artifact != nullptr) {
			cout << "ZEBRALES ARTEFAKT!" << endl;
			m_ArtifactsObtained++;

			m_pMaze->m_Artifacts.erase(std::find(m_pMaze->m_Artifacts.begin(), m_pMaze->m_Artifacts.end(),
				m_pMaze->m_pMap[next.x][next.y].artifact));

			m_pMaze->m_pMap[m_Position.x][m_Position.y].NPC = nullptr;
			m_pMaze->m_pMap[next.x][next.y].artifact = nullptr;
			m_pMaze->m_pMap[next.x][next.y].NPC = this;
			m_Position = next;
		}
		else if (m_pMaze->m_pMap[next.x][next.y].NPC != nullptr) {
			cout << endl << endl << "SPOTKALISMY SIE. NIE MOGE PRZEJSC DALEJ";
		}
		else {
			m_pMaze->m_pMap[m_Position.x][m_Position.y].NPC = nullptr;
			m_pMaze->m_pMap[next.x][next.y].NPC = this;
			m_Position = next;
		}
	}
	m_Direction = CENTER;

	m_Timer.tock();
}

void Player::show() {
	#if defined(CONSOLE_VIEW_BUILD)
	cout << "P";
	#endif
}

Player::Player(Point p, PlayerType playerType, Maze* maze) : AbstractPlayer(p, playerType, maze) {
	m_Direction = UP;
}

Player::~Player() {

}