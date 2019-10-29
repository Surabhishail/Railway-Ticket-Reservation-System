#include "station.h"

void
Station::setStationNo(int pStationNo)
{
    stationNo = pStationNo;
}

void
Station::setArrivalTimeOfStation(int pArrivalTimeOfStation)
{
    arrivalTimeOfStation = pArrivalTimeOfStation;
}

void
Station::setDepartingTimeFromStation(int pDepartingTimeFromStation)
{
    departingTimeFromStation = pDepartingTimeFromStation;
}

int
Station::getStationNo()
{
    return stationNo;
}

int
Station::getArrivalTimeOfStation()
{
    return arrivalTimeOfStation;
}

int
Station::getDepartingTimeFromStation()
{
    return departingTimeFromStation;
}

Bitmap*
Station::getSeatsBusiness()
{
    return seatsBusiness;
}

Bitmap*
Station::getSeatsCoach()
{
    return seatsCoach;
}

bool
Station::checkBusinessAvailability(int noOfSeats)
{
    if(seatsBusiness -> NumClear() >= noOfSeats)
    {
        return true;
    }
    return false;
}

bool
Station::checkCoachAvailability(int noOfSeats)
{
    if(seatsCoach -> NumClear() >= noOfSeats)
    {
        return true;
    }
    return false;
}

void
Station::reserveSeats(int noOfSeats,int classOfSeats)
{
    if(classOfSeats == 1)
    {
        for(int i = 0;i<noOfSeats;i++)
        {
            int bitNo = seatsBusiness -> FindAndSet();
        }
    }
    else
    {
        for(int i = 0;i<noOfSeats;i++)
        {
            int bitNo = seatsCoach -> FindAndSet();
        }
    }
    
}