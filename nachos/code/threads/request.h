#ifndef REQUEST_H
#define REQUEST_H

class Request
{
    private:
		int requestId;
		int departingStationId;// 1 to 20
		int destinationStationId; // 1 to 20
		int departingTime; // 1 to 960
		int seatClass;    // 1 or 0, 1 = Business and 0 = Coach
		int noOfPassengers; // 1 to 8
    
    public:
        void setRequestId(int pRequestId);
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