#include <Arduino.h>
#include <WebSocketsClient.h>
#include <WiFi.h>
#include <vector>
#include <Adafruit_NeoPixel.h>

const String WS_SERVER_URL = "pesentiws-43f6274c0f11.herokuapp.com";

WebSocketsClient wsClient;

Adafruit_NeoPixel listaLeds = Adafruit_NeoPixel(60, 15, NEO_GRB);

std::vector<int> ledPositions = {0,4,7,20,23,26,38,42,45};

void setup() {
  Serial.begin(115200);
  listaLeds.begin();
  Serial.println("Connecting to WiFi...");
  WiFi.begin("nomeWifi", "passwordWifi");
  while (WiFi.status() != WL_CONNECTED) {};
  Serial.println("WiFi connected! IP Address: " + WiFi.localIP().toString());

  wsClient.beginSSL(WS_SERVER_URL, 443, "/");
  wsClient.onEvent([](WStype_t type, uint8_t *payload, size_t length) {
    if (length == 0) return;
    const String thisWsReceivedStringData =
        String((char *)payload).substring(0, length);
    if (thisWsReceivedStringData == "/") return;

    const String wsKey = thisWsReceivedStringData.substring(0, thisWsReceivedStringData.indexOf(":"));
    const String wsValue = thisWsReceivedStringData.substring(thisWsReceivedStringData.indexOf(":")+1);
    Serial.println("wsKey: " + wsKey);
    // Serial.println("wsValue: " + wsValue);

    const char DELIMITER = ',';
    std::vector<int> dimiliterPositions;
    std::vector<String> splittedStringValues;

    for(int forCharIndex = 0; forCharIndex < wsValue.length(); forCharIndex++) {
      const char thisChar = wsValue[forCharIndex];
      const bool canGoToNextSplittedString = thisChar == DELIMITER;

      if(!canGoToNextSplittedString) continue;
      dimiliterPositions.push_back(forCharIndex);
    }

    for (int forSplittedIndex = 0; forSplittedIndex < dimiliterPositions.size(); forSplittedIndex++) {
      const int thisDimiliterPosition = forSplittedIndex == 0 ? 0 : dimiliterPositions[forSplittedIndex]+1;
      const int nextDimiliterPosition = forSplittedIndex == 0 ? dimiliterPositions[forSplittedIndex] : dimiliterPositions[forSplittedIndex+1];
      const String thisSplittedString = wsValue.substring(thisDimiliterPosition, nextDimiliterPosition);
      // Serial.println("thisSplittedString: " + thisSplittedString);
      splittedStringValues.push_back(thisSplittedString);
    }

    for (int ledIndex = 0; ledIndex < dimiliterPositions.size(); ledIndex++) {
      const int thisLedPosition = ledPositions[ledIndex];
      const int thisValue = splittedStringValues[ledIndex].toInt();
      const int choosedColor = thisValue == 1 ? listaLeds.Color(255, 0, 0) : listaLeds.Color(0, 255, 0);
      listaLeds.setPixelColor(thisLedPosition, choosedColor);

      Serial.println("ledIndex: " + String(ledIndex) + " thisLedPosition: " + String(thisLedPosition) + " thisValue: " + String(thisValue) + " choosedColor: " + String(choosedColor) + " wsValue: " + wsValue);
    }

    listaLeds.show();
  });
}

void loop() { wsClient.loop(); }
