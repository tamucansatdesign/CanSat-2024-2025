// #include <BasicLinearAlgebra.h>


// class KalmanFilter{
// public:
//     KalmanFilter(float dt);


//     float update(float baroAlt, float gpsAlt float accelAcc, float gpsTime){
//         float dt = (gpsTime - prevTime)/1000; 
//         prevTime = gpsTime; 
//         A(0,1) = dt;
//         A(1,0) = 0;
//         A(1,1) = 1;
//         Q(0,0) = 0.5*accelAcc*dt*dt;
//         Q(1,1) = accelAcc*dt;
//         x = A*x;
//         P = A*P*A.transpose() + Q;
//         K = P*H.transpose()*(H*P*H.transpose() + R).inverse();
//         x = x + K*(baroAlt - H*x);
//         P = (Eigen::Matrix<float, 2, 2>::Identity() - K*H)*P;
//         return x(0);
//     }


// private:
//     BLA::Matrix<float, 2, 2> A; // State transition matrix
//     BLA::Matrix<float, 2, 2> P; // Error covariance matrix
//     BLA::Matrix<float, 2, 2> Q; // Process noise covariance matrix
//     BLA::Matrix<float, 1, 2> H; // Observation Matrix
//     BLA::Matrix<float, 1, 1> R; // Measurement noise covariance matrix
//     BLA::Matrix<float, 2, 1> x; // State estimate vector 
//     BLA::Matrix<float, 2, 1> K; // Kalman gain
//     unsigned long prevTime;
// };