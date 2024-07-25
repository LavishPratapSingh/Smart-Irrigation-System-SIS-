#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 4 // soil temperature
#define sensorPin A0 // capacitive soil moisture
#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
//Variables
int chk;
float airhum;  //Stores humidity value
float airtemp; //Stores temperature value
float soiltempc;
float soiltempf;
float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setup()
{
    Serial.begin(9600);
	  dht.begin();
    sensors.begin();
}
void loop()
{
    //Read data and store it to variables hum and temp
    // Read the Analog Input
    int soilmois = analogRead(sensorPin);                    // soil moisture
    soilmois=1023-soilmois;
    airhum = dht.readHumidity();                             // air humidity
    airtemp= dht.readTemperature();                          // air temperature
    sensors.requestTemperatures();                           // soil temperature
    soiltempc=sensors.getTempCByIndex(0);                    // soil temperature in Celcius
    soiltempf=sensors.getTempFByIndex(0);                    // soil temperature in fahrenheit
    float minValue = 440.0; // Minimum value of input range
    float maxValue = 610.0; // Maximum value of input range
    float outputMin = 0.01400; // Minimum value of output range
    float outputMax = 0.2300; // Maximum value of output range
    float VWCsm = mapFloat(soilmois, minValue, maxValue, outputMin, outputMax);
    //Print values
    Serial.print("Soil Moisture: ");
    Serial.print(VWCsm,7);
    Serial.print(" ,Air Rel Humi: ");
    Serial.print(airhum);
    Serial.print(" ,Air Celcius Temp: ");
    Serial.print(airtemp);
    Serial.print(" ,Soil Celsius temperature: ");
    Serial.print(soiltempc);
    Serial.println();
    delay(2000); //Delay 2 sec.
}
