#include "AbstractPlayer.hpp"

ostream& operator<< (ostream& os, const AbstractPlayer& pl) {
	if (pl.m_Timer.time.first == 0)
		os << pl.m_Name << " hasn't finished the simulation!";
	else
	os << pl.m_Name << " has finished earning "<< pl.m_ArtifactsObtained << " artifacts with total time of moving: " << (double)pl.m_Timer.time.first / 1000.0
		<< "s and with average per move: " << pl.m_Timer.time.second << "ms." << endl;
	return os;
}