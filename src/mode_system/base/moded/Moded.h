#pragma once
template <typename T>
class Moded {
private:
  T mode;

protected:
  Moded(T mode) : mode(mode) {}
  virtual ~Moded() = default;
  void setMode(T mode) {
    this->mode = mode;
  }

  T getMode() const {
    return mode;
  }
};