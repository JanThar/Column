///* 
// *  Distance
// */
// 
//#include <VL6180X.h>
//VL6180X distance;
//int minDistance = 20; //mm //200mm max, 600mm with reduced resolution
//int offsetDistance = 40;
//
//
//void start_distance() {
//  distance.init();
//  Serial.println("Distance input initialized!");
//  distance.configureDefault();
//  distance.writeReg(VL6180X::SYSRANGE__MAX_CONVERGENCE_TIME, 30);
//  distance.writeReg16Bit(VL6180X::SYSALS__INTEGRATION_PERIOD, 50);
//  distance.setTimeout(500);
//  distance.stopContinuous();
//  delay(300);
//  distance.startInterleavedContinuous(100);
//}
//
//void test_distance() {
//  Serial.print("Ambient: ");
//  Serial.print(distance.readAmbientContinuous());
//  if (distance.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
//  Serial.print("\tRange: ");
//  Serial.print(distance.readRangeContinuousMillimeters());
//  if (distance.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
//  Serial.println();
//}
//
//void check_distance() {
//  gameInput = 0;
//  int newDistance = distance.readRangeContinuousMillimeters();
//  for (int i=0; i<4; i++) {
//    if((newDistance>=minDistance+offsetDistance*i) && (newDistance<minDistance+offsetDistance*(i+1))) {
//      gameInput = i+1;
//    }
//  }
//}
