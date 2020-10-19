#ifndef ROOM_H
#define ROOM_H
#include <iostream>
using namespace std;

class Room
{
	protected:
		int status, type;
		float cleaningFee, rentalChargePerDay;
	public:
		Room(int, int);
		float getCleaningFee();
		float getRentalFeePerDay();
		int getStatus();
		void setStatus(int );
		int getType();
};

#endif
