///* 
// *  Brain
// *  
// *  Meditieren, Gehirnwellen ordnen -> Mindflex natürlich (QS: Gehirnströme/Elektrizität)
// *  8 channel, attention, meditation -> Mapping auf 4 Pfosten, 3 Farben. Erezugen Sparks durch Input, Gewinn: Meditation oder Attention über bestimmten wert
// *  Pfuschen: Abwarten bis Signalqualität für ne bestimmte Zeit gut genug   
// *  4 SEITEN, 3 RGB Farben... einzelwerte anzeigen bis bestimmter Attention/meditation wert erreicht wird... oder reaktion auf farben (Pattern?)
// *  glätten über zeit -> aufsummieren und dämpfen wie bei highstriker, Feueranimation mit unterschiedlicher Höhe bzw neie werte als Sparks?
// *  
// *  uint8_t readSignalQuality(); readMeditation(); readAttention(); uint32_t* readPowerArray();
// *  uint32_t readDelta(); readTheta(); readLowAlpha(); readHighAlpha(); readLowBeta(); readHighBeta(); uint32_t readLowGamma(); uint32_t readMidGamma();
// *  -> Attention/Mediation 0...100, Rest 0...40000, Signal Quality muss 0 sein
// */
//
//#define COLOR_BRN WHITEVIOLETT_COLOR
//#define DIR_BRN FIREBOTTOM
//#define ATTENTIONSPAN 10000
//
//static byte heat_BRN[NUM_LEDS];
//
//void loop_BRN() {
//  if (Serial.available()) { //...get brain value as gameInput... 
//    gameInput = Serial.read();
//  }
//
//  if (gameInput == 0) { //not on head
//    showSleep(COLOR_BRN);
//    gameState = STATE_SLEEP;
//  } else {
//    switch(gameState) {
//      case STATE_SLEEP:
//        startBRN();
//        break;
//      case STATE_RUN:
//        runBRN();
//        spreadSparks();
//        break;
//      case STATE_WIN:
//        if(millis() > gameTimer+TIMEWIN) {
//          flashColor(COLOR_BRN);
//          gameState = STATE_SLEEP;
//          showSleep(COLOR_BRN);
//        }
//        else showWinning(COLOR_BRN, DIR_BRN);
//        break; 
//    }
//  }
//}
//
//void runBRN() { 
//  spreadSparks();// create new sparks from meditation level
//  if (millis() > gameTimer+ATTENTIONSPAN) {
//    gameState = STATE_WIN;
//    flashColor(COLOR_BRN);
//    showWinning(COLOR_BRN, DIR_BRN);
//    gameTimer = millis();
//  }
//}
//
//void spreadSparks() { 
//// Step 1.  Cool down every cell a little
//  for(int i = 0; i < NUM_LEDS; i++) {
//    heat_BRN[i] = qsub8( heat_BRN[i],  random8(0, ((cooling * 10) / NUM_LEDS) + 2));
//  }
//  
//// Step 2.  Heat from each cell drifts 'up' and diffuses a little
//  for( int k= NUM_LEDS-1; k >= 1; k--) {
//    heat_BRN[k] = (heat_BRN[k-1] + heat_BRN[k-2] + heat_BRN[k - 2]) / 3;
//  }
// 
//// Step 3.  Randomly ignite new 'sparks' of heat near the bottom
//  heat_BRN[gameInput] = qadd8( heat_BRN[gameInput], random8(160,255) );
//  
//  fire(FIREBOTTOM, COLOR_BRN, 0, NUM_LEDS);
//  FastLED.show();
//  FastLED.delay(FLICKER);
//}
//
//void startBRN() {
//  gameTimer = millis();
//  gameState = STATE_RUN;
//}
//
//void checkBrain() {
////  if (brain.update()) { // Expect packets about once per second.
////    if (brain.readSignalQuality() < 10) {
////      gameInput = 0;
////    } else {
////      gameInput = (int) brain.readMeditation()*NUM_LEDS/100;
////      gameInput = (int) brain.readAttention()*NUM_LEDS/100;
////      gameInput = (int) brain.readDelta()*NUM_LEDS/40000;
////      gameInput = (int) brain.readTheta()*NUM_LEDS/40000; 
////      gameInput = (int) brain.readLowAlpha()*NUM_LEDS/40000; 
////      gameInput = (int) brain.readHighAlpha()*NUM_LEDS/40000; 
////      gameInput = (int) brain.readLowBeta()*NUM_LEDS/40000; 
////      gameInput = (int) brain.readHighBeta()*NUM_LEDS/40000; 
////      gameInput = (int) brain.readLowGamma()*NUM_LEDS/40000; 
////      gameInput = (int) brain.readMidGamma()*NUM_LEDS/40000;
////    }
////  }
//}
//
///* Program for Mindflex Arduino
// *  
//
//#include <SoftwareSerial.h>
//#include <Brain.h>
//
//SoftwareSerial softSerial(10, 11);
//Brain brain(softSerial);
//
//void setup() {
//    softSerial.begin(9600);
//    Serial.begin(9600);
//}
//
//void loop() {
//  if (brain.update()) { // Expect packets about once per second.
//    if (readSignalQuality() < 10) {
//      Serial.println(0);
//    } else {
//      Serial.println((int) readMeditation()*NUM_LEDS/100);
//      Serial.println((int) readAttention()*NUM_LEDS/100);
//      Serial.println((int) readDelta()*NUM_LEDS/40000);
//      Serial.println((int) readTheta()*NUM_LEDS/40000); 
//      Serial.println((int) readLowAlpha()*NUM_LEDS/40000); 
//      Serial.println((int) readHighAlpha()*NUM_LEDS/40000); 
//      Serial.println((int) readLowBeta()*NUM_LEDS/40000); 
//      Serial.println((int) readHighBeta()*NUM_LEDS/40000); 
//      Serial.println((int) readLowGamma()*NUM_LEDS/40000); 
//      Serial.println((int) readMidGamma()*NUM_LEDS/40000);
//    }
//  }
//}
//
//*/
