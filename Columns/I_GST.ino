///*
// *  Gesture
// */
// 
//#include "Adafruit_APDS9960.h"
//Adafruit_APDS9960 gesture;
//
//void start_gesture() {
//  if(!gesture.begin()) Serial.println("Gesture input initialisation failed!");
//  else Serial.println("Gesture input initialized!");
//
//  //gesture mode will be entered once proximity mode senses something close
//  gesture.enableProximity(true);
//  gesture.enableGesture(true);
//}
//
//void test_gesture() {
//  uint8_t gesture_detect = gesture.readGesture();
//    if(gesture_detect == APDS9960_DOWN) Serial.println("v");
//    if(gesture_detect == APDS9960_UP) Serial.println("^");
//    if(gesture_detect == APDS9960_LEFT) Serial.println("<");
//    if(gesture_detect == APDS9960_RIGHT) Serial.println(">");
//    if(gesture_detect == 0) Serial.println("0");
//}
//
//void check_gesture() {
//  uint8_t gesture_detect = gesture.readGesture();
//  gameInput = 0;
//  if(gesture_detect == APDS9960_DOWN) gameInput = 4;
//  else if(gesture_detect == APDS9960_UP) gameInput = 1;
//  else if(gesture_detect == APDS9960_LEFT) gameInput = 2;
//  else if(gesture_detect == APDS9960_RIGHT) gameInput = 3;
//}
