#include <WiFi.h>
#include <PubSubClient.h>

// ===== WIFI =====
const char* ssid = "LAB_ESEG_IOT"; // usar o nome da rede - aqui usei meu roteador
const char* password = ""; // senha da rede

// ===== MQTT =====
const char* mqtt_server = "52.91.140.98"; // ip da máquina virtual
const int mqtt_port = 1883;
const char* mqtt_topic = "esp32/teste";

// ===== Constante auxiliar =====
const float dis_max = 1500.00

// ===== OBJETOS =====
WiFiClient espClient;
PubSubClient client(espClient);

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
}

// ===== LOOP =====
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  float temperatura = temperatureRead();

  // ===== PUBLICAR DADO =====
  String mensagem = "{\"temperatura\": " + String(temperatura) + "," + "\"umidade\": " + String(umidade) + "\"distancia\": " + String(distancia) + "\"alt_rel\": " + String(dis_max - distancia) + "\"alt_rel_p\": " + String((distancia/dis_max)*100)
  "}";

  {
    temperatura: 50.0
    umidade: 75
    distancia: 90
    altura_relativa: 600
    altura_relativa_perc: 5
  }

  Serial.println("Enviando: " + mensagem);
  client.publish(mqtt_topic, mensagem.c_str());

  delay(1000);
}
