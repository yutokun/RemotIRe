#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRsend.h>
#include <IRutils.h>

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
// uint16_t offSignal[] = {4428, 4352, 588, 1576, 584, 1580, 588, 1576, 588, 1576, 588, 496, 584, 496, 584, 1580, 584, 496, 584, 496, 588, 496, 584, 496, 584, 500, 580, 1580, 584, 1580, 588, 492, 588, 1576, 588, 496, 584, 496, 584, 524, 560, 496, 584, 496, 584, 524, 556, 1580, 584, 1580, 584, 1576, 592, 1576, 588, 1576, 588, 1576, 588, 1576, 588, 1576, 588, 524, 556, 496, 588, 496, 584, 496, 584, 496, 584, 496, 584, 496, 584, 528, 556, 492, 588, 1576, 588, 1580, 584, 496, 584, 500, 584, 1576, 588, 500, 580, 496, 584, 496, 584, 496, 584, 1580, 588, 1576, 588, 496, 584, 496, 584, 496, 584, 1580, 588, 1576, 588, 1576, 588, 496, 584, 496, 584, 496, 584, 496, 588, 492, 588, 492, 588, 496, 584, 496, 584, 500, 580, 1580, 588, 496, 584, 1576, 588, 496, 584, 1580, 584, 1580, 588, 492, 588, 5108, 4432, 4352, 584, 1580, 584, 1580, 584, 1580, 588, 1576, 588, 496, 584, 496, 584, 1580, 584, 496, 588, 496, 584, 500, 580, 496, 584, 496, 584, 1580, 584, 1580, 584, 500, 584, 1576, 588, 496, 584, 496, 588, 492, 584, 500, 584, 492, 588, 524, 556, 1576, 588, 1580, 584, 1580, 588, 1576, 584, 1584, 584, 1576, 588, 1576, 588, 1576, 588, 496, 584, 496, 584, 496, 588, 492, 588, 496, 584, 500, 580, 524, 556, 496, 588, 496, 584, 1580, 584, 1576, 588, 496, 584, 496, 588, 1576, 588, 496, 584, 496, 584, 496, 584, 496, 584, 1580, 588, 1576, 588, 496, 584, 496, 584, 496, 584, 1580, 584, 1580, 588, 1576, 588, 496, 584, 496, 584, 496, 584, 496, 588, 496, 584, 496, 584, 500, 580, 496, 584, 496, 588, 1576, 584, 500, 584, 1580, 584, 524, 556, 1580, 584, 1580, 588, 492, 588};

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  sender.begin();
  Serial.begin(115200, SERIAL_8N1);
  while (!Serial)
    delay(50);
  receiver.enableIRIn();
}

void loop()
{
  char command;
  // Receive();

  if (Serial.available())
  {
    command = Serial.read();
    if (command == 's')
      Send();
    else
      Serial.println("Unknown command.");
  }
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

void Send()
{
  Serial.println("Sending Signal...");
  sender.sendRaw(onSignal, sizeof(onSignal) / sizeof(onSignal[0]), khz);
  Serial.println("Sent");

  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
}