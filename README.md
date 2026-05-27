# Sistema de Monitoramento de Enchentes com ESP32

## Integrantes do Grupo

| Nome         | RA    |
| ------------ | ----- |
| Ana Catarina | 41383 |
| Colin Beluco | 40975 |
| Diego Santos | 41331 |
| Joyce Lidia  | 41397 |

---

# Resumo do Projeto

O projeto consiste em um sistema inteligente de monitoramento de enchentes e alagamentos utilizando computação embarcada e infraestrutura em nuvem. A solução foi desenvolvida com um microcontrolador ESP32 conectado a sensores responsáveis pela coleta de dados ambientais em tempo real, incluindo temperatura, umidade e nível da água.

As informações coletadas são transmitidas via protocolo MQTT para uma infraestrutura hospedada na AWS, onde são processadas e armazenadas em um banco de dados PostgreSQL. Por fim, os dados são exibidos em um painel web desenvolvido com Ionic, permitindo acompanhamento remoto das condições monitoradas e auxiliando na prevenção de riscos à população.

---

# Arquitetura do Projeto

## Hardware Utilizado

* ESP32 com conexão Wi-Fi
* Sensor DHT11

  * Medição de temperatura
  * Medição de umidade
* Sensor Ultrassônico HC-SR04

  * Medição do nível da água

---

# Comunicação e Protocolos

O sistema utiliza o protocolo MQTT para comunicação entre o ESP32 e os serviços em nuvem.

## Broker MQTT Utilizado

* Mosquitto MQTT

## Tópico MQTT Utilizado

```txt
esp32/topico
```

---

# Portas Utilizadas

| Serviço          | Porta |
| ---------------- | ----- |
| MQTT (Mosquitto) | 1883  |
| API Backend      | 3000  |
| PostgreSQL       | 5432  |
| Frontend Ionic   | 8101  |

---

# Infraestrutura em Nuvem

Toda a infraestrutura do sistema, exceto o frontend, foi executada em uma instância EC2 da AWS.

## Serviços Hospedados

* Broker MQTT (Mosquitto)
* API Node.js
* Banco de Dados PostgreSQL

## Instância Utilizada

* AWS EC2 t3.micro

---

# Frontend

O frontend foi desenvolvido utilizando:

* Ionic
* Angular
* HTML
* SCSS
* JavaScript

## Funcionalidades do Frontend

* Visualização da temperatura em tempo real
* Visualização da umidade em tempo real
* Monitoramento da distância relativa da água
* Exibição do nível de atenção conforme aumento do nível do rio

---

# Como Executar o Projeto

## Pré-requisitos

Instalar as versões mais recentes dos seguintes softwares:

* Node.js
* PostgreSQL
* Ionic CLI
* Mosquitto MQTT
* Arduino IDE

---

# Configuração Inicial

## 1. Configurar Banco de Dados PostgreSQL

Criar o banco de dados utilizado pela API backend.

---

## 2. Configurar Broker MQTT

Iniciar o serviço do Mosquitto MQTT utilizando a porta padrão:

```txt
1883
```

---

## 3. Atualizar Endereço IP Público

Antes de executar o sistema, atualizar o endereço IP público da máquina AWS:

* Nos arquivos do backend
* No código da ESP32 (Arduino)

---

## 4. Configurar Wi-Fi da ESP32

No código da ESP32, atualizar:

* Nome da rede Wi-Fi (SSID)
* Senha da rede Wi-Fi

---

# Executando o Backend

Acessar a pasta do backend e executar:

```bash
node <nome_do_arquivo>.js
```

## Exemplo

```bash
node server.js
```

---

# Executando o Frontend Ionic

## Instalar Dependências

```bash
npm install
```

## Executar Frontend

```bash
ionic serve --port=8101
```

---

# Executando o Código da ESP32

1. Abrir o código na Arduino IDE
2. Selecionar a placa ESP32
3. Compilar e enviar o código
4. Verificar conexão MQTT e envio dos dados

---

# Fluxo Geral do Sistema

```txt
ESP32 + Sensores
        ↓
      MQTT
        ↓
 Broker Mosquitto
        ↓
    API Node.js
        ↓
    PostgreSQL
        ↓
  Frontend Ionic
```
