#include "Wire.h"
#include <SD.h>
#include "RTClib.h"
#include "Adafruit_BMP085.h"
RTC_DS1307 RTC;
#include <dht11.h>

dht11 DHT11;
#define DHT11PIN 5

const int chipSelect = 8;   //SD CARD
const int mqpin = 2;
int sensorValue;


Adafruit_BMP085 bmp;

void setup() {
Serial.begin(9600);
Wire.begin();
  RTC.begin();
  
//  RTC.adjust(DateTime(__DATE__, __TIME__));  // uncomment to adjust time 
  if (!RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }  

  Serial.println("DHT11 TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT11LIB_VERSION);
  Serial.println();


bmp.begin();
     Serial.println("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("card initialized.");  

}

void loop() {

// MQ2 sensor
float mq2value = analogRead(mqpin);       // read analog input pin 2
Serial.print("MQ2 Pin = ");
Serial.println(mq2value, DEC);  // prints mq2 analog value

  
// barometro
Serial.print("Temperature BAR = ");
float bartemp = bmp.readTemperature();
Serial.print(bartemp);
Serial.println(" *C");
Serial.print("Pressure = ");
float barpre = bmp.readPressure();
Serial.print(barpre);
Serial.println(" Pa");
Serial.print("Real altitude = ");
float alt = bmp.readAltitude(101500);
Serial.print(alt);
Serial.println(" meters");


// humidity
int chk = DHT11.read(DHT11PIN);
Serial.print("Humidity: ");
switch (chk)
{
    case DHTLIB_OK: 
		Serial.println("OK"); 
    		break;
    case DHTLIB_ERROR_CHECKSUM: 
		Serial.println("Checksum error"); 
		break;
    case DHTLIB_ERROR_TIMEOUT: 
		Serial.println("Time out error"); 
		break;
    default: 
		Serial.println("Unknown error"); 
		break;
}

Serial.print("Humidity (%): ");
float dht11um = (float)DHT11.humidity; 
Serial.println(dht11um, 2);
Serial.print("Temperature (C): ");
float dht11temp = (float)DHT11.temperature; 
Serial.println(dht11temp, 2);


// sd 
// mq2value,bartemp,barpre,alt,chk,dht11um,dht11temp
Serial.println();

File dataFile = SD.open("air.log", FILE_WRITE);
      DateTime now = RTC.now();
      if (dataFile) {
          dataFile.print(mq2value);
          dataFile.print(",");
          dataFile.print(bartemp);
          dataFile.print(",");
          dataFile.print(barpre);
          dataFile.print(",");
          dataFile.print(alt);
          dataFile.print(",");
          dataFile.print(chk);
          dataFile.print(",");
          dataFile.print(dht11um);
          dataFile.print(",");
          dataFile.print(dht11temp);
          dataFile.print(",");
          dataFile.print(now.year(), DEC);
          dataFile.print('/');
          dataFile.print(now.month(), DEC);
          dataFile.print('/');
          dataFile.print(now.day(), DEC);
          dataFile.print(' ');
          dataFile.print(now.hour(), DEC);
          dataFile.print(':');
          dataFile.print(now.minute(), DEC);
          dataFile.print(':');
          dataFile.print(now.second(), DEC);
          dataFile.println();
          dataFile.close();
        }
        else{
          Serial.println("Failed to write on SD");
        }

delay(500);

}





 

 
