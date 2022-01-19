#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <fstream>
#include "json.hpp"

// This simulation is not the best experience on my laptop lol
// using int numBodies[] = {10, 20, 50, 100, 200, 500, 1000, 2000}; takes a hot minute to run

// N bodies 
int N = 5; 
// Gravitational constant
double G = 6.673e-11;
// timestep 
double timestep = 0.001; 
//small mass
double initial_mass = 1e32; // have to pump mass up to show any change in position if low number of bodies or k
// num timesteps
double k = 100; // k needs to be 1000+ to show any decent change in position if mass is low

struct R{
    double x;
    double y;

    R(): x(0), y(0){}
    R(double x_input, double y_input): x(x_input), y(y_input){}
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
        if(this == &other){     // I spent several hours debugging to realize I put != instead of ==
            return *this;       // many hours wasted over a dumb mmistake
        }

        x = other.x;
        y = other.y;
        
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

    Body(): ind(0), mass(0), position(R()), velocity(V()), forceVector(nullptr), totalForce(F()), acceleration(A()){}

    Body(int ind_input, double mass_input, R pos, V vel, F total_force, A accel):
        ind(ind_input), 
        mass(mass_input), 
        position(pos), 
        velocity(vel), 
        totalForce(total_force),
        acceleration(accel){
            forceVector = new F[N];
        }

    Body(const Body& other){
        ind = other.ind;
        mass = other.mass;
        position = other.position;
        velocity = other.velocity;
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
        int numBodies[8] = {10, 20, 50, 100, 200, 500, 1000, 2000};
        //int numBodies[2] = {10, 20}; // use for testing custom number of bodies
        double sim_initial_mass; // initial mass
        double sim_k; // k
        bool verbose = false; // default false

    public:
        Simulation(double local_initial_mass, double local_k): sim_initial_mass(local_initial_mass), sim_k(local_k){}

        void set_verbose(bool flag){
            verbose = flag;
        }

        void run(){
            for(int n = 0; n < sizeof(numBodies)/sizeof(numBodies[0]); n++){
                N = numBodies[n];

                // initialize N bodies
                Body* body = new Body[N];
                
                for( int i = 0; i < N; i++){
                    body[i] = Body(i, initial_mass, R(N * i, N* i * 2), V(), F(), A());   // x = N*i, y = N*i*2 
                }                                                                           // I need to change this later

                std::vector<Body> body_v;
                std::vector<int> interactions_v;
                
                // loop through timestep(k)
                for(int t_step = 0; t_step < k; t_step++){
                    if(verbose){
                        std::cout << "Step: " << t_step << std::endl;
                    }

                    // loop through bodies to update forceVector
                    for(int bod = 0; bod < N; bod++){
                        if(verbose){
                            [bod](const Body& b){
                                std::cout << "body " << bod << 
                                        ": Position (" << b.position.x << ", " << b.position.y << 
                                        "), Force (" << b.totalForce.x << ", " << b.totalForce.y <<
                                        "), Vel (" << b.velocity.x << ", " << b.velocity.y << 
                                        "), Acc (" << b.acceleration.x << ", " << b.acceleration.y << ")" << std::endl;
                            }(body[bod]);
                        }
                        // push to body vector
                        body_v.push_back(body[bod]);
                        interactions_v.push_back(k * N * N / timestep);
                        
                        // loop through other bodies to update forceVector against all bodies
                        for(int other_bodies = 0; other_bodies < N; other_bodies++){
                            body[bod].forceVector[other_bodies] = [](double mass1, double mass2, R r1, R r2){ // updates forceVector
                                if(r1.x == r2.x && r1.y == r2.y){
                                    return F();
                                }
                                // calculate distance between 2 bodies
                                double distance = [r1, r2]{return std::sqrt(std::pow(r1.x - r2.x, 2) + std::pow(r1.y - r2.y, 2));}();

                                // calculate force between 2 bodies
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
                        }                
                    }
                    
                    // loop through bodies to update all other variables
                    for(int bod = 0; bod < N; bod++){
                        Body& b = body[bod];

                        //Update the force exerted on a body by number of bodies(N)
                        [&b]{
                            for(int i = 0; i < N; i++){
                                b.totalForce.x += b.forceVector[i].x;
                                b.totalForce.y += b.forceVector[i].y;
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
                }
                // write body data to json
                write_data(body_v, N, interactions_v);

                std::cout << "Interactions/sec: " << [] {return k * N * N / timestep;}() << std::endl;

                delete [] body;
            }
        }

        void write_data(std::vector<Body>& body, int& numBody, std::vector<int>& interactions){
            std::string filename = std::to_string(numBody)+"_bodies.json";
            std::ofstream ofs(filename);

            for(int i = 0; i < body.size(); i++){
                nlohmann::ordered_json j = {
                    
                    {"N", body[i].ind},
                    {"Interactions/s", interactions[i]}
                };
                ofs << j << std::endl;
            }
            ofs.close();
        }
};

int main(void){
    Simulation s(initial_mass, k);
    s.set_verbose(false); // set to false to turn off console printing
    s.run();
}