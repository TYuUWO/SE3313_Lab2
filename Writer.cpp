#include <iostream>
#include <thread>
#include <string>
#include <unistd.h>
#include <vector>
using namespace std;

struct MyShared{
	int threadID;
	int reportID;
	double time;
} threadID, report ID, time;

int task1(int delay,bool typeYes, int numThread) {
int i = 0;
while(typeYes){
	sleep(delay);
	i++;
	cout << "Thread #: " << numThread << " Delay: "<< delay <<  " Iteration: " << i << endl;
}
return 0;
}

int main(void) {
	Shared<MyShared> shared("sharedMemory", true); //This is the owner of sharedMamory
	
	std::vector<std::thread> threads;
	string secTime;
	string response;
	int n = 0;
	bool typeYes = true;
	std::cout << "I am a Writer" << std::endl;
	while (typeYes) {
		n++;
		std::cout << "Do you want to make a new thread? (type \"yes\" to continue writing)" << std::endl;
		cin >> response;
		typeYes = (response == "yes");
		if (typeYes){
			cout << "What is the delay time for this thread?" << endl;
			cin >> secTime;
			threads.push_back(thread(task1, std::stoi(secTime), typeYes, n));
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
