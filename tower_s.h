#ifndef TOWER_S_H
#define TOWER_S_H
#include "tower.h"

class Tower2: public Tower{
private:

public:
    Tower2(){}
    virtual ~Tower2(){}
    void levelup();
    void set(double x, double y);
};

class Tower3: public Tower{
  public:
    Tower3(){}
    ~Tower3(){}
    void levelup();
    void set(double x, double y);
};

#endif // TOWER_S_H
