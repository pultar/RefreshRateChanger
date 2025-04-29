#include "yaml-cpp/yaml.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>

struct Settings {
    std::string qresPath;
    int targetRefreshRate;
    int backupRefreshRate;
    int delay;
};

int main() {
    std::string configurationPath = "RefreshRateChanger.yaml";
    Settings settings;
    try {
        std::cout << "Reading configuration from: " << configurationPath << std::endl;
        YAML::Node config = YAML::LoadFile(configurationPath);
        settings.qresPath = config["BinaryPath"].as<std::string>();
        settings.targetRefreshRate = config["TargetRefreshRate"].as<int>();
        settings.backupRefreshRate = config["BackupRefreshRate"].as<int>();
        settings.delay = config["Delay"].as<int>();
    }
    catch (std::exception& e) {
        std::cerr << "Failed to load configuration: " << e.what() << std::endl;
        return 1;
    }

    using namespace std::chrono;

    std::string command1 = settings.qresPath + " /R:" + std::to_string(settings.backupRefreshRate);
    std::string command2 = settings.qresPath + " /R:" + std::to_string(settings.targetRefreshRate);

    std::cout << "Executing: " << command1 << std::endl;
    int result = std::system(command1.c_str());
    if (result == 0) {
        std::cout << "First command executed successfully." << std::endl;
    }
    else {
        std::cerr << "First command failed with return value: " << result << std::endl;
    }

    std::this_thread::sleep_for(seconds(settings.delay));

    std::cout << "Executing: " << command2 << std::endl;
    result = std::system(command2.c_str());
    if (result == 0) {
        std::cout << "Second command executed successfully." << std::endl;
    }
    else {
        std::cerr << "Second command failed with return value: " << result << std::endl;
    }

    std::cout << "Finished executing both commands." << std::endl;

    return 0;
}