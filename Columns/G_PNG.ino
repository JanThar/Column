/* 
 *  Pong
 *  
 *  nur klicken um ball zu treffen -> IR-Distanzsensor (QS: Temperatur)
 *  
 *  Drehpoti entweder runterdrücken oder drehen in der Fläche
 *  bei aufprall richtung (Farbwechsel) und bewegung entlang streifen ändern
 *  apprallen an wänden oder kontinuirlich ändner (dann muss aber Poti durchdrehen)
 *  Eingestellte Farbe sollte in bestimmten bereich ähnlich sein
 *  Siegbedingung Anzahl treffer, jeder treffer beschleunigt
 */

#define COUNTER_PNG 3
#define COUNTUP_PNG 4
#define TOLERANCE_PNG 12

#define COLOR_PNG YELLOW_COLOR
#define DIR_PNG FIRETOP

void loop_PNG() {
  gamePosition += COUNTUP_PNG;
  check_IO();
  //if (gameInput == 0) check_distance();

  if (gameInput == 0) {
    toogleButton = true;
    switch(gameState) {
      case STATE_SLEEP:
        showSleep(COLOR_PNG);
        break;
      case STATE_RUN:
        runPNG(false);
        showComet(COLOR_PNG,gamePosition%(NUM_LEDS*2));
        break;
      case STATE_WIN:
        if(millis() > gameTimer+TIMEWIN) {
          flashColor(COLOR_PNG);
          gameState = STATE_SLEEP;
          showSleep(COLOR_PNG);
        }
        else showWinning(COLOR_PNG, DIR_PNG);
        break;
    }
  } else {
    switch(gameState) {
      case STATE_SLEEP:
        flashColor(COLOR_PNG);
        startPNG();
        break;
      case STATE_RUN:
        if (toogleButton) runPNG(true);
        else runPNG(false);
        showComet(COLOR_PNG,gamePosition%(NUM_LEDS*2));
        break;
      case STATE_WIN:
        startPNG();
        break; 
    }
    toogleButton = false;
  }
}

void runPNG(boolean buttonPressed) {
  if (buttonPressed) {
    if (gamePosition >= (2*NUM_LEDS - TOLERANCE_PNG)) { // pong  
      gameCounter++;
      gamePosition = 0;
    } else { // missed, restart
      flashColor(COLOR_PNG);
      gameState = STATE_SLEEP;
    }
  } else {
    if (gamePosition > 2*NUM_LEDS) { // ball leaves field
      flashColor(COLOR_PNG);
      gameState = STATE_SLEEP;
    }
  }
  if (gameCounter>COUNTER_PNG) {
    flashColor(COLOR_PNG);
    gameState = STATE_WIN;
    gamePosition = NUM_LEDS;
    gameTimer = millis();
    showWinning(COLOR_PNG, DIR_PNG);
  } 
}

void startPNG() {
  gamePosition = NUM_LEDS;
  gameCounter = 0;
  gameTimer = millis();
  gameState = STATE_RUN;
}
