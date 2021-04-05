#include <SimpleDHT.h>                                                    // Importing dht library.
#include<ESP8266WiFi.h>                                                   // Importing esp8266 library.
#define pinDHT11 0                                                        // Defining DHT pin.
SimpleDHT11 dht11(pinDHT11);                                            

int sensorPin = A0;                                                       // Initializing pins for rain sensor and dht11 sensor.
int sensorValue2 = 0; 
int val;                                                                 //Initializing val as an Integer.

String apiKey = "RZUCN184XZS220BL";                                      // Assigning API pin of thingspeak channel.

const char *ssid = "HACKER'S NIGHTMARE";                                //Assigning your Internet user name.
const char *pass = "Radha@1234";                                        // Assigning password of Internet.
const char *server = "api.thingspeak.com";                              // Assigning server site name.

WiFiClient client;                                                      // Initializing Wifi as client.
void setup(){
  
  Serial.begin(115200);                                                 // Initializing serial value as 115200.
  delay(10);

  Serial.println("CONNECTING TO ");
  Serial.println(ssid);

 WiFi.begin(ssid, pass);                                              // Doing some task to connect our node mcu to Internet.

 while (WiFi.status() != WL_CONNECTED)
 {
 delay(500);
 Serial.print(".");
 }
  Serial.print("");
  Serial.println("WiFi connected");
}
void loop(){
  // TAKING VALUES FROM THE SENSORS 
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) 
  {
    Serial.print("Read DHT11 failed, err="); 
    Serial.println(err);
    delay(1000);
    return;
  }                                                                    // Taking sensor values from DHT11 sensor and then printing it on serial monitor.
  Serial.print("\nSurrounding temperature: ");
  Serial.print((int)temperature); 
  Serial.print("*C, ");
  Serial.print("\nSurrounding humidity: ");
  Serial.print((int)humidity); 
  Serial.println("%H");

  sensorValue2 = analogRead(sensorPin);
  sensorValue2 = constrain(sensorValue2,150 ,440);                    // Taking values from rain sensor and converting them into a usefull value.
  sensorValue2 = map(sensorValue2, 150, 440, 1023, 0);
  if (sensorValue2 >= 20)
  {
   
    val = 1;                                                         
  }
  else                                                                // Using if and else condition for rain sensor value to assign (val) 0 or 1.
  {
 
    val = 0;
  }
  
  if (client.connect(server,80))
  {
    String postStr = apiKey;
    postStr += "&field1=";
    postStr +=  String(temperature);                                  // Sending this data to the things spek server.
    postStr += "&field2=";
    postStr += String(humidity);
    postStr += "&field3=";
    postStr += String(val);
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connected: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
    client.print("content-Type: application/x-www-form-urlencoded\n");   // Some task to upload data to the things speak server continously. 
    client.print("content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" degree Celcius ");                                  // Printing all the sensor values on the serial monitor.
    Serial.print("\nHumidity: ");
    Serial.print(humidity);
    Serial.print("\nRain data: ");
    Serial.print(val);
    Serial.println("\n Send to Thingspeak.");
  }
  client.stop();
  
  delay(1000);
}
