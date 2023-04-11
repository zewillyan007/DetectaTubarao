#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <iostream>
#include <string>

const String serialNumber = "15489-15028-69584-15039";
// Substitua com as suas informações de rede Wi-Fi
const char* ssid = "brisa-2908314";
const char* password = "dqszdq8h";
// const char* ssid = "Willyan's Galaxy S20 FE";
// const char* password = "123456789";

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
  //pinMode(pin34, INPUT);
}

void sendRequest(String chipNumber) {
  
  WiFiClient client;
  HTTPClient http;
  http.begin(client, "http://ec2-3-14-134-94.us-east-2.compute.amazonaws.com:5900/incidences"); // Substitua com a URL desejada
  http.addHeader("Content-Type", "application/json");

  // Crie um novo objeto JSON com nome e idade
  DynamicJsonDocument jsonPayload(1024);
  jsonPayload["ChipNumber"] = chipNumber;
  jsonPayload["MicrocontrollerSerialNumber"] = serialNumber;
  //delay(30000);

  // Serialize o objeto JSON como uma string
  String jsonStr;
  serializeJson(jsonPayload, jsonStr);

  if (WiFi.status() == WL_CONNECTED) {
    int httpCode = http.POST(jsonStr);

    // Verifique se a solicitação foi bem-sucedida
    if (httpCode > 0) {
      Serial.printf("[HTTP] Response Code: %d\n", httpCode);
      String response = http.getString();
      Serial.println(response);
    } else {
      Serial.printf("[HTTP] Bad Request. Error Code: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }
}

void loop() {
  // Verifique se o pino 34 está com nível lógico alto
  //if (digitalRead(pin34) == HIGH) {
    // Faça a requisição HTTP POST
     //}

while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Perda de conexão!");
    WiFi.begin(ssid, password);
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("Conectado novamente!");
    }
  }

String numbers[] = {"58479826", "15489823", "58479826", "58479826", "15489823"};

for (String number : numbers) {
  sendRequest(number);
  delay(60000);
}

  delay(1800000);
  // Nada a fazer no loop principal
}
