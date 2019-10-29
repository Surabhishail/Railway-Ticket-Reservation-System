#include "kernel.h"
#include "main.h"
#include "thread.h"
#include "train.h"
#include <fstream>
#include <iostream>
#include <sstream>

void readFileAndPrepareSchedule();
void startSimulation();
List<Train *> *allTrains = new List<Train *>;
int requestGranted = 0;
int requestRejected = 0;
int minute;

Thread *trainThread1 = new Thread("forked thread");
Thread *trainThread2 = new Thread("forked thread");
Thread *trainThread3 = new Thread("forked thread");
Thread *trainThread4 = new Thread("forked thread");
Thread *trainThread5 = new Thread("forked thread");

void
TrainThread(int which)
{
    int maxPassengersStart = 0;
    int maxPassengersEnd = 0;
    kernel->interrupt->SetLevel(IntOff);
    kernel->currentThread->Sleep(false);
    int lastStationBusinessPassengers=0;
    int lastStationCoachPassengers=0;
    while(true)
    {
        //cout<<"Train thread "<<which<<" is up!"<<endl;
        Train *train = allTrains->getItemAtIndex(which);
        if(train->getNextArrivalTime() == minute)
        {
            int businessPassengers = (20 - train->getStationList()->Front()->getSeatsBusiness()->NumClear())-lastStationBusinessPassengers;
            int coachPassengers = (40 - train->getStationList()->Front()->getSeatsCoach()->NumClear())-lastStationCoachPassengers;
            if(businessPassengers<0)
                businessPassengers=0;
            if(coachPassengers<0)
                coachPassengers=0;

            if((businessPassengers+coachPassengers)>=maxPassengersStart)
            {
                maxPassengersStart = businessPassengers+coachPassengers;
                train->updateBusiestStart(train->getStationList()->Front()->getStationNo());
            }
            cout<<businessPassengers<<" Business passengers and "<<coachPassengers<<" Coach passengers on-boarded the train "<<which<<" at minute "<<minute<<endl;
        }
        
        if(train->getNextDepartureTime() == minute)
        {
            Station* station = train->getStationList()->RemoveFront();

            if(!train->getStationList()->IsEmpty())
            {
                train->getStationNos()->RemoveFront();
                train->setNextArrivalTime(train->getStationList()->Front()->getArrivalTimeOfStation());
                train->setNextDepartureTime(train->getStationList()->Front()->getDepartingTimeFromStation());
                lastStationBusinessPassengers = 20-station->getSeatsBusiness()->NumClear();
                lastStationCoachPassengers = 40-station->getSeatsCoach()->NumClear();
                int businessPassengers = lastStationBusinessPassengers-(20 - train->getStationList()->Front()->getSeatsBusiness()->NumClear());
                int coachPassengers = lastStationCoachPassengers-(40 - train->getStationList()->Front()->getSeatsCoach()->NumClear());
                if(businessPassengers<0)
                    businessPassengers=0;
                if(coachPassengers<0)
                    coachPassengers=0;

            if((businessPassengers+coachPassengers)>=maxPassengersEnd)
            {
                maxPassengersEnd = businessPassengers+coachPassengers;
                train->updateBusiestEnd(train->getStationList()->Front()->getStationNo());
            }
                cout<<businessPassengers<<" Business passengers and "<<coachPassengers<<" Coach passengers off-boarded the train "<<which<<" at minute "<<minute<<endl;            
            }
        }
        kernel->currentThread->Sleep(false);
    }
}

void
AdminThread(int which)
{
    trainThread1->Fork((VoidFunctionPtr) TrainThread, (void *) 1);
    trainThread2->Fork((VoidFunctionPtr) TrainThread, (void *) 2);
    trainThread3->Fork((VoidFunctionPtr) TrainThread, (void *) 3);
    trainThread4->Fork((VoidFunctionPtr) TrainThread, (void *) 4);
    trainThread5->Fork((VoidFunctionPtr) TrainThread, (void *) 5);

    readFileAndPrepareSchedule();
    startSimulation();

    /*
    List<int> *somel = new List<int>;
    somel -> Append(10);
    somel -> Append(11);
    somel -> Append(12);
    somel -> Append(13);
    somel -> Append(14);
    int wowowow = somel -> getItemAtIndex(3);
    cout<<wowowow<<endl;
    */
}

void
ReservationThread(int which)
{
    //cout<<"In Reservation Thread number "<<which<<endl;
    int startLocation = 1 + ( rand() % 20 );
    int endLocation;
    while(true)
    {
        endLocation = 1 + ( rand() % 20 );
        if(startLocation != endLocation)
        {
            break;
        }
    }

    int noOfSeats = 1 + ( rand() % 8 );
    int classOfSeats = 0;
    if(rand()%10 == 0)
    {
        classOfSeats = 1;
    }

    for(int checkTrains = allTrains -> NumInList();checkTrains > 0; checkTrains--)
    {
        Train *eachTrain = allTrains -> getItemAtIndex(checkTrains);
        if(eachTrain -> doesRouteExist(startLocation,endLocation))
        {
            bool reservationSuccessful = eachTrain -> reserveSeats(startLocation,endLocation,classOfSeats,noOfSeats);
            if(reservationSuccessful)
            {
                requestGranted++;
                break;
                //cout<<"Minute" <<minute<<" Served request # "<<noOfRequest<<endl;
            }
        }
    }
    requestRejected++;
}


void
ThreadTest()
{
    kernel->interrupt->SetLevel(IntOff);
    Thread *t = new Thread("forked thread");
    t->Fork((VoidFunctionPtr) AdminThread, (void *) 1);
    
    //SimpleThread(0);
}

void
readFileAndPrepareSchedule()
{
    ifstream inFile;
    inFile.open("/home/ruchaudh/nachos/code/threads/data.txt");

    if (!inFile) 
    {
        cerr << "Unable to open file data.txt";
        exit(1);   // call system to stop
    }

    Train *train;
    string x;
    bool isNextTrainFlag = true;
    while (inFile >> x) 
    {
        if(x == "end")
        {
            //cout<<"end is here."<<endl;
            train->setNextArrivalTime(train->getStationList()->Front()->getArrivalTimeOfStation());
            train->setNextDepartureTime(train->getStationList()->Front()->getDepartingTimeFromStation());
            allTrains -> Append(train);
            isNextTrainFlag = true;
            continue;
        }

        int intLineInput;
        std::stringstream linestream(x);
        linestream >> intLineInput;

        if(isNextTrainFlag)
        {
            //cout<<"train is here."<<endl;
            train = new Train();
            train -> setTrainNumber(intLineInput);
            isNextTrainFlag = false;
            continue;
        }
        else
        {
            //cout<<"station is here."<<endl;
            Station *station = new Station();
            station -> setStationNo(intLineInput);
            string stationArrivalTime;
            string stationDepartureTime;
            if(inFile >> stationArrivalTime)
            {
                std::stringstream linestream(stationArrivalTime);
                linestream >> intLineInput;
                station -> setArrivalTimeOfStation(intLineInput);
            }
            if(inFile >> stationDepartureTime)
            {
                std::stringstream linestream(stationDepartureTime);
                linestream >> intLineInput;
                station -> setDepartingTimeFromStation(intLineInput);
            }
            train -> addStationToRoute(station);
        }
    }

    /*    // Check if all objects are populated correctly
    for(int i = allTrains -> NumInList();i>0;i--)
    {
        Train *localTrain = allTrains -> RemoveFront();
        if(i==3)
        {
            someTrain = localTrain;
            cout<<"Train no is."<<someTrain<<endl;
        }
        cout<<"Train no is."<<localTrain<<endl;
        List<Station *> *localTrainStationList = localTrain -> getStationList();
        for(int j = localTrainStationList -> NumInList();j>0;j--)
        {
            Station *localStation = localTrainStationList -> RemoveFront();
            //cout<<"Station # is "<<localStation -> getStationNo()<<endl;
        }
    }
    */

    inFile.close();
}

void
startSimulation()
{
    srand (time(NULL));
    for(minute = 1; minute < 961;minute++) // simulation
    {
        if(minute % 10 == 0)
        {
            int requestGrantedBeforeCurrentSimulationTime = requestGranted;
            int requestRejectedBeforeCurrentSimulationTime = requestRejected;

            for(int noOfRequest = 1; noOfRequest<=5;noOfRequest++) // 5 requests per 10 min
            {
                Thread *reservationThread = new Thread("forked thread");
                reservationThread->Fork((VoidFunctionPtr) ReservationThread, (void *) (minute*1000)+noOfRequest);
            }
            kernel->interrupt->SetLevel(IntOff);
            kernel->currentThread->Yield();                

            cout<<"Reservations summary for minute "<<minute<<endl;
            cout<<"Reservations granted: "<<requestGranted-requestGrantedBeforeCurrentSimulationTime<<endl;
            cout<<"Reservations refused: "<<requestRejected-requestRejectedBeforeCurrentSimulationTime<<endl;
 
        }
        kernel->interrupt->SetLevel(IntOff);
        kernel->currentThread->Yield();
        kernel->scheduler->ReadyToRun(trainThread1);
        kernel->currentThread->Yield();
        kernel->scheduler->ReadyToRun(trainThread2);
        kernel->currentThread->Yield();
        kernel->scheduler->ReadyToRun(trainThread3);
        kernel->currentThread->Yield();
        kernel->scheduler->ReadyToRun(trainThread4);
        kernel->currentThread->Yield();
        kernel->scheduler->ReadyToRun(trainThread5);
        kernel->currentThread->Yield();
    }
    cout<<"---------------------------------------------------------------"<<endl;
    for(int i = 1; i<=allTrains->NumInList();i++)
    {
        cout<<""<<endl;
        cout<<"Train "<<i<<" summary"<<endl;
        cout<<"Total served itinerary : "<<allTrains->getItemAtIndex(i)->getTotalItinerary()<<endl;
        cout<<"Total passengers : "<<allTrains->getItemAtIndex(i)->getTotalPassengers()<<endl;
        cout<<"Busiest section between station "<<allTrains->getItemAtIndex(i)->getBusiestStart()<<" and "<<allTrains->getItemAtIndex(i)->getBusiestEnd()<<endl;
        
    }
    cout<<""<<endl;
    cout<<"Total # of requests : " <<requestGranted+requestRejected<<endl;
    cout<<"Total # of granted request : " <<requestGranted<<endl; 
    cout<<"---------------------------------------------------------------"<<endl;
}