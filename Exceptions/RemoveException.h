#pragma once

#include <exception>
#include <string>

class RemoveException : public std::exception {
public:
    const char* what() const override {
        return errorMessage.c_str();
    }
private:
    std::string errorMessage = "Remove element from empty list";
};