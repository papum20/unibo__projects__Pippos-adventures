#include "artifact.hpp"

Artifact::Artifact(){

}
Artifact::Artifact(const char n[], const char desc[]):item(n, desc){
    id=ID_ARTIFACT_S;
}