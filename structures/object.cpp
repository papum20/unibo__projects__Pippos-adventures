#include "object.hpp"


Object::Object() {
	Object(DFLT_UNIQUE_ID);
}
Object::Object(int unique_id) {
	this->unique_id = unique_id;
}

int Object::getUniqueId() {
	return unique_id;
}