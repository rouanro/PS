//#include <Time.h>
#include <TimeLib.h>

#include <LiquidCrystal.h>
#include <EEPROM.h>

#define EEPROM_MSG_ADR 100

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(6, 7, 8, 9, 10, 11); /// REGISTER SELECT PIN,ENABLE PIN,D4 PIN,D5 PIN, D6 PIN, D7 PIN

// this constant won't change:
const int  buttonPin1 = 2;    // the pin that the pushbutton1 is attached to
const int  buttonPin2 = 3;    // the pin that the pushbutton2 is attached to
const int  back = 4;
const int up = 5;
const int ledPin = 13;       // the pin that the LED is attached to
int cnt = 0;
int nr_i = 0;
int cnt_i = 0;

// Variables will change:
int opt = 1;   // counter for the number of button presses
int buttonPushCounter = 1;
int buttonState1 = 0;         // current state of the button
int buttonState2 = 0;
int backState = 0;
int upState = 0;
int lastButtonState1 = 0;     // previous state of the button
int lastButtonState2 = 0;
int lastBackState = 0;
int lastUpState = 0;
int cs = 0;
int select = 0;
int control = 1;
int temp;

char operation; // Holds operation (R, W, ...)
char mode; // Holds the mode (D, A)
int pin_number; // Holds the pin number
int digital_value; // Holds the digital value
int analog_value; // Holds the analog value
int value_to_write; // Holds the value that we want to write
int wait_for_transmission = 5; // Delay in ms in order to receive the serial data
char a[30];
int i, j;
int ok = 0;

//Counters to change positions of pages and sub-menus
String string ="";
int readData=0;
int memSize= 1024;
int id;
char chArray[50]="";
int counter=0;
int currentCharIdx = 0;

typedef struct message{
  char mesaj[10];
  bool flag=0;
}Message_t;

typedef struct eeprMsg {
  Message_t mesaje[10];
  int index;
}eeprMsg_t;

eeprMsg_t mesajeEeprom;
eeprMsg_t mesajeEeprom_i;

void inundatii(void)
{
  //Serial.print("Index: ");
  //Serial.println(mesajeEeprom.index);
  lcd.setCursor(0, 0);
  lcd.print(opt);
  lcd.print(":");
  lcd.setCursor(0, 1);
  lcd.print(mesajeEeprom_i.mesaje[opt].mesaj);

  //////////////Menu cycle button
  
      // read the pushbutton input pin:
      buttonState1 = digitalRead(buttonPin1);

      // compare the buttonState1 to its previous state
      if (buttonState1 != lastButtonState1) {
        // if the state has changed, increment the counter
        if (buttonState1 == HIGH) {
          // if the current state is HIGH then the button went from off to on:
          opt++;
          lcd.clear();
          if(opt == 10)
          {
            opt = 0;
          }
          //Serial.println("on");
          //Serial.print("number of button pushes: ");
          //Serial.println(opt);
        } else {
          // if the current state is LOW then the button went from on to off:
          //Serial.println("off");
        }
        // Delay a little bit to avoid bouncing
        delay(50);
      }
      // save the current state as the last state, for next time through the loop
      lastButtonState1 = buttonState1;

      //////////////

      //////////////Menu cycle button
  
      // read the pushbutton input pin:
      upState = digitalRead(up);

      // compare the buttonState1 to its previous state
      if (upState != lastUpState) {
        // if the state has changed, increment the counter
        if (upState == HIGH) {
          // if the current state is HIGH then the button went from off to on:
          opt--;
          lcd.clear();
          if(opt == -1)
          {
            opt = 9;
          }
          //Serial.println("on");
          //Serial.print("number of button pushes: ");
          //Serial.println(opt);
        } else {
          // if the current state is LOW then the button went from on to off:
          //Serial.println("off");
        }
        // Delay a little bit to avoid bouncing
        delay(50);
      }
      // save the current state as the last state, for next time through the loop
      lastUpState = upState;

      //////////////
  
  /////////////Back

      backState = digitalRead(back);

      // compare the buttonState1 to its previous state
      if (backState != lastBackState) {
        // if the state has changed, increment the counter
        if (backState == HIGH) {
          // if the current state is HIGH then the button went from off to on:
          opt = 1;
          lcd.clear();
          select = 0;
          //Serial.println("on");
          //Serial.print("number of button pushes: ");
          //Serial.println(opt);
        } else {
          // if the current state is LOW then the button went from on to off:
          //Serial.println("off");
        }
        // Delay a little bit to avoid bouncing
        delay(50);
      }
      // save the current state as the last state, for next time through the loop
      lastBackState = backState;

} /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void debugMsg_stergere(void)
{
  //Serial.print("Index: ");
  //Serial.println(mesajeEeprom.index);
  lcd.setCursor(0, 0);
  lcd.print(opt);
  lcd.print(":");
  lcd.setCursor(0, 1);
  lcd.print(mesajeEeprom.mesaje[opt].mesaj);

  //////////////Menu cycle button
  
      // read the pushbutton input pin:
      buttonState1 = digitalRead(buttonPin1);

      // compare the buttonState1 to its previous state
      if (buttonState1 != lastButtonState1) {
        // if the state has changed, increment the counter
        if (buttonState1 == HIGH) {
          // if the current state is HIGH then the button went from off to on:
          opt++;
          lcd.clear();
          if(opt == 10)
          {
            opt = 0;
          }
          //Serial.println("on");
          //Serial.print("number of button pushes: ");
          //Serial.println(opt);
        } else {
          // if the current state is LOW then the button went from on to off:
          //Serial.println("off");
        }
        // Delay a little bit to avoid bouncing
        delay(50);
      }
      // save the current state as the last state, for next time through the loop
      lastButtonState1 = buttonState1;

      //////////////

      //////////////Menu cycle button
  
      // read the pushbutton input pin:
      upState = digitalRead(up);

      // compare the buttonState1 to its previous state
      if (upState != lastUpState) {
        // if the state has changed, increment the counter
        if (upState == HIGH) {
          // if the current state is HIGH then the button went from off to on:
          opt--;
          lcd.clear();
          if(opt == -1)
          {
            opt = 9;
          }
          //Serial.println("on");
          //Serial.print("number of button pushes: ");
          //Serial.println(opt);
        } else {
          // if the current state is LOW then the button went from on to off:
          //Serial.println("off");
        }
        // Delay a little bit to avoid bouncing
        delay(50);
      }
      // save the current state as the last state, for next time through the loop
      lastUpState = upState;

      //////////////
  
  /////////////Back

      backState = digitalRead(back);

      // compare the buttonState1 to its previous state
      if (backState != lastBackState) {
        // if the state has changed, increment the counter
        if (backState == HIGH) {
          // if the current state is HIGH then the button went from off to on:
          opt = 1;
          lcd.clear();
          select = 1;
          //Serial.println("on");
          //Serial.print("number of button pushes: ");
          //Serial.println(opt);
        } else {
          // if the current state is LOW then the button went from on to off:
          //Serial.println("off");
        }
        // Delay a little bit to avoid bouncing
        delay(50);
      }
      // save the current state as the last state, for next time through the loop
      lastBackState = backState;

      //////////////

      buttonState2 = digitalRead(buttonPin2);

      // compare the buttonState1 to its previous state
      if (buttonState2 != lastButtonState2) {
        // if the state has changed, increment the counter
        if (buttonState2 == HIGH) {
          // if the current state is HIGH then the button went from off to on:
          lcd.clear();
          memset(mesajeEeprom.mesaje[opt].mesaj, 0, sizeof(mesajeEeprom.mesaje[opt].mesaj));
          mesajeEeprom.mesaje[opt].flag = false;
          select = 1;
        } else {
          // if the current state is LOW then the button went from on to off:
          //Serial.println("off");
        }
        // Delay a little bit to avoid bouncing
        delay(50);
      }
      // save the current state as the last state, for next time through the loop
      lastButtonState2 = buttonState2;

      //////////////
}

void debugMsg_necitite(void)
{
  int i = 0;
  int j = 0;
  int v[10];
  int m;
  //Serial.print("Index: ");
  //Serial.println(mesajeEeprom.index);
  memset(v, 0, sizeof(v));
  for (i = 0; i < 10; i++)
  {
    if(mesajeEeprom.mesaje[i].flag == false)
    {
      v[j] = i;
      j++;
    }
    //Serial.print(i); Serial.print(": ");
    //lcd.print(mesajeEeprom.mesaje[i].mesaj);
    //lcd.print(" ");
  }
  m = j;
  if(j == 0)
    select = 1;
  lcd.setCursor(0, 0);
  lcd.print(v[opt]);
  lcd.print(":");
  lcd.setCursor(0, 1);
  lcd.print(mesajeEeprom.mesaje[v[opt]].mesaj);

  //////////////Menu cycle button
  
      // read the pushbutton input pin:
      buttonState1 = digitalRead(buttonPin1);

      // compare the buttonState1 to its previous state
      if (buttonState1 != lastButtonState1) {
        // if the state has changed, increment the counter
        if (buttonState1 == HIGH) {
          // if the current state is HIGH then the button went from off to on:
          opt++;
          lcd.clear();
          if(opt == m)
          {
            opt = 0;
          }
          //Serial.println("on");
          //Serial.print("number of button pushes: ");
          //Serial.println(opt);
        } else {
          // if the current state is LOW then the button went from on to off:
          //Serial.println("off");
        }
        // Delay a little bit to avoid bouncing
        delay(50);
      }
      // save the current state as the last state, for next time through the loop
      lastButtonState1 = buttonState1;

      //////////////

      //////////////Menu cycle button
  
      // read the pushbutton input pin:
      upState = digitalRead(up);

      // compare the buttonState1 to its previous state
      if (upState != lastUpState) {
        // if the state has changed, increment the counter
        if (upState == HIGH) {
          // if the current state is HIGH then the button went from off to on:
          opt--;
          lcd.clear();
          if(opt == -1)
          {
            opt = m;
          }
          //Serial.println("on");
          //Serial.print("number of button pushes: ");
          //Serial.println(opt);
        } else {
          // if the current state is LOW then the button went from on to off:
          //Serial.println("off");
        }
        // Delay a little bit to avoid bouncing
        delay(50);
      }
      // save the current state as the last state, for next time through the loop
      lastUpState = upState;

      //////////////
  
  /////////////Back

      backState = digitalRead(back);

      // compare the buttonState1 to its previous state
      if (backState != lastBackState) {
        // if the state has changed, increment the counter
        if (backState == HIGH) {
          // if the current state is HIGH then the button went from off to on:
          opt = 1;
          lcd.clear();
          select = 1;
          //Serial.println("on");
          //Serial.print("number of button pushes: ");
          //Serial.println(opt);
        } else {
          // if the current state is LOW then the button went from on to off:
          //Serial.println("off");
        }
        // Delay a little bit to avoid bouncing
        delay(50);
      }
      // save the current state as the last state, for next time through the loop
      lastBackState = backState;

      //////////////

      buttonState2 = digitalRead(buttonPin2);

      // compare the buttonState1 to its previous state
      if (buttonState2 != lastButtonState2) {
        // if the state has changed, increment the counter
        if (buttonState2 == HIGH) {
          // if the current state is HIGH then the button went from off to on:
          mesajeEeprom.mesaje[v[opt]].flag = true;
          //debugMsg();
          select = 1;
        } else {
          // if the current state is LOW then the button went from on to off:
          //Serial.println("off");
        }
        // Delay a little bit to avoid bouncing
        delay(50);
      }
      // save the current state as the last state, for next time through the loop
      lastButtonState2 = buttonState2;

      //////////////
}

void debugMsg_citite(void)
{
  int i = 0;
  int j = 0;
  int v[10];
  int m;
  //Serial.print("Index: ");
  //Serial.println(mesajeEeprom.index);
  memset(v, 0, sizeof(v));
  for (i = 0; i < 10; i++)
  {
    if(mesajeEeprom.mesaje[i].flag == true)
    {
      v[j] = i;
      j++;
    }
    //Serial.print(i); Serial.print(": ");
    //lcd.print(mesajeEeprom.mesaje[i].mesaj);
    //lcd.print(" ");
  }
  m = j;
  if(j == 0)
    select = 1;
  else
  {
  lcd.setCursor(0, 0);
  lcd.print(v[opt]);
  lcd.print(":");
  lcd.setCursor(0, 1);
  lcd.print(mesajeEeprom.mesaje[v[opt]].mesaj);

  //////////////Menu cycle button
  
      // read the pushbutton input pin:
      buttonState1 = digitalRead(buttonPin1);

      // compare the buttonState1 to its previous state
      if (buttonState1 != lastButtonState1) {
        // if the state has changed, increment the counter
        if (buttonState1 == HIGH) {
          // if the current state is HIGH then the button went from off to on:
          opt++;
          lcd.clear();
          if(opt == m)
          {
            opt = 0;
          }
          //Serial.println("on");
          //Serial.print("number of button pushes: ");
          //Serial.println(opt);
        } else {
          // if the current state is LOW then the button went from on to off:
          //Serial.println("off");
        }
        // Delay a little bit to avoid bouncing
        delay(50);
      }
      // save the current state as the last state, for next time through the loop
      lastButtonState1 = buttonState1;

      //////////////

      //////////////Menu cycle button
  
      // read the pushbutton input pin:
      upState = digitalRead(up);

      // compare the buttonState1 to its previous state
      if (upState != lastUpState) {
        // if the state has changed, increment the counter
        if (upState == HIGH) {
          // if the current state is HIGH then the button went from off to on:
          opt--;
          lcd.clear();
          if(opt == -1)
          {
            opt = m;
          }
          //Serial.println("on");
          //Serial.print("number of button pushes: ");
          //Serial.println(opt);
        } else {
          // if the current state is LOW then the button went from on to off:
          //Serial.println("off");
        }
        // Delay a little bit to avoid bouncing
        delay(50);
      }
      // save the current state as the last state, for next time through the loop
      lastUpState = upState;

      //////////////
  
  /////////////Back

      backState = digitalRead(back);

      // compare the buttonState1 to its previous state
      if (backState != lastBackState) {
        // if the state has changed, increment the counter
        if (backState == HIGH) {
          // if the current state is HIGH then the button went from off to on:
          opt = 1;
          lcd.clear();
          select = 1;
          //Serial.println("on");
          //Serial.print("number of button pushes: ");
          //Serial.println(opt);
        } else {
          // if the current state is LOW then the button went from on to off:
          //Serial.println("off");
        }
        // Delay a little bit to avoid bouncing
        delay(50);
      }
      // save the current state as the last state, for next time through the loop
      lastBackState = backState;

      //////////////
  }
}

///////////////////////////////////////////PYTHON////////////////////////////////////////////////////////////////////////////

void set_pin_mode(int pin_number, char mode){
    /*
     * Performs a pinMode() operation depending on the value of the parameter
     * mode :
     * - I: Sets the mode to INPUT
     * - O: Sets the mode to OUTPUT
     * - P: Sets the mode to INPUT_PULLUP
     */

    switch (mode){
        case 'I':
            pinMode(pin_number, INPUT);
            break;
        case 'O':
            pinMode(pin_number, OUTPUT);
            break;
        case 'P':
            pinMode(pin_number, INPUT_PULLUP);
            break;
    }
}

void digital_read(int pin_number){
    /*
     * Performs a digital read on pin_number and returns the value read to serial
     * in this format: D{pin_number}:{value}\n where value can be 0 or 1
     */

    digital_value = digitalRead(pin_number);
    Serial.print('D');
    Serial.print(pin_number);
    Serial.print(':');
    Serial.println(digital_value); // Adds a trailing \n
}

void analog_read(int pin_number){
    /*
     * Performs an analog read on pin_number and returns the value read to serial
     * in this format: A{pin_number}:{value}\n where value ranges from 0 to 1023
     */
    if(pin_number == 0)
    {
      analog_value = 5*analogRead(pin_number)*100/1024;
      Serial.print('A');
      Serial.print(pin_number);
      Serial.print(':');
      Serial.print(analog_value); // Adds a trailing \n
    }
    else
    {
      if(pin_number == 4)
      {
        //analog_value = analogRead(pin_number);
        Serial.print('A');
        Serial.print(pin_number);
        Serial.print(':');
        Serial.print(nr_i);
        //Serial.print(analog_value); // Adds a trailing \n
        nr_i = 0;
      }
    }
}

void digital_write(int pin_number, int digital_value){
    /*
     * Performs a digital write on pin_number with the digital_value
     * The value must be 1 or 0
     */
  digitalWrite(pin_number, digital_value);
}

void analog_write(int pin_number, int analog_value){
    /*
   * Performs an analog write on pin_number with the analog_value
   * The value must be range from 0 to 255
     */
  analogWrite(pin_number, analog_value);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void meniuMesaj()
{
  if(opt == 1)
      {
        lcd.setCursor(0, 0); // set the cursor to column 0, line 1
        lcd.print("1.1 Necitite");
        lcd.setCursor(0, 1); // set the cursor to column 0, line 2
        lcd.print("1.2 Citite");
      }
      if(opt == 2)
      {
        lcd.setCursor(0, 0); // set the cursor to column 0, line 1
        lcd.print("1.2 Citite");
        lcd.setCursor(0, 1); // set the cursor to column 0, line 2
        lcd.print("1.3 Stergere");
      }
      if(opt == 3)
      {
        lcd.setCursor(0, 0); // set the cursor to column 0, line 1
        lcd.print("1.3 Stergere");
        lcd.setCursor(0, 1); // set the cursor to column 0, line 2
        lcd.print("1.1 Necitite");
      }
      //////////////Menu cycle button
  
      // read the pushbutton input pin:
      buttonState1 = digitalRead(buttonPin1);

      // compare the buttonState1 to its previous state
      if (buttonState1 != lastButtonState1) {
        // if the state has changed, increment the counter
        if (buttonState1 == HIGH) {
          // if the current state is HIGH then the button went from off to on:
          opt++;
          lcd.clear();
          if(opt == 4)
          {
            opt = 1;
          }
          //Serial.println("on");
          //Serial.print("number of button pushes: ");
          //Serial.println(opt);
        } else {
          // if the current state is LOW then the button went from on to off:
          //Serial.println("off");
        }
        // Delay a little bit to avoid bouncing
        delay(50);
      }
      // save the current state as the last state, for next time through the loop
      lastButtonState1 = buttonState1;

      //////////////

      //////////////Menu cycle button
  
      // read the pushbutton input pin:
      upState = digitalRead(up);

      // compare the buttonState1 to its previous state
      if (upState != lastUpState) {
        // if the state has changed, increment the counter
        if (upState == HIGH) {
          // if the current state is HIGH then the button went from off to on:
          opt--;
          lcd.clear();
          if(opt == 0)
          {
            opt = 3;
          }
          //Serial.println("on");
          //Serial.print("number of button pushes: ");
          //Serial.println(opt);
        } else {
          // if the current state is LOW then the button went from on to off:
          //Serial.println("off");
        }
        // Delay a little bit to avoid bouncing
        delay(50);
      }
      // save the current state as the last state, for next time through the loop
      lastUpState = upState;

      //////////////

      /////////////Back

      backState = digitalRead(back);

      // compare the buttonState1 to its previous state
      if (backState != lastBackState) {
        // if the state has changed, increment the counter
        if (backState == HIGH) {
          // if the current state is HIGH then the button went from off to on:
          opt = 1;
          lcd.clear();
          select = 0;
          //Serial.println("on");
          //Serial.print("number of button pushes: ");
          //Serial.println(opt);
        } else {
          // if the current state is LOW then the button went from on to off:
          //Serial.println("off");
        }
        // Delay a little bit to avoid bouncing
        delay(50);
      }
      // save the current state as the last state, for next time through the loop
      lastBackState = backState;

      //////////////

      buttonState2 = digitalRead(buttonPin2);

      // compare the buttonState1 to its previous state
      if (buttonState2 != lastButtonState2) {
        // if the state has changed, increment the counter
        if (buttonState2 == HIGH) {
          // if the current state is HIGH then the button went from off to on:
          if(opt == 1)
          {
            for (i = 0; i < 10; i++)
            {
              if(mesajeEeprom.mesaje[i].flag == true)
              {
                opt = i;
                break;
              }
            }
            lcd.clear();
            select = 5;
          }
          if(opt == 2)
          {
            for (i = 0; i < 10; i++)
            {
              if(mesajeEeprom.mesaje[i].flag == true)
              {
                opt = i;
                break;
              }
            }
            lcd.clear();
            select = 6;
          }
          if(opt == 3)
          {
            opt = 0;
            lcd.clear();
            select = 7;
          }
        } else {
          // if the current state is LOW then the button went from on to off:
          //Serial.println("off");
        }
        // Delay a little bit to avoid bouncing
        delay(50);
      }
      // save the current state as the last state, for next time through the loop
      lastButtonState2 = buttonState2;

      //////////////
}

void meniuControl()
{
  if(opt == 1 && control == 1)
      {
        lcd.setCursor(0, 0); // set the cursor to column 0, line 1
        lcd.print("2.1 Manual [x]");
        lcd.setCursor(0, 1); // set the cursor to column 0, line 2
        lcd.print("2.2 Automat");
      }
      if(opt == 2 && control == 1)
      {
        lcd.setCursor(0, 0); // set the cursor to column 0, line 1
        lcd.print("2.2 Automat");
        lcd.setCursor(0, 1); // set the cursor to column 0, line 2
        lcd.print("2.1 Manual [x]");
      }
      if(opt == 1 && control == 2)
      {
        lcd.setCursor(0, 0); // set the cursor to column 0, line 1
        lcd.print("2.1 Manual");
        lcd.setCursor(0, 1); // set the cursor to column 0, line 2
        lcd.print("2.2 Automat [x]");
      }
      if(opt == 2 && control == 2)
      {
        lcd.setCursor(0, 0); // set the cursor to column 0, line 1
        lcd.print("2.2 Automat [x]");
        lcd.setCursor(0, 1); // set the cursor to column 0, line 2
        lcd.print("2.1 Manual");
      }
      //////////////Menu cycle button
  
      // read the pushbutton input pin:
      buttonState1 = digitalRead(buttonPin1);

      // compare the buttonState1 to its previous state
      if (buttonState1 != lastButtonState1) {
        // if the state has changed, increment the counter
        if (buttonState1 == HIGH) {
          // if the current state is HIGH then the button went from off to on:
          opt++;
          lcd.clear();
          if(opt == 3)
          {
            opt = 1;
          }
          //Serial.println("on");
          //Serial.print("number of button pushes: ");
          //Serial.println(opt);
        } else {
          // if the current state is LOW then the button went from on to off:
          //Serial.println("off");
        }
        // Delay a little bit to avoid bouncing
        delay(50);
      }
      // save the current state as the last state, for next time through the loop
      lastButtonState1 = buttonState1;

      //////////////

      //////////////Menu cycle button
  
      // read the pushbutton input pin:
      upState = digitalRead(up);

      // compare the buttonState1 to its previous state
      if (upState != lastUpState) {
        // if the state has changed, increment the counter
        if (upState == HIGH) {
          // if the current state is HIGH then the button went from off to on:
          opt--;
          lcd.clear();
          if(opt == 0)
          {
            opt = 2;
          }
          //Serial.println("on");
          //Serial.print("number of button pushes: ");
          //Serial.println(opt);
        } else {
          // if the current state is LOW then the button went from on to off:
          //Serial.println("off");
        }
        // Delay a little bit to avoid bouncing
        delay(50);
      }
      // save the current state as the last state, for next time through the loop
      lastUpState = upState;

      //////////////

      buttonState2 = digitalRead(buttonPin2);

      // compare the buttonState1 to its previous state
      if (buttonState2 != lastButtonState2) {
        // if the state has changed, increment the counter
        if (buttonState2 == HIGH) {
          // if the current state is HIGH then the button went from off to on:
          if(opt == 1)
          {
            lcd.clear();
            control = 1;
          }
          if(opt == 2)
          {
            lcd.clear();
            control = 2;
          }
        } else {
          // if the current state is LOW then the button went from on to off:
          //Serial.println("off");
        }
        // Delay a little bit to avoid bouncing
        delay(50);
      }
      // save the current state as the last state, for next time through the loop
      lastButtonState2 = buttonState2;

      //////////////

      /////////////Back

      backState = digitalRead(back);

      // compare the buttonState1 to its previous state
      if (backState != lastBackState) {
        // if the state has changed, increment the counter
        if (backState == HIGH) {
          // if the current state is HIGH then the button went from off to on:
          opt = 1;
          lcd.clear();
          select = 0;
          //Serial.println("on");
          //Serial.print("number of button pushes: ");
          //Serial.println(opt);
        } else {
          // if the current state is LOW then the button went from on to off:
          //Serial.println("off");
        }
        // Delay a little bit to avoid bouncing
        delay(50);
      }
      // save the current state as the last state, for next time through the loop
      lastBackState = backState;

      //////////////
}

void temperatura()
{
  lcd.setCursor(0, 0); // set the cursor to column 0, line 1
  lcd.print("Temperatura:");
  lcd.setCursor(0, 1); // set the cursor to column 0, line 2
  temp = 5*analogRead(A0)*100/1024;
  lcd.print(temp);
  /////////////Back

      backState = digitalRead(back);

      // compare the buttonState1 to its previous state
      if (backState != lastBackState) {
        // if the state has changed, increment the counter
        if (backState == HIGH) {
          // if the current state is HIGH then the button went from off to on:
          opt = 1;
          lcd.clear();
          select = 0;
          //Serial.println("on");
          //Serial.print("number of button pushes: ");
          //Serial.println(opt);
        } else {
          // if the current state is LOW then the button went from on to off:
          //Serial.println("off");
        }
        // Delay a little bit to avoid bouncing
        delay(50);
      }
      // save the current state as the last state, for next time through the loop
      lastBackState = backState;

      //////////////
}

void meniuInundatii()
{
  lcd.setCursor(0, 0); // set the cursor to column 0, line 1
  lcd.print("inuntatie 1");
  lcd.setCursor(0, 1); // set the cursor to column 0, line 2
  lcd.print("inundatie 2...");
  debugMsg_i();

  /////////////Back

      backState = digitalRead(back);

      // compare the buttonState1 to its previous state
      if (backState != lastBackState) {
        // if the state has changed, increment the counter
        if (backState == HIGH) {
          // if the current state is HIGH then the button went from off to on:
          opt = 1;
          lcd.clear();
          select = 0;
          //Serial.println("on");
          //Serial.print("number of button pushes: ");
          //Serial.println(opt);
        } else {
          // if the current state is LOW then the button went from on to off:
          //Serial.println("off");
        }
        // Delay a little bit to avoid bouncing
        delay(50);
      }
      // save the current state as the last state, for next time through the loop
      lastBackState = backState;

      //////////////
}

void meniuDefault()
{
      if(opt == 1)
      {
        lcd.setCursor(0, 0); // set the cursor to column 0, line 1
        lcd.print("1. Mesaje");
        lcd.setCursor(0, 1); // set the cursor to column 0, line 2
        lcd.print("2. Control");
      }
      if(opt == 2)
      {
        lcd.setCursor(0, 0); // set the cursor to column 0, line 1
        lcd.print("2. Control");
        lcd.setCursor(0, 1); // set the cursor to column 0, line 2
        lcd.print("3. Temperatura");
      }
      if(opt == 3)
      {
        lcd.setCursor(0, 0); // set the cursor to column 0, line 1
        lcd.print("3. Temperatura");
        lcd.setCursor(0, 1); // set the cursor to column 0, line 2
        lcd.print("4. Inundatii");
      }
      if(opt == 4)
      {
        lcd.setCursor(0, 0); // set the cursor to column 0, line 1
        lcd.print("4. Inundatii");
        lcd.setCursor(0, 1); // set the cursor to column 0, line 2
        lcd.print("1. Mesaje");
      }

      //////////////Menu cycle button
  
      // read the pushbutton input pin:
      buttonState1 = digitalRead(buttonPin1);

      // compare the buttonState1 to its previous state
      if (buttonState1 != lastButtonState1) {
        // if the state has changed, increment the counter
        if (buttonState1 == HIGH) {
          // if the current state is HIGH then the button went from off to on:
          opt++;
          lcd.clear();
          if(opt == 5)
          {
            opt = 1;
          }
          //Serial.println("on");
          //Serial.print("number of button pushes: ");
          //Serial.println(opt);
        } else {
          // if the current state is LOW then the button went from on to off:
          //Serial.println("off");
        }
        // Delay a little bit to avoid bouncing
        delay(50);
      }
      // save the current state as the last state, for next time through the loop
      lastButtonState1 = buttonState1;

      //////////////

      //////////////Menu cycle button
  
      // read the pushbutton input pin:
      upState = digitalRead(up);

      // compare the buttonState1 to its previous state
      if (upState != lastUpState) {
        // if the state has changed, increment the counter
        if (upState == HIGH) {
          // if the current state is HIGH then the button went from off to on:
          opt--;
          lcd.clear();
          if(opt == 0)
          {
            opt = 4;
          }
          //Serial.println("on");
          //Serial.print("number of button pushes: ");
          //Serial.println(opt);
        } else {
          // if the current state is LOW then the button went from on to off:
          //Serial.println("off");
        }
        // Delay a little bit to avoid bouncing
        delay(50);
      }
      // save the current state as the last state, for next time through the loop
      lastUpState = upState;

      //////////////
      
      buttonState2 = digitalRead(buttonPin2);

      // compare the buttonState1 to its previous state
      if (buttonState2 != lastButtonState2) {
        // if the state has changed, increment the counter
        if (buttonState2 == HIGH) {
          // if the current state is HIGH then the button went from off to on:
          if(opt == 1)
          {
            opt = 1;
            lcd.clear();
            select = 1;
          }
          if(opt == 2)
          {
            opt = 1;
            lcd.clear();
            select = 2;
          }
          if(opt == 3)
          {
            opt = 1;
            lcd.clear();
            select = 3;
          }
          if(opt == 4)
          {
            opt = 1;
            lcd.clear();
            select = 4;
          }
        } else {
          // if the current state is LOW then the button went from on to off:
          //Serial.println("off");
        }
        // Delay a little bit to avoid bouncing
        delay(50);
      }
      // save the current state as the last state, for next time through the loop
      lastButtonState2 = buttonState2;

      //////////////

        /////////////Back

      backState = digitalRead(back);

      // compare the buttonState1 to its previous state
      if (backState != lastBackState) {
        // if the state has changed, increment the counter
        if (backState == HIGH) {
          // if the current state is HIGH then the button went from off to on:
          opt = 1;
          lcd.clear();
          select = 8;
          //Serial.println("on");
          //Serial.print("number of button pushes: ");
          //Serial.println(opt);
        } else {
          // if the current state is LOW then the button went from on to off:
          //Serial.println("off");
        }
        // Delay a little bit to avoid bouncing
        delay(50);
      }
      // save the current state as the last state, for next time through the loop
      lastBackState = backState;

      //////////////
}

void blocat()
{
  int i = 0;
  int j = 0;
  int v[10];
  int m;
  memset(v, 0, sizeof(v));
  for (i = 0; i < 10; i++)
  {
    if(mesajeEeprom.mesaje[i].flag == false)
    {
      v[j] = i;
      j++;
    }
  }
  lcd.setCursor(5, 0); // set the cursor to column 0, line 1
  lcd.print(hour());
  lcd.setCursor(7,0);
  lcd.print(":");
  lcd.setCursor(8,0);
  lcd.print(minute());
  lcd.setCursor(0,1);
  temp = 5*analogRead(A0)*100/1024;
  lcd.print(temp);
  lcd.setCursor(2,1);
  lcd.print("`C");
  lcd.setCursor(7, 1); // set the cursor to column 0, line 1
  lcd.print(j);
  lcd.setCursor(10, 1); // set the cursor to column 0, line 1
  lcd.print("mesaje");
          /////////////Back

      backState = digitalRead(back);

      // compare the buttonState1 to its previous state
      if (backState != lastBackState) {
        // if the state has changed, increment the counter
        if (backState == HIGH) {
          // if the current state is HIGH then the button went from off to on:
          if(opt == 1)
          {
            opt++;
          }
          else
          {
            if(opt == 3)
            {
              opt++;
            }
            else
              opt = 1;
          }
          //Serial.println("on");
          //Serial.print("number of button pushes: ");
          //Serial.println(opt);
        } else {
          // if the current state is LOW then the button went from on to off:
          //Serial.println("off");
        }
        // Delay a little bit to avoid bouncing
        delay(50);
      }
      // save the current state as the last state, for next time through the loop
      lastBackState = backState;

      //////////////

      //////////////
      
      buttonState2 = digitalRead(buttonPin2);

      // compare the buttonState1 to its previous state
      if (buttonState2 != lastButtonState2) {
        // if the state has changed, increment the counter
        if (buttonState2 == HIGH) {
          // if the current state is HIGH then the button went from off to on:
          if(opt == 2)
          {
            opt++;
          }
          else
          {
            if(opt == 4)
            {
              opt = 1;
              lcd.clear();
              select = 0;
            }
            else
              opt = 1;
          }
        } else {
          // if the current state is LOW then the button went from on to off:
          //Serial.println("off");
        }
        // Delay a little bit to avoid bouncing
        delay(50);
      }
      // save the current state as the last state, for next time through the loop
      lastButtonState2 = buttonState2;

      //////////////
}

void debugMsg(void)
{
  int i =0;
  Serial.print("Index: ");
  Serial.println(mesajeEeprom.index);
  for (i =0; i<10; i++)
  {
    Serial.print(i); Serial.print(": ");
    Serial.println(mesajeEeprom.mesaje[i].mesaj);
    Serial.println(mesajeEeprom.mesaje[i].flag);
  }
}

void debugMsg_i(void)
{
  int i =0;
  Serial.print("Index: ");
  Serial.println(mesajeEeprom_i.index);
  for (i =0; i<10; i++)
  {
    Serial.print(i); Serial.print(": ");
    Serial.println(mesajeEeprom_i.mesaje[i].mesaj);
  }
}

void setup()
{
  Serial.begin(9600);
  // set up the LCD’s number of columns and rows:
  lcd.begin(16, 2);
  // initialize the button pin as a input:
  pinMode(buttonPin1, INPUT);
  // initialize the LED as an output:
  pinMode(ledPin, OUTPUT);
  EEPROM.get(EEPROM_MSG_ADR, mesajeEeprom);
  setTime(16,21,30,29,5,2018);

  //debugMsg();
}




void loop()
{
  if(cnt_i = 400)
  {
    if(analogRead(4) > 950)
    {
      nr_i++;
      if(nr_i == 500)
      {
        int nr_afis = nr_i / 500;
      char myConcatenation[14];
    char myCharArray[7]="Inun: ";
    sprintf(myConcatenation,"%s = %i",myCharArray,nr_afis);
      strncpy(mesajeEeprom_i.mesaje[mesajeEeprom_i.index].mesaj, myConcatenation, sizeof(myConcatenation)-1);
      mesajeEeprom_i.index++;
      memset(myConcatenation, 0, sizeof(myConcatenation));
      EEPROM.put(EEPROM_MSG_ADR, mesajeEeprom_i);
      //debugMsg();
      currentCharIdx=0;
      }
    }
    cnt_i = 0;
  }
  if(mesajeEeprom_i.index >=10)
    {
      mesajeEeprom_i.index = 0;
    }
  if(control == 2 && cnt == 200)
  {
    if(digitalRead(13) == HIGH)
      digitalWrite(13, LOW);
    else
      digitalWrite(13, HIGH);
    cnt = 0;
  }
  if(control == 2)
  {
    cnt++;
  }
  if(mesajeEeprom.index >=10)
    {
      mesajeEeprom.index = 0;
    }
  lcd.setCursor(0, 0); // set the cursor to column 0, line 1
  i = 0;
  if(Serial.available() > 0)
  {
    while((a[i] = Serial.read()) != -1)
    {
      lcd.clear();
      i++;
      delay(5);
      ok = 1;
    }
    if(ok == 1)
    {
      a[i] = '.';
      i++;
      for(j = 0; j < i; j++)
      {
        if(a[j] == 'R')
        {
          if(a[j+1] == 'A')
          {
            if(a[j+2] == '0')
              analog_read(0);
            else
            {
              if(a[j+2] == '4')
                analog_read(4);
            }
          }
        }
        else
        {
          if(control == 1)
          {
            if(a[j] == 'o')
            {
              if(a[j+1] == 'n')
                digitalWrite(13, HIGH);
              else
              {
                if(a[j+1] == 'f')
                {
                  if(a[j+2] == 'f')
                    digitalWrite(13, LOW);
                }
              }
            }
          }
            if (a[j]=='\n' || a[j]=='\r')
            {
            //skip new line characters
            }
            else if (a[j]!='.')
            {
              chArray[currentCharIdx++] = a[j];
            }
            else
            {
              strncpy(mesajeEeprom.mesaje[mesajeEeprom.index].mesaj, chArray, sizeof(chArray)-1);
              mesajeEeprom.index++;
              memset(chArray, 0, sizeof(chArray));
              EEPROM.put(EEPROM_MSG_ADR, mesajeEeprom);
              //debugMsg();
              currentCharIdx=0;
            }
        }
      }
        ok = 0;
        memset(a, 0, sizeof(a));
    }
  }
  if(select == 0)
  {
    meniuDefault();
  }
  if(select == 1)
  {
    meniuMesaj();
  }
  if(select == 2)
  {
    meniuControl();
  }
  if(select == 3)
  {
    temperatura();
  }
  if(select == 4)
  {
    inundatii();
  }
  if(select == 5)
  {
    debugMsg_necitite();
  }
  if(select == 6)
  {
    debugMsg_citite();
  }
  if(select == 7)
  {
    debugMsg_stergere();
  }
  if(select == 8)
  {
    blocat();
  }
}
