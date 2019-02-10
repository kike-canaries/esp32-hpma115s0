#include "GUIUtils.hpp"

/******************************************************************************
*   D I S P L A Y  M E T H O D S
******************************************************************************/

void GUIUtils::displayInit(U8G2 &u8g2){
  u8g2.begin();
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setContrast(255);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
  u8g2.setFontMode(0);
  this->u8g2 = u8g2;
  Serial.println("-->[OLED] display ready.");
}

void GUIUtils::showWelcome(){
  u8g2.firstPage();  // only for first screen
#ifdef D1MINI
  u8g2.drawStr(0, 0, "CanAirIO");
  String version = "("+String(VERSION_CODE+VCODE)+")";
  u8g2.drawStr(0, 11,version.c_str());
  u8g2.drawLine(0, 22, 128, 22);
#else
  String version = "CanAirIO ("+String(VERSION_CODE+VCODE)+")";
  u8g2.drawStr(0, 0,version.c_str());
  u8g2.drawLine(0, 11, 128, 11);
#endif
  // only for first screen
  Serial.println("-->[OLED] welcome screen ready\n");
  u8g2.nextPage();
}

void GUIUtils::displayCenterBig(String msg){
#ifdef D1MINI
  u8g2.setCursor(0,0);
  u8g2.setFont(u8g2_font_inb24_mn);
#else
  u8g2.setCursor(73,40);
  u8g2.setFont(u8g2_font_freedoomr25_mn);
#endif
  u8g2.print(msg.c_str());
}

void GUIUtils::displayBottomLine(String msg){
  u8g2.setFont(u8g2_font_4x6_tf);
#ifdef D1MINI
  u8g2.setCursor(0, 27);
  u8g2.print(msg.c_str());
#else
  u8g2.setCursor(0, 16);
  u8g2.print(msg.c_str());
#endif
}

void GUIUtils::displayEndLine(String msg){
  u8g2.setFont(u8g2_font_4x6_tf);
#ifdef D1MINI
  u8g2.setCursor(0, 33);
  u8g2.print(msg.c_str());
#else
  u8g2.setCursor(0, 16);
  u8g2.print(msg.c_str());
#endif
}

void GUIUtils::displaySensorError(){
  char output[22];
  if(ecount==99)ecount=0;
  sprintf(output,"%04d E:%03d",mcount,ecount++);
  displayEndLine(String(output));
}

void GUIUtils::displaySensorAvarage(int avarage){
  char output[4];
  sprintf(output, "%03d", avarage);
  displayCenterBig(output);
}

void GUIUtils::displaySensorData(int pm25, int pm10){
  char output[22];
  if(mcount<9999)mcount++;
  else mcount=0;
#ifdef D1MINI
  sprintf(output, "%03d %03d %02d %04d", pm25, pm10, ecount, mcount);
#else
  sprintf(output, "%04d P25:%03d P10:%03d", mcount, pm25, pm10);
#endif
  displayBottomLine(String(output));
}

void GUIUtils::pageStart(){
  u8g2.firstPage();
}

void GUIUtils::pageEnd(){
  do; while(u8g2.nextPage());
}