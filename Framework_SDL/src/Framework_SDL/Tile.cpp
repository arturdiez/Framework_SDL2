//#include "Tile.h"
//
//Tile::Tile() {
//	bool creationEnded = false;
//	int roomCount = 0;
//
//	while(!creationEnded) {
//		for (int i = 0; i < MAX_ROOM_W; ++i) {
//			for (int j = 0; j < MAX_ROOM_H; j++) {
//				tileRoom[i][j] = new Texture("Tile.png");
//				tileRoom[i][j]->Parent(rooms[roomCount]);
//			}
//		}
//		roomCount++;
//
//		if (roomCount > MAX_NUM_ROOMS) {
//			creationEnded = true;
//		}
//	}
//
//	for (int i = 0; i < MAX_NUM_ROOMS; ++i) {
//		rooms[i]->Parent(map);
//	}
//	
//
//}
//
//
//Tile::~Tile() {
//
//}



