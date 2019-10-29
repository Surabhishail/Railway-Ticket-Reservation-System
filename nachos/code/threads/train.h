#ifndef TRAIN_H
#define TRAIN_H

#include "list.h"
#include "station.h"
#include "request.h"

class Train
{
    private:
        int trainNumber;
        List<int> *stationNos = new List<int>;
	    List<Station *> *route = new List<Station *>;
		List<Request *> *currentlyOnTrain;
        int nextArrivalTime;
        int nextDepartureTime;
        int totalItinerary;
        int totalPassengers;
        int busiestStart;
        int busiestEnd;

    public:
        int getTrainNumber();
        List<Station *>* getStationList();
        List<int>* getStationNos();
        void setTrainNumber(int pTrainNumber);
        void addStationToRoute(Station *pStation);
        void incrementItinerary();
        bool doesRouteExist(int start, int end);
        bool reserveSeats(int startLocation,int endLocation,int classOfSeats,int noOfSeats);
        void setNextArrivalTime(int pNextArrivalTime);
        void setNextDepartureTime(int pNextDepartureTime);
        int getNextArrivalTime();
        int getNextDepartureTime();
        int getTotalItinerary();
        void incrementPassengers(int no);
        int getTotalPassengers();
        void updateBusiestStart(int start);
        void updateBusiestEnd(int end);
        int getBusiestStart();
        int getBusiestEnd();
};

#endif