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
        cout << "���� ����� ��� ������." << endl;
        return;
    }

    cout << "\n������ ��� ������:\n";
    for (size_t i = 0; i < residents.size(); ++i) {
        cout << "����� " << i + 1 << ":\n";
        cout << "  �������: " << residents[i].surname << "\n";
        cout << "  �������: " << residents[i].initials << "\n";
        cout << "  ����� ������: " << residents[i].room_number << "\n";
        cout << "  ��� ������: " << (residents[i].is_single_room ? "��������" : "�������") << "\n";
    }
    cout << endl;
}

// Function to add a new resident
void add_resident(vector<Resident>& residents, int room_number, bool is_single_room) {
    Resident resident;
    cout << "������ ������� ��������: ";
    cin >> resident.surname;
    cout << "������ ������� ��������: ";
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
        cout << "��������� � �������� " << surname << " ���������.\n";
    }
    else {
        cout << "�������� � ����� �������� �� ��������.\n";
    }
}

// Function to edit resident information
void edit_resident(vector<Resident>& residents, const string& surname) {
    bool found = false;
    for (auto& resident : residents) {
        if (resident.surname == surname) {
            cout << "�������� ��������. ������ ��� ���.\n";
            cout << "���� �������: ";
            cin >> resident.surname;
            cout << "��� �������: ";
            cin >> resident.initials;
            found = true;
            cout << "��� ��������.\n";
            break;
        }
    }
    if (!found) {
        cout << "�������� � ����� �������� �� ��������.\n";
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
        cout << "�������� � ����� �������� �� ��������.\n";
    }
    else if (matches.size() == 1) {
        cout << "�������: " << matches[0]->surname << "\n";
        cout << "�������: " << matches[0]->initials << "\n";
        cout << "����� ������: " << matches[0]->room_number << "\n";
    }
    else {
        cout << "�������� ����� ��������� � ����� ��������. ������ �������: ";
        string initials;
        cin >> initials;
        bool found = false;
        for (const auto* resident : matches) {
            if (resident->initials == initials) {
                cout << "�������: " << resident->surname << "\n";
                cout << "�������: " << resident->initials << "\n";
                cout << "����� ������: " << resident->room_number << "\n";
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "�������� � ������ ��������� �� ��������.\n";
        }
    }
}

// Main menu display
void display_menu() {
    cout << "\n����:\n";
    cout << "1. ������ ��������\n";
    cout << "2. �������� ��������\n";
    cout << "3. ���������� ��� ��� ��������\n";
    cout << "4. ������ �������� �� ��������\n";
    cout << "5. �������� �� ������\n";
    cout << "6. �����\n";
    cout << "������� �����: ";
}

int main() {
    SetConsoleCP(1251); // ������������ ������� win-cp1251 � ���� �����
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
            cout << "������ ����� ������ (1-5 ��� ���������, 6-15 ��� ��������): ";
            cin >> room_number;
            if (room_number >= 1 && room_number <= 5) {
                is_single_room = true;
            }
            else if (room_number >= 6 && room_number <= 15) {
                is_single_room = false;
            }
            else {
                cout << "������������ ����� ������.\n";
                break;
            }
            add_resident(residents, room_number, is_single_room);
            break;
        }
        case 2: {
            string surname;
            cout << "������ ������� �������� ��� ���������: ";
            cin >> surname;
            remove_resident(residents, surname);
            break;
        }
        case 3: {
            string surname;
            cout << "������ ������� �������� ��� �����������: ";
            cin >> surname;
            edit_resident(residents, surname);
            break;
        }
        case 4: {
            string surname;
            cout << "������ ������� ��� ������ ��������: ";
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
            cout << "������������ ����. ��������� �� ���." << endl;
        }
    }
    return 0;
}