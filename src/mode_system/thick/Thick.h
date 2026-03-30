#pragma once

class Thick {
private:
  int thickness;

public:
  Thick();
  Thick(int thickness);
  void setThickness(int thickness);
  int getThickness() const;
};