#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <Windows.h>

using namespace std;

// Struct to store resident information
struct Resident {
    string surname;
    string initials;
    int room_number;
    bool is_single_room;
};

// Function to display all resident data
void display_all_data(const vector<Resident>& residents) {
    if (residents.empty()) {
        cout << "ЌемаЇ даних дл€ виводу." << endl;
        return;
    }

    cout << "\n—писок вс≥х запис≥в:\n";
    for (size_t i = 0; i < residents.size(); ++i) {
        cout << "«апис " << i + 1 << ":\n";
        cout << "  ѕр≥звище: " << residents[i].surname << "\n";
        cout << "  ≤н≥ц≥али: " << residents[i].initials << "\n";
        cout << "  Ќомер к≥мнати: " << residents[i].room_number << "\n";
        cout << "  “ип к≥мнати: " << (residents[i].is_single_room ? "ќдном≥сна" : "ƒвом≥сна") << "\n";
    }
    cout << endl;
}

// Function to add a new resident
void add_resident(vector<Resident>& residents, int room_number, bool is_single_room) {
    Resident resident;
    cout << "¬вед≥ть пр≥звище мешканц€: ";
    cin >> resident.surname;
    cout << "¬вед≥ть ≥н≥ц≥али мешканц€: ";
    cin >> resident.initials;
    resident.room_number = room_number;
    resident.is_single_room = is_single_room;

    residents.push_back(resident);
}

// Function to remove a resident by last name
void remove_resident(vector<Resident>& residents, const string& surname) {
    auto it = remove_if(residents.begin(), residents.end(), [&surname](const Resident& r) {
        return r.surname == surname;
        });

    if (it != residents.end()) {
        residents.erase(it, residents.end());
        cout << "ћешканець з пр≥звищем " << surname << " видалений.\n";
    }
    else {
        cout << "ћешканц€ з таким пр≥звищем не знайдено.\n";
    }
}

// Function to edit resident information
void edit_resident(vector<Resident>& residents, const string& surname) {
    bool found = false;
    for (auto& resident : residents) {
        if (resident.surname == surname) {
            cout << "«найдено мешканц€. ¬вед≥ть нов≥ дан≥.\n";
            cout << "Ќове пр≥звище: ";
            cin >> resident.surname;
            cout << "Ќов≥ ≥н≥ц≥али: ";
            cin >> resident.initials;
            found = true;
            cout << "ƒан≥ оновлено.\n";
            break;
        }
    }
    if (!found) {
        cout << "ћешканц€ з таким пр≥звищем не знайдено.\n";
    }
}

// Function to search for a resident by last name
void find_resident(const vector<Resident>& residents, const string& surname) {
    vector<const Resident*> matches;
    for (const auto& resident : residents) {
        if (resident.surname == surname) {
            matches.push_back(&resident);
        }
    }

    if (matches.empty()) {
        cout << "ћешканц€ з таким пр≥звищем не знайдено.\n";
    }
    else if (matches.size() == 1) {
        cout << "ѕр≥звище: " << matches[0]->surname << "\n";
        cout << "≤н≥ц≥али: " << matches[0]->initials << "\n";
        cout << "Ќомер к≥мнати: " << matches[0]->room_number << "\n";
    }
    else {
        cout << "«найдено к≥лька мешканц≥в з таким пр≥звищем. ¬вед≥ть ≥н≥ц≥али: ";
        string initials;
        cin >> initials;
        bool found = false;
        for (const auto* resident : matches) {
            if (resident->initials == initials) {
                cout << "ѕр≥звище: " << resident->surname << "\n";
                cout << "≤н≥ц≥али: " << resident->initials << "\n";
                cout << "Ќомер к≥мнати: " << resident->room_number << "\n";
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "ћешканц€ з такими ≥н≥ц≥алами не знайдено.\n";
        }
    }
}

// Main menu display
void display_menu() {
    cout << "\nћеню:\n";
    cout << "1. ƒодати мешканц€\n";
    cout << "2. ¬идалити мешканц€\n";
    cout << "3. –едагувати дан≥ про мешканц€\n";
    cout << "4. «найти мешканц€ за пр≥звищем\n";
    cout << "5. ѕоказати вс≥ записи\n";
    cout << "6. ¬ийти\n";
    cout << "¬ибер≥ть пункт: ";
}

int main() {
    SetConsoleCP(1251); // встановленн€ стор≥нки win-cp1251 в пот≥к вводу
    SetConsoleOutputCP(1251);
    vector<Resident> residents;

    bool running = true;
    while (running) {
        display_menu();
        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            int room_number;
            bool is_single_room;
            cout << "¬вед≥ть номер к≥мнати (1-5 дл€ одном≥сних, 6-15 дл€ двом≥сних): ";
            cin >> room_number;
            if (room_number >= 1 && room_number <= 5) {
                is_single_room = true;
            }
            else if (room_number >= 6 && room_number <= 15) {
                is_single_room = false;
            }
            else {
                cout << "Ќеправильний номер к≥мнати.\n";
                break;
            }
            add_resident(residents, room_number, is_single_room);
            break;
        }
        case 2: {
            string surname;
            cout << "¬вед≥ть пр≥звище мешканц€ дл€ видаленн€: ";
            cin >> surname;
            remove_resident(residents, surname);
            break;
        }
        case 3: {
            string surname;
            cout << "¬вед≥ть пр≥звище мешканц€ дл€ редагуванн€: ";
            cin >> surname;
            edit_resident(residents, surname);
            break;
        }
        case 4: {
            string surname;
            cout << "¬вед≥ть пр≥звище дл€ пошуку мешканц€: ";
            cin >> surname;
            find_resident(residents, surname);
            break;
        }
        case 5:
            display_all_data(residents);
            break;
        case 6:
            running = false;
            break;
        default:
            cout << "Ќеправильний виб≥р. —пробуйте ще раз." << endl;
        }
    }
    return 0;
}