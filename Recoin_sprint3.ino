#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int counter = 0;

int charges = 0;
int recoins = 0;
float SREC = 0.0000;
const int chargePin = 7;
const int startDrive = 8;
const int endDrive = 9;
int cP_state = 0;
int sD_state = 0;
int eD_state = 0;
int power = 0;
int totalPower =0;

byte block[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};

void setup() {
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  pinMode(chargePin, INPUT);
  pinMode(startDrive, INPUT);
  pinMode(endDrive, INPUT);
  
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("hello, world!");
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  // read the state of pushbuttons
  cP_state = digitalRead(chargePin);
  sD_state = digitalRead(startDrive);

  if (cP_state == HIGH) {
    lcd.clear();
    lcd.createChar(0, block);
    lcd.begin(16,2);
    lcd.setCursor(4,0);
    lcd.print("Charging");
    lcd.setCursor(0,1);

    for (int i = 0; i <= 16; i++)  {
    lcd.write(byte(0));
    delay(300);
    }
    charges = charges +1;    // increment charges count
    power = 32;              // fills up the power in the car
    totalPower = totalPower + 32;
    //SREC = SREC + 32/1000;
    printLog(); 
  }
  if (sD_state == HIGH) {
    if (power == 0) {
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("No Power");
    lcd.setCursor(4,1);
    lcd.print("Go Charge!");
    printLog();
    delay(3000);
    goto exit;
    }
    lcd.clear();
    lcd.createChar(0, block);
    lcd.begin(16,2);
    lcd.setCursor(4,0);
    lcd.print("Driving");

    lcd.setCursor(0,1);
    for (int j = 0; j <= 16; j++)  {
        eD_state = digitalRead(endDrive);
        power = power - 2;                  //FIX POWER calculation
        if (power == 0) {
        lcd.clear();
        lcd.setCursor(1,0);
        lcd.print("NoPower,Charge!");
        lcd.setCursor(3,1);
        lcd.print(j*7);
        lcd.print(" Recoins");
        recoins = recoins +j*7;
        printLog();
        delay(3000);
        goto exit;
        }
        
        if (eD_state == HIGH) {
        lcd.clear();
        lcd.setCursor(3,0);
        lcd.print("Drive Ended");
        lcd.setCursor(3,1);
        lcd.print(j*7);
        lcd.print(" Recoins");
        recoins = recoins + j*7; //add to recoins made
        printLog();
        delay(3000);
        goto exit;
    }
    lcd.write(byte(0));
    delay(600);
    }
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Drive Ended");
    lcd.setCursor(3,2);
    lcd.print("112 Recoins");
    recoins = recoins + 112;    // add to recount balance
    printLog();
    delay(3000);
  }
  else {
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("Charge");
    lcd.setCursor(4,1);
    lcd.print("or Drive");
    
    /*
    lcd.setCursor(1,1);
    lcd.createChar(0, block);
    lcd.begin(16,2);
    for (int i = 0; i <= 16; i++)  {
    lcd.write(byte(0));
    delay(300);
    */
    
  }
  exit:
  //lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  //lcd.print(millis() / 1000);
  //printLog();
  delay(100);

  
}

void printLog()
{
  String json = "{ \"charges\": ";
  json += charges;
  json += ",\"power\": ";
  json += power;
  json += ", \"recoins\": ";
  json += recoins; 
  json += ", \"srec\": ";
  json += totalPower;
  json += "}";
  
  //+ charges + ", power: " + power + ", recoins: " + recoins + ", SREC: " + totalPower + "}";
 Serial.println(json);
 /*
   Serial.print("Charges: ");
   Serial.println(charges);
   Serial.print("Power: ");
   Serial.println(power);
   Serial.print("Recoinds Mined: ");
   Serial.println(recoins);
   Serial.print("SREC: ");
   Serial.println(totalPower);
*/
}

