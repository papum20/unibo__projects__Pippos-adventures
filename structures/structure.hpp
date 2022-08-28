//// CLASSE PADRE PER LE STRUTTURE DATI

#ifndef STRUCTURE_HPP
#define STRUCTURE_HPP


#define UNIQUE_ID_START 0


class Structure {
	private:
		int next_unique_id;
	protected:
		int nextUniqueId();
	public:
		Structure();
};


#endif