#include "structure.hpp"


Structure::Structure() {
	next_unique_id = UNIQUE_ID_START;
}

int Structure::nextUniqueId() {
	next_unique_id++;
	return next_unique_id - 1;
}