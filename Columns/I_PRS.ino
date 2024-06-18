///* 
// *  Pressure
// */
//
//#include <HX711_ADC.h>
//HX711_ADC LoadCell(PRS_O, PRS_S);
//const int calVal_calVal_eepromAdress = 0;
//unsigned long t = 0;
//
//
//void start_pressure() {
//  Serial.println("Starting...");
//
//  float calibrationValue; // calibration value
//  calibrationValue = 696.0; // uncomment this if you want to set this value in the sketch
//
//  LoadCell.begin();
//  unsigned long stabilizingtime = 2000; // tare preciscion can be improved by adding a few seconds of stabilizing time
//  boolean _tare = true; //set this to false if you don't want tare to be performed in the next step
//  LoadCell.start(stabilizingtime, _tare);
//  if (LoadCell.getTareTimeoutFlag()) {
//    Serial.println("Timeout, check MCU>HX711 wiring and pin designations");
//  }
//  else {
//    LoadCell.setCalFactor(calibrationValue); // set calibration factor (float)
//    Serial.println("Startup is complete");
//  }
//  while (!LoadCell.update());
//  Serial.print("Calibration value: ");
//  Serial.println(LoadCell.getCalFactor());
//  Serial.print("HX711 measured conversion time ms: ");
//  Serial.println(LoadCell.getConversionTime());
//  Serial.print("HX711 measured sampling rate HZ: ");
//  Serial.println(LoadCell.getSPS());
//  Serial.print("HX711 measured settlingtime ms: ");
//  Serial.println(LoadCell.getSettlingTime());
//  Serial.println("Note that the settling time may increase significantly if you use delay() in your sketch!");
//  if (LoadCell.getSPS() < 7) {
//    Serial.println("!!Sampling rate is lower than specification, check MCU>HX711 wiring and pin designations");
//  }
//  else if (LoadCell.getSPS() > 100) {
//    Serial.println("!!Sampling rate is higher than specification, check MCU>HX711 wiring and pin designations");
//  }
//}
//
//void test_pressure() {
//  static boolean newDataReady = 0;
//  const int serialPrintInterval = 500; //increase value to slow down serial print activity
//
//  // check for new data/start next conversion:
//  if (LoadCell.update()) newDataReady = true;
//
//  // get smoothed value from the dataset:
//  if (newDataReady) {
//    if (millis() > t + serialPrintInterval) {
//      float i = LoadCell.getData();
//      Serial.print("Load_cell output val: ");
//      Serial.println(i);
//      newDataReady = 0;
//      t = millis();
//    }
//  }
//
//  // receive command from serial terminal, send 't' to initiate tare operation:
//  if (Serial.available() > 0) {
//    char inByte = Serial.read();
//    if (inByte == 't') LoadCell.tareNoDelay();
//  }
//
//  // check if last tare operation is complete:
//  if (LoadCell.getTareStatus() == true) {
//    Serial.println("Tare complete");
//  }
//}
//
//int check_pressure() {
//  if(LoadCell.update()) gameInput = LoadCell.getData();
//  else gameInput = 0;
//}
