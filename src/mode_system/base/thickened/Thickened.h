#pragma once

class Thickened {
private:
  int thickness;

protected:
  Thickened();
  Thickened(int thickness);
  virtual ~Thickened() = default;
  void setThickness(int thickness);
  int getThickness() const;
};