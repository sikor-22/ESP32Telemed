#include "SimpleServer.h"
#include <string.h>

void SimpleServer::setup()
{
    m_server.begin();
    Serial.println("Server set up");
}

void SimpleServer::mainLoop()
{
    while(1)
    {
        WiFiClient client = m_server.available();

        // Raise the semaphore
        if(client.connected())
        {
            xSemaphoreGive(m_client_connected);
            Serial.println("Server: client connected");
            // Send data
            while(client.connected())
            {
                xQueueReceive(m_measurements_queue, &m_measurement, portMAX_DELAY);
                //Serial.println("Server: " + String(m_measurement.timestamp) + "," + String(m_measurement.value));
                client.println(String(m_measurement.timestamp) + "," + String(m_measurement.value));
            }
            xSemaphoreTake(m_client_connected, portMAX_DELAY);
        }
    }
}