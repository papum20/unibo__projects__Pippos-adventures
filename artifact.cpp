#include "artifact.hpp"

Artifact::Artifact():item(){

}
Artifact::Artifact(const char n[], const char desc[]):item(n, desc){
    id=ID_ARTIFACT_S;
}

void Artifact::copyArtifact(Artifact B) {
    copyItem(B);
}


void Artifact::use_item(pItem item, int &stat) {

}