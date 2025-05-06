#include "LaaWifiWsBoiderplate.h"

#include <Arduino.h>
#include <vector>
#include <WebSocketsClient.h>
#include <WiFi.h>

class LaaWifiWs {
  public:
    LaaWifiWs(String wsServerUrl, String wifiNome = "nomeWifi",
              String wifiPassword = "passwordWifi") {
      laaConnectToWifi(wifiNome, wifiPassword);
      laaConnectToWs(wsServerUrl);
    };
}

void LaaWifiWs::laaConnectToWifi(String wifiNome, String wifiPassword) {
  Serial.println("Connecting to WiFi...");

  WiFi.begin(wifiNome, wifiPassword);
  while (WiFi.status() != WL_CONNECTED);
  Serial.println("WiFi connected! IP Address: " + WiFi.localIP().toString());
}

void LaaWifiWs::laaConnectToWs(String wsServerUrl) {
  wsClient.beginSSL(wsServerUrl, 443, "/");
}

void LaaWifiWs::laaLoop() {
  wsClient.loop();
};

void LaaWifiWs::laaOnReceiveMessage(void (*myCallback)(String wsKey, String wsValue)) {
  wsClient.onEvent([myCallback](WStype_t type, uint8_t *payload, size_t length) {
    if (length == 0) { return; }

    const String thisWsReceivedStringData = String((char *) payload).substring(0, length);
    if (thisWsReceivedStringData == "/") { return; }

    const String wsKey =
      thisWsReceivedStringData.substring(0, thisWsReceivedStringData.indexOf(":"));
    const String wsValue =
      thisWsReceivedStringData.substring(thisWsReceivedStringData.indexOf(":") + 1);

    std::vector<int>    dimiliterPositions;
    std::vector<String> splittedStringValues;
    const char          DELIMITER = ',';

    for (int forCharIndex = 0; forCharIndex < wsValue.length(); forCharIndex++) {
      const char thisChar                  = wsValue[forCharIndex];
      const bool canGoToNextSplittedString = thisChar == DELIMITER;
      if (!canGoToNextSplittedString) { continue; }

      dimiliterPositions.push_back(forCharIndex);
    }

    for (int forSplittedIndex = 0; forSplittedIndex < dimiliterPositions.size();
         forSplittedIndex++) {
      const int thisDimiliterPosition =
        forSplittedIndex == 0 ? 0 : dimiliterPositions[forSplittedIndex] + 1;
      const int nextDimiliterPosition = forSplittedIndex == 0
                                        ? dimiliterPositions[forSplittedIndex]
                                        : dimiliterPositions[forSplittedIndex + 1];

      const String thisSplittedString =
        wsValue.substring(thisDimiliterPosition, nextDimiliterPosition);
      splittedStringValues.push_back(thisSplittedString);
    }

    myCallback(wsKey, wsValue);
  });
}