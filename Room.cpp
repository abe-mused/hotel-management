#include "Room.h"

Room::Room(int type, int status){
	this->type = type;
	setStatus(status);
}
float Room::getCleaningFee(){
	return this->cleaningFee;
}
float Room::getRentalFeePerDay(){
	return this->rentalChargePerDay;
}
int Room::getStatus(){
	return this->status;
}
void Room::setStatus(int status){
	if(status == 0 || status == 1){
		//only changing the status to 0 or 1
		this->status = status;
	} else {
		cout<<"error, a problem ocurred changing the room's status"<<endl;
		exit(0);		
	}
}
int Room::getType(){
	return this->type;
}


