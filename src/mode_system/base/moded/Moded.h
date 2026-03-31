#pragma once
template <typename T>
class Moded {
private:
  T mode;

public:
  Moded(T mode) : mode(mode) {}
  void setMode(T mode) {
    this->mode = mode;
  }

  T getMode() const {
    return mode;
  }
};