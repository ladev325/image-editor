#pragma once

class Thresholded {
private:
  float threshold;

protected:
  Thresholded();
  Thresholded(float threshold);
  virtual ~Thresholded() = default;
  void setThreshold(float threshold);
  float getThreshold() const;
};