#include "KalmanFilter.h"



KalmanFilter::KalmanFilter(){
    
    // Initialize state estimate vector x
    x = {0.0f, 0.0f}; // Initial state estimate (position and velocity)
    // Initialize matrices


    P = {1.0f, 0.0f, 
        0.0f, 1.0f}; // Initial error covariance matrix
    Q = {0.1, 0.0, 
        0.0, 0.1}; // Process noise covariance matrix
    R = {0.1, 0.0, 
        0.0, 0.1}; // Measurement noise covariance matrix

    H = {1.0f, 0.0f,
        0.0f, 1.0f}; // State to measurement matrix

    A = {1.0f, 0.0f,
        0.0f, 1.0f}; // State transition matrix
    
    B = {0.0f, 0.0f}; // Control input vector

    z = {0.0f, 0.0f}; // Measurement vector

    K = {0.0f, 0.0f,
        0.0f, 0.0f}; // Kalman gain matrix

    


}


void KalmanFilter::update(float baroAlt, float gpsAlt, float accelAcc, float dt){
    
    z = {baroAlt, gpsAlt}; // Measurement vector (barometric and GPS altitudes)

    BLA::Matrix<2, 2> S = H * P * ~H + R;
    K = P * ~H * S.Inverse(); // Kalman gain matrix

    

    x = x + K * (z - H * x);

    Matrix<2, 2> I = {1.0f, 0.0f,
                      0.0f, 1.0f}; // Identity matrix (2x2)
                      

    P = (I - K * H) * P; // Update error covariance matrix

}


void KalmanFilter::predict(float accelAcc, float dt){
    // Update the state transition matrix A based on the time step dt
    A = {1.0f, dt
        0.0f, 1.0f}; // State transition matrix (2x2)
    
    // Update the control input matrix B based on the acceleration
    B = {0.5f * dt * dt,
        dt}; 

    x = A * x + B * accelAcc;

    P = A * P * ~A + Q;
}

