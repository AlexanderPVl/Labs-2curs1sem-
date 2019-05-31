#include "algorithms.h"

template<class Func>
class force{
public:
private:
	vectorn vector;
};

template<class F1, class F2, class F3>
class particle{
public:
	particle(vectorn pos, vectorn vel, double mass_, func_tuple<F1, F2, F3> *forces_) : forces(forces_), position(list, size_) {}
	pair apply_forces(pair_s<vectorn, double>* part_info, int part_cnt, double dtime) { // pair_s: <position, mass>
		vectorn dvel(0, 3);
		dvel += *forces->get_1(position, *time) / m * dtime;
		dvel += *forces->get_2(position, *time) / m * dtime;
		dvel += *forces->get_3(position, *time) / m * dtime;
		for (int i = 0; i < forces_cnt; ++i){
			dvel += (*G) * mass * part_info[i].result * position.dist(part_info[i].argument) / m * dtime;
		}
	position += dvel * dtime;
	}
private:
	func_tuple<F1, F2, F3> *forces;
	vectorn position;
	vectorn velisity;
	double mass;
	double *time;
	double* G;
};