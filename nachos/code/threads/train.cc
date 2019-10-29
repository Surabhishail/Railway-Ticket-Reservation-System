#include "train.h"

void
Train::setNextArrivalTime(int pNextArrivalTime)
{
    nextArrivalTime = pNextArrivalTime;
}

void
Train::setNextDepartureTime(int pNextDepartureTime)
{
    nextDepartureTime = pNextDepartureTime;
}

int
Train::getNextArrivalTime()
{
    return nextArrivalTime;
}

int
Train::getNextDepartureTime()
{
    return nextDepartureTime;
}

void
Train::setTrainNumber(int pTrainNumber)
{
    trainNumber = pTrainNumber;
}

void
Train::addStationToRoute(Station *pStation)
{
    route -> Append(pStation);
    stationNos -> Append(pStation -> getStationNo());
}

int
Train::getTrainNumber()
{
    return trainNumber;
}

List<Station *>*
Train::getStationList()
{
    return route;
}

List<int>*
Train::getStationNos()
{
    return stationNos;
}

bool
Train::doesRouteExist(int start, int end)
{
    if(stationNos -> IsInList(start) && stationNos -> IsInList(end) && ((stationNos ->getIndexOf(start)) < (stationNos ->getIndexOf(end))))
    {
        return true;
    }
    return false;
}

bool
Train::reserveSeats(int startLocation,int endLocation,int classOfSeats,int noOfSeats)
{
    int indexOfStartLocation = stationNos -> getIndexOf(startLocation);
    int indexOfEndLocation = stationNos -> getIndexOf(endLocation);

    for(int i = indexOfStartLocation;i<=indexOfEndLocation;i++)
    {
        Station *currentStation = route -> getItemAtIndex(i);
        if(classOfSeats == 1)
        {
            if(!currentStation -> checkBusinessAvailability(noOfSeats))
            {
                return false;
            }
        }
        else
        {
            if(!currentStation -> checkCoachAvailability(noOfSeats))
            {
                return false;
            }
        }
    }

    for(int i = indexOfStartLocation;i<=indexOfEndLocation;i++)
    {
        Station *currentStation = route -> getItemAtIndex(i);
        currentStation -> reserveSeats(noOfSeats,classOfSeats);
    }
    incrementPassengers(noOfSeats);
    incrementItinerary();
    return true;
}

void
Train::incrementItinerary()
{
    totalItinerary++;
    return;
}

int
Train::getTotalItinerary()
{
    return totalItinerary;
}

void
Train::incrementPassengers(int no)
{
    totalPassengers+=no;
    return;
}

int
Train::getTotalPassengers()
{
    return totalPassengers;
}

void
Train::updateBusiestStart(int start)
{
    busiestStart = start;
    return;
}

void
Train::updateBusiestEnd(int end)
{
    busiestEnd = end;
    return;
}

int
Train::getBusiestStart()
{
    return busiestStart;
}

int
Train::getBusiestEnd()
{
    return busiestEnd;
}