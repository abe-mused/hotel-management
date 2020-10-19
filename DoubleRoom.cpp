#include "DoubleRoom.h"

DoubleRoom::DoubleRoom(int type, int status):Room(type, status){
	this->cleaningFee = 45;
	this->rentalChargePerDay = 210;
}
