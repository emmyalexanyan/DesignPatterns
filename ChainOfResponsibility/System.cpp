#include <iostream>
#include <memory>
#include <string>

class AccessHandler {
public:
    virtual ~AccessHandler() = default;
    void setNextHandler(std::shared_ptr<AccessHandler> next) {
        nextHandler = std::move(next);
    }
    virtual void handleRequest(const std::string& userRole) {
        if (nextHandler) {
            nextHandler->handleRequest(userRole);
        } else {
            std::cout << "Access denied for role: " << userRole << std::endl;
        }
    }
protected:
    std::shared_ptr<AccessHandler> nextHandler;
};

class GuestAccessHandler : public AccessHandler {
public:
    void handleRequest(const std::string& userRole) override {
        if (userRole == "Guest") {
            std::cout << "Guest access granted. Limited permissions." << std::endl;
        } else {
            AccessHandler::handleRequest(userRole);
        }
    }
};

class UserAccessHandler : public AccessHandler {
public:
    void handleRequest(const std::string& userRole) override {
        if (userRole == "User") {
            std::cout << "User access granted. Standard permissions." << std::endl;
        } else {
            AccessHandler::handleRequest(userRole);
        }
    }
};

class AdminAccessHandler : public AccessHandler {
public:
    void handleRequest(const std::string& userRole) override {
        if (userRole == "Admin") {
            std::cout << "Admin access granted. Full permissions." << std::endl;
        } else {
            AccessHandler::handleRequest(userRole);
        }
    }
};

int main() {

    auto guestHandler = std::make_shared<GuestAccessHandler>();
    auto userHandler = std::make_shared<UserAccessHandler>();
    auto adminHandler = std::make_shared<AdminAccessHandler>();

    guestHandler->setNextHandler(userHandler);
    userHandler->setNextHandler(adminHandler);
    std::cout << "Testing Guest role:" << std::endl;
    guestHandler->handleRequest("Guest");

    std::cout << "Testing User role:" << std::endl;
    guestHandler->handleRequest("User");

    std::cout << "Testing Admin role:" << std::endl;
    guestHandler->handleRequest("Admin");

    std::cout << "Testing Unknown role:" << std::endl;
    guestHandler->handleRequest("Unknown");

    return 0;
}
