#ifndef TOWER_S_H
#define TOWER_S_H
#include "tower.h"

class Tower2: public Tower{
private:

public:
    Tower2(){}
    Tower2(int range, int spd, int power, int allhp, int make_score, int level_score): Tower(range, spd, power, allhp, make_score, level_score){
        picture=":/images/minilong.png";
        id=2;
        hp=this->allhp;
    }
    virtual ~Tower2(){}
    int levelup();
    void set(double x, double y);
    void getenemy(vector<Enemy *> &es);
};

class Tower3: public Tower{
  public:
    Tower3(){}
    Tower3(int range, int spd, int power, int allhp, int make_score, int level_score): Tower(range, spd, power, allhp, make_score, level_score){
        picture=":/images/jienigui.png";
        id=3;
        hp=this->allhp;
    }
    ~Tower3(){}
    int levelup();
    void set(double x, double y);
    void getenemy(vector<Enemy *> &es);
};

class Tower4: public Tower{
public:
    Tower4(){}
    Tower4(int range, int spd, int power, int allhp, int make_score, int level_score): Tower(range, spd, power, allhp, make_score, level_score){
        picture=":/images/leixilamu.png";
        id=4;
        hp=this->allhp;
    }
    ~Tower4(){}
    int levelup();
    void set(double x, double y);
    void getenemy(vector<Enemy *> &es);
    void attack();
    void show(QPainter &p);
};

class Tower5: public Tower{
public:
    Tower5(){}
    Tower5(int range, int spd, int power, int allhp, int make_score, int level_score): Tower(range, spd, power, allhp, make_score, level_score){
        picture=":/images/wanpidan.png";
        id=5;
        hp=this->allhp;
    }
    ~Tower5(){}
    int levelup();
    void set(double x, double y);
    void getenemy(vector<Enemy *> &es);
    void attack();
};

#endif // TOWER_S_H
