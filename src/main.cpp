#include <Arduino.h>
#include <WebSocketsClient.h>
#include <WiFi.h>

#include <vector>
// #include <Adafruit_NeoPixel.h>
#include <ESP32Servo.h>

const String WS_SERVER_URL = "pesentiws-43f6274c0f11.herokuapp.com";

WebSocketsClient wsClient;

Servo motoreEntrata;
const int pinMotoreEntrata = 15;
Servo motoreUscita;
const int pinMotoreUscita = 2;

void setup() {
  Serial.begin(115200);
  Serial.println("Connecting to WiFi...");
  WiFi.begin("nomeWifi", "passwordWifi");
  while (WiFi.status() != WL_CONNECTED) {
  };
  Serial.println("WiFi connected! IP Address: " + WiFi.localIP().toString());
  motoreEntrata.attach(pinMotoreEntrata);
  motoreUscita.attach(pinMotoreUscita);

  wsClient.beginSSL(WS_SERVER_URL, 443, "/");
  wsClient.onEvent([](WStype_t type, uint8_t *payload, size_t length) {
    if (length == 0) return;
    const String thisWsReceivedStringData =
        String((char *)payload).substring(0, length);
    if (thisWsReceivedStringData == "/") return;

    const String wsKey = thisWsReceivedStringData.substring(
        0, thisWsReceivedStringData.indexOf(":"));
    const String wsValue = thisWsReceivedStringData.substring(
        thisWsReceivedStringData.indexOf(":") + 1);
    Serial.println("wsKey: " + wsKey + " wsValue: " + wsValue);

    const char DELIMITER = ',';
    std::vector<int> dimiliterPositions;
    std::vector<String> splittedStringValues;

    for (int forCharIndex = 0; forCharIndex < wsValue.length();
         forCharIndex++) {
      const char thisChar = wsValue[forCharIndex];
      const bool canGoToNextSplittedString = thisChar == DELIMITER;

      if (!canGoToNextSplittedString) continue;
      dimiliterPositions.push_back(forCharIndex);
    }

    for (int forSplittedIndex = 0; forSplittedIndex < dimiliterPositions.size();
         forSplittedIndex++) {
      const int thisDimiliterPosition =
          forSplittedIndex == 0 ? 0 : dimiliterPositions[forSplittedIndex] + 1;
      const int nextDimiliterPosition =
          forSplittedIndex == 0 ? dimiliterPositions[forSplittedIndex]
                                : dimiliterPositions[forSplittedIndex + 1];
      const String thisSplittedString =
          wsValue.substring(thisDimiliterPosition, nextDimiliterPosition);
      splittedStringValues.push_back(thisSplittedString);
    }

    // INIZIO LOGICA

    if (wsKey == "ingresso") {
      motoreEntrata.write(wsValue == "0" ? 90 : 0);
    }

    if (wsKey == "uscita") {
      motoreUscita.write(wsValue == "1" ? 90 : 180);
    }

    // FINE LOGICA
  });
}

void loop() { wsClient.loop(); }
