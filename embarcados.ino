#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

// ===== PINAGEM =====
#define DHTPIN 2
#define DHTTYPE DHT11

#define trigDist 14
#define echoDist 33

#define PINO_BUZZER  4


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

// ===== AUXILIAR TEMPORIZADOR =====
unsigned long marcaTempo = 0;

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

void obterDadosSensores()  {
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

  // Verificando se o sensor ultrassônico não vai dar erro
  long duracao = pulseIn(echoDist, HIGH);
  
  if(duracao == 0) {
    Serial.println("Erro no sensor ultrassônico");
  }

  distancia = (duracao * 0.0343) / 2;

  // Sensor de temperatura e humidade DHT11
  temperatura = sensorT.readTemperature();
  umidade = sensorT.readHumidity();

  if(isnan(temperatura) || isnan(umidade))  {
    Serial.println("Erro ao ler sensor DHT :| ");
  }

  // ===== PUBLICAR DADO =====
  String mensagem = "{\"temperatura\": " + String(temperatura) + "," + "\"umidade\": " + String(umidade) + "," + "\"distancia\": " + String(distancia) + "}";

  Serial.println("Enviando: " + mensagem);
  client.publish(mqtt_topic, mensagem.c_str());

}

// ===== DISPARAR ALARME =====
void disparaAlarme()  {
  // Faz la-mi por 4 vezes
  /*
  for(int i = 0; i < 4)  {
    tone(PORTA_BUZZER, 440, 250);
    delay(250);
    tone(PORTA_BUZZER, 330, 250);
    delay(250);
  }
  */
  int tempo = 120;
  marcaTempo = millis() - 2000;
  
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
  // Leitura de sensores, comunicação com MQTT, no tempo determinado de 2 segundos
  unsigned long tempoAtual = millis();
  if(tempoAtual - marcaTempo >= 2000)  {
    obterDadosSensores();
    marcaTempo = tempoAtual;
  }
  if(distancia <= 3.5)  {
    disparaAlarme();
  }
}

/* UNDERTALE
tone(PORTA_BUZZER, 279, tempo);
  delay(tempo);
  tone(PORTA_BUZZER, 279, tempo);
  delay(tempo);
  tone(PORTA_BUZZER, 279*2, tempo);
  delay(tempo);
  noTone(PORTA_BUZZER);
  delay(tempo);
  tone(PORTA_BUZZER, 417, tempo);
  delay(tempo);
  noTone(PORTA_BUZZER);
  delay(2*tempo);
  tone(PORTA_BUZZER, 392, tempo);
  delay(2*tempo);
  tone(PORTA_BUZZER, 371, tempo);
  delay(2*tempo);
  tone(PORTA_BUZZER, 330, 2*tempo);
  delay(2*tempo);
  tone(PORTA_BUZZER, 279, 2*tempo);
  delay(tempo);
  tone(PORTA_BUZZER, 330, tempo);
  delay(tempo);
  tone(PORTA_BUZZER, 371, tempo);
  delay(tempo);
*/

/* SWEET CHILD OF MINE
  tone(PORTA_BUZZER, 295, tempo);
  delay(tempo);
  tone(PORTA_BUZZER, 295*2, tempo);
  delay(tempo);
  tone(PORTA_BUZZER, 440, tempo);
  delay(tempo);
  tone(PORTA_BUZZER, 392, tempo);
  delay(tempo);
  tone(PORTA_BUZZER, 392*2, tempo);
  delay(tempo);
  tone(PORTA_BUZZER, 440, tempo);
  delay(tempo);
  tone(PORTA_BUZZER, 371*2, tempo);
  delay(tempo);
  tone(PORTA_BUZZER, 440, tempo);
  delay(tempo);
*/

/* NOKIA
tone(PORTA_BUZZER, 663*2, tempo);
  delay(tempo);
  tone(PORTA_BUZZER, 590*2, tempo);
  delay(tempo);
  tone(PORTA_BUZZER, 371*2, 2*tempo);
  delay(2*tempo);
  tone(PORTA_BUZZER, 417*2, 2*tempo);
  delay(2*tempo);
  tone(PORTA_BUZZER, 558*2, tempo);
  delay(tempo);
  tone(PORTA_BUZZER, 497*2, tempo);
  delay(tempo);
  tone(PORTA_BUZZER, 295*2, 2*tempo);
  delay(2*tempo);
  tone(PORTA_BUZZER, 330*2, 2*tempo);
  delay(2*tempo);
  tone(PORTA_BUZZER, 497*2, tempo);
  delay(tempo);
  tone(PORTA_BUZZER, 441*2, tempo);
  delay(tempo);
  tone(PORTA_BUZZER, 279*2, 2*tempo);
  delay(2*tempo);
  tone(PORTA_BUZZER, 330*2, 2*tempo);
  delay(2*tempo);
  tone(PORTA_BUZZER, 441*2, 4*tempo);
  delay(4*tempo);
  noTone(8);
*/
