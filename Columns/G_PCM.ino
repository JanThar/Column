/* 
 *  1D-Pacman
 *  
 *  Up down entlang strip, left/right invertiert position (blockweise) Omnomnom...schmecken -> Gestensensor (QS: Partikel)
 *  
 *  spielfigur bewegen: links/recht invertiert position, up/down normalbewegung. genug Punkte sammeln für sieg
 *  standardgelbe punke, dicke powerups zum fressen, 4 gegner... nur fressen, nicht töten!
 *  
 *  nur eine farbe: Einzelpunkte ok, aber Monster ein problem
 */

#define COLOR_PCM ORANGE_COLOR
#define DIR_PCM FIREBOTTOM
#define TOLERANCE_PCM 20
#define NUMBER_MON 4
#define MAXSPEED 200

#define NUM_COOKIES 27
#define NUM_ADVERSARIES 2

int dirComet = FIREBOTTOM;

int pcm_speed_adv[NUM_ADVERSARIES]   = {};
float pcm_position_adv[NUM_ADVERSARIES] = {}; 
int pcm_position_food[NUM_COOKIES] = {}; 

void loop_PCM() {
  check_IO();
  //if (gameInput == 0) check_gesture();
  
  if(gameState == STATE_RUN) {
    update_PositionPCM();
    check_CollisionPCM();
  }
  
  if (gameInput == 0) {
    switch(gameState) {
      case STATE_SLEEP:
        showSleep(COLOR_PCM);
        break;
      case STATE_RUN:
        if (millis() > gameTimer+20000) {
          Serial.println("Timeout");
          showSleep(COLOR_PCM);
          gameState = STATE_SLEEP;
          showSleep(COLOR_PCM);
        }
        else {
          if (gameCounter<0) gameCounter = 0;
        }
        break;
      case STATE_WIN:
        if(millis() > gameTimer+TIMEWIN) {
          flashColor(COLOR_PCM);
          gameState = STATE_SLEEP;
          showSleep(COLOR_PCM);
        }
        else showWinning(COLOR_PCM, DIR_ADV);
        break;
    }
  } else {
    switch(gameState) {
      case STATE_SLEEP:
        flashColor(COLOR_PCM);
        startPCM();
        break;
      case STATE_RUN:
        gameTimer = millis();
        runPCM();
        break;
      case STATE_WIN:
        startPCM();
        break; 
    }
  }
}

void update_PositionPCM() {
  switch(gameInput) {
    case 3:
      gamePosition --;
      dirComet = FIREBOTTOM;
      break;
    case 2:
      gamePosition = (NUM_LEDS-1)-gamePosition;
      delay(100);
      break;
    case 1: // Jump, Sideways??
      gamePosition ++;
      dirComet = FIRETOP;
      break;
    case 4:
      break;
  }
  if (gamePosition<0) gamePosition = 0; //save zone
  if (gamePosition>NUM_LEDS-1) gamePosition = NUM_LEDS-1;
}

void check_CollisionPCM() {
  fireHeat(COMET);
  fire(dirComet,COLOR_PCM,gamePosition, COMET); //TOP or BOTTOM Spin

  for(int i=0; i<NUM_ADVERSARIES; i++) {
    if (pcm_speed_adv[i] == 0) {
      pcm_speed_adv[i] = random8(2*MAXSPEED)-MAXSPEED;
    } else if (pcm_speed_adv[i] > 0) {
      pcm_position_adv[i] += 0.3;
      pcm_speed_adv[i] --;
    } else {
      pcm_position_adv[i] -= 0.3;
      pcm_speed_adv[i] ++;
    }
    if (pcm_position_adv[i]<20) {
      pcm_position_adv[i] = 20;
      pcm_speed_adv[i] = -pcm_speed_adv[i];
    }
    if (pcm_position_adv[i]>NUM_LEDS-1) {
      pcm_position_adv[i] = NUM_LEDS-1;
      pcm_speed_adv[i] = -pcm_speed_adv[i];
    }
    
    pixel(COLOR_PCM, (int)(pcm_position_adv[i]), 180); 
    if (gamePosition == (int)(pcm_position_adv[i])) {
      flashColor(COLOR_PCM);
      gameTimer = millis();
      gamePosition=0;
    }
  }

  for(int i=0; i<NUM_COOKIES; i++) {
    if (gamePosition == pcm_position_food[i]) {
      pcm_position_food[i] = 300;
      gameCounter++;
    }
    if(pcm_position_food[i]<NUM_LEDS) pixel(COLOR_PCM, pcm_position_food[i], 30); 
  }

  FastLED.show();
  FastLED.delay(FLICKER);
}
     



void runPCM() {
  if (gameCounter == 27) {
    flashColor(COLOR_PCM);
    gameState = STATE_WIN;
    gameTimer = millis();
    showWinning(COLOR_PCM, DIR_PCM);
  } 
}

void startPCM() {
  for(int i=0; i<NUM_COOKIES; i++) pcm_position_food[i] = i*(NUM_LEDS/NUM_COOKIES);
  for(int i=0; i<NUM_ADVERSARIES; i++) {
    pcm_speed_adv[i] = random8(2*MAXSPEED)-MAXSPEED;
    pcm_position_adv[i] = random8(20,NUM_LEDS);
  }
  gamePosition = 0;
  gameTimer = millis();
  gameState = STATE_RUN;
  gameCounter = 0;
}
