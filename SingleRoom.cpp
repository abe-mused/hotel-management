#include "SingleRoom.h"

SingleRoom::SingleRoom(int type, int status):Room(type, status){
	this->cleaningFee = 25;
	this->rentalChargePerDay = 140;
}
