//// TIENE IL POSTO A UN OGGETTO PHYSICAL (IN ROOM), CON UN PUNTATORE AD ESSO

#ifndef PLACEHOLDER_HPP
#define PLACEHOLDER_HPP

#include "physical.hpp"


class Placeholder : public Physical {
	private:
		pPhysical pointed;
	public:
		Placeholder(pPhysical pointed);
		pPhysical getObject();
};


#endif