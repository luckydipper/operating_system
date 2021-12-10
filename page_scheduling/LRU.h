#pragma
#include <deque>
using namespace std;

int LruNumPagefault(const deque<int>& reference_string, const int& num_frame);
int FindBeforeOffset(const deque<int>& feild, int end_index, const int finding_elem);

bool PageCaching(deque<int>& frame, int demend_page_index);
int ChooseExtractIndex(const deque<int>& reference_string, const deque<int>& frame,int index);
