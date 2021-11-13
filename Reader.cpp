#include "./SharedObject.h"
#include <iostream>
#include <iomanip>
#include "SharedObject.h"
#include "Semaphore.h"
#include <unistd.h>
using namespace std;
struct MyShared{
	int threadID;
	int reportID;
	double timerVar;
	int setThreadID(int id){
		threadID = id;
		return 0;
	};
	int setReportID(int id){
		reportID = id;
		return 0;
	};
	int setTimer(double timer){
		timerVar = timer;
		return 0;
	};
	int getThreadID(){
		return threadID;
	}
	int getReportID(){
		return reportID;
	}
	double getTimer(){
		return timerVar;
	}
	
} threadID, reportID, timerVar;


int main(void)
{
	Shared<MyShared> shared("sharedMemory");
	MyShared* sharedPoint = shared.get();
	MyShared sharedStruct = (*sharedPoint);
	Semaphore sharedSem1("sharedSem1");
	Semaphore sharedSem2("sharedSem2");
	
	bool read = true;
	std::cout << "I am a reader" << std::endl;
	//struct* sharedPoint = shared.get()
	
	while(read){
		MyShared* sharedPoint = shared.get();
		MyShared sharedStruct = (*sharedPoint); //update local copy of MyShared
		sharedSem2.Wait();
		sharedSem1.Signal();
		
		std::cout << to_string(sharedStruct.getThreadID()) + " " + to_string(sharedStruct.getReportID()) + " " + std::to_string(sharedStruct.getTimer()) <<std::endl;

		sharedSem1.Wait();
//		usleep(1000000);
	}
}

