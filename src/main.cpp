/*
 * Equal Safe lock system
 * Author: Fadi Jarray
 *
 * Daemon responsible for lock/unlock commands and maintaining the statuses of multiple access points.
 * © Equal Safe. All rights reserved.
 */

#include "lock/Deadlock.hpp"

int main() {
    std::string endpoint = "a3k8g52cygaavt-ats.iot.us-east-2.amazonaws.com";
    std::string certPath = "/project/src/certs/safe.cert.pem";
    std::string keyPath = "/project/src/certs/safe.private.key";
    std::string clientId = "lock_sys";
    std::string address = "tcp://127.0.0.1:1883";

    Deadlock deadlock(address, clientId);
    deadlock.start();

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    deadlock.stop();

    return 0;
}
