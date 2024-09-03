#include "Directory.h"
#include "File.h"
#include <iostream>
#include <memory>

void createFile(Directory& dir, const std::string& fileName, const std::string& content) {
    std::unique_ptr<File> newFile(new File(fileName, content));
    dir.addFile(std::move(newFile));
    std::cout<<"File "<< fileName << " created successfully."<< std::endl;
}

int main() {
    try {
        // Create the root directory and add some files and subdirectories
        Directory root("root");

        // Create a file in the root directory
        createFile(root, "file1.txt", "This is the first file in the root directory!");

        // Create a subdirectory and a file within it
        Directory* subDir = root.createSubDirectory("subdir1");
        std::cout<<"Subdirectory 'subdir1' created successfully."<< std::endl;
        createFile(*subDir, "file2.txt", "This is a file in the first subdirectory!");

        // Save the file system state to a file
        std::string saveFilePath = "filesystem.txt";
        root.saveToFile(saveFilePath);
        std::cout << "File system saved to " << saveFilePath << std::endl;

        // Load the file system state from the file into a new directory object
        Directory loadedRoot("loadedRoot");
        std::cout << "Directory 'loadedRoot' created for loading data." << std::endl;
        loadedRoot.loadFromFile(saveFilePath);
        std::cout << "\nLoaded file system from " << saveFilePath << ":" << std::endl;

        // List the contents of the loaded directory to verify the loaded state
        loadedRoot.listDetails();

    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
