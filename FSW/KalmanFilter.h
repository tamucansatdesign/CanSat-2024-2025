#include <BasicLinearAlgebra.h>


class KalmanFilter{
public:
    KalmanFilter();
    void update(float baroAlt, float gpsAlt);
    void predict(float accelAcc, float dt)

    void getAltitude() const;
    void getVelocity() const;

private:
    BLA::Matrix<float, 2, 1> x; // State estimate vector 
    BLA::Matrix<float, 2, 2> A; // State transition matrix
    BLA::Matrix<float, 2, 1> B; // Control input vector
    BLA::Matrix<float, 2, 2> P; // Error covariance matrix
    BLA::Matrix<float, 2, 2> Q; // Process noise covariance matrix
    BLA::Matrix<float, 2, 2> H; // State to measurement Matrix
    BLA::Matrix<float, 2, 1> z; // Measurement vector
    BLA::Matrix<float, 2, 2> R; // Measurement noise covariance matrix
    BLA::Matrix<float, 2, 2> K; // Kalman gain matrix
};