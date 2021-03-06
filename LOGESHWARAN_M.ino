//Designing an Automatic Contactless Door with Temperature Detection and Sanitation System for Covid-19
//LOGESHWARAN M

#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
LiquidCrystal_I2C lcd(0x27,16,2);

const int BUTTON_PIN = 9;
const int SERVO_PIN  = 8;

int angle = 0; 
int lastButtonState;    
int currentButtonState; 

Servo myservo1;  

#define red 13
#define green 12
#define haha 4
int pos1;

void setup() {
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT_PULLUP);     
  myservo1.attach(SERVO_PIN);           
  myservo1.write(angle);
  currentButtonState = digitalRead(BUTTON_PIN);
  
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(haha,INPUT);

  myservo1.attach(8);  
  myservo1.write(90);
  mlx.begin();  
 
  lcd.init();
  lcd.backlight();
}

void loop() {
  
        int montion = digitalRead(haha);
        
        if(montion == 1){
          
          Serial.print("made");
          Serial.print("\n");
          
          lcd.setCursor(3,0);
          lcd.print("NO DETECTION");
          covid();
          }   
}
        
void covid(){
   int temp_obj = mlx.readObjectTempC();
   Serial.print(temp_obj);
  
          if(temp_obj < 31){
           lcd.setCursor(3,0);
           lcd.print("NO DETECTION");
           lcd.setCursor(0,1);
           lcd.clear(); 
          }
          
          if(temp_obj > 30 && temp_obj <38){ 
           digitalWrite(green,HIGH);
           lcd.setCursor(3,0);
           lcd.print("TEMPERATURE"); 
           lcd.setCursor(6,1);
           lcd.print(temp_obj);
           lcd.setCursor(8,1);
           lcd.print("*C");
           delay(3000);
           lcd.begin(16, 2);
           lcd.clear();
           
           lcd.setCursor(2,0);
           lcd.print("SANITIZE YOUR");
           lcd.setCursor(6,1);
           lcd.print("HANDS!");
           delay(3000);

           lcd.begin(16, 2);
           lcd.clear();

           lcd.setCursor(5,0);
           lcd.print("GO IN!"); 
           lcd.setCursor(0,1);
           lcd.print("YOU ARE WELCOME!"); 
           delay(2500);
           
           for(pos1 = 90; pos1 <= 180; pos1 += 1)
          {                        
            myservo1.write(pos1);     
            delay(15);
          }
            delay(7000);

           for(pos1 = 180; pos1>=90; pos1 -=1)
           {
            myservo1.write(pos1);
            delay(15);                     
           }
           
  digitalWrite(green,LOW);
          } 
          if(temp_obj>37)
          {
            digitalWrite(red,HIGH);
            lcd.setCursor(0,0);
            lcd.print("TEMPERATURE:"); 
            lcd.setCursor(13,0);
            lcd.print(temp_obj);
            lcd.setCursor(15,0);
            lcd.print("*C"); 
            lcd.setCursor(5,1);
            lcd.print("KEEP OUT");
            delay(500);
  }
  digitalWrite(red,LOW);
lastButtonState    = currentButtonState;      
  currentButtonState = digitalRead(BUTTON_PIN); 

  if(lastButtonState == HIGH && currentButtonState == LOW) {
 
    if(angle == 90)
      angle = 0;
    myservo1.write(angle);
  }

if(lastButtonState == LOW && currentButtonState == HIGH) {
    if(angle == 0)
      angle = 90;
      delay(5000);
    myservo1.write(angle);
  }
}                   
