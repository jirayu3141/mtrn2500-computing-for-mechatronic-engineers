/* Sample code for constructing a number of data structures
using the STL containers as well as timing, assert and sleep.
*/
#include <iostream>
#include <conio.h>
#include <vector>
#include <deque>  // std::queue + std::priority_queue
#include <list>
#include <stack>
#include <queue>
#include <set>  // std::set + std::multiset
#include <map> // std::map + std::multimap
#include <cassert>
#include <ctime>
#include <windows.h> // For sleep


using namespace std;

int main ()
{
  
  // constructors used in the same order as described above:
  vector<int> first;                                // empty vector of ints
  vector<int> second (4,100);                       // four ints with value 100
  vector<int> third (second.begin(),second.end());  // iterating through second
  vector<int> fourth (third);                       // a copy of third

  time_t start_time = time(NULL);
  clock_t start_time_clock = clock();

  // the iterator constructor can also be used to construct from arrays:
  int myints[] = {16,2,77,29};

  vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

  // Use an assert to throw an exception and halt execution if false
  assert(first.empty());
  
  if (first.empty())
	  cout << "The first is empty " << endl;
  else
	  cout << "The first is not empty" << endl;


  cout << "The contents of second are:";
  for (vector<int>::iterator it = second.begin(); it != second.end(); ++it)
    cout << ' ' << *it;
  cout << '\n';

  cout << "The contents of fifth are:";
  for (vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
    cout << ' ' << *it;
  cout << '\n';
  
  // Try other containers: deque
  deque<int> sixth;
  int i = 1;
  for (; i < 5; i++)
  {
	  sixth.push_front(i);
  }
  for (; i < 10; i++)
  {
	  sixth.push_back(i);
  }
  cout << "Deque" << endl << "The contents of sixth are:";
  for (deque<int>::iterator it = sixth.begin(); it != sixth.end(); ++it)
	  cout << ' ' << *it;
  cout << '\n';

  // List
  list<int> seventh;
  i = 1;
  for (; i < 5; i++)
  {
	  seventh.push_front(i);
  }
  for (; i < 10; i++)
  {
	  seventh.push_back(i);
  }
  list<int>::iterator it = seventh.begin();
  cout << "Lists" << endl << "The contents of seventh before insertion are:";
  for (it = seventh.begin(); it != seventh.end(); ++it)
	  cout << ' ' << *it;
  cout << '\n';
  it = seventh.end();
  
  seventh.insert(it, 100);

  cout << "Lists" << endl << "The contents of seventh after insertion are:";
  for (it = seventh.begin(); it != seventh.end(); ++it)
	  cout << ' ' << *it;
  cout << '\n';


  // Stack
  stack<int> eighth;
  i = 1;
  for (; i < 5; i++)
  {
	  eighth.push(i);
  }
  cout << "The contents of stack eighth are:";
  while (!eighth.empty()) {
	  cout << ' ' << eighth.top();
	  eighth.pop();
  }
  cout << '\n';
  
  // Queue
  queue<int> ninth;
  i = 1;
  for (; i < 5; i++)
  {
	  ninth.push(i);
  }
  ninth.pop();
  ninth.push(5);
  ninth.push(6);
  ninth.pop();
  cout << "The contents of queue ninth are:";
  while (!ninth.empty()) {
	  cout << ' ' << ninth.front();
	  ninth.pop();
  }
  cout << '\n';


  
  // Set
  set<int> tenth;
  set<int>::iterator itset;
  pair<set<int>::iterator, bool> ret;

  // set some initial values:
  for (int i = 1; i <= 5; ++i) tenth.insert(i * 10);    // set: 10 20 30 40 50

  ret = tenth.insert(20);               // no new element inserted



  if (ret.second == false) itset = ret.first;  // "it" now points to element 20

  tenth.insert(itset, 25);                 // max efficiency inserting
  tenth.insert(itset, 24);                 // max efficiency inserting, 24 goes before next element from the one pointed to by it (20)
  tenth.insert(itset, 26);                 // no max efficiency inserting, 26 goes after 25, which is not the element pointed to by it (20)

  int mynewints[] = { 1,10,20 };              // 10 already in set, not inserted
  tenth.insert(mynewints, mynewints + 3); // ??

  cout << endl << "myset contains:";
  for (itset = tenth.begin(); itset != tenth.end(); ++itset)
	  cout << ' ' << *itset;
  cout << '\n';


  
// Map: example from http://www.cplusplus.com/reference/map/map/insert/
  map<char, int> eleventh;

  // first insert function version (single parameter):
  eleventh.insert(pair<char, int>('a', 100));
  eleventh.insert(pair<char, int>('z', 200));
  eleventh.insert(pair<char, int>('x', 500));



  
  pair<map<char, int>::iterator, bool> ret_value;
  ret_value = eleventh.insert(pair<char, int>('z', 500));
  if (ret_value.second == false) {
	  cout << "element 'z' already existed";
	  cout << " with a value of " << (ret_value.first)->second << '\n';
  }

  map<char, int>::iterator it2 = eleventh.begin();
 
  // second insert function version (with hint position):
  eleventh.insert(it2, pair<char, int>('b', 300));  // max efficiency inserting
  eleventh.insert(it2, pair<char, int>('c', 400));  // no max efficiency inserting

												 // third insert function version (range insertion):
  map<char, int> anothermap;
  anothermap.insert(eleventh.begin(), eleventh.find('c'));

  // showing contents:
  cout << "eleventh contains:\n";
  for (it2 = eleventh.begin(); it2 != eleventh.end(); ++it2)
	  cout << it2->first << " => " << it2->second << '\n';


  cout << "anothermap contains:\n";
  for (it2 = anothermap.begin(); it2 != anothermap.end(); ++it2)
	  cout << it2->first << " => " << it2->second << '\n';
  
  // Priority queue, first argument are the 
  priority_queue<int> twelfth(myints, myints+4);  // Inserts everything from address of myints to address of myints+4
  cout << endl << "priority queue contains items in decreasing priority:";

  twelfth.push(100);
  twelfth.push(101);
  
  while (!twelfth.empty()) {
	  cout << ' ' << twelfth.top();
	  twelfth.pop();
  }
  cout << '\n';

  //Sleep(2000); //Units: milliseconds
  time_t end_time = time(NULL);
  double seconds = difftime(end_time, start_time);
  cout << "duration of this program in seconds is: " << seconds << endl;
  
  clock_t end_time_clock = clock();
  clock_t duration_clock = end_time_clock - start_time_clock;
  cout << "duration of this program in seconds by CPU clock is: " << ((float)duration_clock / CLOCKS_PER_SEC) << endl;
  
  _getch();

  return 0;
}