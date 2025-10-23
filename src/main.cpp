#include <iostream>
#include <cmath>
#include <random>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <thread>
#include <chrono>


struct Option{
    double S_0, K, T, r, sigma;
    std::string type; // 'call'/'put'
};


std::pair<double, double> simulate_S_T(double S_0, double r, double sigma, double T, std::mt19937& gen){
    std::normal_distribution<> N(0.0, 1.0); // normal distribution with mean=0, std_dev=1

    double Z = N(gen); // generate random number from normal distribution

    double S_T1 = S_0 * std::exp((r - 0.5*sigma*sigma) * T + sigma*std::sqrt(T)*Z); // generating random path S_T
    double S_T2 = S_0 * std::exp((r - 0.5*sigma*sigma) * T + sigma*std::sqrt(T)*-Z); // generating random negative path S_T

    return {S_T1, S_T2};
}


void worker(int num_sim_thread, const Option& option, double& result){
    // initalize simulation arguments
    std::random_device rd;
    std::mt19937 gen(rd());

    double total_payoff = 0.0;

    for (int i=0; i<num_sim_thread; i++){
        std::pair<double, double> S_T = simulate_S_T(option.S_0, option.r, option.sigma, option.T, gen); // generate possible future price
        double pay_off1;
        double pay_off2;
        if (option.type == "call"){
            pay_off1 = std::max(S_T.first - option.K, 0.0); // payoff is max of predicted future price and strike price
            pay_off2 = std::max(S_T.second - option.K, 0.0); // payoff is max of predicted future price and strike price
        }
        else{
            pay_off1 = std::max(-S_T.first + option.K, 0.0); // payoff is max of predicted future price and strike price
            pay_off2 = std::max(-S_T.second + option.K, 0.0); // payoff is max of predicted future price and strike price
        }
        
        double pay_off = (pay_off1+pay_off2)/2.0;
        total_payoff += pay_off;

    }
    result = total_payoff;
}


class MonteCarloPricer {
    public:
        double run_simulation(const Option& option, int num_sim){
            
            unsigned int num_threads = std::thread::hardware_concurrency();
            std::cout<<"Using "<<num_threads<<" threads"<<std::endl;
            std::cout<<"---------------------------------"<<std::endl;

            int num_sim_per_thread = (num_sim/2)/num_threads;

            std::vector<std::thread> threads;
            std::vector<double> results(num_threads);

            for(int i=0; i<num_threads; ++i){
                threads.emplace_back(worker, num_sim_per_thread, std::cref(option), std::ref(results[i]));
            }

            for(auto& t: threads){
                t.join(); // join threads
            }
            
            double total_payoff = 0.0;

            for (double res: results){
                total_payoff+=res;
            }

            double avg_payoff = total_payoff/(num_sim_per_thread*num_threads); // expected payoff
            double option_price = avg_payoff * std::exp(-option.r*option.T); // discount expected payoff to get present value

            return option_price;
        }
};


int main(){
    // simulation parameter
    auto start = std::chrono::high_resolution_clock::now(); // start time
    int num_sim = 5000;
    std::cout<<"Starting simulation"<<std::endl;
    std::cout<<"---------------------------------"<<std::endl;

    // initalize simulation arguments
    Option my_option = {100.0, 105.0, 1.0, 0.05, 0.2, "put"};
    MonteCarloPricer pricer;

    double option_price = pricer.run_simulation(my_option, 100000); // discount expected payoff to get present value

    auto end = std::chrono::high_resolution_clock::now(); // start time

    std::chrono::duration<double> duration = end-start;

    std::cout<<"Finished simulation"<<std::endl;
    std::cout<<"---------------------------------"<<std::endl;
    std::cout<<"Time elapsed: " <<duration.count()<<std::endl;
    std::cout<<"---------------------------------"<<std::endl;
    std::cout<<"European Call Option Price: " <<option_price<<std::endl;
    std::cout<<"---------------------------------"<<std::endl;
}