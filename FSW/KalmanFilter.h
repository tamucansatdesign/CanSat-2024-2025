#include <BasicLinearAlgebra.h>


class KalmanFilter{
public:
    KalmanFilter();
    void update(float baroAlt, float gpsAlt, float accelAcc, float dt);
    void predict(float accelAcc, float dt);

    float getAltitude() const;
    float getVelocity() const;

private:
    BLA::Matrix<2, 1, float> x; // State estimate vector
    BLA::Matrix<2, 2, float> A; // State transition matrix
    BLA::Matrix<2, 1, float> B; // Control input vector
    BLA::Matrix<2, 2, float> P; // Error covariance matrix
    BLA::Matrix<2, 2, float> Q; // Process noise covariance matrix
    BLA::Matrix<2, 2, float> H; // State to measurement Matrix
    BLA::Matrix<2, 1, float> z; // Measurement vector
    BLA::Matrix<2, 2, float> R; // Measurement noise covariance matrix
    BLA::Matrix<2, 2, float> K; // Kalman gain matrix
};