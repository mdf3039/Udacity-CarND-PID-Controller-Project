## Writeup Template

### You can use this file as a template for your writeup if you want to submit it as a markdown file, but feel free to use some other method and submit a pdf if you prefer.

---

**PID Controller Project**

The goals / steps of this project are the following:

* Build a PID controller and tune the PID hyperparameters by applying the general processing flow as described in the previous lessons.
* Code should compile.
* The PID procedure follows what was taught in the lessons.
* Describe the effect each of the P, I, D components had in your implementation.
* Describe how the final hyperparameters were chosen.
* The vehicle must successfully drive a lap around the track.


## [Rubric](https://review.udacity.com/#!/rubrics/824/view) Points

### Here I will consider the rubric points individually and describe how I addressed each point in my implementation.  

---

### Writeup / README  

You're reading it!


### Compilation

#### 1. Your code should compile. Code must compile without errors with cmake and make.

After the last push to GitHub, I compiled the code to ensure there were not any errors before submitting for review.


### Implementation

#### 1. The PID procedure follows what was taught in the lessons.

The PID procedure follows a similar structure to what was taught in the lessons. The steering value is derived from negating the sum of proportional values of the cte, differential of the cte, and a composite of previous ctes (line 80 main.cpp).


### Reflection

#### 1. Describe the effect each of the P, I, D components had in your implementation.

The PID controller has three parts that work together to make the controller work to find the best steering angle. The first part, P, moves the car in proportion to cte. Based upon simulation attempts, it was easy to recognize that the P would have to be set with respect to the speed; for two identical cars traveling at different speeds with the same P, the car with the higher speed will have broader steering angle shifts with cte fluctuations. The second part, D, protects the car from overshooting its target. It uses a proportion of the difference between the previous cte and current cte; without this, the car would continuously overshoot its target, moving about in a sinusoidal fashion around the target. The third part, I, is the sum of the previous ctes. This protects from potential biases of drifts and turns. I have found the third part to be most helpful during turns. I use a queue of the last 20 ctes. The sum of the queue while traveling on a straight line approaches a constant number (the drift or constant biases). When the car is traveling on a road with turns, however, the sum of the queue will begin to increase/decrease depending on the direction of the curve, since the recent ctes will suddenly begin to increase. This sudden increase in the queue sum increases the magnitude of the steering angle. 

#### 2. Describe how the final hyperparameters were chosen.

The final hyperparameter for P, I, and D were chosed manually. I set P to be proportional to the speed of the car. I set D to be 3.5; I initially had it at 3 (similar to the lectures, but found I wanted smoother descent towards the target). I set I to be 0.008, which is twice the amount in the lectures. This increase provides a stronger turn when at a curve. The number of elements in the queue was chosen to be 20 and the throttle shuts down if the speed is above 10.


### Simulation

#### 1. The vehicle must successfully drive a lap around the track.

The final model has a vehicle that drives successfully around the track, without hitting any ledges or unsafe surfaces.


---

### Discussion

#### 1. Briefly discuss any problems / issues you faced in your implementation of this project.  Where will your model likely fail?  What could you do to make it more robust?

Here I'll talk about the approach I took, what techniques I used, what worked and why, where the model might fail and how I might improve it if I were going to pursue this project further.  

My initial approach was to code a considerably complex algorithm I imagined in my head to procude the best tau parameters. The approach would have had a computational time of O(n^n), but I was sure it would produce optimal results. After thinking this through, I realized I can just make the tau parameters proportional to the speed, since equivalent tau parameters at different speeds produce incorrect results. I only set the P tau parameter proportional to the speed and the model worked, with the other parameters taken from the lecture notes. I manually tweaked the I and D tau parameters slightly, but much more work can be done. One major reason my model works is because I have set the throttle to shut off once the speed reached 10. My model will likely fail at some point where the speed is beyond 10. Making the I and D tau parameters proportional to the speed as well could help the car run at any speed. I would do this to make the model more robust. 
One aspect that works really well with turns is the queue. I did not manually tune the number of elements in the queue. 20 was just the first number tried. What I would expect, with different speeds, is the higher the speed, the less the amount of elements needed in the queue to help the turn.
