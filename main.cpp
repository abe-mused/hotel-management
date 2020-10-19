//abe mused
//theis is a hotel management system, read the readme.txt file for more information.
#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>
#include <sstream>
#include <exception>
#include<iterator>
#include "Room.h"
#include "SingleRoom.h"
#include "DoubleRoom.h"
#include "KingRoom.h"
#include "ExecutiveSuite.h"
#include "Reservation.h"
using namespace std;
void validateInt(int , int , int &);
void makeReservation();
vector<Room> importRoomData();
void askAboutAddOns(Reservation&);
void printReservationInfo(Reservation);
void updateRoomDataBase(vector<Room>);
void appendReservationDataBase(Reservation);
void searchReservations();
vector<Reservation> importReservations();
void displayRoomsPricing();
int generateReservationNumber();
void about();

template <typename T, typename X> //template to check if a vector of number contains a sepicific number
bool contains(vector<T> allNumbers, X Number){
	for(T fromVector: allNumbers){
		if(fromVector == Number)
		return true;
	}
}
class InvalidEntryException: public exception
{
  virtual const char* what() const throw()
  {
    return "Invalid entry, entry must be a digit. ";
  }
} IEException; 
// i created this exception to give the user a meaningful feedback when they enter a non-digit character for int

int main(int argc, char** argv) {
	srand (time(NULL));
	int choice;
	while(choice != 5){
		system("cls");
		cout<<endl<<"welcome to the the luxury collection hotels"<<endl;
		cout<<endl<<"1) make a reservation"<<endl;
		cout<<"2) search reservations"<<endl;
		cout<<"3) rooms and pricing"<<endl;
		cout<<"4) about the luxury collection hotel"<<endl;
		cout<<"5) close program"<<endl;
		cin>>choice;
		validateInt(5, 1, choice);
			
		switch(choice){
			case 1:
				makeReservation();
				break;
			case 2:
				searchReservations();
				break;
			case 3:
				displayRoomsPricing();
				break;
			case 4:
				about();
				break;
			default:
				break;
		}
	}
	cout<<"thank you for choosing the luxury collection hotels!"<<endl;
	return 0;
}
void validateInt(int max, int min, int &choice){// this is a function that validates ints, i used it throuhgout the program
	while(choice < min || choice > max || cin.fail()){
		try{
			cout<<"please enter a number between "<<min<<" and "<<max<<": "<<endl;
			cin>>choice;
			if(cin.fail()){throw IEException;}//throw the exception i created when the user inputs anything that'd not integer
		}catch(exception& e){
			cout<<e.what();
			cin.clear();
			cin.ignore(10, '\n');
		}
	}
}
void makeReservation(){
	vector<Room> allRooms;
	allRooms = importRoomData();//imported the most up-to-date room data from allroom.txt
	int typechoice, numberOfGuests, moreRooms, duration;
	bool roomAdded;//to tell the user whether the room they selected was added to the reservationn or not
	cout<<"welcome! please enter the number of guests: (max is 10, call us if more) ";
	cin>>numberOfGuests;
	validateInt(10, 1, numberOfGuests);
	cout<<"how long do you plan on staying: ";
	cin>>duration;
	validateInt(100, 1, duration);//they can't stay longer than 100 days
	Reservation reservation(generateReservationNumber(), numberOfGuests, duration);/*i created and used a function that 
	reads all current reservation records and generates a reservation number that's never been created before*/
	do{
		roomAdded = false;
		cout<<endl<<"1) single room           $70 /day"<<endl;
		cout<<"2) double room           $100/day"<<endl;
		cout<<"3) king room             $90 /day"<<endl;
		cout<<"4) executive suite       $300/day"<<endl<<endl;
		cout<<"what type of room would you like to book: ";
		cin>>typechoice;
		validateInt(4, 1, typechoice);
		for(int i = 0; i < allRooms.size(); i++){
			if(allRooms.at(i).getType() == typechoice && allRooms.at(i).getStatus() == 1) {/*checking if we have any avialable rooms 
		of the selected type, if so i add it to the reservation.i also mark the room unavialable so i can update room records*/
				reservation.addRoom(allRooms.at(i));
				allRooms[i].setStatus(0);
				cout<<endl<<"the selected room has been added to your reservation"<<endl;
				roomAdded = true;
				break;
			}
		}
		if(!roomAdded)
			cout<<endl<<"we apologize, there are no avialable room of selected type."<<endl;

		if(reservation.getReservedRooms().size()*2 < numberOfGuests){
		//only if the user has at least room/2guests they can proceed
			moreRooms = 1;
			cout<<endl<<endl<<endl<<"you have "<<reservation.getReservedRooms().size()<<" rooms in your current reservation and "<<numberOfGuests;
			cout<<" guests, "<<endl<<"according to our polciy, there has to be at least a room for every two guests in a reservation.";
			cout<<endl<<"press any button to continue adding rooms ..."<<endl;
			getch();
		}else{
		cout<<endl<<"would you like to add another room to your reservation? 1-yes 2-no ";
		cin>>moreRooms;
		validateInt(2, 1, moreRooms);
		}
		system("cls");
	}while(moreRooms == 1);
	system("cls");
	askAboutAddOns(reservation);//after theu're done adding rooms, they're asked if they want any add-ons
	system("cls");
	updateRoomDataBase(allRooms);
	appendReservationDataBase(reservation);
	//keeping everything in files, even if you close the program, the data will still be the same.
	//you can make a reservation, close the program, then open it and use the reservation # to look up your reservation.
	//booked rooms will still be booked even if you restart the program, same for avialable ones.
	printReservationInfo(reservation);

}
vector<Room> importRoomData(){
	vector<Room> allRooms;
	ifstream inputFile("allrooms.txt");
	
	if(inputFile.fail()){
		cout<<"error, couldn't import rooms data from file"<<endl;
		exit (EXIT_FAILURE);
	}else{
		int roomType, status;
		while(inputFile >> roomType >> status){//every line in the file represents one room; type then status
			switch(roomType){
				//based on the type of the room, i create the corresponding object and add it to all rooms
				case 1:
					allRooms.push_back(SingleRoom(roomType,status));
					break;
				case 2:
					allRooms.push_back(DoubleRoom(roomType,status));
					break;
				case 3:
					allRooms.push_back(KingRoom(roomType,status));
					break;
				case 4:
					allRooms.push_back(ExecutiveSuite(roomType,status));
					break;
				default:
					cout<<"error, could'nt identify one room type"<<endl;
					break;
			}
		}
	}
	inputFile.close();
	return allRooms;
}
void askAboutAddOns(Reservation& reservation){
	int temp;
	//i didn't indicate the prices on purpose, because most hotels don't unitl checkout :)
	cout<<"we have a private parking structure. it is 24-hr monitored and it includes a car wash everyday!"<<endl;
	cout<<"would you like to purchase a spot in our private parking? 1-yes 2-no "<<endl;
	cin>>temp;
	validateInt(2, 1, temp);
	if(temp == 1){reservation.setPrivateParkingToTrue();}
	cout<<"we also have a fine collection of wine, some of it dates back to the 1890s!"<<endl;
	cout<<"would you like to add in-room-wine to your reservation? 1-yes 2-no "<<endl;
	cin>>temp;
	validateInt(2, 1, temp);
	if(temp == 1){reservation.setInRoomWineToTrue();}
	cout<<"would you like to add some delicious breakfast to you mornings? 1-yes 2-no "<<endl;
	cin>>temp;
	validateInt(2, 1, temp);
	if(temp == 1){reservation.setBreakfastToTrue();}
	
	cout<<"do you want us to send someone to pick you up at the airport? 1-yes 2-no "<<endl;
	cin>>temp;
	validateInt(2, 1, temp);
	if(temp == 1){reservation.setAirportPickupToTrue();}
}
void printReservationInfo(Reservation reservation){
	//this function generates a receipt/report from raw data stored in a reservation object
	float addOnTotal = 0, subTotal = 0;
	cout<<"\t\there's your reservation info"<<endl<<endl;
	cout<<"reservation number:    "<<reservation.getReservationNumber()<<endl;
	cout<<"duration:              "<<reservation.getDuration()<<" days"<<endl;
	cout<<"number of guests:      "<<reservation.getNumberOfGuests()<<endl<<endl;
	cout<<"Your Room Information:"<<endl;
	if(reservation.getNumSingle() >= 1){//only display single rooms if any is booked, same for the erst of the room types 
		cout<<"\tSingle Rooms:             "<<reservation.getNumSingle()<<" rooms * $140 * ";
		cout<<reservation.getDuration()<<" days = $"<<reservation.getNumSingle()*140*reservation.getDuration()<<endl;
	}
	if(reservation.getNumDouble() >= 1){
		cout<<"\tDouble Rooms:             "<<reservation.getNumDouble()<<" rooms * $210 * ";
		cout<<reservation.getDuration()<<" days = $"<<reservation.getNumDouble()*210*reservation.getDuration()<<endl;
	}
	if(reservation.getNumKing() >= 1){
		cout<<"\tKing Rooms:               "<<reservation.getNumKing()<<" rooms * $190 * ";
		cout<<reservation.getDuration()<<" days = $"<<reservation.getNumKing()*190*reservation.getDuration()<<endl;
	}
	if(reservation.getNumExe() >= 1){
		cout<<"\tExecutive Suites:         "<<reservation.getNumExe()<<" rooms * $485 * ";
		cout<<reservation.getDuration()<<" days = $"<<reservation.getNumExe()*485*reservation.getDuration()<<endl;
	}
	
	cout<<endl<<"your add ons information:"<<endl;
	if(reservation.getBreakfastFee()>0){ //only display add-ons if they were added to the reservation
		cout<<"\tBreakfast:                $"<<reservation.getBreakfastFee()<<" * "<< reservation.getDuration();
		cout<<" days = $"<<reservation.getBreakfastFee()*reservation.getDuration()<<endl;
		addOnTotal += reservation.getBreakfastFee()*reservation.getDuration();
	}
	if(reservation.getInRoomWineFee()>0){
		cout<<"\tIn-Room-Wine:             $"<<reservation.getInRoomWineFee()<<" * "<< reservation.getDuration();
		cout<<" days = $"<<reservation.getInRoomWineFee()*reservation.getDuration()<<endl;
		addOnTotal += reservation.getInRoomWineFee()*reservation.getDuration();
	}
	if(reservation.getPrivateParkingFee()>0){
		cout<<"\tPrivate Parking:          $"<<reservation.getPrivateParkingFee()<<" * "<< reservation.getDuration();
		cout<<" days = $"<<reservation.getPrivateParkingFee()*reservation.getDuration()<<endl;
		addOnTotal += reservation.getPrivateParkingFee()*reservation.getDuration();
	}
	if(reservation.getAirportPickupFee()>0){
		cout<<"\tAirport Pickup:           $"<<reservation.getAirportPickupFee()<<endl;
		addOnTotal += reservation.getAirportPickupFee();
	}
	subTotal = reservation.getTotalForRooms() + addOnTotal + reservation.getTotalCleaningFee();
	cout<<endl<<"rooms total:                 $"<<reservation.getTotalForRooms()<<endl;
	cout<<"extras total:                $"<<addOnTotal<<endl;
	cout<<"cleaning fees:               $"<<reservation.getTotalCleaningFee()<<endl;
	cout<<endl<<"subtotal:                    $"<<subTotal<<endl;
	cout<<"taxes:                       $"<<subTotal*0.06<<endl;
	cout<<endl<<"total due:                   $"<<subTotal+subTotal*0.06<<endl;
	cout<<endl<<"thank you for your business!"<<endl;
	getch();
}
void updateRoomDataBase(vector<Room> allRooms){	
	//overriting the rooms database to save for next time the program is opened
	ofstream outputFile("allrooms.txt");
	for(Room room : allRooms){
		outputFile<<room.getType()<<" "<<room.getStatus()<<endl;
	}
	outputFile.close();
}
void appendReservationDataBase(Reservation reservation){
	//adding reservation to database 
	ofstream outputFile("reservations.txt",ios::app);
	outputFile<<reservation.getReservationNumber()<<" "<<reservation.getNumberOfGuests()<<" "<<reservation.getDuration();
	outputFile<<" "<<reservation.getInRoomWineFee()<<" "<<reservation.getPrivateParkingFee()<<" ";
	outputFile<<reservation.getBreakfastFee()<<" "<<reservation.getAirportPickupFee();
	for(Room room : reservation.getReservedRooms()){
		outputFile<<" "<<room.getType();
	}
	outputFile<<endl;
	outputFile.close();
}
void searchReservations(){
	//searching previous reservation
	int reservationNumber, flag = 0;
	vector<Reservation> allReservations = importReservations();//importing reservation that were saved previously
	cout<<"enter the number of your reservation: ";
	cin>>reservationNumber;
	validateInt(999999999,0,reservationNumber);
	//i don't care what they input, only sent it to validat function to prevent crash if user inputs a letter
	for(Reservation reservation : allReservations){
		if(reservation.getReservationNumber() == reservationNumber){
			printReservationInfo(reservation);
			flag = 1;
			break;
		}
	}
	if(flag ==0 ){
		cout<<"no reservation with that number was found, press any button to continue...";
		getch();
	}
}
vector<Reservation> importReservations(){
	int reservationNumber = 0, numberOfGuests = 0, duration = 0, roomType = 0;
	float inRoomWine = 0, privateParking = 0, breakfast = 0, airportPickup = 0;
	string line;
	vector<Reservation> allReservations;	
	ifstream inputFile("reservations.txt");
	
	if(inputFile.fail()){
		cout<<"error, couldn't import reservation data from file"<<endl;
		exit (EXIT_FAILURE);
	}else{

		while(getline(inputFile, line)){//reading data line by line, each line is a reservation
			istringstream iss(line); 
			iss>>reservationNumber>>numberOfGuests>>duration>>inRoomWine>>privateParking>>breakfast>>airportPickup;
			//first three numbers in each line go towards creating the reservation
			Reservation reservation(reservationNumber,numberOfGuests,duration);
			//now i check if that reservation had add-ons and i add them to the reservation i'm creating now
			if(inRoomWine > 0){reservation.setInRoomWineToTrue();}
			if(privateParking > 0){reservation.setPrivateParkingToTrue();}
			if(breakfast > 0){reservation.setBreakfastToTrue();}
			if(airportPickup > 0){reservation.setAirportPickupToTrue();}
			//i don't know how many rooms were added to that reservation at the time of creation, after the seven digits
			//each number represents the TYPE of a room that was in the reservation, the type is all i need, the status 
			//is autumatically 0, booked, because the room is in a reservation(reserved);
			while ( iss >> roomType){
				switch(roomType){//based on what the number is, i create the appropriate room object.
				case 1:
					reservation.addRoom(SingleRoom(roomType,0));
					break;
				case 2:
					reservation.addRoom(DoubleRoom(roomType,0));
					break;
				case 3:
					reservation.addRoom(KingRoom(roomType,0));
					break;
				case 4:
					reservation.addRoom(ExecutiveSuite(roomType,0));
					break;
				default:
					cout<<"error, could'nt identify one room type"<<endl;
					break;
				}
			}
			allReservations.push_back(reservation);//reservation is added to the vector after it's complete.
		}
	}
	inputFile.close();
	return allReservations;
}
void displayRoomsPricing(){
	system("cls");
	cout<<endl<<"welcome to the the luxury collection hotel"<<endl;
	cout<<endl<<"while we have many unique rooms and suites that can be booked by calling an agent,"<<endl;
	cout<<"we have four main types of spaces: "<<endl<<endl;
	cout<<"\t1) single room "<<endl;
	cout<<"\t	325 square feet, one bathroom"<<endl;
	cout<<"\t	$140 per day, $25 one-time cleaning fee"<<endl<<endl;
	cout<<"\t2) double room "<<endl;
	cout<<"\t	500 square feet, one bathroom"<<endl;
	cout<<"\t	$210 per day, $25 one-time cleaning fee"<<endl<<endl;
	cout<<"\t3) king room "<<endl;
	cout<<"\t	465 square feet, one bathroom"<<endl;
	cout<<"\t	$190 per day, $25 one-time cleaning fee"<<endl<<endl;
	cout<<"\t4) executive suite "<<endl;
	cout<<"\t	945 square feet, two bathrooms"<<endl;
	cout<<"\t	$485 per day, $25 one-time cleaning fee"<<endl<<endl;
	
	cout<<endl<<"press any button to go back to the main menu...";
	getch();
}
int generateReservationNumber(){
	int reservationNumber = (rand() % 8999999) + 1000000;
//	int reservationNumber;
//	cout<<"enter a reservation Number: "<<endl; 				used this to test if this function actually works
//	cin>>reservationNumber;
	vector<Reservation> allReservations = importReservations();
	vector<int> allReservationNumbers;
	vector<Reservation>::iterator it;//i prefer advanced for loops, i only did this for the xtra credit.
	for(it = allReservations.begin(); it != allReservations.end(); it++){
		allReservationNumbers.push_back(it->getReservationNumber());
	}//i imported reservations from records and extracted reservations numbers from them.
	while(contains(allReservationNumbers, reservationNumber)){
		//used the template to check if the reservation numbers  vector contains the newly-generated one.
		//if it does, then i keep incrementing the generated # until it's unique. if there are so many reservation numbers 
		//in the data base,the # reaches the limit, it is reset to the minimum, 1000000;
		if(reservationNumber == 9999999){
			reservationNumber = 1000000;
		}
			reservationNumber++;
	}
	return reservationNumber;
}
void about(){
	system("cls");
	cout<<endl<<"the luxury collection hotels owns more than 150 hotels around the world"<<endl;
	cout<<"the largest one being in Detroit, Mi. we have been operating hotels since the 1960s"<<endl;
	cout<<"is you have any questions, concerns or thaughts, please don't hesitate to contact us."<<endl<<endl;
	cout<<endl<<"	contact info:"<<endl<<endl;
	cout<<"	phone:     +1(313) 552-9846"<<endl;
	cout<<"	email:     info@luxurycollection.com"<<endl;
	cout<<"	website:   luxurycollection.com"<<endl<<endl;
	cout<<"press any button to go back to the main menu...";
	getch();
}
