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
    void getenemy(vector<Enemy *> &es);
};

class Tower3: public Tower{
  public:
    Tower3(){}
    ~Tower3(){}
    void levelup();
    void set(double x, double y);
    void getenemy(vector<Enemy *> &es);
};

class Tower4: public Tower{
public:
    Tower4(){}
    ~Tower4(){}
    void levelup();
    void set(double x, double y);
    void getenemy(vector<Enemy *> &es);
    void attack();
    void show(QPainter &p);
};

#endif // TOWER_S_H
