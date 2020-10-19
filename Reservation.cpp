#include "Reservation.h"
Reservation::Reservation(int reservationNumber, int numberOfGuests, int duration){
	this->numberOfGuests = numberOfGuests;
	this->duration = duration;
	this->reservationNumber = reservationNumber;
	inRoomWine = 0;
	privateParking = 0;
	airportPickup = 0;
	breakfast = 0;
}
void Reservation::addRoom(Room room){
	this->reservedRooms.push_back(room);
}
vector<Room> Reservation::getReservedRooms(){
	return this->reservedRooms;
}
int Reservation::getReservationNumber(){ return this->reservationNumber;}
int Reservation::getDuration(){ return this->duration;}
int Reservation::getNumberOfGuests(){ return this->numberOfGuests;}
float Reservation::getTotalForRooms(){
	float totalForRooms = 0;
	for(Room room : this->reservedRooms){
		totalForRooms += room.getRentalFeePerDay();
	}
	return totalForRooms*this->duration;
}
float Reservation::getTotalCleaningFee(){
	float cleaningFee = 0;
	for(Room room : this->reservedRooms){
		cleaningFee += room.getCleaningFee();
	}
	return cleaningFee;
}
int Reservation::getNumSingle(){
	int numOfSingleRooms = 0;
	for(Room room : this->reservedRooms){
		if(room.getType() == 1)
			numOfSingleRooms++;
	}
	return numOfSingleRooms;
}
int Reservation::getNumDouble(){
	int numOfDoubleRooms = 0;
	for(Room room : this->reservedRooms){
		if(room.getType() == 2)
			numOfDoubleRooms++;
	}
	return numOfDoubleRooms;
}
int Reservation::getNumKing(){
	int numOfKingRooms = 0;
	for(Room room : this->reservedRooms){
		if(room.getType() == 3)
			numOfKingRooms++;
	}
	return numOfKingRooms;
}
int Reservation::getNumExe(){
	int numOfExecutiveSuites = 0;
	for(Room room : this->reservedRooms){
		if(room.getType() == 4)
			numOfExecutiveSuites++;
	}
	return numOfExecutiveSuites;
}
void Reservation::setInRoomWineToTrue(){this->inRoomWine = 330.0;}
void Reservation::setPrivateParkingToTrue(){this->privateParking = 50.0;}
void Reservation::setBreakfastToTrue(){	this->breakfast = 40.0;}
void Reservation::setAirportPickupToTrue(){ this->airportPickup = 200.0;}
float Reservation::getInRoomWineFee(){ return this->inRoomWine;}
float Reservation::getPrivateParkingFee(){ return this->privateParking;}
float Reservation::getBreakfastFee(){ return this->breakfast;}
float Reservation::getAirportPickupFee(){ return this->airportPickup;}


