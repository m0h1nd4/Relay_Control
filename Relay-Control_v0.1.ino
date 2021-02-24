/*
 *  Follow The White Rabbit
 *  
 *  print on LCD
 *  
 */


// include the library code:

#include <LiquidCrystal.h>



// variabel

int relayPin1 = 23; // pin 23 for relay 1
int relayPin2 = 24; // pin 24 for relay 2
int relayPin3 = 25; // pin 25 for relay 3
int relayPin4 = 26; // pin 26 for relay 4
int t_X = 1000; // set time base
int rep = 10; // set repeat base
int anaX_t = 0; 

int anaX;


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// set UP

void setup() {

   // Initialize the output
   pinMode(relayPin1, OUTPUT);     
   pinMode(relayPin2, OUTPUT);
   pinMode(relayPin3, OUTPUT);
   pinMode(relayPin4, OUTPUT);
   
   // Serial start
   Serial.begin(115200);
   
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    
    // Print a message to the LCD.
    lcd.setCursor(0,0);
    lcd.print("Follow The White Rabbit!");
    delay(500);
    for (int positionCounter = 0; positionCounter < 8; positionCounter++) {
    
    //scroll one position left:
    lcd.scrollDisplayLeft();
    
    // wait a bit:
    delay(250);
  }
    delay(1000);
    lcd.clear();
    lcd.print("Rabbit Will");
    lcd.setCursor(0,1);
    lcd.print("Start To Run...!");    
    delay(2500);
    
    //lcd.print("LCD Key Shield");
    
    Serial.println("Knock... Knock... Wake Up... LCD Key Shield start");
    
    //lcd.setCursor(0,1);
    //lcd.clear();
    //lcd.print("Press Key:");
}

// boolean done=false;



// main Loop

void loop() {
  anaX = analogRead (0);
  
  //setTX();
  // lcd.print(anaX);

  if (anaX < 60) {
    t_X += 1000;
    delay(500);
    setTX();
  }
  else if (anaX < 200) {
    rep += 1;
    delay(500);
    setTX();
  }
  
  else if (anaX < 400) {
    rep -= 1;
    delay(500);
    setTX();
  }
 
  else if (anaX < 600) {
    t_X -= 1000;
    delay(500);
    setTX();
  }
  
  else if (anaX < 800){ 
    messstart();
  }
  
  

}

// void 

void setTX() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("time: ");
  lcd.setCursor(7,0);
  lcd.print(t_X/1000);
  lcd.print(" sec");
  lcd.setCursor(0,1);
  lcd.print("rounds: ");
  lcd.setCursor(8,1);
  lcd.print(rep);
  }

void messstart() {
  boolean done=false;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Rabbit Start");
  lcd.setCursor(0,1);
  lcd.print("Running... NOW!");
  delay(5000);
  lcd.clear();
    if (!done) { // Nur ausführen, wenn noch nicht ausgeführt
      digitalWrite(relayPin2, HIGH);  // Schaltet ein
      digitalWrite(relayPin3, HIGH);
      digitalWrite(relayPin4, HIGH);
      for (int x = 1; x <= rep; x++) {
         digitalWrite(relayPin1, HIGH);  // Schaltet ein
         lcd.setCursor(0,0);
         lcd.print("HIGH");
         lcd.setCursor(12,0);
         lcd.print(x);
         delay(t_X);
         lcd.clear();
         digitalWrite(relayPin1, LOW);   // Schaltet aus
         lcd.setCursor(0,1);
         lcd.print("LOW");
         lcd.setCursor(12,1);
         lcd.print(x);
         delay(t_X);
         lcd.clear();
      }
      done=true;
      digitalWrite(relayPin2, LOW);  // Schaltet aus
      lcd.print("Rabbit Is Gone...!");
      lcd.setCursor(0,1);
      lcd.print("Follow Again?!");
    } // loop !done
} 
