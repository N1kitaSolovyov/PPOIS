#include "SecurityCamera.h"
#include <iostream>

SecurityCamera::SecurityCamera(int id, const std::string& loc, const std::string& type)
    : cameraId(id), location(loc), cameraType(type), isActive(false), resolution(1080.0) {
}

void SecurityCamera::activate() {
    isActive = true;
    std::cout << "Camera " << cameraId << " activated at " << location << std::endl;
}

void SecurityCamera::deactivate() {
    isActive = false;
    std::cout << "Camera " << cameraId << " deactivated" << std::endl;
}

void SecurityCamera::recordFootage() {
    if (isActive) {
        std::cout << "Recording footage from camera " << cameraId << std::endl;
    }
}

bool SecurityCamera::isRecording() const {
    return isActive;
}

std::string SecurityCamera::getLocation() const {
    return location;
}

void SecurityCamera::setResolution(double res) {
    resolution = res;
}
