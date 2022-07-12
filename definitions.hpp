#ifndef GENERAL_DEFINITIONS
#define GENERAL_DEFINITIONS


#pragma region CAMERA_DEFINITIONS
#define CAMERA_WIDTH 135	//larghezza (massima) inquadratura livello
#define CAMERA_HEIGHT 35	//altezza (massima) inquadratura livello
#pragma endregion CAMERA_DEFINITIONS


#pragma region ROOM_DEFINITIONS
#define X_SCALE 9									//coefficiente di "allargamento orizzontale" della stanza
#define ROOM_WIDTH_T 30								//larghezza (senza scala) stanza
#define ROOM_WIDTH (ROOM_WIDTH_T * X_SCALE)//320	//larghezza (reale) stanza
#define ROOM_HEIGHT 40//180							//altezza stanza
#define ROOM_AREA_T (ROOM_WIDTH_T * ROOM_HEIGHT)
#define ROOM_AREA (ROOM_WIDTH * ROOM_HEIGHT)
#define CENTRAL_ROOM_SIZE 8							//dimensioni dello spazio vuoto quadrato al centro
#pragma endregion ROOM_DEFINITIONS

#endif