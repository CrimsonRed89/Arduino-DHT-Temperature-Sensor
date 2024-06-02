#include <DHT.h>

#define DHT_SENSOR_PIN 27

#define DHT_SENSOR_TYPE DHT11

DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

void setup() { 
  Serial.begin(9600); 
  dht_sensor.begin(); 
 

}

void loop() {
float humi = dht_sensor.readHumidity();
float tempC = dht_sensor.readTemperature();
float tempF = dht_sensor.readTemperature(true);


if (isnan(tempC) || isnan(tempF) || isnan (humi)) { 
  Serial.println("Failed to read from DHT sensor!");
} 
else {
Serial.print("Humidity: ");

Serial.print(humi);

Serial.print("%");

Serial.print(" ");

Serial.print("Temperature: ");

Serial.print(tempC);

Serial.print("°C ~ ");

Serial.print(tempF);

Serial.println("F");


}
delay(1000);
}


