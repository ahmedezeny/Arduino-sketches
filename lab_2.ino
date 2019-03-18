//Sample using LiquidCrystal library
#include <LiquidCrystal.h>

/*******************************************************

  This program will test the LCD panel and the buttons
  Mark Bramwell, July 2010

********************************************************/

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

struct ALU_Driver {
    int a=0;
    int b=0;
    byte opcode : 3;

};

// read the buttons
int read_LCD_buttons()
{
    adc_key_in = analogRead(0);      // read the value from the sensor
    if (adc_key_in > 1000) return btnNONE;
    if (adc_key_in < 100) return btnRIGHT;
    if (adc_key_in < 200)  return btnUP;
    if (adc_key_in < 400)  return btnDOWN;
    if (adc_key_in < 600)  return btnLEFT;
    if (adc_key_in < 800)  return btnSELECT;

    return btnNONE;  // when all others fail, return this...
}

ALU_Driver alu[8];
int result[8];
int iteratorr = -1;
void setup()
{
    alu[0].a=10;
    alu[0].b=1;
    alu[0].opcode=1 ;
    alu[1].a=3;
    alu[1].b=5;
    alu[1].opcode=2;
    alu[2].a= 11;
    alu[2].b=1;
    alu[2].opcode=3;
    alu[3].a=3;
    alu[3].b=5;
    alu[3].opcode=4;
    alu[4].a=3;
    alu[4].b=5;
    alu[4].opcode=5;
    alu[5].a=5;
    alu[5].b=3;
    alu[5].opcode=6;
    alu[6].a=5;
    alu[6].b=3;
    alu[6].opcode=7;
    alu[7].a=5;
    alu[7].b=7;
    alu[7].opcode=0;

//-------------------------------------------------------
//  Serial.begin(9600);
//  delay(25);
//  result[2] = (unsigned int)alu[2].a + alu[2].b;
//            String woord;
//           woord += alu[2].a;
//           woord += "+";
//            woord += alu[2].b;
//            woord += "=";
//            woord += result[2];
//            Serial.println(woord);
//            Serial.println(alu[2].opcode);
//-------------------------------------------------------

    
    //enable debugging mode
    //Serial.begin(9600);
    Serial.println("--- Start Serial Monitor ---"); // print on monitor

    lcd.begin(16, 2);              // start the library
    lcd.setCursor(0, 0);
    lcd.print("Push the buttons"); // print a simple message
}


String getRes() {
    switch (alu[iteratorr].opcode) {
        case 0: {
            result[iteratorr] = alu[iteratorr].a + alu[iteratorr].b;
            String woord;
            woord += alu[iteratorr].a;
            woord += "+";
            woord += alu[iteratorr].b;
            woord += "=";
            woord += result[iteratorr];
            return woord;
        }
        case 1: {
            result[iteratorr] = alu[iteratorr].a - alu[iteratorr].b;
            String woord;
            woord += alu[iteratorr].a;
            woord += "-";
            woord += alu[iteratorr].b;
            woord += "=";
            woord += result[iteratorr];
            return woord;
        }
        case 2: {
            result[iteratorr] = alu[iteratorr].a << alu[iteratorr].b;
            String woord;
            woord += alu[iteratorr].a;
            woord += "<<";
            woord += alu[iteratorr].b;
            woord += "=";
            woord += result[iteratorr];
            return woord;
        }
        case 3: {
            result[iteratorr] = (unsigned)alu[iteratorr].a >> alu[iteratorr].b;
            String woord;
            woord += alu[iteratorr].a;
            woord += " u >>";
            woord += alu[iteratorr].b;
            woord += "=";
            woord += result[iteratorr];
            return woord;
        }
        case 4: {
            result[iteratorr] = alu[iteratorr].a >> alu[iteratorr].b;
            String woord;
            woord += alu[iteratorr].a;
            woord += ">>";
            woord += alu[iteratorr].b;
            woord += "=";
            woord += result[iteratorr];
            return woord;
        }
        case 5: {
            result[iteratorr] = alu[iteratorr].a & alu[iteratorr].b;
            String woord;
            woord += alu[iteratorr].a;
            woord += " & ";
            woord += alu[iteratorr].b;
            woord += "=";
            woord += result[iteratorr];
            return woord;
        }
        case 6: {
            result[iteratorr] = alu[iteratorr].a | alu[iteratorr].b;
            String woord;
            woord += alu[iteratorr].a;
            woord += " | ";
            woord += alu[iteratorr].b;
            woord += "=";
            woord += result[iteratorr];
            return woord;
        }
        case 7: {
            result[iteratorr] = alu[iteratorr].a ^ alu[iteratorr].b;
            String woord;
            woord += alu[iteratorr].a;
            woord += " ^ ";
            woord += alu[iteratorr].b;
            woord += "=";
            woord += result[iteratorr];
            return woord;
        }
    }

}





void loop()
{
    lcd.setCursor(9, 1);           // move cursor to second line "1" and 9 spaces over

    lcd.setCursor(0, 1);           // move to the begining of the second line
    delay(50);

    lcd_key = read_LCD_buttons();  // read the buttons
    Serial.println(adc_key_in);

    switch (lcd_key)               // depending on which button was pushed, we perform an action
    {
        case btnUP:
        {
            if(iteratorr >= 7){
                iteratorr=-1;
            }
            iteratorr++;
            lcd.print(getRes());
            Serial.println(getRes());
            break;
        }
        case btnDOWN:
        {
            if(iteratorr <= 0){
                iteratorr=8;
            }
            iteratorr--;
            lcd.print(getRes());
            Serial.println(getRes());
            break;
        }
    }

}
