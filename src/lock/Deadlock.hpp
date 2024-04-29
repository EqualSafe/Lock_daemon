/*
 * Equal Safe lock system
 * Author: Fadi Jarray
 *
 * Daemon responsible for lock/unlock commands and maintaining the statuses of multiple access points.
 * © Equal Safe. All rights reserved.
 */

#ifndef DEADLOCK_HPP
#define DEADLOCK_HPP

// #include "../utils/MqttWrapper.hpp"
#include "../utils/mqtt_client.hpp"

#include "pigpio.h"
#include <string>
#include <nlohmann/json.hpp>

using Json = nlohmann::json;
const int PIN = 17;

class Deadlock
{
public:
    std::string state;

    Deadlock(const std::string &endpoint, const std::string &certPath, const std::string &keyPath, const std::string &clientId);
    ~Deadlock();
    //Deadlock(const std::string &endpoint, const std::string &certPath, const std::string &keyPath, const std::string &clientId);

    Deadlock(const std::string& address, const std::string& clientId);
    void start();
    void stop();

private:
    MQTTClientServer mqtt;
    int processMessage(const std::string &topic, const std::string &message);
};

#endif // DEADLOCK_HPP
