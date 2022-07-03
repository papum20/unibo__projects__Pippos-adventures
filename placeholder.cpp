#include "placeholder.hpp"

Placeholder::Placeholder(pPhysical pointed) {
	id = ID_PLACEHOLDER;
	this->pointed = pointed;
}

pPhysical Placeholder::getObject() {
	return pointed;
}