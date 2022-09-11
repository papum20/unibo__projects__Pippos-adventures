#include "artifact.hpp"

Artifact::Artifact():item(){
    id=ID_ARTIFACT_S;
    strcpy (rarity, " ");
}


void Artifact::copyArtifact(Artifact B) {
    id=B.id;
    strcpy (rarity, B.rarity);
    copyItem(B);
}


void Artifact::use_item(pItem item, int &stat, System_text* text) {

}

void apply_rune(){
    
}