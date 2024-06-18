///*
// *  Rotary - alternative Poti
// */
//
//int state = 0;
//int maxValue = 3;
//int maxCount = 20; //20 Raststellungen
// 
//#include <SimpleRotary.h>
//SimpleRotary rotary(ROT_A, ROT_B, ROT_C); // Pin A, Pin B, Button Pin
//
//void start_rotary() {
//  rotary.setTrigger(HIGH);
//  rotary.setDebounceDelay(5);
//  rotary.setErrorDelay(250);
//}
//
//void test_rotary() {
//  byte i;
//  i = rotary.rotate();
//  if ( i == 1 ) Serial.println("<");
//  if ( i == 2 ) Serial.println(">");
//  if(rotary.push() == 1) Serial.println("P");
//}
//
//void check_rotary() {
//  byte i;
//  i = rotary.rotate();
//  if ( i == 1 ) {
//    if (state < maxCount) state++;
//    else state = 0;
//  } 
//  if ( i == 2 ) {
//    if (state > 0) state--;
//    else state = maxCount;
//  }
//  gameInput = (state+1)%(maxCount%maxValue)-1;
//}
