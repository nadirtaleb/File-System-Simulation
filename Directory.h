#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "FileSystemEntity.h"
#include <vector>
#include <memory>
#include <string>

class File; // Forward declaration of File class

class Directory : public FileSystemEntity {
private:
    std::vector<std::unique_ptr<FileSystemEntity>> contents; // Use unique_ptr to manage contents
    void saveDirectory(std::ofstream& outFile, const Directory& dir, int level) const;


public:
    Directory(const std::string& name);
    ~Directory();

    void addFile(std::unique_ptr<File> file);
    void addDirectory(std::unique_ptr<Directory> directory);
    void moveFileTo(Directory* destination, const std::string& fileName);
    Directory* findSubDirectory(const std::string& dirName);
    Directory* createSubDirectory(const std::string& dirName);  // Create and add a subdirectory
    void listDetails() const override; // Implementing the abstract method
    void saveToFile(const std::string& filePath) const;    // Save the directory structure to a file
    void loadFromFile(const std::string& filePath);        // Load the directory structure from a file
    
};

#endif // DIRECTORY_H
