/*
 * Earthquake Alert System with ESP32 and MPU6050
 *
 * This code implements a basic earthquake alert system using an ESP32
 * microcontroller and an MPU6050 accelerometer. The ESP32 reads data from
 * the accelerometer, analyzes it for earthquake-like vibrations based on
 * acceleration thresholds, and sends the data (including timestamps and peak
 * accelerations) to a ThingSpeak channel for monitoring and visualization.
 *
 * This is a starting point, and the code may require further refinement
 * for real-world applications.
 *
 * Author: Sumit Bhardwaj
 * Date: 01/05/2024
 */
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <LiquidCrystal_I2C.h>// lcd Header
#include <WiFi.h>
#include <HTTPClient.h>
// Set the I2C address for your specific LCD module
int lcdAddress = 0x27; // Change this to your LCD's address (usually 0x27 or 0x3F)

// Initialize the LiquidCrystal_I2C library with the LCD's address and the number of columns and rows
LiquidCrystal_I2C lcd(lcdAddress, 16, 2);
Adafruit_MPU6050 mpu;
 
#define buzzer 19 // buzzer pin
#define led 18 //led pin
 
/*variables*/
int xsample=0;
int ysample=0;
int zsample=0;
long start;
int buz=0;
 
/*Macros*/
#define samples 30
#define maxVal 5 // max change limit
#define minVal -5 // min change limit
#define buzTime 1000 // buzzer on time

const char* ssid = "Admin";
const char* password = "alita123";
// Domain Name with full URL Path for HTTP POST Request
const char* serverName = "http://api.thingspeak.com/update";
// write API Key provided by thingspeak
String apiKey = "EDFQ7NOOBUTH1MS5";
 
void setup()
{
Serial.begin(115200);
delay(1000);
lcd.init(); //initializing lcd
lcd.backlight(); 
delay(1000);
lcd.print("EarthQuake ");
lcd.setCursor(0,1);
lcd.print("Detector ");
delay(2000);
lcd.clear();
WiFi.mode(WIFI_STA); //Optional
 WiFi.begin(ssid, password);
 Serial.println("Connecting");
 lcd.print("Connecting to");
  lcd.setCursor(0,1);
lcd.print("Wifi ... .. .");
 while(WiFi.status() != WL_CONNECTED) {
   delay(500);
   Serial.print(".");
 }
 Serial.println("");
 lcd.clear();
 Serial.print("Connected to WiFi network with IP Address: ");
 Serial.println(WiFi.localIP());
 lcd.print("Conected to:");
 lcd.setCursor(0,1);
 lcd.print(WiFi.localIP());
 delay(2000);
 lcd.clear();

 // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    lcd.print("MPU6050");
    lcd.setCursor(0,1);
    lcd.print("not found");
    delay(2000);
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
lcd.print("Calibrating.....");
lcd.setCursor(0,1);
lcd.print("Please wait...");
pinMode(buzzer, OUTPUT);
pinMode(led, OUTPUT);
buz=0;
digitalWrite(buzzer, buz);
digitalWrite(led, buz);
mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
for(int i=0;i<samples;i++) // taking samples for calibration
{
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  xsample+= a.acceleration.x; // X axis data
  ysample+= a.acceleration.y;
  zsample+= a.acceleration.z; // Y axis data
}
 
xsample/=samples; // taking avg for x
ysample/=samples; // taking avg for y
zsample/=samples; // taking avg for z
 
delay(2000);
lcd.clear();
lcd.print("Calibrated");
delay(1000);
lcd.clear();
lcd.print("Device Ready");
delay(1000);
lcd.clear();
lcd.print(" X    Y    Z ");
}

void loop()
{
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  int value1 = a.acceleration.x; // X axis data
  int value2 = a.acceleration.y;
  int value3 = a.acceleration.z; // Y axis data
 
int xValue=xsample-value1; // finding change in x
int yValue=ysample-value2; // finding change in y
int zValue=zsample-value3; // finding change in z
 
/*displying change in x,y and z axis values over lcd*/
lcd.setCursor(0,1);
lcd.print(xValue);
lcd.setCursor(6,1);
lcd.print(yValue);
lcd.setCursor(12,1);
lcd.print(zValue);
delay(100);
 
/* comparing change with predefined limits*/
if(xValue < minVal || xValue > maxVal || yValue < minVal || yValue > maxVal || zValue < minVal || zValue > maxVal)
{
  if(buz == 0){
  start=millis(); // timer start
  buz=1; // buzzer / led flag activated
  lcd.setCursor(0,0);
  lcd.print("Earthquake Alert ");
  digitalWrite(buzzer, buz); // buzzer on and off command
  digitalWrite(led, buz); // led on and off command
  }
}
//Sending data to ThingsSpeak
if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
       // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);
      // Specify content-type header
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      // Data to send with HTTP POST
      String httpRequestData = "api_key=" + apiKey + "&field1=" + String(xValue) + "&field2=" + String(yValue) + "&field3=" + String(zValue) + "&field4=" + String(buz);          
      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      http.end();
 }
else {
      Serial.println("WiFi Disconnected");
    }
//Turning off buzzer
if(buz == 1) // buzzer flag activated then alerting earthquake
{
  if(millis()>= start+buzTime)
  buz=0;
}
else
{
  lcd.clear();
  lcd.print(" X    Y    Z ");
}
 
digitalWrite(buzzer, buz); // buzzer on and off command
digitalWrite(led, buz); // led on and off command
 
/*sending values to processing for plot over the graph*/
Serial.print("x=");
Serial.println(xValue);
Serial.print("y=");
Serial.println(yValue);
Serial.print("z=");
Serial.println(zValue);
Serial.println(" $");

}
