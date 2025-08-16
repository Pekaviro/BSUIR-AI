#include "Anemometer.h"

void Anemometer::display() {
    std::cout << "Wind speed: " << windSpeed_ << " m/s, Impulses: " << impulses_ << " m/s, Direction: " << direction_ << std::endl;
}

int Anemometer::setWindSpeed(int windSpeed) {
    this->windSpeed_ = windSpeed;
    return 0;
}

int Anemometer::getWindSpeed() const {
    return windSpeed_;
}