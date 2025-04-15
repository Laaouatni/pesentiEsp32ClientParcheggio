#include <Arduino.h>
#include <WebSocketsClient.h>
#include <WiFi.h>
#include <vector>

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
      const int thisDimiliterPosition = dimiliterPositions[forSplittedIndex];
      const int nextDimiliterPosition = (forSplittedIndex + 1) < dimiliterPositions.size() ? dimiliterPositions[forSplittedIndex + 1] : wsValue.length();
      const String thisSplittedString = wsValue.substring(thisDimiliterPosition, nextDimiliterPosition);
      Serial.println("thisSplittedString: " + thisSplittedString);
      splittedStringValues.push_back(thisSplittedString);
    }

    // int lastSplittedStringIndex = 0;

    // for (int forCharIndex = 0; forCharIndex < wsValue.length(); forCharIndex++) {
    //   const char thisChar = wsValue[forCharIndex];
    //   const bool canGoToNextSplittedString = thisChar == ',';

    //   if(!canGoToNextSplittedString) {
    //     splittedStringValues[splittedStringValues.size() - 1] += thisChar;
    //     continue;
    //   }
    //   splittedStringValues.push_back("");
    // }

    // for(String thisSplittedString : splittedStringValues) {
    //   Serial.print(thisSplittedString);
    // };
    // Serial.println("-----");
  });
}

void loop() { wsClient.loop(); }
