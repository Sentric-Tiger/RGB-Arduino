/*
 * RGB.h - Libary for controlling RGB lights
 * Created by David O. OluFemi, Jaunary 15th, 2021.
 * FGL is yours to command.
 */
 #ifndef RGB_h
 #define RGB_h

 #include "Arduino.h"

 class RGB
 {
  
  public:
  RGB(int pinR, int pinG, int pinB);
  ~RGB();
  void Blue();
  void Red();
  void Green();
  void White();
  void Yellow();
  void Magenta();
  void Cyan();
  void Raspberry();
  void begin(int baudRate = 9600);
  void changeBlue(int blue);
  void changeGreen(int green);
  void changeRed(int red);
  void changeBrightness(int state);
  void OFF();
  int getBluePin();
  int getRedPin();
  int getGreenPin();
  int getBlueState();
  int getGreenState();
  int getRedState();
  int getBrightness();
  int getState(char letter);
  int getPin(char letter);
  void returnState(char letter, int &state);
  void setTimer(int Time);
  void transToRed();
  void transToGreen();
  void transToBlue();
  void transitionToPrimary(char letter1, char letter2, char letter3);
  void transitionToSecondary(char letter1, char letter2, char letter3);
  void transOff();

  private:
   const int RED;
    const int GREEN;
    const int BLUE;
    int brightness = 255;
    int delayTime = 20;
    int Rstate = 0;
    int Gstate = 0;
    int Bstate = 0;
 
 };
#endif
