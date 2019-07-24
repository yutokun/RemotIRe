#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRsend.h>
#include <IRutils.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <FS.h>

// Receiver
const uint16_t pin = 14; // D5 pin
const uint16_t bufferSize = 1024;
const uint8_t timeout = 15;
IRrecv receiver(pin, bufferSize, timeout, true);
decode_results results;

// Sender
int khz = 38;
IRsend sender(4); // D2 pin
uint16_t onSignal[295] = {4432, 4348, 588, 1576, 588, 1576, 588, 1576, 588, 1576, 588, 524, 556, 524, 556, 1580, 584, 496, 584, 496, 588, 496, 584, 524, 556, 496, 584, 1576, 588, 1576, 588, 524, 556, 1580, 588, 520, 560, 496, 584, 496, 584, 500, 584, 496, 584, 496, 584, 1576, 588, 1576, 588, 1576, 588, 1580, 584, 1580, 584, 1580, 584, 1580, 588, 1576, 588, 524, 556, 496, 584, 496, 584, 524, 556, 500, 584, 524, 556, 524, 556, 496, 584, 500, 580, 1580, 588, 1576, 588, 524, 556, 496, 584, 1580, 584, 496, 588, 492, 588, 492, 588, 496, 584, 1576, 588, 1580, 584, 496, 584, 500, 580, 500, 584, 524, 556, 1580, 584, 1576, 588, 496, 584, 496, 588, 496, 584, 496, 584, 492, 588, 496, 584, 496, 584, 500, 584, 496, 584, 1576, 588, 492, 588, 1576, 588, 500, 580, 496, 588, 1576, 588, 496, 584, 5224, 4432, 4348, 588, 1580, 584, 1580, 584, 1576, 588, 1576, 588, 496, 588, 496, 584, 1576, 588, 496, 584, 496, 584, 496, 584, 524, 556, 500, 584, 1576, 588, 1580, 584, 500, 580, 1576, 588, 500, 584, 496, 584, 496, 584, 492, 588, 496, 584, 524, 556, 1580, 584, 1580, 588, 1576, 588, 1580, 584, 1576, 588, 1576, 588, 1576, 588, 1580, 584, 496, 588, 496, 584, 496, 584, 492, 588, 496, 584, 524, 560, 520, 560, 492, 588, 524, 556, 1576, 588, 1576, 588, 500, 580, 496, 588, 1576, 588, 496, 584, 496, 584, 496, 584, 524, 560, 1576, 588, 1576, 588, 496, 584, 496, 584, 524, 556, 500, 584, 1576, 588, 1576, 588, 524, 556, 524, 556, 524, 556, 500, 584, 496, 584, 496, 584, 496, 584, 496, 588, 492, 584, 1580, 588, 496, 584, 1576, 588, 496, 584, 496, 588, 1576, 588, 492, 588};
uint16_t offSignal[295] = {4428, 4352, 588, 1576, 584, 1580, 588, 1576, 588, 1576, 588, 496, 584, 496, 584, 1580, 584, 496, 584, 496, 588, 496, 584, 496, 584, 500, 580, 1580, 584, 1580, 588, 492, 588, 1576, 588, 496, 584, 496, 584, 524, 560, 496, 584, 496, 584, 524, 556, 1580, 584, 1580, 584, 1576, 592, 1576, 588, 1576, 588, 1576, 588, 1576, 588, 1576, 588, 524, 556, 496, 588, 496, 584, 496, 584, 496, 584, 496, 584, 496, 584, 528, 556, 492, 588, 1576, 588, 1580, 584, 496, 584, 500, 584, 1576, 588, 500, 580, 496, 584, 496, 584, 496, 584, 1580, 588, 1576, 588, 496, 584, 496, 584, 496, 584, 1580, 588, 1576, 588, 1576, 588, 496, 584, 496, 584, 496, 584, 496, 588, 492, 588, 492, 588, 496, 584, 496, 584, 500, 580, 1580, 588, 496, 584, 1576, 588, 496, 584, 1580, 584, 1580, 588, 492, 588, 5108, 4432, 4352, 584, 1580, 584, 1580, 584, 1580, 588, 1576, 588, 496, 584, 496, 584, 1580, 584, 496, 588, 496, 584, 500, 580, 496, 584, 496, 584, 1580, 584, 1580, 584, 500, 584, 1576, 588, 496, 584, 496, 588, 492, 584, 500, 584, 492, 588, 524, 556, 1576, 588, 1580, 584, 1580, 588, 1576, 584, 1584, 584, 1576, 588, 1576, 588, 1576, 588, 496, 584, 496, 584, 496, 588, 492, 588, 496, 584, 500, 580, 524, 556, 496, 588, 496, 584, 1580, 584, 1576, 588, 496, 584, 496, 588, 1576, 588, 496, 584, 496, 584, 496, 584, 496, 584, 1580, 588, 1576, 588, 496, 584, 496, 584, 496, 584, 1580, 584, 1580, 588, 1576, 588, 496, 584, 496, 584, 496, 584, 496, 588, 496, 584, 496, 584, 500, 580, 496, 584, 496, 588, 1576, 584, 500, 584, 1580, 584, 524, 556, 1580, 584, 1580, 588, 492, 588};

// Network
const char *ssid;
const char *pswd;
const char *commandPath;
const char *commandIOPath;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  sender.begin();
  Serial.begin(115200, SERIAL_8N1);
  while (!Serial)
    delay(50);
  receiver.enableIRIn();

  if (!LoadConfig())
  {
    Serial.println("Failed to load configs.");
    return;
  }

  ConnectToWiFi();
}

void loop()
{
  // Receive();
  String command = GET(commandPath);
  SendCommand(command);

  for (size_t i = 0; i < 3; i++)
    delay(1000);
}

bool LoadConfig()
{
  SPIFFS.begin();
  File configFile = SPIFFS.open("/config.json", "r");
  if (!configFile)
  {
    Serial.println("Failed to open config file");
    return false;
  }

  size_t size = configFile.size();
  if (size > 1024)
  {
    Serial.println("Config file size is too large");
    return false;
  }

  std::unique_ptr<char[]> buf(new char[size]);
  configFile.readBytes(buf.get(), size);

  const int capacity = JSON_OBJECT_SIZE(4);
  StaticJsonDocument<capacity> doc;
  auto error = deserializeJson(doc, buf.get());
  if (error)
  {
    Serial.println("Failed to deserialize config file");
    Serial.println(error.c_str());
    return false;
  }

  ssid = doc["ssid"];
  pswd = doc["pswd"];
  commandPath = doc["command"];
  commandIOPath = doc["commandIO"];

  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("Password: ");
  Serial.println(pswd);
  Serial.print("Path to command: ");
  Serial.println(commandPath);
  Serial.print("Path to command IO: ");
  Serial.println(commandIOPath);
  return true;
}

void Receive()
{
  if (receiver.decode(&results))
  {
    uint32_t now = millis();
    Serial.printf("Timestamp : %06u.%03u\n", now / 1000, now % 1000);
    if (results.overflow)
    {
      Serial.printf("IR code is too big. Please increase bufferSize.");
    }

    // Display the basic output of what we found.
    Serial.print(resultToHumanReadableBasic(&results));
    yield(); // Feed the WDT as the text output can take a while to print.
    // Output RAW timing info of the result.
    Serial.println(resultToTimingInfo(&results));
    yield(); // Feed the WDT (again)
    // Output the results as source code
    Serial.println(resultToSourceCode(&results));
    Serial.println(); // Blank line between entries
    yield();          // Feed the WDT (again)
  }
}

void SendCommand(String command)
{
  Serial.println("Command: " + command);

  if (command == "s")
  {
    sender.sendRaw(onSignal, sizeof(onSignal) / sizeof(onSignal[0]), khz);
  }
  else if (command == "t")
  {
    sender.sendRaw(offSignal, sizeof(offSignal) / sizeof(offSignal[0]), khz);
  }
  else if (command == "wait")
  {
    Serial.println("Wait for next command.");
    return;
  }
  else
  {
    Serial.println("Unknown command. Fixing...");
  }

  POST(commandIOPath, "c=wait");
  Serial.println("Sent");

  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
}

void ConnectToWiFi()
{
  WiFi.mode(WIFI_STA);
  // WiFi.printDiag(Serial);
  Serial.println(ssid);
  Serial.println(pswd);
  WiFi.begin(ssid, pswd);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("Connected to Wi-Fi");

  WiFi.printDiag(Serial);
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

String GET(const char *host)
{
  HTTPClient http;
  http.begin(host);
  int httpCode = http.GET();

  String result = "";
  if (httpCode < 0)
  {
    result = http.errorToString(httpCode);
  }
  else if (http.getSize() < 0)
  {
    result = "size is invalid";
  }
  else
  {
    result = http.getString();
  }

  http.end();
  return result;
}

void POST(const char *host, const char *payload)
{
  HTTPClient http;
  http.begin(host);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpCode = http.POST(String(payload));
  Serial.printf("[HTTP] POST... code: %d\n", httpCode);
  Serial.println(http.getString());
  http.end();
}