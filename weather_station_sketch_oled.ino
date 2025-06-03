// Missing sketch lines 
#include <LiquidCrystal.h>
#include <RTClib.h>                        
#include <DHT.h>                           
#include <Adafruit_BMP085.h>
#include <Adafruit_SSD1306.h>
#include <BH1750.h>

//LiquidCrystal_I2C lcd(0x20,20,4); 
Adafruit_BMP085 bmp;
RTC_DS3231 rtc;
BH1750 lightMeter;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
                                           

unsigned long startTime;        
unsigned long endTime;                     

// Setup the OLED display                                
#define OLED_WIDTH 128 
#define OLED_HEIGHT 64

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, 1);


#define DHTPIN 3                           
#define DHTTYPE DHT11                      
DHT dht(DHTPIN, DHTTYPE);                  
                                  

                                           
const byte interpin=2;                     
volatile unsigned long sTime=0;            
unsigned long dataTimer=0;                 
volatile float pulseTime=0;                
volatile float culPulseTime=0;             
volatile bool startt =true;                
volatile unsigned int avgWindCount=0;      
float aSetting=60.0;                       
float aWSpeed;

float pres;
float lux;
float h;
float t;
float pa;                       

void setup()
{
   Serial.begin(9600);                                   
 //lcd.init();
 //lcd.backlight();
  display.begin(SSD1306_SWITCHCAPVCC, OLED_HEIGHT);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  
  Wire.begin();
  lightMeter.begin();
  Serial.println(F("BH1750 Test"));


  if (! rtc.begin()) {                                
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }
 
  rtc.adjust(DateTime(__DATE__, __TIME__));           


  startTime = millis();                               
  Serial.begin(9600);                                     
  dht.begin();

  // Display start-up test
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED Failed!"));
    for(;;); // Does not loop forever
  }

  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  //lcd.begin(20, 4);
  pinMode(interpin,INPUT_PULLUP);                     
  attachInterrupt(interpin,anemometerISR, RISING);    
  dataTimer=millis();                                 
}

void loop()
 {
   printTime();                                       
   printpress();                                      
   printlux();                                        
   printtemp();                                       
   printwind();                                       
   Serial.println();
   Serial.println("-----------------------");
   Serial.println();
   if(millis()-startTime < 5000){
 Display1();
 endTime = millis();}
 else 
 { if (millis()-endTime < 5000)
   { Display2();}else
   {startTime = millis();}}
delay(500);}                                         

float getAneFreq(float pTime){return(1/pTime);}      
float getWindMPH(float freq){return (freq*2.4);}     
float getWindKPH(float wMPH){return(wMPH*1.61);}   
float getAvgWindSpeed(float cPulse,int per){         
  if(per)return getWindMPH(getAneFreq((float)(cPulse/per)));
  else return 0;                                     
   }

void anemometerISR(){
  unsigned long cTime=millis();                      
  if(!startt){                                       
    pulseTime=(float)(cTime-sTime)/1000;             
    culPulseTime+=pulseTime;                         
    avgWindCount++;                                  
  }
  sTime=cTime;                                       
  startt =false;                                     
}


void printwind(){
    unsigned long rTime=millis();                       
    detachInterrupt(interpin);                          
   aWSpeed=getAvgWindSpeed(culPulseTime,avgWindCount);  
    culPulseTime=0;                                    
    avgWindCount=0;                                     
    
    float aFreq=0;                                      
    Serial.print("Aver Windspeed:");
    Serial.print(aWSpeed);                              
    Serial.println(" Km/H");
   
    startt=true;                                        
    attachInterrupt(digitalPinToInterrupt(interpin),anemometerISR,RISING); 
    dataTimer=millis();                                 
   }


void read_time1(){
  DateTime now = rtc.now();

  //lcd.print(now.hour(), DEC);
  //lcd.print(":");
  //lcd.print(now.minute(), DEC);
  //lcd.print(":");
  //lcd.println(now.second(), DEC);
  display.print(now.hour(), DEC);
  display.print(":");
  display.print(now.minute(), DEC);
  display.print(":");
  display.println(now.second(), DEC);
  }

 
 void read_time2()
 {
  DateTime now = rtc.now();

  //lcd.print(now.day(), DEC);
  //lcd.print("/");
  //lcd.print(now.month(), DEC);
  //lcd.print("/");
  //lcd.println(now.year(), DEC);
  display.print(now.day(), DEC);
  display.print("/");
  display.print(now.month(), DEC);
  display.print("/");
  display.println(now.year(), DEC); 
}

void printTime() 
{
      DateTime now = rtc.now();            
      Serial.print(now.year(), DEC);       
      Serial.print('/');
      Serial.print(now.month(), DEC);      
      Serial.print('/');
      Serial.print(now.day(), DEC);        
      Serial.print(' ');
      Serial.print(now.hour(), DEC);       
      Serial.print(':');
      Serial.print(now.minute(), DEC);     
      Serial.print(':');
      Serial.print(now.second(), DEC);     
      Serial.println();
  }


  void printpress()                      
  {
   pres = bmp.readPressure();
   pa = pres/100;         
   Serial.print("Pressure:");
   Serial.print(pa);                      
   Serial.println(" hpa");                
 }

  
  void printlux(){
  //int value=analogRead(A0);               
  //lux=map(value,1,595,1,1000);            
  lux = lightMeter.readLightLevel();
  Serial.print("LUX : ");
  Serial.print(lux);                  
  Serial.println(" lux");
 }


  void printtemp(){
  h = dht.readHumidity();                   
  t = dht.readTemperature();                  
  Serial.print("Humidity = ");
  Serial.print(h);                          
  Serial.println("%");
  Serial.print("Temperature = ");
  Serial.print(t);                          
  Serial.println(" C");
  }


   // Display data on the OLED Screen
   void Display1(void)                    
  {
    //lcd.clear(); 
    //lcd.setCursor(0,0);
    //lcd.print("Date : ");
    //read_time2();                         
    //lcd.setCursor(0,1);
    //lcd.print("Time : ");
    //read_time1();
    //lcd.setCursor(0,2);
    //lcd.print("Humidity : ");
    //lcd.print(h);
    //lcd.println("%");
    //lcd.setCursor(0,3);
    //lcd.print("Temperature : ");
    //lcd.print(t);                                     
    //lcd.println(" C");
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,10);
    display.print("Date : ");
    read_time2();                         
    display.setCursor(10,10);
    display.print("Time : ");
    read_time1();
    //display.setCursor(20,10);
    //display.print("Humidity : ");
    //display.print(h);
    //display.print("%");
    //display.setCursor(30,10);
    //display.print("Temperature : ");
    //display.print(t);                                     
    //display.println(" C");
    
    display.display();
   }                   
    
void Display2(void)                     
  {
    //lcd.clear(); 
    //lcd.setCursor(0,0);
    //lcd.print("Pres :  ");
    //lcd.print(pa);
    //lcd.println(" Pa");                         
    //lcd.setCursor(0,1);
    //lcd.print("Wind Speed : ");
    //lcd.print(aWSpeed);
    //lcd.println(" km/h");
    //lcd.SetCursor(0,3);
    //lcd.print("LUX :");
    //lcd.print(lux);
    //lcd.println(" lux");
    //display.clearDisplay();
    //display.setTextSize(1);
    //display.setTextColor(WHITE);
    //display.setCursor(0,10);
    //display.print("Pres :  ");
    //display.print(pa);
    //display.print(" Pa");                         
    //display.setCursor(10,10);
    //display.print("Wind Speed : ");
    //display.print(aWSpeed);
    //display.println(" km/h");
    //display.setCursor(20,10);
    //display.print("LUX :");
    //display.print(lux);
    //display.println(" lux");
    //display.display();
    }
