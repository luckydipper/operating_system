#include "scheduler.h"
#include <iostream>
using namespace std;

Scheduler::Scheduler() : front(nullptr), back(nullptr), length(0) { cout << "queue made" << endl; };
Scheduler::~Scheduler() { cout << "queue deleted" << endl; }

