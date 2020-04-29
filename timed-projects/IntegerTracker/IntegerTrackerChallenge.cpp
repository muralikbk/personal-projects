/*
CODE CHALLENGE

Write a class IntegerTracker with these methods:


track(int) - Receives an integer for tracking.

get_max() - Returns the max (int) of all integers seen so far.

get_min() - Returns the min (int) of all integers seen so far.

get_mean() - Returns the mean (float) of all integers seen so far.

get_mode() - Returns the mode (most frequent) (int) of all integers seen so far.


Ensure each method, including track, runs in constant time (O(1) time complexity). You may assume track will be called at least once. State any other assumptions you make in your solution.

*/

//Written in gvim. compiled and tested with g++ command line on osx

//Assumption: Min,Max,Mode, Avg will return 0 if no data is available.
#include <iostream>
#include <limits>
#include <unordered_map>


using namespace std;


class IntegerTracker
{
    unordered_map<int, int> countTrack;
    //We keep the running total as long integers in case of overflows
    long runningTotal;
    int count;
    int min;
    int max;
    int mode;
    
    public:
    IntegerTracker(): count(0), runningTotal(0), min(0), max(0),mode(0)
    {
        

    }

    //We assume this will always be a success - not adding error checks for the sake of time
    void track(int input) //Receives an integer for tracking.
    {
        countTrack[input]++;
        count++;
        if(1 == count) //First element
        {
            mode = runningTotal = max = min = input;
            
            
        }
        else
        {
            runningTotal += input; 
            if(min > input)
            {
                min = input;
            } 
            if(max < input)
            {
                max = input;
            }

            //Mode is updated ONLY if the current input has a 
            //greater count than the previous mode
            if(countTrack[input] > countTrack[mode])
            {
                mode = input;
            }
        }

    }


    int get_max() //Returns the max (int) of all integers seen so far.
    {
        return max;
    }

    int get_min() //Returns the min (int) of all integers seen so far.
    {
        return min;
    }

 
    float get_mean() //Returns the mean (float) of all integers seen so far.
    {
        if(0 != count)
        {
            return( ((float)runningTotal)/ count ) ;
        }

        return 0.0;
    }


    int get_mode()  //Returns the mode (most frequent) (int) of all integers seen so far.
    {
        return mode;
    }

};

int main(int argc, char *argv[])
{
    IntegerTracker integer_tracker;
    integer_tracker.track(1);
    integer_tracker.track(0);
    cout << "Max:" << integer_tracker.get_max() << endl;
    cout << "Min:" << integer_tracker.get_min() << endl;
    cout << "Mean:" << integer_tracker.get_mean() << endl;
    cout << "Mode:" << integer_tracker.get_mode() << endl;

    integer_tracker.track(3);
    integer_tracker.track(1);
    cout << "Max:" << integer_tracker.get_max() << endl;
    cout << "Min:" << integer_tracker.get_min() << endl;
    cout << "Mean:" << integer_tracker.get_mean() << endl;
    cout << "Mode:" << integer_tracker.get_mode() << endl;

    integer_tracker.track(-10);
    integer_tracker.track(100);
    cout << "Max:" << integer_tracker.get_max() << endl;
    cout << "Min:" << integer_tracker.get_min() << endl;
    cout << "Mean:" << integer_tracker.get_mean() << endl;
    cout << "Mode:" << integer_tracker.get_mode() << endl;

    integer_tracker.track(-10000);
    integer_tracker.track(32000);
    integer_tracker.track(-10);
    integer_tracker.track(-10);
    cout << "Max:" << integer_tracker.get_max() << endl;
    cout << "Min:" << integer_tracker.get_min() << endl;
    cout << "Mean:" << integer_tracker.get_mean() << endl;
    cout << "Mode:" << integer_tracker.get_mode() << endl;

}

