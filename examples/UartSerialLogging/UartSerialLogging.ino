#include <Arduino.h>
#include <Log.h>

const uint16_t TIME_BETWEEN_LOGS_MS = 3000;

void setup()
{
    Serial1.begin(115200);
    Logger::addOutputStream(&Serial1);
}

uint64_t timeOfLastLog_ms = 0;
void loop()
{
    if (millis() >= timeOfLastLog_ms + TIME_BETWEEN_LOGS_MS)
    {
        LOG_INFO("time: %lu", millis());
        timeOfLastLog_ms = millis();
    }
    delay(100);
}