// ok 0 Ajna         WAM  WhackAMole - Abstandssensor infrarotbasiert -> QS Temperatur
// ok 1 Vishuddha    RCR  Racer - Multipayer?, möglichst schnell klicken -> QS Zeit
// ok 2 Manipura     PNG  Pong/Breakout - Drehung, Runde fläche, mit Fuss drehen. Encoder -> QS Magnetfeld
// ok 3 Anahata      ADV  Twang - Waagenfläche, 4 Taster (gefedert) als Gyrosimulator -> QS Gyroskop
// ok 4 Svadhisthana PCM  Pacman - Gestensensor, Minipunkt -> QS Partikel
// ok 5 Muladhara    HIGH Highstriker - Waage 30*30, Hx711 -> QS Gravitation
// -- 6 Sahasrara    MEM  Memory MindFlex - Gehirnstrom, (Funksensor) Mindflex, Seriell -> QS Elektro

int column = 5;

// Erklärung auf Bodenfläche Quantensensor -> Übertragung auf grosse Welt -> Spielbeschreibung
// Holz, davor Acryl beleuchtet??
// runde Fläche, 40cm Durchmesser

// A3 Analog
// XX XX Softwareserial -> Mindflex (besser wireless!!)

// 0x76 BME280 -> probably not usable
// 0x39 gesten
// 0x57 Pulse -> takes too much space for sampling, not contactless
// 0x29 Distanz
// 0x68 MPU
// ???? Temperature -> TMP 006 outdated

// General stuff
#include <FastLED.h>
//#include "I2Cdev.h"
//#include <Wire.h>
//#include <Adafruit_Sensor.h>
//#include <SoftwareSerial.h>
//#include <Brain.h>

// LEDs
#define LED_PIN       16

#define BTN_A         35 // schwarz
#define BTN_B         32 // grün
#define BTN_C         33 // weiss
#define BTN_D         14 // rot

#define NUM_LEDS    135 // 135
#define BRIGHTNESS  200

int cooling   =  55; // flame length, bigger number = shorter flame, range 20...100 //55
int sparkling = 170; // new sparks, lower number ? more flickering, range 50...200 //120

//#define ROT_A         3
//#define ROT_B         4
//#define ROT_C         5

// I2C:SDA           A4  
// I2C:SCL           A5 

//#define POTI         A2

//#define PRS_O        A0
//#define PRS_S        A1

//#define MISO         12
//#define MOSI         11
//#define SCK          13
//#define MCP2515_CS   10
//#define MCP2515_INT   2

//SoftwareSerial softSerial(2, 10);
//Brain brain(softSerial);

#define FIRETOP       0
#define FIREBOTTOM    1
#define FIREMIDDLE    2

#define TIMEOUT    1000
#define FLICKER      75

#define STATE_SLEEP   0 
#define STATE_RUN     1 
#define STATE_START   2
#define STATE_WIN     3

#define RED_COLOR 0          // Wurzel,   ich habe,    riechen,   Blumen/Barfuss,                    standhaltung/vorbeugen          // Highstriker
#define ORANGE_COLOR 1       // Sakral,   ich fühle,   schmecken, Musik/Malen/Schwimmen/Trinken,     Becken                          // Pacman
#define YELLOW_COLOR 2       // S.plexus, ich handle,  sehen,     Sonnenbad/Bauchatmung/Kerzenlicht, Drehungen                       // Pong
#define GREEN_COLOR 3        // Herz,     ich liebe,   berühren,  Natur/Lebewesen,                   Rückbeugen/Brust_öffnen         // WhackAMole
#define BLUE_COLOR 4         // Hals,     ich spreche, hören,     Singen/Schreiben,                  Kopfstand                       // Racer
#define DARKVIOLETT_COLOR 5  // Stirn,    ich sehe,    sehen,     Fantasie/Traumtagebuch,            Essen/Fasten                    // Adventure
#define WHITEVIOLETT_COLOR 6 // Krone,    ich weiss,   einfühlen, Weite                              Aussicht/verneigen/respektieren // Brain
#define BLACK_COLOR 7        // Black

#define TIMEALLOWED 10000
#define TIMEWIN 5000

#define SEGMENT_NUMBER 4
#define SEGMENT NUM_LEDS/SEGMENT_NUMBER
#define COMET 10

#define COUNTDOWN 1

int gameState = 0;
long gameTimer = 0;
int gameInput = 0;
long gameCounter = 0;
int gamePosition = 0;

boolean toogleButton = false;

// I2C scanner
//#include "I2CScanner.h"
//I2CScanner scanner;

void setup() {
  delay(1000); // sanity delay
  
  Serial.begin(9600); // MindFlex
  //softSerial.begin(9600);
  //Wire.begin(); // other sensors

  start_LED();
  start_IO();
  //start_rotary();
  //start_distance();
  //start_gesture();
  //start_pressure();

  gameState = STATE_SLEEP;
  gameTimer = millis();
  gameCounter = 0;
  gamePosition = NUM_LEDS;

  //scanner.Init();
}

void loop() {
//  if (digitalRead(BTN_COLUMN) == 0) {
//    column++;
//    gameState = STATE_SLEEP;
//    gameTimer = millis();
//    gameCounter = 0;
//    gamePosition = NUM_LEDS;
//    delay(100);
//  }
//  if (column==7) column = 0;
  // 0 WAM  4 Buttons
  // 1 RCR  1 Buttons
  // 2 PNG  1 Buttons
  // 3 ADV  2 Buttons
  // 4 PCM  3 Buttons
  // 5 HIGH 1 Buttons
  // 6 MEM  4 Buttons
  //Serial.println(column);
  //test_LED();
  
  //test_IO();
  //test_gesture();
  //test_distance();
  //test_pulse();
  //test_pressure();
  //test_rotary();
  
  //scanner.Scan();

  switch (column) {
    case 0:
      loop_WAM();
      break;
    case 1:
      loop_RCR();
      break;
    case 2:
      loop_PNG();
      break;
    case 3:
      loop_ADV();
      break;
    case 4:
      loop_PCM();
      break;
    case 5:
      loop_HIGH();
      break;
    case 6:
      loop_MEM();
      break;
  }
  
//  Serial.print("GamePosition: ");
//  Serial.print(gamePosition);
//  Serial.print(" GameInput: ");
//  Serial.print(gameInput);
//  Serial.print(" GameState: ");
//  Serial.print(gameState);
//  Serial.print(" Counter: ");
//  Serial.print(gameCounter);
//  Serial.print(" GameTimer: ");
//  Serial.println(millis() - gameTimer);

}
