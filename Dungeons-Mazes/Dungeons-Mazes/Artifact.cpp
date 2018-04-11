#include "Artifact.hpp"

void Artifact::show() {
#if defined(CONSOLE_VIEW_BUILD)
	cout << "$";
#endif
}