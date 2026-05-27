# Sistema de Monitoramento de Enchentes com ESP32

## Integrantes do Grupo

| Nome | RA |
|---|---|---|
| Ana Catarina | 41383 |
| Colin Beluco | 40975 |
| Diego Santos | 41331 |
| Joyce Lidia | 41397 |

---

# Resumo do Projeto

O projeto consiste em um sistema inteligente de monitoramento de enchentes e alagamentos utilizando computação embarcada e infraestrutura em nuvem. A solução foi desenvolvida com um microcontrolador ESP32 conectado a sensores responsáveis pela coleta de dados ambientais em tempo real, incluindo temperatura, umidade e nível da água. As informações são transmitidas via protocolo MQTT para uma infraestrutura hospedada na AWS, onde são processadas e armazenadas em um banco de dados PostgreSQL. Por fim, os dados são exibidos em um painel web desenvolvido com Ionic, permitindo acompanhamento remoto das condições monitoradas e auxiliando na prevenção de riscos à população.

---

# Arquitetura do Projeto

## Hardware Utilizado

- ESP32 com conexão Wi-Fi
- Sensor DHT11
  - Temperatura
  - Umidade
- Sensor Ultrassônico HC-SR04
  - Medição do nível da água

---

# Comunicação e Protocolos

O sistema utiliza o protocolo MQTT para comunicação entre o ESP32 e os serviços em nuvem. O broker utilizado foi o Mosquitto MQTT.

### Tópico MQTT utilizado

```txt
esp32/topico
