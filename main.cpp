#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

int main(int argc, char* argv[]) {
    std::string startTime, endTime, logFilePath;

    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (std::strcmp(argv[i], "-start") == 0 && i + 1 < argc) {
            startTime = argv[++i];
        } else if (std::strcmp(argv[i], "-end") == 0 && i + 1 < argc) {
            endTime = argv[++i];
        } else if (std::strcmp(argv[i], "-file") == 0 && i + 1 < argc) {
            logFilePath = argv[++i];
        }
    }

    if (startTime.empty() || endTime.empty() || logFilePath.empty()) {
        std::cerr << "Usage: ./cut -start=\"MM/DD/YYYY HH:MM:SS\" -end=\"MM/DD/YYYY HH:MM:SS\" -file=\"path/to/logfile.log\"" << std::endl;
        return 1;
    }

    std::ifstream logFile(logFilePath);
    if (!logFile.is_open()) {
        std::cerr << "Error opening file: " << logFilePath << std::endl;
        return 1;
    }

    std::string line;
    bool capture = false;

    while (std::getline(logFile, line)) {
        if (line.find(startTime) != std::string::npos) {
            capture = true;
        }
        if (capture) {
            std::cout << line << std::endl;
        }
        if (line.find(endTime) != std::string::npos) {
            capture = false;
            break;
        }
    }

    if (logFile.bad()) {
        std::cerr << "Error reading file: " << logFilePath << std::endl;
    }

    return 0;
}
