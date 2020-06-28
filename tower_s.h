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

class Tower6: public Tower{
public:
    Tower6(){}
    Tower6(int range, int spd, int power, int allhp, int make_score, int level_score): Tower(range, spd, power, allhp, make_score, level_score){
        picture=":/images/pikaqiu.png";
        id=6;
        hp=this->allhp;
    }
    ~Tower6(){}
    int levelup();
    void set(double x, double y);
    void getenemy(vector<Enemy *> &es);
};

class Tower7: public Tower{
public:
    Tower7(){}
    Tower7(int range, int spd, int power, int allhp, int make_score, int level_score): Tower(range, spd, power, allhp, make_score, level_score){
        picture=":/images/jidongniao.png";
        id=7;
        hp=this->allhp;
    }
    ~Tower7(){}
    int levelup();
    void set(double x, double y);
    void getenemy(vector<Enemy *> &es);
    void attack();
};

class Tower8: public Tower{
public:
    Tower8(){}
    Tower8(int range, int spd, int power, int allhp, int make_score, int level_score): Tower(range, spd, power, allhp, make_score, level_score){
        picture=":/images/menghuan.png";
        id=8;
        hp=this->allhp;
    }
    ~Tower8(){}
    int levelup();
    void set(double x, double y);
    void getenemy(vector<Enemy *> &es);
    void attack();
};

class Tower9: public Tower{
public:
    Tower9(){}
    Tower9(int range, int spd, int power, int allhp, int make_score, int level_score): Tower(range, spd, power, allhp, make_score, level_score){
        picture=":/images/ladiyasi.png";
        id=9;
        hp=this->allhp;
    }
    ~Tower9(){}
    int levelup();
    void set(double x, double y);
    void getenemy(vector<Enemy *> &es);
};

#endif // TOWER_S_H
