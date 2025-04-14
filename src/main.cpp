#include <Arduino.h>
#include <WebSocketsClient.h>
#include <WiFi.h>

const String WS_SERVER_URL = "pesentiws-43f6274c0f11.herokuapp.com";

WebSocketsClient wsClient;

void setup() {
  Serial.begin(115200);
  Serial.println("Connecting to WiFi...");
  WiFi.begin("nomeWifi", "passwordWifi");
  while (WiFi.status() != WL_CONNECTED) {};
  Serial.println("WiFi connected! IP Address: " + WiFi.localIP().toString());

  wsClient.beginSSL(WS_SERVER_URL, 443, "/");
  Serial.println("wsClient.beginSSL: " + WS_SERVER_URL + ", 443, /");
  wsClient.onEvent([](WStype_t type, uint8_t *payload, size_t length) {
    const bool hasData = type == WStype_TEXT && length > 0;
    Serial.print("Type: "); Serial.println(type);
    Serial.print("Length: "); Serial.println(length);
    Serial.print("Payload: "); Serial.println((char *)payload);
    if (!hasData) { return; }
    Serial.println("🟩hasData: " + String(hasData));
    const String thisWsReceivedStringData = String((char *) payload).substring(0, length);
    Serial.println("payload: " + String((char *) payload));
    Serial.println("thisWsReceivedStringData: " + thisWsReceivedStringData);
    Serial.println(thisWsReceivedStringData);
  });
}

void loop() {
  wsClient.loop();
}
