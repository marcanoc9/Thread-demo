#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>



using namespace std;

bool isready = false;
mutex mutx;  
condition_variable conv;  
const int NUM_THREADS = 5;  

// Function executed by each thread

void threadFunction(int id){
unique_lock<mutex> lock(mutx);

// Wait 
while (!isready){
        conv.wait(lock);
    }

    cout << "A thread " << id << " is running" << endl;


// Notify that something happened
    conv.notify_all();
}
int main(){
    vector<thread> threads;
// Create and start the threads

    for (int i = 0; i < NUM_THREADS; ++i){

        threads.push_back(thread(threadFunction, i));
    }
// Allow  threads to proceed

    {
        lock_guard<mutex> lock(mutx);
        isready = true;
    }
    conv.notify_all();
// Wait for all threads to finish

    for (auto& thread : threads)

    {
        thread.join();
    }
    cout << "All threads have finished" << endl;

    return 0;

}



