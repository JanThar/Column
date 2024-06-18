/* 
 *  WhackAMole
 *  
 *  4 Segmente,  Encoder (QS: Magnetfeld)
 *  richtigen Button passend zu Segment drücken
 */

//#define COUNTER_MEM 1000
#define MEM_TIMER_ON 100
#define MEM_TIMER_OFF 10

#define COLOR_MEM WHITEVIOLETT_COLOR
#define DIR_MEM FIREBOTTOM

#define MEM_COUNT 5
#define MEM_SHOWLEDS 1000

#define STATE_SHOW   0
#define STATE_WAIT   1
#define STATE_IN     2

int displayState;

int mem_array[MEM_COUNT+1];

long timeSequence;
int counterSequence;
int counterReplay;

int lastButton =0;

void loop_MEM() {
  check_IO();
  if (gameInput != 0) {
    if (gameInput == lastButton) {
      gameInput = 0;
    } else {
      lastButton = gameInput;
    }
  } else {
    lastButton = 0; 
  }

  if (gameInput == 0) {
    switch(gameState) {
      case STATE_SLEEP:
        showSleep(COLOR_MEM);
        break;
      case STATE_RUN:
        if (millis() > gameTimer+TIMEALLOWED) {
          showSleep(COLOR_MEM);
          gameState = STATE_SLEEP;
        } else { // play game
          //if (counterSequence<MEM_COUNT) showSequence();
          //else showSegment(COLOR_MEM);
          runMEM();
        }
        break;
      case STATE_WIN:
        if(millis() > gameTimer+TIMEWIN) {
          flashColor(COLOR_MEM);
          gameState = STATE_SLEEP;
          showSleep(COLOR_MEM);
        }
        else showWinning(COLOR_MEM, DIR_MEM);
        break;
    }
  } else {
    switch(gameState) {
      case STATE_SLEEP:
        gameCounter = 0;
        flashColor(COLOR_MEM);
        startMEM();
        break;
      case STATE_RUN:
        runMEM();
        break;
      case STATE_WIN:
        startMEM();
        break; 
    }
  }
}

void showSequence() {
  for(int i=0; i<MEM_COUNT; i++) {
    timeSequence = millis();
    gamePosition=mem_array[i];
    while(millis() < timeSequence+MEM_SHOWLEDS) {
      showSegment(COLOR_MEM);
      delay(FLICKER);
    }
    timeSequence = millis();
    while(millis() < timeSequence+100) {
      showSegment(BLACK_COLOR);
      delay(FLICKER);
    }
  }
  gameTimer = millis();
  //counterSequence = MEM_COUNT;
  //gamePosition = 3;
}

void runMEM() {
  if (displayState == STATE_SHOW) {
    showSequence(); // play sequence, ignore buttons
    displayState = STATE_WAIT;
    lastButton = 0; 
  } else if (displayState == STATE_WAIT) {
    showSegment(BLACK_COLOR);
  } 
  if (gameInput != 0 && gameState !=STATE_WIN) { 
    int storeInput;
   if (gameInput==1) storeInput=4;
   if (gameInput==2) storeInput=3;
   if (gameInput==3) storeInput=2;
   if (gameInput==4) storeInput=1;
    displayState = STATE_IN;     
    Serial.print(gameInput);
    Serial.print(" : ");
    Serial.println(mem_array[counterReplay]);
    if (storeInput-1 == mem_array[counterReplay]) {
      //position ok
      Serial.println("Next Pos");
      gamePosition = storeInput-1;
      counterReplay++;
      Serial.println(counterReplay);
      if (counterReplay==MEM_COUNT) {// win 
        gameState = STATE_WIN;
        gameTimer = millis();
        Serial.println("Winning");
      }
    } else {
      Serial.println("Restart");
      flashColor(COLOR_MEM);
      startMEM();
      // wrong button, loose & restart
      
    }
  }
  if (displayState == STATE_IN) showSegment(COLOR_MEM);
}

void startMEM() {
  Serial.print("StartMEM ");
  counterSequence=0;
  counterReplay=0;
  timeSequence = millis();
  gameTimer = millis();

  for(int i=0; i<MEM_COUNT; i++){
    mem_array[i]=random8(SEGMENT_NUMBER);
    Serial.print(mem_array[i]);
    Serial.print(" ");
  }
  Serial.println();
  gamePosition=mem_array[0];
  gameState = STATE_RUN;
  displayState = STATE_SHOW;
}
