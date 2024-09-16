#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address may vary
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

byte rowPins[ROWS] = { 2, 3, 4, 5 };
byte colPins[COLS] = { 12, 7, 8, 13 };

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

struct User {
  String id;
  String password;
  bool active;  // A flag to indicate if the user is active or deleted
};

User users[] = {
  { "2001", "A87B", true },
  { "2002", "C34D", true },
  { "2003", "B11B", true },
  { "2004", "D0A1", true },
  { "2005", "32B0", true },
  { "2006", "9D23", true },
  { "2007", "7C9A", true },
  { "2008", "5AB2", true },
  { "2009", "146D", true },
  { "2010", "0C85", true },
  { "2011", "B123", true },
  { "2012", "C456", true },
  { "2013", "A789", true },
  { "2014", "DABC", true },
  { "2015", "D7B1", true },
  { "2016", "D83C", true },
  { "2017", "A92C", true },
  { "2018", "CB40", true },
  { "2019", "CA92", true },
  { "2020", "2345", true },
 
 
  

};

const int Wled = 10;
const int Rled = 6;
const int Gled = 9;
const int Bled = 11;


String currentUserId = "";
String currentPassword = "";

int partyVotes[10] = { 0 };



void blink() {
  analogWrite(Bled, 32);
  analogWrite(Rled, 32);
  analogWrite(Gled, 32);
  analogWrite(Wled, 32);
  delay(100);
  analogWrite(Bled, 0);
  analogWrite(Rled, 0);
  analogWrite(Gled, 0);
  analogWrite(Wled, 0);
  delay(100);
}
void green() {
  analogWrite(Gled, 255);
  delay(3000);
  analogWrite(Gled, 0);
}

void setup() {

  lcd.init();
  lcd.backlight();
  pinMode(Wled, OUTPUT);
  pinMode(Gled, OUTPUT);
  pinMode(Rled, OUTPUT);
  pinMode(Bled, OUTPUT);
  blink();
  blink();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter your ID:");
  lcd.setCursor(0, 1);
}

void loop() {
  char key = keypad.getKey();

  if (key != NO_KEY) {
    if (key == '#') {
      authenticateUser();
    } else {
      if (currentUserId.length() < 16) {  // Limit the ID length
        currentUserId += key;
        lcd.print(key);
      }
    }
  }
}

void authenticateUser() {
  bool flag = false;
  // currentUserId.trim();
  for (int i = 0; i < sizeof(users) / sizeof(users[0]); i++) {


    if ((currentUserId) == "008") {
      analogWrite(Wled, 32);
      int maxVotes = -1;         // Initialize maxVotes to a value less than zero
      int winningParty = -1;     // Initialize the winningParty to a value less than zero
      bool tie = false;          // Initialize a flag for a tie to false
      bool tieWithNota = false;  // Initialize a flag for a tie with NOTA to false

      // Loop through all the parties to find the one with the most votes
      for (int i = 9; i >= 0; i--) {
        if (partyVotes[i] > maxVotes) {
          maxVotes = partyVotes[i];
          winningParty = i;
          tie = false;          // Reset the tie flag since a new winner is found
          tieWithNota = false;  // Reset the tie with NOTA flag
        } else if (partyVotes[i] == maxVotes) {
          tie = true;  // There's a tie among multiple parties
          if (i == 0) {
            tieWithNota = true;  // The tie involves NOTA
          }
        }
      }
      // Check the conditions and display the election result
      lcd.clear();
      lcd.setCursor(0, 0);

      if (tie) {
        if (tieWithNota) {
          lcd.setCursor(0, 0);
          lcd.print("   Tie With  ");
          lcd.setCursor(0, 1);
          lcd.print("   NOTA  ");
          delay(2000);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("  Re-Election!!");
        } else {
          lcd.setCursor(0, 0);
          lcd.print(" Tie among ");
          lcd.setCursor(0, 1);
          lcd.print(" candidates ");
          delay(2000);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("  Re-Election!!");
        }
      } else if (winningParty == 0) {
        lcd.setCursor(0, 0);
        lcd.print("  NOTA wins!");
        lcd.setCursor(0, 1);
        lcd.print(" Re-Election ");
        delay(2000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("ALL Candidates");
        lcd.setCursor(0, 1);
        lcd.print(" Are Rejected ");

      } else if (maxVotes > partyVotes[0]) {
        lcd.print("Party ");
        switch (winningParty) {
          case 0:
            lcd.print("NOTA Wins!!");
            delay(3000);
            break;
          case 1:
            lcd.print("BJP Wins!!");
            delay(3000);
            break;
          case 2:
            lcd.print("INC Wins!!");
            delay(3000);
            break;
          case 3:
            lcd.print("SP Wins!!");
            delay(3000);
            break;
          case 4:
            lcd.print("AAP Wins!!");
            delay(3000);
            break;
          case 5:
            lcd.print("DMK Wins!!");
            delay(3000);
            break;
          case 6:
            lcd.print("BSP Wins!!");
            delay(3000);
            break;
          case 7:
            lcd.print("CPI Wins!!");
            delay(3000);
            break;
          case 8:
            lcd.print("AP Wins!!");
            delay(3000);
            break;
          case 9:
            lcd.print("JDU Wins!!");
            delay(3000);
            break;
        }


      } else {
        lcd.print("No clear winner");
      }

      delay(3000);  // Display the result for 3 seconds
      analogWrite(Wled, 0);
      lcd.clear();
      break;
    }




    if ((currentUserId) == "007") {
      flag = true;
      lcd.clear();
      analogWrite(Wled, 32);
      lcd.setCursor(0, 0);
      lcd.print("BJP-");
      lcd.print(partyVotes[1]);
      lcd.print("  INC-");
      lcd.print(partyVotes[2]);
      lcd.setCursor(0, 1);
      lcd.print("SP -");
      lcd.print(partyVotes[3]);
      lcd.print("  AAP-");
      lcd.print(partyVotes[4]);
      delay(3000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("DMK-");
      lcd.print(partyVotes[5]);
      lcd.print("  BSP-");
      lcd.print(partyVotes[6]);
      lcd.setCursor(0, 1);
      lcd.print("CPI-");
      lcd.print(partyVotes[7]);
      lcd.print("  AP-");
      lcd.print(partyVotes[8]);
      delay(3000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("JDU-");
      lcd.print(partyVotes[9]);
      lcd.print("  NOTA-");
      lcd.print(partyVotes[0]);
      delay(3000);
      analogWrite(Wled, 0);
      lcd.clear();
      break;
    }
    if (users[i].active && users[i].id == currentUserId) {
      digitalWrite(Bled,32);
      delay(300);
      digitalWrite(Bled,0);

      flag == true;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Enter password:");
      lcd.setCursor(0, 1);
      String enteredPassword = "";
      while (true) {
        char key = keypad.getKey();
        if (key != NO_KEY) {
          if (key == '#') {
            if (enteredPassword == users[i].password) {

              lcd.clear();
              analogWrite(Bled, 32);
              lcd.setCursor(0, 0);
              lcd.print("Access granted!");
              delay(1000);
              analogWrite(Bled, 0);
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("Your Vote Matters, Please Cast Your Vote");
              for (int i = 0; i < 24; i++) {
                lcd.scrollDisplayLeft();
                delay(350);
              }
              delay(1000);
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("1-BJP 2-INC 3-SP");
              lcd.setCursor(0, 1);
              lcd.print("  4-AAP 5-DMK   ");
              delay(3000);
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("6-BSP 7-CPI 8-AP");
              lcd.setCursor(0, 1);
              lcd.print("  9-JDU 0-NOTA");
              delay(3000);
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("Enter Party no:");
              lcd.setCursor(0, 1);
              char partyKey = keypad.getKey();
              while (partyKey < '0' || partyKey > '9') {
                partyKey = keypad.getKey();
              }
              lcd.print(partyKey);
              delay(500);
              int partyNumber = partyKey - '0';
              if (partyNumber >= 0 && partyNumber <= 9) {
                partyVotes[partyNumber]++;
                lcd.setCursor(0, 1);
                lcd.print("Voted for: ");
                switch (partyNumber) {
                  case 0:
                    lcd.print("NOTA");
                    green();
                    break;
                  case 1:
                    lcd.print("BJP");
                    green();
                    break;
                  case 2:
                    lcd.print("INC");
                    green();
                    break;
                  case 3:
                    lcd.print("SP");
                    green();
                    break;
                  case 4:
                    lcd.print("AAP");
                    green();
                    break;
                  case 5:
                    lcd.print("DMK");
                    green();
                    break;
                  case 6:
                    lcd.print("BSP");
                    green();
                    break;
                  case 7:
                    lcd.print("CPI");
                    green();
                    break;
                  case 8:
                    lcd.print("AP");
                    green();
                    break;
                  case 9:
                    lcd.print("JDU");
                    green();
                    break;
                }

                lcd.clear();
                lcd.print("Thank You");
                lcd.setCursor(0, 1);
                lcd.print("For Voting!!!");
                delay(3000);
                lcd.clear();
              }

              // Call removeUser function after access is granted
              removeUser(currentUserId);

            } else {
              lcd.clear();
              lcd.setCursor(0, 0);
              analogWrite(Rled, 32);
              lcd.print("Access denied!");
              delay(2000);
              analogWrite(Rled, 0);
            }
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Enter your ID:");
            lcd.setCursor(0, 1);
            currentUserId = "";
            break;
          } else {
            if (enteredPassword.length() < 16) {  // Limit the password length
              enteredPassword += key;
              lcd.print('*');  // Mask the password
            }
          }
        }
      }
      break;
    }
  }

  if (flag == 0) {
    lcd.clear();
    analogWrite(Rled, 32);
    // lcd.print("Invalid ID");
    delay(500);
    analogWrite(Rled, 0);
  }

  // Clear the current ID and reset the state
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter your ID:");
  lcd.setCursor(0, 1);
  currentUserId = "";
}

void removeUser(String userId) {
  for (int i = 0; i < sizeof(users) / sizeof(users[0]); i++) {
    if (users[i].id == userId) {
      // Mark the user as inactive (deleted)
      users[i].active = false;
      break;
    }
  }
}
