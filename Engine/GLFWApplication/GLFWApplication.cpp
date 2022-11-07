#include "GLFWApplication.h"

#include <iostream>

GLFWApplication::GLFWApplication(const std::string& name, const std::string& version)
{
    
}

GLFWApplication::~GLFWApplication()
= default;

unsigned GLFWApplication::ParseArguments(int argc, char** argv)
{
    return 1;
}

unsigned GLFWApplication::Init()
{
    return 1;
}

unsigned GLFWApplication::Run() const
{
    return 1;
}
