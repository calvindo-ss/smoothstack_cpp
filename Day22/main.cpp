#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>
#include <queue>

#include "json.hpp"

// This simulation is not the best experience on my laptop lol
// using int numBodies[] = {10, 20, 50, 100, 200, 500, 1000, 2000}; takes a hot minute to run

// Gravitational constant
double G = 6.673e-11;
// timestep 
double timestep = 0.001; 
//small mass
double initial_mass = 1e32; // have to pump mass up to show any change in position if low number of bodies or k
// num timesteps
double k = 100; // k needs to be 1000+ to show any decent change in position if mass is low

nlohmann::ordered_json j;

struct R{
    double x;
    double y;

    R(): x(0), y(0){}
    R(double x_input, double y_input): x(x_input), y(y_input){}

    bool operator==(const R& other){
        return x == other.x && y == other.y;
    }
};

struct V{
    double x;
    double y;

    V(): x(0), y(0){}
    V(double x_input, double y_input): x(x_input), y(y_input){}
};

struct F{
    double x;
    double y;

    F(): x(0), y(0){}
    F(double x_input, double y_input): x(x_input), y(y_input){}

    F(const F& other){
        x = other.x; 
        y = other.y;
    }

    F& operator=(const F& other){
        if(this == &other){     
            return *this;       
        }

        x = other.x;
        y = other.y;
        
        return *this;
    }

    F operator*(const int& num){
        F temp;
        temp.x *= num;
        temp.y *= num;

        return temp;
    }

    F operator+=(const F& other){
        x += other.x;
        y += other.y;

        return *this;
    }

    ~F(){}
};

struct A{
    double x;
    double y;

    A(): x(0), y(0){}
    A(double x_input, double y_input): x(x_input), y(y_input){}
};

struct Body {
    int ind; // index of body
    double mass;
    R position;
    V velocity;
    F* forceVector; // computed {f-i1,fi2...fiN}
    F totalForce; // computed by adding forceVector
    A acceleration;  // computed from f = ma
    int N;

    Body(): ind(0), mass(0), position(R()), velocity(V()), forceVector(nullptr), totalForce(F()), acceleration(A()), N(0){}

    Body(int ind_input, double mass_input, R pos, V vel, F total_force, A accel, int n):
        ind(ind_input), 
        mass(mass_input), 
        position(pos), 
        velocity(vel), 
        totalForce(total_force),
        acceleration(accel),
        N(n){
            forceVector = new F[N];
        }

    Body(const Body& other){
        ind = other.ind;
        mass = other.mass;
        position = other.position;
        velocity = other.velocity;
        N = other.N;
        forceVector = new F[N];
        for(int i=0; i<N; i++){
            forceVector[i] = other.forceVector[i];
        }
        totalForce = other.totalForce;
        acceleration = other.acceleration;
    }

    Body& operator=(const Body& other){
        if(this == &other){
            return *this;
        }

        ind = other.ind;
        mass = other.mass;
        position = other.position;
        velocity = other.velocity;
        N = other.N;
        forceVector = new F[N];
        for(int i=0; i<N; i++){
            forceVector[i] = other.forceVector[i];
        }
        totalForce = other.totalForce;
        acceleration = other.acceleration;

        return *this;
    }

    ~Body(){
            delete[] forceVector;
    }
};

class Simulation{
private:
    double sim_initial_mass; // initial mass
    double sim_k; // k
    bool write = true; // default true
    int numThreads;

    void calc_forceVector(Body* body, int bod, int N){
        // loop through other bodies to update forceVector against all bodies
        for(int other_bodies = 0; other_bodies < N; other_bodies++){
            
            if(body[bod].forceVector[other_bodies].x == 0 && body[bod].forceVector[other_bodies].y == 0){ 
                body[bod].forceVector[other_bodies] = [](double mass1, double mass2, R r1, R r2){ // updates forceVector
                if(r1 == r2){
                    return F();
                }

                // lambda calculate distance between 2 bodies
                double distance = [r1, r2]{return std::sqrt(std::pow(r1.x - r2.x, 2) + std::pow(r1.y - r2.y, 2));}();

                // lambda calculate force between 2 bodies
                double force = [mass1, mass2, distance]{return -1 * G * mass1 * mass2 / (distance * distance);}();

                // calculate x, y force values
                double r = std::atan(std::abs(r1.y - r2.y) / std::abs(r1.x - r2.x));
                F temp_force = F(std::cos(r) * force, std::sin(r) * force);

                if(r1.x < r2.x){
                    temp_force.x = std::abs(temp_force.x);
                }

                if(r1.y < r2.y){
                    temp_force.y = std::abs(temp_force.y);
                }

                return temp_force;
            }(body[bod].mass, body[other_bodies].mass, body[bod].position, body[other_bodies].position);

            // set opposing half pair
            body[other_bodies].forceVector[bod] = body[bod].forceVector[other_bodies] * -1;
            }

        }    
    }

    void update_body(Body &b, int N){
                //Update the force exerted on a body by number of bodies(N)
                [&]{
                    for(int i = 0; i < N; i++){
                        b.totalForce += b.forceVector[i];
                    }
                }();

                //Update the acceleration on a body
                [&b]{
                    b.acceleration.x = b.totalForce.x / b.mass;
                    b.acceleration.y = b.totalForce.y / b.mass;
                }();

                //Update velocity of a body
                [&b](){
                    b.velocity.x += b.acceleration.x * timestep;
                    b.velocity.y += b.acceleration.y * timestep;
                }();

                //Update position of a body
                [&b]{
                    b.position.x += timestep * b.velocity.x;
                    b.position.y += timestep * b.velocity.y;
                }();
    }

public:
    Simulation(double local_initial_mass, double local_k, int numThreads): 
        sim_initial_mass(local_initial_mass), sim_k(local_k), numThreads(numThreads){}


    void set_write(bool flag){
        write = flag;
    }

    void run(int& N){ // N is number of bodies, M is number of cores
        std::cout << "Simulating " << N << " n-bodies" << std::endl;
        
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        Body* body = new Body[N];
        
        for( int i = 0; i < N; i++){
            body[i] = Body(i, initial_mass, R(N * i, N* i * 2), V(), F(), A(), N);   // x = N*i, y = N*i*2 
        }                
        
        // loop through timestep(k)
        for(int t_step = 0; t_step < k; t_step++){
            std::vector<std::thread> threads;

            // loop through bodies to update forceVector
            // this updates forceVector on all bodies before position is updated, 
            // preventing inconsistent data between bodies
            // no need for mutex to lock data
            for(int bod = 0; bod < N; bod++){
                if(threads.size() == numThreads){       // if number of threads hits max threads,
                    threads.front().join();             // join first thread
                    threads.erase(threads.begin());     // delete first element in threads vec
                }   

                std::thread t(&Simulation::calc_forceVector, this, body, bod, N);
                threads.push_back(std::move(t));
            }

            for(auto& t:threads){
                t.join();
            }
            threads.clear();
            
            // loop through bodies to update all other variables
            // updates position, etc AFTER all bodies' forceVector is updated
            for(int bod = 0; bod < N; bod++){
                Body& b = body[bod];

                std::thread t(&Simulation::update_body, this, std::ref(b), N);  // Passing Arguments rvalue to non-const ref fail
                threads.push_back(std::move(t));                                // need to use std::ref()
            }

            for(auto& t:threads){
                t.join();
            }
            threads.clear();
        }

        // write body data to json object
        if(write){
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            double time = std::chrono::duration<double> (end - begin).count();
            j[std::to_string(numThreads)][std::to_string(N)]["Interactions/s"] = k * N * N / time;
            j[std::to_string(numThreads)][std::to_string(N)]["Elapsed_time"] = time;
            j[std::to_string(numThreads)][std::to_string(N)]["Total_number_of_calculations"] = k * N * N;
        }

        delete[] body;
    }
};

int main(void){
    //int numBodies[] = {10, 11, 12, 13, 14, 15, 16, 17}; // use for testing custom number of bodies
    //int numBodies[] = {1000, 1001, 1002, 1003, 1004, 1005, 1006, 1007}; // use for testing custom number of bodies
    int numBodies[] = {10, 20, 50, 100, 200, 500, 1000, 2000};
    int numThreads = 8;

    Simulation s(initial_mass, k, numThreads);

    for(int i = 0; i < sizeof(numBodies)/sizeof(numBodies[0]); i++){
        s.run(numBodies[i]);
    }

    // writing to json file
    std::ofstream ofs("data.json", std::ios::app);
    ofs << std::setw(4) << j << std::endl;
    ofs.close();
}
