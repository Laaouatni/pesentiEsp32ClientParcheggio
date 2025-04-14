#include <Arduino.h>
#include <WebSocketsClient.h>
#include <WiFi.h>

const String WS_SERVER_URL = "pesentiws-43f6274c0f11.herokuapp.com";

WebSocketsClient wsClient;

void setup() {
  Serial.begin(115200);
  Serial.println("Connecting to WiFi...");
  WiFi.begin("nomeWifi", "passwordWifi");
  while (WiFi.status() != WL_CONNECTED) {
  };
  Serial.println("WiFi connected! IP Address: " + WiFi.localIP().toString());

  wsClient.beginSSL(WS_SERVER_URL, 443, "/");
  Serial.println("wsClient.beginSSL: " + WS_SERVER_URL + ", 443, /");
  wsClient.onEvent([](WStype_t type, uint8_t *payload, size_t length) {
    if (length == 0) return;
    const String thisWsReceivedStringData =
        String((char *)payload).substring(0, length);
    if (thisWsReceivedStringData == "/") return;
    Serial.println(" '" + thisWsReceivedStringData + "' received from server.");
    // Serial.println(thisWsReceivedStringData);
  });
}

void loop() { wsClient.loop(); }
