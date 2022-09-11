#ifndef ARTIFACT_HPP
#define ARTIFACT_HPP

#include "item.hpp"

class Artifact: public item{
    protected:

    public:
        Artifact();
		void copyArtifact(Artifact B);			//copia i parametri di B

        virtual void use_item (pItem item, int &stat, System_text* text);

};

typedef Artifact* pArtifact;



#endif