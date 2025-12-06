#pragma once
#ifndef SECURITY_CAMERA_H
#define SECURITY_CAMERA_H

#include <string>

class SecurityCamera {
private:
    int cameraId;
    std::string location;
    bool isActive;
    std::string cameraType; // "indoor", "outdoor", "kitchen"
    double resolution;

public:
    SecurityCamera(int id, const std::string& loc, const std::string& type);
    void activate();
    void deactivate();
    void recordFootage();
    bool isRecording() const;
    std::string getLocation() const;
    void setResolution(double res);
};

#endif