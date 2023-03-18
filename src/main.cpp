#include <WiFi.h>
#include "SimpleServer.h"
#include "AnalogReader.h"


// Wifi params
const char* ssid = "Antena 6G Test 150% Mocy"; //edit this with network name
const char* password = "rektor123"; //edit this with network password

// Components params
const int port = 42069;
const int adc_pin = 32;

// Inter task comms
static SemaphoreHandle_t client_connected = xSemaphoreCreateBinary();
static QueueHandle_t measurements = xQueueCreate(2048, sizeof(Measurement));

// Components
SimpleServer server = SimpleServer(port, measurements, client_connected);
AnalogReader reader = AnalogReader(adc_pin, measurements, client_connected);

// Wrapper functions
void server_loop(void *parameters)
{
    server.mainLoop();
}

void reader_loop(void *parameters)
{
    reader.collect();
}


void setup()
{
    /// Begin serial
    Serial.begin(115200);
    delay(1000);

    /// Connect to WiFi
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("\nConnecting");

    while(WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(100);
    }

    Serial.println("\nConnected to the WiFi network");
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());

    server.setup();

    // Create tasks
    xTaskCreatePinnedToCore(
        server_loop,
        "Server Loop",
        10000,
        NULL,       
        0,
        NULL,
        1
    );

    xTaskCreatePinnedToCore(
        reader_loop,
        "reader Loop",
        10000,
        NULL,       
        0,
        NULL,
        0
    );
    Serial.println("main: Tasks created");
}

void loop()
{
    vTaskDelay(1000 / portTICK_PERIOD_MS);
}