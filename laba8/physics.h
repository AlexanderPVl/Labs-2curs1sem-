#include "algorithms.h"

#include <chrono>

vectorn force0(double, vectorn&){ return vectorn(0, 3); }

class force{
public:
	typedef vectorn(*f_type)(double, vectorn&);
	force() { f = force0; }
	force(f_type func){ f = func; }
	vectorn operator ()(double t, vectorn vec){ return f(t, vec); }
	f_type f;
private:
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

class particle{
public:
	particle(){}
	particle(vectorn pos, vectorn vel, double mass_, initializer_list<force> forces_) : flist(forces_), position(pos), velocity(vel), mass(mass_) {}
	void move(pair_s<vectorn, double>* part_info, int particles_cnt, double dtime, double* time, double* G) { // pair_s: <position, mass>
		vectorn dvel(0, 3);
		for (int i = 0; i < flist.size; ++i){
			dvel += dtime / mass * flist[i](*time, position);
		}

		for (int i = 0; i < particles_cnt; ++i){
			dvel + dtime * (*G) * part_info[i].result * position.dir(part_info[i].argument);
		}
		velocity += dvel;
		position += (dtime * velocity);
	}
	void move(list_s<particle>* particles, double dtime, double* time, double* G) {
		vectorn dvel(0, 3);
		for (int i = 0; i < flist.size; ++i){
			dvel += dtime / mass * flist[i](*time, position);
		}
		int particles_cnt = particles->size;
		for (int i = 0; i < particles_cnt; ++i){
			dvel += dtime * (*G) * mass * (*particles)[i].mass * position.dir((*particles)[i].position);
		}
		velocity += dvel;
		position += (dtime * velocity);
		velocity.prints("velocity");
		position.prints("current position");
	}
	vectorn get_position(){ return position; }
	vectorn get_velocity(){ return velocity; }
private:
	list_s<force> flist;
	vectorn position;
	vectorn velocity;
	double mass;
};

class particle_system{
public:
	typedef vectorn(*force_type)(double, vectorn&);
	particle_system(initializer_list<particle> pcl_list, initializer_list<force_type> forces_list, double t0) : particles(pcl_list), forces(forces_list){
		time = new double;
		G = new double;
		*time = t0;
		*G = 6.674301515151515151515 * 10E-11;
	}
	particle_system(list_s<particle> pcl_list, list_s<force_type> forces_list, double t0) : particles(pcl_list), forces(forces_list){
		time = new double;
		G = new double;
		*time = t0;
		*G = 6.674301515151515151515 * 10E-11;
	}
	void calculate(double limit_time, double step){
		while (*time < limit_time){
			cout << "time: " << *time << endl;
			for (int i = 0; i < particles.size; ++i){
				particles[i].move(&particles, step, time, G);
			}
			*time += step;
		}
	}
	double* get_time() const { return time; }
	double* get_G() const { return G; }
private:
	double* time;
	double* G;
	list_s<particle> particles;
	list_s<force_type> forces;
};