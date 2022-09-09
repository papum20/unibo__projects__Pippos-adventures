#ifndef ARTIFACT_HPP
#define ARTIFACT_HPP

#include "character.hpp"
#include "item.hpp"
//#include "player.hpp"

class Artifact: public item{
    protected:

    public:
        Artifact();
		void copyArtifact(Artifact B);			//copia i parametri di B

        virtual void use_item (pItem item, int &stat);

};

typedef Artifact* pArtifact;



#endif