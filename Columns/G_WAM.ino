/* 
 *  WhackAMole
 *  
 *  4 Segmente,  Encoder (QS: Magnetfeld)
 *  richtigen Button passend zu Segment drücken
 */

#define COUNTER_WAM 1000
#define COUNTUP_WAM 100

#define COLOR_WAM DARKVIOLETT_COLOR
#define DIR_WAM FIRETOP

void loop_WAM() {
  check_IO();
  //if (gameInput == 0) check_rotary();

  if (gameInput == 0) {
    switch(gameState) {
      case STATE_SLEEP:
        showSleep(COLOR_WAM);
        break;
      case STATE_RUN:
        if (millis() > gameTimer+TIMEALLOWED) {
          showSleep(COLOR_WAM);
          gameState = STATE_SLEEP;
        }
        else {
          showSegment(COLOR_WAM);
          gameCounter -= COUNTDOWN;
          if (gameCounter<0) gameCounter = 0;
        }
        break;
      case STATE_WIN:
        if(millis() > gameTimer+TIMEWIN) {
          flashColor(COLOR_WAM);
          gameState = STATE_SLEEP;
          showSleep(COLOR_WAM);
        }
        else showWinning(COLOR_WAM, DIR_WAM);
        break;
    }
  } else {
    switch(gameState) {
      case STATE_SLEEP:
        gameCounter = 0;
        flashColor(COLOR_WAM);
        startWAM();
        break;
      case STATE_RUN:
        runWAM();
        break;
      case STATE_WIN:
        gameCounter = 0;
        startWAM();
        break; 
    }
  }
}

void runWAM() {
  int storeInput;
  if (gameInput==1) storeInput=4;
  if (gameInput==2) storeInput=3;
  if (gameInput==3) storeInput=2;
  if (gameInput==4) storeInput=1;
  if (storeInput == gamePosition+1) { // correct button
    gameCounter += COUNTUP_WAM;
    if (gameCounter >= COUNTER_WAM) {
      flashColor(COLOR_WAM);
      gameState = STATE_WIN;
      gameTimer = millis();
      showWinning(COLOR_WAM, FIRETOP);
    }
    else startWAM();
  } else {
    showSegment(COLOR_WAM);
  }
}

void startWAM() {
  gamePosition = random8(SEGMENT_NUMBER);
  gameTimer = millis();
  showSegment(COLOR_WAM);
  gameState = STATE_RUN;
}
