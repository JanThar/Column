/*
 * LED Output
 * 
 * particle punkt in farbe aus palette, schweif aus abdunkelnden farben (flickern)
 * Achtung: wendung am ende, start mit dunkelster Farbe als erstes zeichen wegen überschreiben mit hellen Farben am Ende
 * 1) Lichtsegmente WhackaMole: Mittelbereich, auslauf zu beiden seiten. Breite Segement, Position, eine Farbe reicht
 * 2) Racer: Lichtpunkt, bewegen in beide Richtungen?, eine Farbe
 * 3) Pong: Lichtpunkt als Farbanzeige unten, bewegter Lichtpunkt Spielpunkt, Regenbogenfarbe
 * 4) Brain: gesamter bereich, analog zu flamme, 4 Streifen, je 2 Farben?, Sparkling, alle farben
 * 5) Highstriker: Lichtlinie bewegen, Höhe ändern, 1 Farbe
 * 6) Adventure: Lichtpunkt Spielfigur bewegen rauf/runter, Pendel seitwärts (nur ein Punkt, ausblenden "seitwärts"), gruben auslaufende farbe(zu zwei seiten) 1 farbe Spieler, 1 Farbe Pendel, ggfs 1 Farbe Gruben
 * 7) Pacman: Lichtpunkt als Spielfigur, Einzellichtpunkte zum Essen (2 helligkeitsstufen), Monster (2 farben im Wechsel) -> 1 Farbe Spieler, 2 Farben Monster, 1 Farbe Essen
 */

#define COLOR_ORDER GRB
#define CHIPSET     WS2812

CRGBPalette16 basePalette[] = {
  CRGBPalette16( CRGB::Black, 0x200000, CRGB::Red, CRGB::MistyRose), // rot ok 0xFF0000
  CRGBPalette16( CRGB::Black, 0x201000, CRGB::OrangeRed, CRGB::Moccasin), // orange ok 0xFF4500
  CRGBPalette16( CRGB::Black, 0x202000, CRGB::Yellow, CRGB::LightYellow), // gelb ok 0xFFFF00
  CRGBPalette16( CRGB::Black, 0x002000, CRGB::DarkGreen, CRGB::MediumSeaGreen), // grün ok 0x006400
  CRGBPalette16( CRGB::Black, 0x000020, CRGB::Blue, CRGB::LightSkyBlue), // blau ok 0x0000FF
  CRGBPalette16( CRGB::Black, 0x050020, 0x200064, CRGB::MediumPurple), // dunkelviolett ?? 0x200064
  CRGBPalette16( CRGB::Black, 0x200020, CRGB::DarkMagenta, CRGB::Amethyst), // weissviolett ok 0x8B008B
  CRGBPalette16( CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black), //off
  RainbowColors_p
};

CRGB leds[NUM_LEDS];
CRGBPalette16 gPal;

void start_LED() {
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );
}

void test_LED() {
  random16_add_entropy(esp_random());
  for(int i=0;i<7;i++) { // Farbwechsel
    //for(int j=0;j<NUM_LEDS;j++) { // Durchlauf Position
      for(int k=0; k<60; k++) { // Flicker
        fireHeat(NUM_LEDS); // update Heat
        //fire(FIRETOP,2,j, 10); 
        //fire(FIREMIDDLE,2,j, 10); 
        //fire(FIREBOTTOM,3,NUM_LEDS-j, 10); 
        fire(FIREBOTTOM,i,0, NUM_LEDS); 
        FastLED.show();
        FastLED.delay(100);
      //}
    }
  } 
}

static byte heat[NUM_LEDS];

void fireHeat(int fireLength) {
  // Step 1.  Cool down every cell a little
  for(int i = 0; i < fireLength; i++) {
    heat[i] = qsub8( heat[i],  random8(0, ((cooling * 10) / fireLength) + 2));
  }

  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for( int k= fireLength - 1; k >= 1; k--) {
    heat[k] = (heat[k-1] + heat[k-2] + heat[k - 2]) / 3;
  }
  
  // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
  if( random8() < sparkling ) {
    int y = random8(fireLength/5+1);
    heat[y] = qadd8( heat[y], random8(160,255) );
  }
}

void fire(int fireDirection, int fireColor, int firePosition, int fireLength) {
  // Step 4.  Map from heat cells to LED colors
  for(int l=0; l<NUM_LEDS; l++) {
    leds[l] = CRGB::Black;
  }
  for( int j=0; j<fireLength; j++) {
    byte colorindex = scale8( heat[j], 240);
    CRGB color = ColorFromPalette( basePalette[fireColor], colorindex);
    int pixelnumber;
    if( fireDirection == FIRETOP ) { 
      pixelnumber = firePosition - j;
      if (pixelnumber >= 0) leds[pixelnumber] = color;
      else if (pixelnumber < 0 && -pixelnumber > firePosition) leds[-pixelnumber] = color;
    } else if ( fireDirection == FIREBOTTOM ) {
      pixelnumber = firePosition+j; 
      if (pixelnumber < NUM_LEDS) leds[pixelnumber] = color;
      else if (pixelnumber > NUM_LEDS-1 && -pixelnumber+2*NUM_LEDS-1 < firePosition) leds[-pixelnumber+2*NUM_LEDS-1] = color;
    } else if ( fireDirection == FIREMIDDLE ) { 
      if (j%2==0) pixelnumber = firePosition+j/2;    
      else        pixelnumber = firePosition-(j+1)/2;
      if(pixelnumber >=0 && pixelnumber < NUM_LEDS) leds[pixelnumber] = color;
    }
  }
}

void pixel(int pixelColor, int pixelPosition, int pixelIndex) {
  leds[pixelPosition] = ColorFromPalette( basePalette[pixelColor], pixelIndex);
}

void showSegment(int gameColor) {
  fireHeat(SEGMENT); // update Heat
  fire(FIREMIDDLE,gameColor,gamePosition*SEGMENT+SEGMENT/2, SEGMENT); //TOP or BOTTOM Spin
  FastLED.show();
  FastLED.delay(FLICKER);
}

void showWinning(int gameColor, int winningDirection) {
  fireHeat(NUM_LEDS); // update Heat
  fire(winningDirection,gameColor,0, NUM_LEDS); //TOP or BOTTOM Spin
  FastLED.show();
  FastLED.delay(FLICKER);
}

void flashColor(int pixelColor) {
  for(int k=0; k<25; k++) {
    for(int l=0; l<NUM_LEDS; l++) {
      leds[l] = ColorFromPalette(basePalette[pixelColor], k*4);
    }
    FastLED.show();
    FastLED.delay(FLICKER/10);
  }
  for(int k=25; k>=0; k--) {
    for(int l=0; l<NUM_LEDS; l++) {
      leds[l] = ColorFromPalette(basePalette[pixelColor], k*4);
    }
    FastLED.show();
    FastLED.delay(FLICKER/10);
  }
}

void showNothing() {
  for(int l=0; l<NUM_LEDS; l++) {
    leds[l] = CRGB::Black;
  }
  FastLED.show();
  FastLED.delay(FLICKER);
}

void showSleep(int gameColor) {
  fireHeat(NUM_LEDS); // update Heat
  fire(FIREMIDDLE,gameColor,NUM_LEDS/2, NUM_LEDS); 
  FastLED.show();
  FastLED.delay(FLICKER);
}

void showComet(int gameColor, int positionComet) {
  fireHeat(COMET); // update Heat
  if (positionComet > NUM_LEDS-1) fire(FIREBOTTOM,gameColor,NUM_LEDS*2-positionComet-1, COMET); //TOP or BOTTOM Spin
  else fire(FIRETOP,gameColor,positionComet, COMET); //TOP or BOTTOM Spin
  FastLED.show();
  FastLED.delay(FLICKER);
}

void showCometMod(int gameColor, int positionComet) {
  fireHeat(COMET); // update Heat
  if (positionComet > NUM_LEDS-1) fire(FIREBOTTOM,gameColor,NUM_LEDS*2-positionComet-1, COMET); //TOP or BOTTOM Spin
  else fire(FIRETOP,gameColor,positionComet, COMET); //TOP or BOTTOM Spin
}

// particle
// punkt in farbe aus palette, schweif aus abdunkelnden farben (flickern)
// achtung: wendung am ende, start mit dunkelster Farbe als erstes zeichen wegen überschreiben mit hellen Farben am Ende
// 1) Lichtsegmente WhackaMole: Mittelbereich, auslauf zu beiden seiten. Breite Segement, Position, eine Farbe reicht
// 2) Racer: Lichtpunkt, bewegen in beide Richtungen?, eine Farbe
// 3) Pong: Lichtpunkt als Farbanzeige unten, bewegter Lichtpunkt Spielpunkt, Regenbogenfarbe
// 4) Brain: gesamter bereich, analog zu flamme, 4 Streifen, je 2 Farben?, Sparkling, alle farben
// 5) Highstriker: Lichtlinie bewegen, Höhe ändern, 1 Farbe
// 6) Adventure: Lichtpunkt Spielfigur bewegen rauf/runter, Pendel seitwärts (nur ein Punkt, ausblenden "seitwärts"), gruben auslaufende farbe(zu zwei seiten) 1 farbe Spieler, 1 Farbe Pendel, ggfs 1 Farbe Gruben
// 7) Pacman: Lichtpunkt als Spielfigur, Einzellichtpunkte zum Essen (2 helligkeitsstufen), Monster (2 farben im Wechsel) -> 1 Farbe Spieler, 2 Farben Monster, 1 Farbe Essen
