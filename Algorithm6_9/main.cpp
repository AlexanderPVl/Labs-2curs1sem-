#include "thread_queue.h"

#define JOIN_THREADS(t1, t2, t3, t4, t5) t1.join(), t2.join(), t3.join(), t4.join(), t5.join()

int update() {
	int state = -1;
	thread t1(print_number, 1, 50, &state);
	thread t2(print_number, 2, 50, &state);
	thread t3(print_number, 3, 50, &state);
	thread t4(print_number, 4, 50, &state);
	thread t5(print_number, 5, 50, &state);
	while (1) {
		this_thread::sleep_for(chrono::milliseconds(1000));
		cout << endl;
		state += 1;
		state %= 5;
	}
	JOIN_THREADS(t1, t2, t3, t4, t5);
}

int main() {
#if NUM_OF_PROC < 6
	cout << "Programm can not be terminated. Not enough processors." << endl;
	return -1;
#endif

	thread upd(update);
	upd.join();

	return 0;
}
