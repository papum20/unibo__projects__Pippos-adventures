#ifndef ARTIFACT_HPP
#define ARTIFACT_HPP

#include "character.hpp"
#include "item.hpp"
//#include "player.hpp"

class Artifact: public item{
    protected:

    public:
        Artifact();
        Artifact(const char n[], const char desc[]);
		void copy(Artifact B);			//copia i parametri di B

        //virtual void use_item (Player *p);
        virtual void use_item (equipment *equip, int &stat);

};

typedef Artifact* pArtifact;



#endif