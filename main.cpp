#include <iostream>
#include <string>
#include <ctime>
#include <Windows.h>

using namespace std;

enum class Color {
    Red = 12,
    Green = 10,
    Blue = 11
};

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

class ColorHandler {
private:
    Color currentColor;

    void setConsoleColor(Color color) const {
        SetConsoleTextAttribute(hConsole, static_cast<int>(color));
    }

    void printColorPropertiesImpl() const {
        setConsoleColor(currentColor);
        switch (currentColor) {
        case Color::Red:
            cout << "Red is often associated with energy and passion." << endl;
            break;
        case Color::Green:
            cout << "Green represents nature and tranquility." << endl;
            break;
        case Color::Blue:
            cout << "Blue is often linked with calmness and stability." << endl;
            break;
        }
        SetConsoleTextAttribute(hConsole, 7);
    }

public:
    ColorHandler(Color color) : currentColor(color) {
        setConsoleColor(color);
    }

    void setColor(Color color) {
        currentColor = color;
        setConsoleColor(color);
    }

    Color getColor() const {
        return currentColor;
    }

    virtual void printColorProperties() const {
        printColorPropertiesImpl();
    }

    virtual ~ColorHandler() {
        SetConsoleTextAttribute(hConsole, 7);
    }
};

class RandomColorHandler : public ColorHandler {
public:
    RandomColorHandler(Color color) : ColorHandler(color) {
        srand(static_cast<unsigned>(time(0)));
    }

    void setRandomColor() {
        int random = rand() % 3;
        Color newColor;
        switch (random) {
        case 0: newColor = Color::Red; break;
        case 1: newColor = Color::Green; break;
        case 2: newColor = Color::Blue; break;
        }
        setColor(newColor);
    }

    void printColorProperties() const override {
        cout << "Current color properties:" << endl;
        ColorHandler::printColorProperties();
    }
};

int main() {
    RandomColorHandler handler(Color::Red);
    handler.printColorProperties();

    handler.setRandomColor();
    handler.printColorProperties();

    return 0;
}
