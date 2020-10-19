#include "ExecutiveSuite.h"

ExecutiveSuite::ExecutiveSuite(int type, int status):Room(type, status){
	this->cleaningFee = 75;
	this->rentalChargePerDay = 485;
}
