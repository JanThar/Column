/* 
 *  1D Adventure
 *  
 *  Richtung, 2 Taster (Neigung mit federn drunter... Taster einfacher) (QS: Gyroscope)
 *  
 *  ledpunkt position spieler
 *  bewegen rauf runter, links/rechts springen
 *  Lichtpunkte schwingen von seite rein, aka Pendel
 *  Sieg: bestimmte Anzahl Level erreicht
 *  
 *  einzelpunkte als pendel
 */

#define COLOR_ADV GREEN_COLOR
#define DIR_ADV FIREBOTTOM
#define TOLERANCE_ADV 20

float pnd_speed[]    = {0.11, 0.07, 0.09, 0.08, 0.1}; // 0.1 ... 0.2
float pnd_position[] = {  33,   48,   80,   90, 120}; 

void loop_ADV() {
  
  check_IO();
  if(gameState == STATE_RUN) {
    gameCounter++;
    update_PositionADV();
    check_CollisionADV();
  }
  
  if (gameInput == 0) {
    switch(gameState) {
      case STATE_SLEEP:
        showSleep(COLOR_ADV);
        break;
      case STATE_RUN:
        if (millis() > gameTimer+20000) {
          Serial.println("Timeout");
          showSleep(COLOR_ADV);
          gameState = STATE_SLEEP;
          showSleep(COLOR_ADV);
        }
        else {
          if (gameCounter<0) gameCounter = 0;
        }
        break;
      case STATE_WIN:
        if(millis() > gameTimer+TIMEWIN) {
          flashColor(COLOR_ADV);
          gameState = STATE_SLEEP;
          showSleep(COLOR_ADV);
        }
        else showWinning(COLOR_ADV, DIR_ADV);
        break;
    }
  } else {
    switch(gameState) {
      case STATE_SLEEP:
        flashColor(COLOR_ADV);
        startADV();
        break;
      case STATE_RUN:
        gameTimer = millis();
        runADV();
        break;
      case STATE_WIN:
        startADV();
        break; 
    }
  }
}

void update_PositionADV() {
  switch(gameInput) {
    case 1:
      gamePosition ++;
      break;
    case 2: //shoot??
      gamePosition --;
      break;
    case 3:
      break;
    case 4:
      break;
  }
  if (gamePosition<0) gamePosition = 0;
}

void check_CollisionADV() {
  fireHeat(COMET);
  if (gamePosition > NUM_LEDS-1) fire(FIREBOTTOM,COLOR_ADV,NUM_LEDS*2-gamePosition-1, COMET); //TOP or BOTTOM Spin
  else fire(FIRETOP,COLOR_ADV,gamePosition, COMET); //TOP or BOTTOM Spin

  for(int i=0; i<5; i++) {
    pixel(COLOR_ADV, pnd_position[i], 125*cos(pnd_speed[i] * gameCounter)+125); 
    if (gamePosition == pnd_position[i] && 125*cos(pnd_speed[i] * gameCounter)+125 >TOLERANCE_ADV) {
      flashColor(COLOR_ADV);
      gameTimer = millis();
      gamePosition=0;
    }
  }
       
  FastLED.show();
  FastLED.delay(FLICKER);
}

void runADV() {
  if (gamePosition == NUM_LEDS-1) {
    flashColor(COLOR_ADV);
    gameState = STATE_WIN;
    gameTimer = millis();
    showWinning(COLOR_ADV, DIR_ADV);
  } 
}

void startADV() {
  gamePosition = 0;
  gameTimer = millis();
  gameState = STATE_RUN;
  gameCounter = 0;
}
