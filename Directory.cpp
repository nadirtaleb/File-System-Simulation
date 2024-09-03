#include "Directory.h"
#include "File.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

Directory::Directory(const std::string& name) : FileSystemEntity(name) {}

Directory::~Directory() {}

void Directory::addFile(std::unique_ptr<File> file) {
    contents.push_back(std::move(file));
}

void Directory::addDirectory(std::unique_ptr<Directory> directory) {
    contents.push_back(std::move(directory));
}

Directory* Directory::createSubDirectory(const std::string& dirName) {
    // Manually creating a unique_ptr because I am on c++11
    std::unique_ptr<Directory> subDir(new Directory(dirName));
    Directory* subDirPtr = subDir.get();  // Keep a raw pointer to return
    addDirectory(std::move(subDir));  // Move the unique_ptr to contents
    return subDirPtr;
}

Directory* Directory::findSubDirectory(const std::string& dirName) {
    for (auto& entity : contents) {
        if (Directory* dir = dynamic_cast<Directory*>(entity.get())) {
            if (dir->getName() == dirName) {
                return dir;
            }
        }
    }
    return nullptr;
}

void Directory::listDetails() const {
    std::cout << "Directory: " << name << std::endl;
    for (const auto& entity : contents) {
        entity->listDetails();
    }
}

void Directory::moveFileTo(Directory* destination, const std::string& fileName) {
    for (auto it = contents.begin(); it != contents.end(); ++it) {
        if (File* file = dynamic_cast<File*>(it->get())) {
            if (file->getName() == fileName) {
                // Move the unique_ptr to the destination directory
                destination->contents.push_back(std::move(*it));
                // Remove the unique_ptr from the current directory
                contents.erase(it);
                return;
            }
        }
    }
    throw std::runtime_error("File not found: " + fileName);
}



void Directory::saveToFile(const std::string& filePath) const {
    std::ofstream outFile(filePath);
    if (!outFile.is_open()) {
        throw std::runtime_error("Unable to open file for saving: " + filePath);
    }

    // Recursive helper function to save the directory and its contents
    saveDirectory(outFile, *this, 0);

    outFile.close();
}

// Helper function to save directory structure
void Directory::saveDirectory(std::ofstream& outFile, const Directory& dir, int level) const {
    std::string indent(level * 2, ' '); // Indentation based on directory level
    outFile << indent << "D " << dir.getName() << std::endl;

    for (const auto& entity : dir.contents) {
        if (auto subDir = dynamic_cast<Directory*>(entity.get())) {
            saveDirectory(outFile, *subDir, level + 1);
        } else if (auto file = dynamic_cast<File*>(entity.get())) {
            outFile << indent << "  F " << file->getName() << " " << file->readFile().size() 
                    << " " << file->readFile() << std::endl;
        }
    }
}


// Method to load the directory structure from a file
void Directory::loadFromFile(const std::string& filePath) {
    std::ifstream inFile(filePath);
    if (!inFile.is_open()) {
        throw std::runtime_error("Unable to open file for loading: " + filePath);
    }

    std::string line;
    std::vector<Directory*> dirStack;
    dirStack.push_back(this); // Start with the root directory

    while (getline(inFile, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "D") {
            std::string dirName;
            iss >> dirName;
            Directory* newDir = dirStack.back()->createSubDirectory(dirName);
            dirStack.push_back(newDir);
        } else if (type == "F") {
            std::string fileName, content;
            int fileSize;
            iss >> fileName >> fileSize;
            getline(iss, content); // Read the remaining content
            content = content.substr(1); // Remove the leading space
            std::unique_ptr<File> newFile(new File(fileName, content));
            dirStack.back()->addFile(std::move(newFile));
        }
    }

    inFile.close();
}
