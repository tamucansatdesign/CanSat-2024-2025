#include <iostream>  // Include necessary libraries for input-output
#include <vector>    // Include vector for storing values
#include <sstream>   // Include sstream for string stream operations
#include "matplotlibcpp.h" // Include matplotlib-cpp for plotting.
//I dont know exactly how matplotlib works with C, but this may be it.

namespace plt = matplotlibcpp;

// Struct to store parsed CSV data
struct Frame {
    std::string ID;
    double mission_time;
    double packet_count;
    std::string mode;
    std::string state;
    double altitude;
    double temperature;
    double pressure;
    double voltage;
    double gyro_r;
    double gyro_p;
    double gyro_y;
    double accel_r;
    double accel_p;
    double accel_y;
    std::string mag_r;
};

// Function to split a CSV string into individual values
std::vector<std::string> splitCSV(const std::string& csvString) {
    std::vector<std::string> result;  // Vector used to store split values
    std::stringstream ss(csvString);  // Creates a string stream from input
    std::string item;  // Temporary string to store extracted values

    // Read values from the stream, separated by commas
    while (std::getline(ss, item, ',')) {
        result.push_back(item);  // Store each extracted value into the vector
    }

    return result;  // Return the vector of split values
}

// Function to parse CSV data into a Frame struct
Frame parseFrame(const std::string& csvData) {
    std::vector<std::string> values = splitCSV(csvData);
    Frame frame;

    if (values.size() >= 16) {
        frame.ID = values[0];
        frame.mission_time = std::stod(values[1]);
        frame.packet_count = std::stod(values[2]);
        frame.mode = values[3];
        frame.state = values[4];
        frame.altitude = std::stod(values[5]);
        frame.temperature = std::stod(values[6]);
        frame.pressure = std::stod(values[7]);
        frame.voltage = std::stod(values[8]);
        frame.gyro_r = std::stod(values[9]);
        frame.gyro_p = std::stod(values[10]);
        frame.gyro_y = std::stod(values[11]);
        frame.accel_r = std::stod(values[12]);
        frame.accel_p = std::stod(values[13]);
        frame.accel_y = std::stod(values[14]);
        frame.mag_r = values[15];
    }
    return frame;
}

int main() {
    std::string csvData = "ID1,123.4,5,mode1,state1,1000.5,22.4,1013.2,3.7,0.02,0.03,0.01,9.81,0.01,-9.81,N";  // Example CSV string
    Frame frame = parseFrame(csvData);  // Parse CSV into struct

    // Graphing
    std::vector<double> mission_time = {frame.mission_time};

    // Altitude vs Mission Time
    std::vector<double> altitude = {frame.altitude};
    plt::figure();
    plt::plot(mission_time, altitude, "b-");
    plt::title("Altitude vs Mission Time");
    plt::xlabel("Mission Time (s)");
    plt::ylabel("Altitude (m)");
    plt::show();

    // Temperature vs Mission Time
    std::vector<double> temperature = {frame.temperature};
    plt::figure();
    plt::plot(mission_time, temperature, "r-");
    plt::title("Temperature vs Mission Time");
    plt::xlabel("Mission Time (s)");
    plt::ylabel("Temperature (°C)");
    plt::show();

    // Pressure vs Mission Time
    std::vector<double> pressure = {frame.pressure};
    plt::figure();
    plt::plot(mission_time, pressure, "g-");
    plt::title("Pressure vs Mission Time");
    plt::xlabel("Mission Time (s)");
    plt::ylabel("Pressure (kPa)");
    plt::show();

    // Gyro (R, P, Y) vs Mission Time
    std::vector<double> gyro_r = {frame.gyro_r};
    std::vector<double> gyro_p = {frame.gyro_p};
    std::vector<double> gyro_y = {frame.gyro_y};
    plt::figure();
    plt::plot(mission_time, gyro_r, "r-", mission_time, gyro_p, "g-", mission_time, gyro_y, "b-");
    plt::title("Gyro (R, P, Y) vs Mission Time");
    plt::xlabel("Mission Time (s)");
    plt::ylabel("Gyro Values (degrees/s)");
    plt::legend({"Gyro R", "Gyro P", "Gyro Y"});
    plt::show();

    // Accel (R, P, Y) vs Mission Time
    std::vector<double> accel_r = {frame.accel_r};
    std::vector<double> accel_p = {frame.accel_p};
    std::vector<double> accel_y = {frame.accel_y};
    plt::figure();
    plt::plot(mission_time, accel_r, "r-", mission_time, accel_p, "g-", mission_time, accel_y, "b-");
    plt::title("Accel (R, P, Y) vs Mission Time");
    plt::xlabel("Mission Time (s)");
    plt::ylabel("Acceleration Values (m/s^2)");
    plt::legend({"Accel R", "Accel P", "Accel Y"});
    plt::show();

    // Mag R vs Mission Time
    std::vector<double> mag_r = {std::stod(frame.mag_r)};
    plt::figure();
    plt::plot(mission_time, mag_r, "m-");
    plt::title("Mag R vs Mission Time");
    plt::xlabel("Mission Time (s)");
    plt::ylabel("Mag R (G)");
    plt::show();

    return 0;  // Indicate successful program execution
}

//overall created a struct that characterizes 16 inputs from given .csv files that contian mission data. The overall input is taken as a string. The data is then separated by commas, and each
//value is stored sequentially into the given Struct Variables
//Finally, the values per each struct are plotted vs time, to produce 6 graphs as visualized in the PDR presentation, slide 100.
//Hopefully this works...
