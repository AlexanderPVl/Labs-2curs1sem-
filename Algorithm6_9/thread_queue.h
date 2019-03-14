#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

mutex gl_mute;

#ifndef NUM_OF_PROC
	#define NUM_OF_PROC std::thread::hardware_concurrency()
#endif

#if defined(_WIN64) || defined(_WIN32)
	#include <Windows.h>
	double get_system_time() {
		SYSTEMTIME st;
		GetLocalTime(&st);
		return	(double)st.wHour * 3600.0 +
				(double)st.wMinute * 60.0 +
				(double)st.wSecond +
				(double)st.wMilliseconds / 1000.0;
	}
#endif



template<class Func, class ... Args>
double func_run_time(Func *f, Args ... args){
	double start_time = get_system_time(), end_time;
	f(args ...);
	return get_system_time() - start_time;
}

int print_number(int n, signed int delay, int *state) {
	n -= 1;
	int i = 0;
	while (1){
		if (*state != n) this_thread::yield();
		else {
			cout << n + 1 << " ";
			this_thread::sleep_for(chrono::milliseconds(delay));
		}
	}
	cout << endl;
	return 0;
}
