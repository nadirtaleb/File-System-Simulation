#ifndef FILE_H
#define FILE_H

#include "FileSystemEntity.h"


class File : public FileSystemEntity {
private:
    std::string content;
    size_t size;

public:
    File(const std::string& name, const std::string& content);
    void createRealFile();
    std::string readFile();
    void appendToFile(const std::string& additionalContent);
    void deleteFile();
    void listDetails() const override; // Implementing the abstract method
};

#endif // FILE_H
