#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

const char* ssid = "esp"; // Nome da rede Wi-Fi
const char* password = "teste32esp"; // Senha da rede Wi-Fi

AsyncWebServer server(80); // Criação do objeto do servidor na porta 80

void setup() {
  Serial.begin(115200); // Inicialização da comunicação serial

  WiFi.begin(ssid, password); // Conexão Wi-Fi

  while (WiFi.status() != WL_CONNECTED) { // Aguarda a conexão Wi-Fi ser estabelecida
    delay(1000);
    Serial.println("Connecting to WiFi..."); // Mensagem exibida durante a tentativa de conexão
  }

  Serial.println("Connected to WiFi"); // Mensagem exibida quando a conexão Wi-Fi é estabelecida

  // Imprime o endereço IP no console
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); // Exibe o endereço IP local atribuído ao ESP32

  // Configuração do endpoint "/"
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
   
    // Criando um objeto JSON
    DynamicJsonDocument jsonDoc(1024);

    // Preenche o objeto JSON com os dados simulados do sensor
    jsonDoc["sensor"] = "ESP32";
    jsonDoc["temperatura"] = random(0, 50);   // Gera um valor aleatório entre 0 e 50 para temperatura
    jsonDoc["umidade"] = random(30, 80);      // Gera um valor aleatório entre 30 e 80 para umidade

    // Convertendo o objeto JSON para uma string
    String jsonString;
    serializeJson(jsonDoc, jsonString);

    // Configurando o cabeçalho da resposta HTTP e enviando o JSON como resposta
    request->send(200, "application/json", jsonString);
  });

  server.begin(); // Inicia o servidor web
}

void loop() {
  // Aguarda novas requisições
}
