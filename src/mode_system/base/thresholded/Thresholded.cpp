#include "Thresholded.h"

Thresholded::Thresholded() : Thresholded(0.2) {}
Thresholded::Thresholded(float threshold) : threshold(threshold) {}

void Thresholded::setThreshold(float threshold) {
  this->threshold = threshold;
}

float Thresholded::getThreshold() const {
  return threshold;
}