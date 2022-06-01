#include <Servo.h>
#include <Keypad.h> 
#include <LiquidCrystal.h>
#define BUZZER 11

LiquidCrystal lcd(7,6,5,4,3,2);


Servo motor;
int basamak = 0;
const byte satir = 4;
const byte sutun = 4;
String girilen_sifre="";    
String sifre = "1658*"; 

char tus_takimi[satir][sutun]= 
{
{'1', '2', '3', 'A'}, 
{'4', '5', '6', 'B'}, 
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};

byte satirpin[satir] = {A0, A1, A2, A3};
byte sutunpin[sutun] = {A4, A5, 13, 10};

Keypad tus_takimim= Keypad(makeKeymap(tus_takimi), satirpin, sutunpin, satir, sutun);

void setup()
{
  motor.attach(9);
  motor.write(0);
  pinMode(9, OUTPUT);
  pinMode(BUZZER,OUTPUT); 
  lcd.begin(16,2);                     
  lcd.setCursor(0,0);
  lcd.print("SIFRE GIRINIZ:");
 
}


void loop()
{
char tus = tus_takimim.getKey();  // Keypad'den alınan değer.
  if (tus != NO_KEY) {
    
      lcd.setCursor(basamak,1);
      lcd.print(tus);
      digitalWrite(BUZZER,HIGH);
      delay(100);
      digitalWrite(BUZZER,LOW);
      girilen_sifre = girilen_sifre + tus;
      basamak++;
   
  }



  if(tus=='#'){
      
      if((girilen_sifre.substring(0,basamak-1)) == sifre) {
        lcd.setCursor(0,1);
        lcd.print("SIFRE DOGRU");
        motor.write(0);
        delay(1000);
        motor.write(180);
        delay(1000);
        for(int i=0; i<16; i++)
        {
        lcd.setCursor(i,1);
        lcd.print(" ");
        }
        girilen_sifre = "";
        basamak = 0;
        }
     
       else if (( girilen_sifre.substring(0,basamak-1) != sifre))  {
       lcd.setCursor(0,1);
       lcd.print("HATALI SIFRE");
       digitalWrite(BUZZER,HIGH);
       delay(800);
       digitalWrite(BUZZER,LOW);
       delay(1000);
       for(int i=0; i<16; i++)
       {
        lcd.setCursor(i,1);
        lcd.print(" ");
       }
        girilen_sifre = "";
        basamak = 0;
        

      }
  }    
 
}
