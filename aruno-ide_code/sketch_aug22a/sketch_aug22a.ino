#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// Replace these with your WiFi and MQTT broker settings
const char* ssid = "Ho Huu Nghia 2.4G";
const char* password = "0977421571";
const char* mqtt_server = "192.168.1.4"; // Replace with your MQTT broker address

// DHT11 sensor settings
#define DHTPIN D2    // Pin connected to the DHT11 sensor
#define DHTTYPE DHT11   // Define the type of sensor used (DHT11)

// Create an instance of the DHT class
DHT dht(DHTPIN, DHTTYPE);

// Create an instance of the WiFiClient and PubSubClient
WiFiClient espClient;
PubSubClient client(espClient);

// Connect to the WiFi network
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

// Callback function for when a message is received (not used in this example)
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

// Reconnect to the MQTT server if the connection is lost
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Subscribe to topics if needed
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1884);
  client.setCallback(callback);

  // Initialize the DHT sensor
  dht.begin();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Read temperature and humidity from DHT11 sensor
  float temperature = dht.readTemperature(); // Read temperature in Celsius
  float humidity = dht.readHumidity();       // Read humidity in percentage

  // Check if any reads failed and exit early (to try again)
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Prepare the payload
  String timestamp = "2024-08-20T05:00:00Z"; // Example timestamp, replace with actual time if needed
  String payload = "{\"temperature\": " + String(temperature, 1) + ", \"humidity\": " + String(humidity, 1) + ", \"timestamp\": \"" + timestamp + "\"}";

  // Publish data to the topic
  client.publish("esp8266/sensor_data", payload.c_str());

  // Wait for 10 seconds before publishing again
  delay(10000);
}