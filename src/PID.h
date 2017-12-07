#ifndef PID_H
#define PID_H

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;

  /*
  * Coefficients
  */
  double Kp;
  double Ki;
  double Kd;

  /*
  * Store previous CTE and the sum of all previous CTEs
  */
  double previous_cte;
  double sum_previous_ctes;

  /*
  * Other variables
  */
  //boolean specifying whether first observation or not.
  bool first_obs;
  //steering angle
  double steer_angle;
  //vector of the y-distance traveled based on steer angle
  std::vector<double> y_distance;
  //vector of the delta_distances traveled between each time period.
  std::vector<double> delta_distance_vector;
  //vector of the full_cte[0]=cte[0], full_cte[t]= cte[t] +y_distance[t-1]
  std::vector<double> full_cte_vector;
  //vector of the cte
  std::vector<double> cte_vector;
  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp0, double Ki0, double Kd0);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte, double delta_distance);

  /*
  * Calculate the total PID error.
  */
  double TotalError();
  /*
  * Calculate the steering angle.
  */
  double SteeringAngle();
};

#endif /* PID_H */
