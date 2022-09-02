#ifndef ARTIFACT_HPP
#define ARTIFACT_HPP

#include "physical.hpp"
#include "player.hpp"


class Artifact: public item{
    protected:

    public:
        Artifact();
        Artifact(const char n[], const char desc[]);
		void copy(Artifact B);			//copia i parametri di B

        virtual void use_item (pPlayer p){};

};

typedef Artifact* pArtifact;

#endif