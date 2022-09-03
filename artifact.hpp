#ifndef ARTIFACT_HPP
#define ARTIFACT_HPP

#include "item.hpp"
class Player;

class Artifact: public item{
    protected:

    public:
        Artifact();
        Artifact(const char n[], const char desc[]);
		void copy(Artifact B);			//copia i parametri di B

        virtual void use_item (Player *p);

};

typedef Artifact* pArtifact;


#include "player.hpp"

#endif