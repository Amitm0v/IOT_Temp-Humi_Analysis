#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>
// Replace with your network credentials
const char* ssid = "Amit Main Phone";
const char* password = "987654321";
// Google Sheets script URL
const char* scriptURL = "https://script.google.com/macros/s/AKfycbyoAyUcZIjX1xclexhEAlwsDQpy3XNIyORZzfHe6kE_45LiMxWFUoNhDVBsle3iGAgcjw/exec";

// DHT sensor settings
#define DHTPIN 4  // GPIO pin where the DHT11 is connected
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
  dht.begin();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Reading temperature and humidity from DHT11
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    // Construct the URL with parameters
    String url = String(scriptURL) + "?temp=" + temperature + "&hum=" + humidity;
    http.begin(url);

    // Send HTTP GET request
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      Serial.println(http.getString());
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }

  delay(5000);  
}
