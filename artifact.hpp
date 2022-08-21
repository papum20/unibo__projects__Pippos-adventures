#ifndef ARTIFACT_HPP
#define ARTIFACT_HPP

#include "physical.hpp"

class Artifact: public item{
    protected:

    public:
        Artifact();

        virtual void use_item (pPlayer p);

};

typedef Artifact* pArtifact;

#endif