const mqtt = require("mqtt");
const { Pool } = require("pg");
const express = require("express");
const cors = require("cors");

// ===== CONFIG =====
const MQTT_BROKER = "mqtt://54.91.1.57:1883";  // IP públic condizendo com o IP atual da instância na AWS
const TOPIC = "esp32/teste";

// ===== DB =====
const pool = new Pool({
  user: "postgres",
  host: "localhost",
  database: "iot",
  password: "123456",
  port: 5432,
});

(async () => {
  try {
    const result = await pool.query("SELECT current_database()");
    console.log("Banco conectado:", result.rows[0]);
  } catch (err) {
    console.error("Erro ao conectar no banco:", err);
  }
})();

// ===== MQTT =====
const client = mqtt.connect(MQTT_BROKER);

client.on("connect", () => {
  console.log("Conectado ao MQTT");
  client.subscribe(TOPIC);
});

client.on("message", async (topic, message) => {
  console.log("RAW:", message.toString());

  try {
    const data = JSON.parse(message.toString());


    console.log("JSON:", data);
    const temperatura = data.temperatura;
    const umidade = data.umidade;
    const distancia = data.distancia;

    if(temperatura === undefined || umidade === undefined || distancia === undefined)   {
        console.log("Dados inválidos!");
        return;
    }

    await pool.query(
      "INSERT INTO leituras (temperatura, umidade, distancia) VALUES ($1, $2, $3)",
      [temperatura, umidade, distancia]
    );

    console.log(" INSERT realizado!");
  } catch (err) {
    console.error(" ERRO COMPLETO:", err);
  }
});

// ===== API =====
const app = express();
app.use(cors());

app.get("/dados", async (req, res) => {
  const result = await pool.query(
    "SELECT * FROM leituras ORDER BY timestamp DESC LIMIT 1"
  );
  res.json(result.rows);
});

app.listen(3000, () => {
  console.log("API rodando na porta 3000");
});

// ====== End point para a aplicação web ======
app.get("/historico", async (req, res) => {
        try {
          const result = await pool.query(
            "SELECT * FROM leituras ORDER BY timestamp DESC LIMIT 20"
          );
          res.json(result.rows);
        } catch (err) {
                console.error(err);
                res.status(500).send("Erro no servidor");
        }
});
