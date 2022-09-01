#include "artifact.hpp"

Artifact::Artifact(const char n[], const char desc[]):item(n, desc){
    id=ARTIFACT_ID;
}