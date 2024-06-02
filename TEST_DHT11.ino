// initializes or defines the output pin of the LM35 temperature sensor
#include <WiFi.h>
#include <DHT.h>
#include <ThingSpeak.h>
#define DHT_SENSOR_PIN  27
#define led_pin 26
#define DHT_SENSOR_TYPE DHT11
DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);
//this sets the ground pin to LOW and the input voltage pin to high

WiFiClient client;

long myChannelNumber =    2464043;
const char myWriteAPIKey[] = "BVR1D3JD03AE5D8V";

void setup() {
 Serial.begin(9600);
 pinMode(led_pin, OUTPUT); 
 WiFi.begin("Oneplus", "123456789");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print("..");
  }
  Serial.println();
  Serial.println("ESP32 is connected!");
  Serial.println(WiFi.localIP());
  dht_sensor.begin();
  ThingSpeak.begin(client);
}

void loop()       //main loop

{
// int analogValue = analogRead(outputpin);
  float humi  = dht_sensor.readHumidity();
  // read temperature in Celsius
  float tempC = dht_sensor.readTemperature();
  // read temperature in Fahrenheit
  float tempF = dht_sensor.readTemperature(true);
  // check whether the reading is successful or not
  if ( isnan(tempC) || isnan(tempF) || isnan(humi)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Humidity: ");
    Serial.print(humi);
    Serial.print("%");

    Serial.print("  |  ");

    Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.print("°C  ~  ");
    Serial.print(tempF);
    Serial.println("°F");

    ThingSpeak.writeField(myChannelNumber, 1, tempC, myWriteAPIKey);
  }
 if (tempC >= 26 && tempC <= 32) {
      int brightness = map(tempC, 26, 32, 50, 255); // Map temperature to brightness (50 to 255)
      analogWrite(led_pin, brightness); // Set LED brightness
    } else {
      analogWrite(led_pin, 0); // Turn off LED
    }
    
  delay(1000);
}