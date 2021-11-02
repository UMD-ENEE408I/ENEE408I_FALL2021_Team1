#pragma once

#include <vector>
#include <Arduino.h>
#include "Stopwatch.h"
#include "Utils.h"

/**
 * A z-axis gyroscope that returns an estimate for the current angular
 * heading using numeric integration of the angular speed.
 */
class Gyro {
  private:
    float _currentAngle;
    Stopwatch _integrationTimer;
    float _gyroBias;
        
  public:
    Gyro() :
      _currentAngle(0),
      _integrationTimer(),
      _gyroBias(0)
    {
    }

    /**
     * Initializes the IMU and calibrates the Gyro.
     * Always call this function before use!
     */
    void begin() {
      if (!IMU.begin()) {
        Serial.println("Failed to initialize IMU!");
        while (1);
      }

      calibrate();
    }

    /**
     * Determine the built-in bias for the z-rotation of the gyroscope. The 
     * should be stationary while this method is running!
     * 
     * The bias is calculated using a MEDIAN of samples, not an average, because the median 
     * can better handle the spuriously high angular speeds (~150 deg. / sec.) that the gyro
     * returns for its first few measurements.
     */
    void calibrate() {
      Serial.println("Calibrating Gyroscope bias");
      constexpr int NUM_SAMPLES = 100;
      std::vector<float> gyroSamples;
      gyroSamples.reserve(NUM_SAMPLES);

      // Take many samples of the angular speed
      while (gyroSamples.size() < NUM_SAMPLES) {
        if (IMU.gyroscopeAvailable()) {
          float sensedBias = getAngularSpeed();
          gyroSamples.push_back(sensedBias);
    
          Serial.println(String(gyroSamples.size()) + "th bias measurement (deg / sec): " + String(sensedBias));
        }

        delay(5);
      }

      // Use a median to ignore high-value outliers.
      _gyroBias = Utils::median(gyroSamples);
      
      Serial.println("Detected bias (deg / sec): " + String(_gyroBias));

      zeroOut();
    }

    void zeroOut() {
      _currentAngle = 0;
      _integrationTimer.zeroOut();
    }

    /**
     * Computes and returns the angle in degrees using Euler's Method
     */
    float getAngle() {
      if (!IMU.gyroscopeAvailable()) {
        return _currentAngle;
      }

      // angle ~= angle + (current angular speed) * dt
      _currentAngle += getAngularSpeed() * _integrationTimer.lap();
    
      return _currentAngle;
    }

    /**
     * Returns how fast the robot is turning in the z-direction in degrees per second. Removes
     * the gyro's measured bias from the measurements.
     * 
     * PRECONDITION: always make sure the gyroscope is available before calling this method
     */
    float getAngularSpeed() {
      if (!IMU.gyroscopeAvailable()) {
        Serial.println("ERROR: Tried querying the angular speed before it was available");
        return 0;
      }
      
      float turnSpeedX, turnSpeedY, rawTurnSpeedZ;
      IMU.readGyroscope(turnSpeedX, turnSpeedY, rawTurnSpeedZ);

      // The gyro consistently undershoots angular speed during measurements (mine measures
      // 310 degrees for every 360 degree rotation). We can correct this by multiplying the raw
      // speed by the following constant:
      constexpr float GYRO_UNITS_TO_DPS = 360. / 310;
      
      return rawTurnSpeedZ * GYRO_UNITS_TO_DPS - _gyroBias;
    }
};
