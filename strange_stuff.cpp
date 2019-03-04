#include <Windows.h>
#include <fstream>
#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
#include <cmath>

class Timer
{
public:
	void start()
	{
		m_StartTime = std::chrono::system_clock::now();
		m_bRunning = true;
	}

	void stop()
	{
		m_EndTime = std::chrono::system_clock::now();
		m_bRunning = false;
	}

	double elapsedMilliseconds()
	{
		std::chrono::time_point<std::chrono::system_clock> endTime;

		if (m_bRunning)
		{
			endTime = std::chrono::system_clock::now();
		}
		else
		{
			endTime = m_EndTime;
		}

		return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count();
	}

	double elapsedSeconds()
	{
		return elapsedMilliseconds() / 1000.0;
	}

private:
	std::chrono::time_point<std::chrono::system_clock> m_StartTime;
	std::chrono::time_point<std::chrono::system_clock> m_EndTime;
	bool                                               m_bRunning = false;
};


using namespace std;

auto l_pow = [](double num, double p, double& res) { res = 1; for (int i = 0; i < p; ++i){ for (int j = 0; j < 10000000 * i; ++j){ if (j == 100 * i - 1){ res *= num; } } } };

int main(){
	Timer timer1;
	system("echo %NUMBER_OF_PROCESSORS% > D:\\processors_file.bin");
	ifstream ifs("D:\\processors_file.bin");
	int cores;
	double res1;
	double res2;
	double res3;
	ifs >> cores;
	cout << cores << endl;

	timer1.start();
	/*thread thr1(l_pow, 1323123, 13, ref(res1));
	thread thr2(l_pow, 1323123, 37, ref(res2));
	thread thr3(l_pow, 1323123, 19, ref(res3));
	thr1.join();
	thr2.join();
	thr3.join();*/
	l_pow(1323123, 13, ref(res1));
	l_pow(1323123, 13, ref(res2));
	l_pow(1323123, 13, ref(res3));
	
	timer1.stop();



	//cout << res1 << endl;
	//cout << res2 << endl;
	//cout << res3 << endl;

	cout << "Time: " << timer1.elapsedMilliseconds() << endl;

	return 0;
}
