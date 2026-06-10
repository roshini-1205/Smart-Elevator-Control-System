#include <LiquidCrystal.h>

// LCD Pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

// Buttons
const int floor1Btn = 2;
const int floor2Btn = 3;
const int floor3Btn = 4;
const int floor4Btn = 5;
const int emergencyBtn = 6;

// Buzzer
const int buzzer = 7;

// Current floor
int currentFloor = 1;

void setup() {
  lcd.begin(16, 2);

  pinMode(floor1Btn, INPUT_PULLUP);
  pinMode(floor2Btn, INPUT_PULLUP);
  pinMode(floor3Btn, INPUT_PULLUP);
  pinMode(floor4Btn, INPUT_PULLUP);
  pinMode(emergencyBtn, INPUT_PULLUP);

  pinMode(buzzer, OUTPUT);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Smart Elevator");
  lcd.setCursor(0, 1);
  lcd.print("Floor: 1");
  delay(2000);
}

void loop() {

  // Emergency Stop
  if (digitalRead(emergencyBtn) == LOW) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("EMERGENCY!");
    lcd.setCursor(0, 1);
    lcd.print("STOPPED");

    tone(buzzer, 1000);
    delay(1000);
    noTone(buzzer);

    while (digitalRead(emergencyBtn) == LOW);
    delay(300);

    displayFloor();
  }

  // Floor Requests
  if (digitalRead(floor1Btn) == LOW)
    moveToFloor(1);

  if (digitalRead(floor2Btn) == LOW)
    moveToFloor(2);

  if (digitalRead(floor3Btn) == LOW)
    moveToFloor(3);

  if (digitalRead(floor4Btn) == LOW)
    moveToFloor(4);
}

void moveToFloor(int targetFloor) {

  if (targetFloor == currentFloor)
    return;

  while (currentFloor < targetFloor) {

    currentFloor++;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Moving Up");
    lcd.setCursor(0, 1);
    lcd.print("Floor ");
    lcd.print(currentFloor);

    delay(2000);
  }

  while (currentFloor > targetFloor) {

    currentFloor--;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Moving Down");
    lcd.setCursor(0, 1);
    lcd.print("Floor ");
    lcd.print(currentFloor);

    delay(2000);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Reached");
  lcd.setCursor(0, 1);
  lcd.print("Floor ");
  lcd.print(currentFloor);

  tone(buzzer, 1500);
  delay(500);
  noTone(buzzer);

  delay(1500);

  displayFloor();
}

void displayFloor() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Elevator Ready");
  lcd.setCursor(0, 1);
  lcd.print("Floor ");
  lcd.print(currentFloor);
}