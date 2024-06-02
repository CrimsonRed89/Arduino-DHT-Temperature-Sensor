//22053654 Question 2 Aayush Arora

#define BLYNK_TEMPLATE_ID "TMPL31kqAP5bu"
#define BLYNK_TEMPLATE_NAME "22053654AayushArora"
#define BLYNK_AUTH_TOKEN "wKKx3GDtVNZEIwdLK80N6nVuWiQa5Rvf"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Oneplus";
char pass[] = "123456789";

#define DHTPIN 26         // What digital pin we're connected to
#define DHTTYPE DHT11     // DHT 11

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

// LED pin
#define LEDPIN 14

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  // Send humidity and temperature data to Blynk app
  Blynk.virtualWrite(V0, h);
  Blynk.virtualWrite(V1, t);
  
  // Check conditions for LED control
  if (t > 30 && h > 80) {
    digitalWrite(LEDPIN, HIGH); // Turn on LED
  } else {
    digitalWrite(LEDPIN, LOW); // Turn off LED
  }
}

void setup()
{
  // Debug console
  Serial.begin(115200);

  // Initialize LED pin
  pinMode(LEDPIN, OUTPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  dht.begin();

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
