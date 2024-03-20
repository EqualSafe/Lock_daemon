#include "Deadlock.hpp"
#include <iostream>

Deadlock::Deadlock(const std::string &endpoint, const std::string &certPath, const std::string &keyPath, const std::string &clientId)   
    : mqtt(endpoint, certPath, keyPath, clientId)
{
    state = "";
    if (gpioInitialise() < 0)
    {
        std::cerr << "pigpio initialization failed." << std::endl;
    }
    gpioSetMode(PIN, PI_OUTPUT); // Set the GPIO pin to output mode
}

void Deadlock::start()
{
    if (mqtt.connect() != 0)
    {
        std::cerr << "Failed to connect to MQTT broker." << std::endl;
        return;
    }

    // Lambda function to handle messages
    auto handleMessage = [this](const std::string &topic, std::string message) -> int
    {
        return this->processMessage(topic, message);
    };

    mqtt.subscribe("System/deadbolt/#", handleMessage);
}

int Deadlock::processMessage(const std::string &topic, const std::string &message)
{
    // Split the topic to extract the command and unique ID
    std::vector<std::string> topicParts;
    std::stringstream topicStream(topic);
    std::string part;

    while (getline(topicStream, part, '/'))
    {
        topicParts.push_back(part);
    }

    if (topicParts.size() >= 4) // Ensure the topic has enough parts
    {
        const std::string command = topicParts[2];  // "lock" or "unlock"
        const std::string uniqueId = topicParts[3]; // unique ID

        if ((command == "lock") && (state != "Locked"))
        {
            std::cout << "Lock command received for ID " << uniqueId << std::endl;
            state = "Locked";
            gpioWrite(PIN, 0); // Set the GPIO pin to HIGH to lock
        }
        else if ((command == "unlock") && (state != "Unlocked"))
        {
            std::cout << "Unlock command received for ID " << uniqueId << std::endl;
            state = "Unlocked";
            gpioWrite(PIN, 1); // Set the GPIO pin to LOW to unlock
        }
        else
        {
            std::cout << "Deadlock already " << state << std::endl;
            return 0;
        }

        // Publish the state
        Json statePayload;
        statePayload["state"] = state;
        std::string payload = statePayload.dump();

        mqtt.publish("System/deadbolt/status", payload, true);
    }
    else
    {
        std::cout << "Received message on topic: " << topic << " with payload: "<< message <<std::endl;
        return 1;
    }

    return 0; // Success
}

void Deadlock::stop()
{
    mqtt.disconnect();
}
