#ifndef WAVE_INFO_H
#define WAVE_INFO_H

class Waveinfo{
public:
  Waveinfo(){}
  static const int wave1;
  static const int wave2;
  static const int wave3;
  static const int wave4;
  static const int wave5;
  static const int wave6;
  static const int wave7;
  static const int wave8;
  static const int wave9;
  static const int wave10;
  static const int wave11;
  static const int wave12;
  static const int waveend;
  static const int num_phase1;
  static const int num_phase2;
  static const int num_phase3;
  static bool you_can_rest(int wave){//进入休息界面
      if (wave!=wave1 &&wave!=wave2 &&wave!=wave3 &&wave!=wave4 &&wave!=wave5 &&wave!=wave6 &&wave!=wave7 &&
              wave!=wave8 &&wave!=wave9 &&wave!=wave10 &&wave!=wave11 &&wave!=wave12 &&wave<waveend) return false;
      else return true;
  }
  static int wavetype(int wave){    //特定波数之后新增加敌人
      if (wave<wave1-1) return 3;
      if (wave>=wave1-1 && wave <wave2-1) return 4;
      if (wave>=wave2-1 && wave<wave3-1) return 5;
      if (wave>=wave3-1 && wave<wave4-1) return 5;
      if (wave>=wave4-1 && wave<wave5-1) return 6;
      if (wave>=wave5-1 && wave<wave7-1) return 6;
      if (wave>=wave7-1 && wave<wave9-1) return 6;
      if (wave>=wave8-1 && wave<wave11-1) return 7;
      if (wave>=wave11-1 && wave<waveend-1) return 8;
      if (wave>=waveend-1) return 8;
  }
};

#endif // WAVE_INFO_H
