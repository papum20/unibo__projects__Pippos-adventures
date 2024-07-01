#include "main/artifact.hpp"

Artifact::Artifact():item(){
    id=ID_ARTIFACT_S;
    max_stat = 0;
    increment = 0;
    strcpy (rarity, " ");
    text_error[0] = '\0';
    text_success[0] = '\0';
}


void Artifact::copyArtifact(Artifact B) {
    id=B.id;
    max_stat = B.max_stat;
    increment = B.increment;
    strcpy (rarity, B.rarity);
    strcpy (text_error, B.text_error);
    strcpy (text_success, B.text_success);
    copyItem(B);
}


void Artifact::use_item(pItem item, int &stat, System_text* text) {
    if(id==ID_RUNE) {
        item->apply_rune();
        text->insert_string(text_success);
    }
	else if (stat+increment>=max_stat){
		stat=max_stat;
		text->insert_string(text_error);
	}
	else{
		stat=stat+increment;
		text->insert_string(text_success);
	}
}

