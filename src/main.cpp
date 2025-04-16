#include <Arduino.h>
#include <WebSocketsClient.h>
#include <WiFi.h>
#include <vector>
#include <LPD8806.h>

const String WS_SERVER_URL = "pesentiws-43f6274c0f11.herokuapp.com";

WebSocketsClient wsClient;

const int nLEDs = 36;
const int PIN_CLOCK = 6;
const int PIN_DATA = 15;

// LPD8806 strip = LPD8806(nLEDs, PIN_DATA, PIN_CLOCK);

// std::vector<int> ledPositions = {35, 32, 30, 20, 17, 15, 6, 3, 0};

void setup() {
  Serial.begin(115200);
  strip.begin();
  Serial.println("Connecting to WiFi...");
  WiFi.begin("nomeWifi", "passwordWifi");
  while (WiFi.status() != WL_CONNECTED) {
  };
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
    Serial.println("wsValue: " + wsValue);

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
      Serial.println("thisSplittedString: " + thisSplittedString);
      splittedStringValues.push_back(thisSplittedString);
    }

    for (int ledIndex = 0; ledIndex < dimiliterPositions.size(); ledIndex++) {
      const int thisLedPosition = ledPositions[ledIndex];
      const int thisValue = splittedStringValues[ledIndex].toInt();
      const int choosedColor = thisValue == 0 ? strip.Color(255, 0, 0) : strip.Color(0, 255, 0);
      // strip.setPixelColor(thisLedPosition, choosedColor);
    }

    // strip.show();
  });
}

void loop() { wsClient.loop(); }
