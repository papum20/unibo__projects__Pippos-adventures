#ifndef ARTIFACT_HPP
#define ARTIFACT_HPP

#include "item.hpp"

class Artifact: public item{
    protected:
        int increment;
        int max_stat;
        char text_error[max_words];
        char text_success[max_words];

    public:

        Artifact();
		void copyArtifact(Artifact B);			//copia i parametri di B

        void use_item (pItem item, int &stat, System_text* text);

};

typedef Artifact* pArtifact;



#endif