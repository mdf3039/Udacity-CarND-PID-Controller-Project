#include "PID.h"
#include <vector>
#include<cmath>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp0, double Ki0, double Kd0) {
    Kp = Kp0;
    Ki = Ki0;
    Kd = Kd0;
    p_error = 1.0;
    i_error = 1.0;
    d_error = 1.0;
    previous_cte = 0;
    sum_previous_ctes = 0;
    first_obs = true;
    steer_angle = 0;

}

void PID::UpdateError(double cte, double delta_distance) {
    //if it is the first observation, based on whether the CTE is
    //positive or negative, set steer angle to -1 or 1.
    if (first_obs){
        if (cte>0){
            steer_angle = -1;
        }
        else if (cte<0){
            steer_angle = 1;
        }
        else if (cte==0){
            steer_angle = 0;
        }
        first_obs = false;
        //save the y_distance,delta_distance_vector, cte, and full_cte
        y_distance.push_back(delta_distance*sin(steer_angle));
        delta_distance_vector.push_back(delta_distance);
        cte_vector.push_back(cte);
        full_cte_vector.push_back(cte);
        //return from the call
        return;
    }
    //If it is not the first observation, append to the full_cte_vector
    full_cte_vector.push_back(cte + y_distance.back());
    //append to the delta_distance_vector
    delta_distance_vector.push_back(delta_distance);
    //find the total error and steering angle, given the taus,fCTEs

    //based on the cte and taus, obtain the steering angle
    double steer_angle = SteeringAngle(Kp,Ki,Kd);
    //based on the steering angle, find the expected value of the next cte
    double exp_cte = cte + delta_distance*sin(steer_angle);
    //put the error values and PID coefficient values into a
    //vector for easier use
    std::vector<double> error_vector;
    error_vector.push_back(p_error);
    error_vector.push_back(i_error);
    error_vector.push_back(d_error);
    std::vector<double> pid_vector;
    pid_vector.push_back(Kp);
    pid_vector.push_back(Ki);
    pid_vector.push_back(Kd);
    for (int i = 0; i < pid_vector.size(); ++i) {
        //do comparisons of the exp_cte with the altered_cte.
        // if the altered is better, use the altered steering angle.
        pid_vector[i] += error_vector[i];
        double alt_exp_cte = TotalError(cte,delta_distance,pid_vector);
        if (alt_exp_cte<exp_cte){
            //If the altered error is smaller than the expected error, then
            //the change in tau is appropriate.
            //Change the exp_cte to the alt_exp_cte
            exp_cte = alt_exp_cte;
            //Keep changing the tau parameter by the error amount until it
            //can't be changed anymore.
            bool while_boolean = true;
            while (while_boolean){
                //after adding onto the pid, if the altered error is smaller
                //than the exp_cte, keep going
                pid_vector[i] += error_vector[i];
                double alt_exp_cte = TotalError(cte,delta_distance,pid_vector);
                if (alt_exp_cte < exp_cte){
                    //Change the exp_cte to the alt_exp_cte
                    exp_cte = alt_exp_cte;
                }
                else{
                    pid_vector[i] -= error_vector[i];
                    while_boolean = false;
                }

            }

        }



}

std::vector<double> PID::TotalErrorAndSteerAngle(double taup, double taui, double taud){
    //Using the given taus, iterate through the fCTE to find the total error and
    //new steering angle
    //create a vector that holds all of the training ctes to use
    //with the integrating and derivative
    std::vector<double> cte_vector_train;
    //the first cte in the cte_vector_train is the first cte
    cte_vector_train.push_back(full_cte_vector[0]);
    //create a double total_error that saves the accounted error
    double total_error = full_cte_vector[0];
    //create a double that saves the steering angle
    double steer_angle_train;
    for (int i = 1; i < full_cte_vector.size(); ++i){
        if (i!=1){
            steer_angle_train = taup*1
        }
        else{
            steer_angle_train = taup
        }
    }
}

double PID::TotalError(double cte, double delta_distance, std::vector<double> pid_vector) {
    //find the new steering angle, given the changes made to the
    //PID coefficients
    double altered_angle = SteeringAngle(pid_vector[0],pid_vector[1],pid_vector[2]);
    //Based on the altered angle, find the expected value of the altered next cte
    double alt_exp_cte = cte + delta_distance*sin(altered_angle);
    return alt_exp_cte;
}

double PID::SteeringAngle(double tau_p, double tau_i, double tau_d){
    //Find the steering angle
    double s_angle = tau_p*cte + tau_d*(cte-previous_cte) + tau_i*sum_previous_ctes;
    //make sure the angle is between [-1,1]
    if (s_angle<-1){
        s_angle = -1.0;
    }
    if (s_angle>1){
        s_angle = 1.0;
    }
    return s_angle;
}

