#include "AbstractPlayer.hpp"

string AbstractPlayer::enumToString(PlayerType type) const {
	switch (type) {
	case PLAYER:
		return string("Player");
		break;
	case PLEDGE:
		return string("Pledge bot");
		break;
	case DIJKSTRA:
		return string("Dijkstra bot");
		break;
	case ASTAR:
		return string("Astar bot");
		break;
	}
}


ostream& operator<< (ostream& os, const AbstractPlayer& pl) {
	if (pl.m_Timer.time.first == 0)
		os << "";
	else
		os << pl.enumToString(pl.m_PlayerType) << " has finished earning " << pl.m_ArtifactsObtained;
	if (pl.m_ArtifactsObtained == 1)
		os << " artifact ";
	else 
		os << " artifacts ";
	os << "with total time of moving: " << (double)pl.m_Timer.time.first / 1000.0
		<< "s and with average per move: " << pl.m_Timer.time.second << "ms." << endl;
	return os;
}