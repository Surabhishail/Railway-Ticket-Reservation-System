#ifndef STATION_H
#define STATION_H

#include "list.h"
#include "request.h"
#include "bitmap.h"
class Station
{
    private:
		int stationNo; // 1 to 20
		int arrivalTimeOfStation; // 1 to 960
		int departingTimeFromStation; // 1 to 960
        Bitmap* seatsBusiness = new Bitmap(20);
		Bitmap* seatsCoach = new Bitmap(40);
		List<Request *> onBoardingList;
		List<Request *> offBoardingList;
    
    public:
        int getStationNo();
        int getArrivalTimeOfStation();
        int getDepartingTimeFromStation();
        Bitmap* getSeatsBusiness();
        Bitmap* getSeatsCoach();
        void setStationNo(int pStationNo);
        void setArrivalTimeOfStation(int pArrivalTimeOfStation);
        void setDepartingTimeFromStation(int pDepartingTimeFromStation);
        bool checkBusinessAvailability(int noOfSeats);
        bool checkCoachAvailability(int noOfSeats);
        void reserveSeats(int noOfSeats,int classOfSeats);
    /*
        void setMinutesLeft(int min);

        void reduceMinute();

        int getMinutesLeft();

        int getTimeOfArrival();

        int getTimeOfExit();

        int getExecutionTime();

        void setTimeOfArrival(int min);

        void setTimeOfExit(int min);
    */
};

#endif