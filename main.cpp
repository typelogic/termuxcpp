#include <chrono>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <thread>

using namespace std;

mutex mtx;
condition_variable cv;
bool flag = false;

void delay(int n) { 
  this_thread::sleep_for(
    chrono::seconds(n)
  ); 
}

void fn() {
  delay(3);
  cv.notify_one();
  delay(9);
  flag = true;
  cv.notify_one();
}

int main(int argc, char *argv[]) {
  int a = 5;
  int b = 9;
  int m = a++ + b;
  cout << m << a << endl;

  thread t(fn);
  t.detach();
  // t.join();

  unique_lock<mutex> lck(mtx);
  cv.wait_for(lck, chrono::seconds(20), [&]() {
    cout << "[" << flag << "]\n";
    return flag;
  });

  cout << "\nBYE\n";
  return flag;
}
