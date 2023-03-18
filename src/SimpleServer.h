#pragma once


#include <Arduino.h>
#include <WiFi.h>
#include "AnalogReader.h"

class SimpleServer
{
public:
    /// @brief C-tor
    /// @param port Port to listen on
    SimpleServer(int port, QueueHandle_t& measurements, SemaphoreHandle_t& client_connected)
    : m_port(port)
    , m_server(WiFiServer(port))
    , m_measurements_queue(measurements)
    , m_client_connected(client_connected)
    {}

    /// @brief Setup server and listen for connections 
    void setup();

    /// @brief Accept connections and send measurement data
    void mainLoop();

    int m_port;
    WiFiServer m_server;
    Measurement m_measurement;
    QueueHandle_t m_measurements_queue;
    SemaphoreHandle_t m_client_connected;
};