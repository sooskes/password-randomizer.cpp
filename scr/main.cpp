/*
    Project: Random Password Generator
    Author: Ali Solhjoo

    Description:
    Generates a random 20-character password containing at least one
    lowercase letter, one uppercase letter, one digit, and one
    special character. Includes input validation and allows the user
    to regenerate passwords until they choose to exit.
*/

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <cctype>


// Utility functions
void closeProgram();
void wait(short givenSeconds);
void tolowerString(std::string& givenValue);
bool continuationPermission();
void design();


// Handles password creation, storage, and regeneration.
class Password{
    // Character pools used during password generation.
    const std::string ALL_CHARACRTERS{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789`~!@#$%^&*()-_=+[]{}|;:,.<>/?"};
    const std::string SMALL_CHARACTERS{"abcdefghijklmnopqrstuvwxyz"};
    const std::string CAPITAL_CHARACTERS{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    const std::string NUMBERS{"0123456789"};
    const std::string SPECIAL_CHARACTERS{"`~!@#$%^&*()-_=+[]{}|;:,.<>/?"};
    // Stores the generated password one character at a time.
    std::vector<char> password = {};
    // Stores reserved positions to guarantee each required character type.
    short randomSmallCharacterLocation{};
    short randomCapitalCharacterLocation{};
    short randomSpecialCharacterLocation{};
    short randomNumberLocation{};
    
    public:
        void GetAllCharacters() {
            std::cout << this->ALL_CHARACRTERS;
        }

        void GetAllSmallCharacters() {
            std::cout << this->SMALL_CHARACTERS;
        }

        void GetAllSpecialCharacters() {
            std::cout << this->SPECIAL_CHARACTERS;
        }

        void GetAllNumbers() {
            std::cout << this->NUMBERS;
        }

        void GetPassword() {
            std::cout << "Random password generator: ";
            for (short i{}; i < this->password.size(); i++) {
            std::cout << this->password[i];
            }
            std::cout << '\n';
        }

        // Fills the password with completely random characters.
        // Required character types are inserted afterward.
        void SetBasePassword() {
            for (short i{}; i < 20; i++) {
                this->password.push_back(this->ALL_CHARACRTERS[rand() % this->ALL_CHARACRTERS.size()]);
            }       
        }

        // Replaces one random position with a lowercase letter while
        // ensuring it doesn't overwrite another reserved position.
        void SetRandomSmallCharacter() {
            while (true) {
            this->randomSmallCharacterLocation = short(rand() % 20);
            if (randomSmallCharacterLocation == randomNumberLocation ||
                randomSmallCharacterLocation == randomSpecialCharacterLocation ||
                randomSmallCharacterLocation == randomCapitalCharacterLocation) {
                    continue;
            }
            this->password.at(randomSmallCharacterLocation) = this->SMALL_CHARACTERS[rand() % this->SMALL_CHARACTERS.size()];

            break;
            }
        }

        void SetRandomCapitalCharacter() {
            while (true) {
            this->randomCapitalCharacterLocation = short(rand() % 20);
            if (randomCapitalCharacterLocation == randomNumberLocation ||
                randomCapitalCharacterLocation == randomSpecialCharacterLocation ||
                randomCapitalCharacterLocation == randomSmallCharacterLocation) {
                    continue;
            }
            this->password.at(randomCapitalCharacterLocation) = this->CAPITAL_CHARACTERS[rand() % this->CAPITAL_CHARACTERS.size()];

            break;
            }
        }

        void SetRandomSpecialCharacter() {
            while (true) {
            this->randomSpecialCharacterLocation = short(rand() % 20);
            if (randomSpecialCharacterLocation == randomNumberLocation ||
                randomSpecialCharacterLocation == randomCapitalCharacterLocation ||
                randomSpecialCharacterLocation == randomSmallCharacterLocation) {
                    continue;
            }
            this->password.at(randomSpecialCharacterLocation) = this->SPECIAL_CHARACTERS[rand() % this->SPECIAL_CHARACTERS.size()];

            break;
            }
        }

        void SetRandomNumber() {
            while (true) {
            this->randomNumberLocation = short(rand() % 20);
            if (randomNumberLocation == randomSpecialCharacterLocation ||
                randomNumberLocation == randomCapitalCharacterLocation ||
                randomNumberLocation == randomSmallCharacterLocation) {
                    continue;
            }
            this->password.at(randomNumberLocation) = this->NUMBERS[rand() % this->NUMBERS.size()];

            break;
            }
        }

        // Clears the previous password and resets reserved positions
        // before generating a new one.
        void ResetPassword() {
            this->password.clear();

            this->randomSmallCharacterLocation = 0;
            this->randomCapitalCharacterLocation = 0;
            this->randomSpecialCharacterLocation = 0;
            this->randomNumberLocation = 0;
        }
};


// Generate a new password that satisfies all requirements.
int main() {
    srand(time(nullptr));

    Password password;

    do {
        password.ResetPassword();

        password.SetBasePassword();

        password.SetRandomSmallCharacter();

        password.SetRandomCapitalCharacter();

        password.SetRandomSpecialCharacter();

        password.SetRandomNumber();

        design();

        password.GetPassword();

        wait(5);
    } while (continuationPermission());

    closeProgram();

    return 0;
}


// Pauses execution for the specified number of seconds.
void wait(short givenSeconds) {
    std::this_thread::sleep_for(std::chrono::seconds(givenSeconds));
}

// Displays a closing message before terminating the application.
void closeProgram() {
    std::cout << "Closing program.\n";
    wait(2);
    std::exit(0);
}

// Converts every character in the string to lowercase to allow
// case-insensitive user input.
void tolowerString(std::string& givenValue) {
    for (char& c : givenValue) {
        c = std::tolower(static_cast<unsigned char>(c));
    }
}

// Repeatedly prompts the user until a valid response is entered.
// Returns true to generate another password or false to exit.
bool continuationPermission() {
    while (true) {
        std::string givenValue{};
        std::cout << "Enter the value (0) to close the program or (1) to regenerate the password: ";
        if (!(std::cin >> givenValue)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Please enter a valid input.\n";
            continue;
        }

        // Reject inputs containing extra characters (e.g. "1 abc").
        if (std::cin.peek() != '\n') {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Please enter a valid input.\n";
            continue;  
        }

        tolowerString(givenValue);

        // Accept both numeric and word forms for convenience.
        if (givenValue != "1" && givenValue != "0" && givenValue != "one" && givenValue != "zero") {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Please enter a valid input.\n";
            continue;
        }

        if (givenValue == "1" || givenValue == "one") {
            return true;
        }

        return false;
    }
}

// Prints a separator for cleaner console output.
void design() {
    std::cout << "*******************************************************************\n";
}
