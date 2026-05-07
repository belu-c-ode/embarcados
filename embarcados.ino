#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

// ===== PINAGEM =====
#define DHTPIN 2
#define DHTTYPE 11

#define trigDist 14
#define echoDisk 33


// ===== WIFI =====
const char* ssid = "LAB_ESEG_IOT"; // usar o nome da rede - aqui usei meu roteador
const char* password = ""; // senha da rede

// ===== MQTT =====
const char* mqtt_server = "52.91.140.98"; // ip da máquina virtual
const int mqtt_port = 1883;
const char* mqtt_topic = "esp32/teste";

// ===== OBJETOS =====
WiFiClient espClient;
PubSubClient client(espClient);

DHT sensorT(DHTPIN, DHTTYPE);

// ===== DADOS =====
float temperatura;
float umidade;
float distancia;

// ===== CONECTAR WIFI =====
void setup_wifi() {
  delay(10);
  Serial.println("Conectando ao WiFi...");
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

// ===== CONECTAR MQTT =====
void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT...");
    
    if (client.connect("ESP32Client")) {
      Serial.println("conectado!");
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5s...");
      delay(5000);
    }
  }
}

// ===== SETUP =====
void setup() {
  Serial.begin(115200);

  delay(1000);
  Serial.println("Iniciando...");
  
  setup_wifi();
  
  client.setServer(mqtt_server, mqtt_port);

  sensorT.begin();
  pinMode(trigDist, OUTPUT);
  pinMode(echoDist, INPUT);
}

// ===== LOOP =====
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Sensor ultrassônico
  digitalWrite(trigDist, LOW);
  delayMicroseconds(2);

  digitalWrite(trigDist, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigDist, LOW);

  temperatura = sensorT.readTemperature();
  umidade = sensorT.readHumidity();
  distancia = (pulseIn(pinEcho, HIGH) * 0.0343) / 2;

  if(isnan(temperatura) || isnan(umidade))  {
    Serial.println("Erro ao ler sensor DHT :| ");
  }

  // ===== PUBLICAR DADO =====
  String mensagem = "{\"temperatura\": " + String(temperatura) + "," + "\"umidade\": " + String(umidade) + "," + "\"distancia\": " + String(distancia) + "}";

  Serial.println("Enviando: " + mensagem);
  client.publish(mqtt_topic, mensagem.c_str());

  delay(1000);
}
