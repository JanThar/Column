/*                                                   
 *    Racer                                           
 *    
 *    möglichst schnell klicken zum punkt bewegen (Button, QS: Zeitmessung)
 *    schnell genug klicken um Spitze zu erreichen                                               
 */                                                    

#define COUNTER_RCR NUM_LEDS*1
#define COUNTUP_RCR 4

#define COLOR_RCR BLUE_COLOR
#define DIR_RCR FIREBOTTOM

void loop_RCR() {
  check_IO();

  if (gameInput == 0) {
    toogleButton = true;
    switch(gameState) {
      case STATE_SLEEP:
        showSleep(COLOR_RCR);
        break;
      case STATE_RUN:
        if (millis() > gameTimer+TIMEALLOWED) {
          showSleep(COLOR_RCR);
          gameState = STATE_SLEEP;
        }
        else {
          showComet(COLOR_RCR,gameCounter);
          gameCounter -= COUNTDOWN;
          if (gameCounter<0) gameCounter = 0;
        }
        break;
      case STATE_WIN:
        if(millis() > gameTimer+TIMEWIN) {
          flashColor(COLOR_RCR);
          gameState = STATE_SLEEP;
          showSleep(COLOR_RCR);
        }
        else showWinning(COLOR_RCR, DIR_RCR);
        break;
    }
  } else {
    switch(gameState) {
      case STATE_SLEEP:
        flashColor(COLOR_RCR);
        gameCounter = 0;
        startRCR();
        break;
      case STATE_RUN:
        runRCR();
        break;
      case STATE_WIN:
        gameCounter = 0;
        startRCR();
        break; 
    }
    toogleButton = false;
  }
}

void runRCR() {
  if (toogleButton) gameCounter += COUNTUP_RCR;
  gameTimer = millis();
  if (gameCounter>COUNTER_RCR) {
    flashColor(COLOR_RCR);
    gameState = STATE_WIN;
    showWinning(COLOR_RCR, FIRETOP);
  } else {
    showComet(COLOR_RCR,gameCounter);
  }
} 

void startRCR() {
  gameTimer = millis();
  gameState = STATE_RUN;
}
