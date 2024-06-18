/*  
 *  Highstriker
 *  
 *  Kraftsensor, Lasereffekt -> Poti mit feder oder besser: Druckmatte, Waage & Hx711 (QS: Gravitation - Hold pressure)
 *  
 *  start unten, gegen gravitation. bestimmter bereich, zu hoch setzt auf Null, minimalwert
 *  Aufsummieren??. Anzeigeposition immmer nur +1 bis interner Wert erreicht
 *  Sieg: Bestimmte Position überschreiten
 */

//#define MAXPRESSURE 150 //kg (ab 200kg Probleme)

#define COUNTER_HIGH_UPPER NUM_LEDS-20
#define COUNTER_HIGH_LOWER NUM_LEDS-50
#define COUNTUP_HIGH 2

#define COLOR_HIGH RED_COLOR
#define DIR_HIGH FIRETOP

void loop_HIGH() {
  check_IO();
  //if(gameInput == 0) check_pressure(); // necessary to take total amount instead of sum up!

  
  if (gameInput == 0) {
    switch(gameState) {
      case STATE_SLEEP:
        showSleep(COLOR_HIGH);
        break;
      case STATE_RUN:
        if (millis() > gameTimer+TIMEALLOWED) {
          showSleep(COLOR_HIGH);
          gameState = STATE_SLEEP;
        }
        else {
          if (gameCounter > 0){
            gamePosition = gameCounter/5;
            gameCounter=0;
          }
          if (gamePosition<COUNTER_HIGH_UPPER && gamePosition>COUNTER_HIGH_LOWER) {
            flashColor(COLOR_HIGH);
            gameState = STATE_WIN;
            showWinning(COLOR_HIGH, FIRETOP);
          }
          showCometMod(COLOR_HIGH,gamePosition);

          fireHeat(COMET);
          fire(FIREBOTTOM,COLOR_HIGH,gamePosition, COMET); //TOP or BOTTOM Spin

          for(int i=COUNTER_HIGH_LOWER; i<COUNTER_HIGH_UPPER; i++) pixel(COLOR_HIGH, i, 20); 

          FastLED.show();
          FastLED.delay(FLICKER);
        }
        break;
      case STATE_WIN:
        if(millis() > gameTimer+TIMEWIN) {
          flashColor(COLOR_HIGH);
          gameState = STATE_SLEEP;
          showSleep(COLOR_HIGH);
        }
        else showWinning(COLOR_HIGH, DIR_HIGH);
        break;
    }
  } else {
    switch(gameState) {
      case STATE_SLEEP:
        flashColor(COLOR_HIGH);
        gameCounter = 0;
        startHIGH();
        break;
      case STATE_RUN:
        gameCounter+=COUNTUP_HIGH;
        Serial.print("Counter:");
        Serial.println(gameCounter);
        gameTimer = millis();
        break;
      case STATE_WIN:
        gameCounter = 0;
        startHIGH();
        break; 
    }
  }
}

void startHIGH() {
  gameCounter = 0;
  gamePosition = 0;
  gameTimer = millis();
  gameState = STATE_RUN;
}
