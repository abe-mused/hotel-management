#ifndef RESERVATION_H
#define RESERVATION_H
#include "Room.h"
#include "ExecutiveSuite.h"
#include "KingRoom.h"
#include "DoubleRoom.h"
#include "SingleRoom.h"
#include <stdlib.h>
#include <time.h>
#include <vector>

class Reservation
{
	private:
		int reservationNumber, numberOfGuests, duration;
		float inRoomWine, privateParking, airportPickup, breakfast;
		vector<Room> reservedRooms;
	public:
		Reservation(int, int, int);
		void addRoom(Room room);
		vector<Room> getReservedRooms();
		int getReservationNumber();
		int getDuration();
		int getNumberOfGuests();
		float getTotalForRooms();
		float getTotalCleaningFee();
		int getNumSingle();
		int getNumDouble();
		int getNumKing();
		int getNumExe();
		void setInRoomWineToTrue();
		void setPrivateParkingToTrue();
		void setBreakfastToTrue();
		void setAirportPickupToTrue();
		float getInRoomWineFee();
		float getPrivateParkingFee();
		float getBreakfastFee();
		float getAirportPickupFee();
		
};

#endif
