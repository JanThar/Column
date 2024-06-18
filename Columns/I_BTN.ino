/* 
 *  Buttons
 */
 
int button_pin[] = {BTN_A, BTN_B, BTN_C, BTN_D};
int debounceNumber = 20;

void start_IO() {
  for (int i=0; i<4; i++) {
    pinMode(button_pin[i], INPUT_PULLUP);
  }
}

void test_IO() {
  Serial.print("Buttons: ");
  for (int i=0; i<4; i++) {
    Serial.print(digitalRead(button_pin[i]));
    Serial.print("  ");
  }
//  Serial.print("  Poti: ");
//  Serial.println(analogRead(POTI));
}

void check_IO() { // 3 Buttons
  gameInput = 0;
  for (int i=0; i<debounceNumber; i++) { // debounce
    for (int i=0; i<4; i++) {
      //if (digitalRead(button_pin[i])==1) gameInput = i+1;//inverted buttons
      if (!digitalRead(button_pin[i])) gameInput = i+1;//inverted buttons
    }
  }
}
