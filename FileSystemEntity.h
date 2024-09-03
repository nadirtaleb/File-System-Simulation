#ifndef FILESYSTEMENTITY_H
#define FILESYSTEMENTITY_H

#include <string>

class FileSystemEntity {
protected:
    std::string name;

public:
    FileSystemEntity(const std::string& name) : name(name) {}
    virtual ~FileSystemEntity() {}

    std::string getName() const { return name; }
    virtual void listDetails() const = 0; // Pure virtual function to make the class abstract
};

#endif // FILESYSTEMENTITY_H
