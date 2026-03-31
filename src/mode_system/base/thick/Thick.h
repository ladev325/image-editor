#pragma once

class Thick {
private:
  int thickness;

protected:
  Thick();
  Thick(int thickness);
  virtual ~Thick() = default;
  void setThickness(int thickness);
  int getThickness() const;
};