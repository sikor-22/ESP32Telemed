#include "AnalogReader.h"



void AnalogReader::collect()
{
    // Wait for client connection
    while(1)
    {
        while(uxSemaphoreGetCount(m_client_connected) != 1)
        {
            delay(100);
        }
        Serial.println("Reader: starting collection");

        int startTime = millis();

        // While client is connected collect data
        while(xSemaphoreTake(m_client_connected, 0) == pdTRUE)
        {
            m_measurement.timestamp = millis()-startTime;
            m_measurement.value = analogRead(m_gpio);
            xQueueSendToFront(m_measurements_queue, (void*)&m_measurement, portMAX_DELAY);
            xSemaphoreGive(m_client_connected);
            delay(1);
        }
        Serial.println("Reader: ending collection");
    }
}