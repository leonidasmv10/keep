#pragma once
#include <string>

class GLFWApplication
{
public:
    GLFWApplication(const std::string& name, const std::string& version);
    virtual ~GLFWApplication();
    
    //Argument parsing
    virtual unsigned int ParseArguments(int argc, char** argv); // Virtual function with default behavior.
    // Initialization 
    virtual unsigned Init(); // Virtual function with defaut behavior
    // Run function
    virtual unsigned Run() const; // Pure virtual function, it must be redefined
};
