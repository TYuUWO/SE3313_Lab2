#include "./SharedObject.h"
#include "./Semaphore.h"
#include <iostream>
#include <thread>
#include <string>
#include <unistd.h>
#include <vector>
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

namespace{
	volatile bool typeYes = true;
}

int task1(int delay, int numThread) {
int i = 0;
time_t timer;
time_t prevTime;
Shared<MyShared> shared("sharedMemory"); //create a local instance of "shared"
MyShared* sharedPoint = shared.get();
MyShared sharedStruct = (*sharedPoint);
Semaphore sharedSem1("sharedSem1"); //create a local instance of "sharedSem"
Semaphore sharedSem2("sharedSem2");


time(&prevTime);

while(typeYes){
	i++;
	cout << "Thread #: " << numThread << " Delay: "<< delay <<  " Iteration: " << i << endl;
	sleep(delay);
	
	sharedSem1.Wait(); //writing process begins after the wait
	sharedStruct.setThreadID(numThread);
	sharedStruct.setReportID(i);
	time(&timer);
	sharedStruct.setTimer(difftime(timer,prevTime));
	prevTime = timer;
	
	(*sharedPoint) = sharedStruct; //update global copy of MyShared
	
	sharedSem2.Signal();
	sharedSem1.Signal();
	//comment out later
	//std::cout << to_string(sharedStruct.getThreadID()) + " " + to_string(sharedStruct.getReportID()) + " " + std::to_string(sharedStruct.getTimer()) <<std::endl;
}

return 0;
}

int main(void) {
	Shared<MyShared> shared("sharedMemory", true); //This is the owner of sharedMemory
	Semaphore sharedSem1("sharedSem1", 1, true); //This is the owner of sharedSem
	Semaphore sharedSem2("sharedSem2", 0, true);
	std::vector<std::thread> threads;
	string secTime;
	string response;
	int n = 0;
	std::cout << "I am a Writer" << std::endl;
	while (typeYes) {
		n++;
		std::cout << "Do you want to make a new thread? (type \"yes\" to continue writing)" << std::endl;
		cin >> response;
		typeYes = (response == "yes");
		if (typeYes){
			cout << "What is the delay time for this thread?" << endl;
			cin >> secTime;
			threads.push_back(thread(task1, std::stoi(secTime), n));
		}
	}
	for (thread &th : threads){
		th.join();
	}

	return EXIT_SUCCESS;
	//Note: can't terminate thread yet

	//Compile code via g++ -pthread Writer.cpp
	////////////////////////////////////////////////////////////////////////
	// This is a possible starting point for using threads and shared memory. 
	// You do not have to start with this
	////////////////////////////////////////////////////////////////////////
	/*...
	Shared<MyShared> shared("sharedMemory", true); //This is the owner of sharedMamory
	...
	while(true){
		...
		//create thread using user input
		thread1 = new WriterThread(xyz); //add arguments as needed
		...
	}
	//example for one thread thread1
	thread1->flag= true;
	delete thread1;
	*/
}


////////////////////////////////////////////////////////////////////////
// This is a possible starting point for using threads and shared memory. 
// You do not have to start with this
////////////////////////////////////////////////////////////////////////
/*class WriterThread : public Thread{
	public:
		int 	threadNum;
		bool	flag;
		
		WriterThread(int in):Thread(8*1000){
			this->threadNum = in; //or whatever you want/need here
		}

		virtual long ThreadMain(void) override{
			...
			//declare shared memory var so this thread can access it
			Shared<MyShared> sharedMemory ("sharedMemory");
			while(true)
			{
				//write to shared memory
				...  
				if(flag){//Exit loop to end the thread
					break;
				}
			}
		}
};
*/
