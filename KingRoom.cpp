#include "KingRoom.h"

KingRoom::KingRoom(int type, int status):Room(type, status){
	this->cleaningFee = 55;
	this->rentalChargePerDay = 190;
}
