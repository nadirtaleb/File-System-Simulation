#include "File.h"
#include <fstream>
#include <iostream>

File::File(const std::string& name, const std::string& content)
    : FileSystemEntity(name), content(content) {
    size = content.length();
    createRealFile();
}

void File::createRealFile() {
    std::ofstream outfile(name);
    if (outfile.is_open()) {
        outfile << content;
        outfile.close();
        std::cout << "File " << name << " created successfully." << std::endl;
    } else {
        throw std::runtime_error("Failed to create file: " + name);
    }
}

std::string File::readFile() {
    std::ifstream infile(name);
    std::string content, line;
    if (infile.is_open()) {
        while (getline(infile, line)) {
            content += line + "\n";
        }
        infile.close();
    } else {
        throw std::runtime_error("Unable to open file: " + name);
    }
    return content;
}

void File::appendToFile(const std::string& additionalContent) {
    std::ofstream outfile(name, std::ios::app);  // Open in append mode
    if (outfile.is_open()) {
        outfile << additionalContent;
        outfile.close();
        std::cout << "Content appended to " << name << std::endl;
    } else {
        throw std::runtime_error("Failed to open file for appending: " + name);
    }
}

void File::deleteFile() {
    if (remove(name.c_str()) != 0) {
        throw std::runtime_error("Error deleting file: " + name);
    } else {
        std::cout << "File " << name << " deleted successfully." << std::endl;
    }
}

void File::listDetails() const {
    std::cout << "File: " << name << " (" << size << " bytes)" << std::endl;
}
