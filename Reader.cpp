#include <iostream>
#include <iomanip>
#include "SharedObject.h"
#include <unistd.h>
using namespace std;
struct MyShared{
	std::string threadID;
	std::string reportID;
	double time;
};
int main(void)
{
	Shared<MyShared> shared("sharedMemory");
	bool read = true;
	std::cout << "I am a reader" << std::endl;
	
	/*while(read){
		std::cout << shared->threadID + " " + shared->reportID + " " + std::to_string(shared->time) <<std::endl;
		usleep(1000000);
	}*/
}

