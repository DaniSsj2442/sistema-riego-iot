#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#include "config.h"

#include "certificates.h"

// =====================================
// OBJETOS
// =====================================

WiFiClientSecure espClient;

PubSubClient client(espClient);

// =====================================
// PINES
// =====================================

const int humedadPin = 34;

const int ldrPin = 35;

// GPIO conectado a IN1 del ULN2003

const int relePin = 4;

// =====================================
// TOPICS MQTT
// =====================================

const char* topicSensores = "riego/sensores";

const char* topicControl = "riego/control";

// =====================================
// CALLBACK MQTT
// =====================================

void callback(char* topic, byte* payload, unsigned int length) {

  String mensaje;

  for (int i = 0; i < length; i++) {

    mensaje += (char)payload[i];
  }

  Serial.println("\n===== COMANDO MQTT =====");

  Serial.print("Mensaje recibido: ");

  Serial.println(mensaje);

  // =====================================
  // CONTROL BOMBA
  // =====================================

  if (mensaje == "ON") {

    Serial.println("BOMBA ACTIVADA");


    digitalWrite(relePin, HIGH);
  }

  else if (mensaje == "OFF") {

    Serial.println("BOMBA APAGADA");

    digitalWrite(relePin, LOW);
  }

  Serial.println("========================");
}

// =====================================
// WIFI
// =====================================

void setup_wifi() {

  delay(10);

  Serial.println();

  Serial.println("================================");

  Serial.print("Conectando a WiFi");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");
  }

  Serial.println("");

  Serial.println("WiFi conectado");

  Serial.print("IP ESP32: ");

  Serial.println(WiFi.localIP());

  Serial.println("================================");
}

// =====================================
// MQTT
// =====================================

void reconnect() {

  while (!client.connected()) {

    Serial.println("================================");

    Serial.println("Probando conexión TLS...");

    Serial.print("Conectando MQTT TLS... ");

    if (client.connect("ESP32_RIEGO", mqtt_user, mqtt_pass)) {

      Serial.println("CONECTADO");

      client.subscribe(topicControl);

      Serial.print("Suscrito a: ");

      Serial.println(topicControl);

    } else {

      Serial.print("FALLO, rc=");

      Serial.print(client.state());

      Serial.println(" -> Reintentando en 5 segundos");

      delay(5000);
    }
  }
}

// =====================================
// SETUP
// =====================================

void setup() {

  Serial.begin(115200);

  delay(2000);

  // =====================================
  // RELÉ
  // =====================================

  pinMode(relePin, OUTPUT);

  // ULN2003:
  // LOW = apagado

  digitalWrite(relePin, LOW);

  // =====================================
  // WIFI
  // =====================================

  setup_wifi();

  // =====================================
  // TLS
  // =====================================

  espClient.setCACert(root_ca);

  // =====================================
  // MQTT
  // =====================================

  client.setServer(mqtt_server, mqtt_port);

  client.setCallback(callback);
}

// =====================================
// LOOP
// =====================================

void loop() {

  if (!client.connected()) {

    reconnect();
  }

  client.loop();

  // =====================================
  // SENSOR HUMEDAD
  // =====================================

  long sumaHumedad = 0;

  for(int i = 0; i < 20; i++) {

    sumaHumedad += analogRead(humedadPin);

    delay(10);
  }

  int adcHumedad = sumaHumedad / 20;

  // =====================================
  // CALIBRACIÓN HUMEDAD
  // =====================================

  int humedad = map(adcHumedad, 4095, -500, 0, 100);

  humedad = constrain(humedad, 0, 100);

  // =====================================
  // SENSOR LUZ
  // =====================================

  long sumaLuz = 0;

  for(int i = 0; i < 20; i++) {

    sumaLuz += analogRead(ldrPin);

    delay(5);
  }

  int adcLuz = sumaLuz / 20;

  int luz = map(adcLuz, 3150, 150, 0, 100);

  luz = constrain(luz, 0, 100);

  // =====================================
  // DÍA / NOCHE
  // =====================================

  String estadoLuz;

  if(adcLuz > 2000) {

    estadoLuz = "NOCHE";

  } else {

    estadoLuz = "DIA";
  }

  // =====================================
  // JSON
  // =====================================

  StaticJsonDocument<256> doc;

  doc["humedad"] = humedad;

  doc["adc_humedad"] = adcHumedad;

  doc["luz"] = luz;

  doc["adc_luz"] = adcLuz;

  doc["estado_luz"] = estadoLuz;

  doc["dispositivo"] = "ESP32_RIEGO";

  char buffer[256];

  serializeJson(doc, buffer);

  // =====================================
  // PUBLICAR MQTT
  // =====================================

  client.publish(topicSensores, buffer);

  // =====================================
  // SERIAL MONITOR
  // =====================================

  Serial.println("\n===== DATOS ENVIADOS MQTT TLS =====");

  Serial.print("ADC Humedad: ");

  Serial.print(adcHumedad);

  Serial.print(" | Humedad: ");

  Serial.print(humedad);

  Serial.println("%");

  Serial.print("ADC Luz: ");

  Serial.print(adcLuz);

  Serial.print(" | Luz: ");

  Serial.print(luz);

  Serial.println("%");

  Serial.print("Estado Luz: ");

  Serial.println(estadoLuz);

  Serial.println("--------------------------------");

  Serial.print("JSON MQTT: ");

  Serial.println(buffer);

  Serial.println("================================");

  delay(5000);
}