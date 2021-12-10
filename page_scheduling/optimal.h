#pragma once
#include <deque>
using namespace std;

int OptimalNumPagefault(const deque<int>& reference_string, const int& num_frame);
int ChooseExtractIndex_(const deque<int>& reference_string, const deque<int>& frame, int index);
int FindFutureOffset(const deque<int>& feild, int start_index, const int finding_elem);
