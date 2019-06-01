#include "algorithms.h"

#include <chrono>

template<class Func>
class force{
public:
private:
	vectorn vector;
};
/*
template<class F1, class F2, class F3>
class particle{
public:
	typedef vectorn(*force)(double, initializer_list<vectorn>);
	particle(vectorn pos, vectorn vel, double mass_, func_tuple<F1, F2, F3> *forces_, double* G_, double *time_) : forces(forces_), position(pos), velocity(vel), G(G_), time(time_) {}
	void apply_forces(pair_s<vectorn, double>* part_info, int particles_cnt, double dtime) { // pair_s: <position, mass>
		vectorn dvel(0, 3);
		forces->get_1()(position, *time).prints("first");
		position.prints("position");
		dvel + dtime / mass * forces->get_1()(position, *time);
		dvel + dtime / mass * forces->get_2()(position, *time);
		dvel + dtime / mass * forces->get_3()(position, *time);
		dvel.prints("inner");
		for (int i = 0; i < particles_cnt; ++i){
			dvel + dtime * (*G) * part_info[i].result * position.dir(part_info[i].argument);
		}
		position + dtime * dvel;
	}
	vectorn get_position(){ return position; }
private:
	func_tuple<F1, F2, F3> *forces;
	vectorn position;
	vectorn velocity;
	double mass;
	double *time;
	double* G;
};
*/

template<class Force>
class particle{
public:
	particle(vectorn pos, vectorn vel, double mass_, initializer_list<Force> forces_, double* G_, double *time_) : flist(forces_), position(pos), velocity(vel), G(G_), time(time_), mass(mass_) {}
	void apply_forces(pair_s<vectorn, double>* part_info, int particles_cnt, double dtime) { // pair_s: <position, mass>
		vectorn dvel(0, 3);
		dvel += dtime / mass * flist[0](*time, position);
		dvel += dtime / mass * flist[1](*time, position);
		dvel += dtime / mass * flist[2](*time, position);
		for (int i = 0; i < particles_cnt; ++i){
			dvel + dtime * (*G) * part_info[i].result * position.dir(part_info[i].argument);
		}
		velocity += dvel;
		position += (dtime * velocity);
	}
	vectorn get_position(){ return position; }
	vectorn get_velocity(){ return velocity; }
private:
	list_s<Force> flist;
	vectorn position;
	vectorn velocity;
	double mass;
	double *time;
	double* G;
};
