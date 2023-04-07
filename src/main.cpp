#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Substitua com as suas informações de rede Wi-Fi
// const char* ssid = "Willyan's Galaxy S20 FE";
// const char* password = "123456789";

const char* ssid = "brisa-2908314";
const char* password = "dqszdq8h";

// Pino de entrada para verificar o nível lógico
const int pin34 = 34;

void setup() {
  // Inicialize a comunicação serial
  Serial.begin(9600);

  // Conecte-se à rede Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("Conectado ao WiFi");

  // Configure o pino 34 como entrada
  pinMode(pin34, INPUT);
}

void loop() {
  // Verifique se o pino 34 está com nível lógico alto
  if (digitalRead(pin34) == HIGH) {
    // Faça a requisição HTTP POST
    WiFiClient client;
    HTTPClient http;
    http.begin(client, "https://www.example.com"); // Substitua com a URL desejada
    http.addHeader("Content-Type", "application/json");

    // Crie um novo objeto JSON com nome e idade
    DynamicJsonDocument jsonPayload(1024);
    jsonPayload["nome"] = "Willyan";
    jsonPayload["idade"] = 23;

    // Serialize o objeto JSON como uma string
    String jsonStr;
    serializeJson(jsonPayload, jsonStr);

    int httpCode = http.POST(jsonStr);

    // Verifique se a solicitação foi bem-sucedida
    if (httpCode > 0) {
      Serial.printf("[HTTP] Código de resposta: %d\n", httpCode);
      String response = http.getString();
      Serial.println(response);
    } else {
      Serial.printf("[HTTP] Falha na solicitação. Código de erro: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }

  // Nada a fazer no loop principal
}
