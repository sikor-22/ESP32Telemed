#pragma once

#include <Arduino.h>


struct Measurement
{
    /// @brief C-tor
    /// @param timestamp Timestamp of measurement 
    /// @param value Measured value
    Measurement(int timestamp, int value)
    : timestamp(timestamp)
    , value(value)
    {}
    
    /// @brief Default constructor
    Measurement()
    {}


    int timestamp;
    int value;
};

class AnalogReader
{
public:
    /// @brief C-tor
    /// @param adc Number of gpio pin with ADC
    AnalogReader(int adc, QueueHandle_t& measurements, SemaphoreHandle_t& client_connected)
    : m_gpio(adc)
    , m_measurements_queue(measurements)
    , m_client_connected(client_connected)
    {}

    /// @brief continously read data from gpio, as long as client connected semaphore is up 
    void collect();

    /// @brief Number of gpio pin to read from
    int m_gpio;
    Measurement m_measurement;
    QueueHandle_t m_measurements_queue;
    SemaphoreHandle_t m_client_connected;
};