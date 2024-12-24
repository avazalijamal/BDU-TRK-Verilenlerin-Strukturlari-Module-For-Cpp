import task_manager; // Modulu daxil edir
#include <iostream> // Giriş-çıxış üçün
#include <string>   // getline funksiyası üçün
using namespace std;


using namespace std;

// Menyu göstərir
void showMenu() {
    cout << "\n---- Tapşırıq İdarəetmə Sistemi ----" << endl;
    cout << "1. Tapşırıq əlavə et" << endl;
    cout << "2. Tapşırıqları göstər" << endl;
    cout << "3. Tapşırığı icra et" << endl;
    cout << "4. Tapşırığı sil" << endl;
    cout << "5. Tapşırığı axtar" << endl;
    cout << "6. Tapşırığın prioritetini yenilə" << endl;
    cout << "7. Çıxış" << endl;
    cout << "Seçim: ";
}

int main() {
    TaskManager manager; // TaskManager obyektini yaradır
    int choice;

    do {
        showMenu(); // Menyunu göstərir
        cin >> choice;

        switch (choice) {
        case 1: {
            string description, details;
            int priority;
            cout << "Təsviri daxil edin: ";
            cin.ignore();
            getline(cin, description);
            cout << "Prioritet (1-High, 2-Medium, 3-Low): ";
            cin >> priority;
            cout << "Ətraflı məlumat (tarix, vaxt və s.): ";
            cin.ignore();
            getline(cin, details);
            manager.addTask(description, priority, details); // Yeni tapşırıq əlavə edir
            break;
        }
        case 2:
            manager.showTasks(); // Mövcud tapşırıqları göstərir
            break;
        case 3:
            manager.executeTask(); // Ən yüksək prioritetli tapşırığı icra edir
            break;
        case 4: {
            int id;
            cout << "Silinməli tapşırığın ID-sini daxil edin: ";
            cin >> id;
            manager.deleteTask(id); // Verilmiş ID-ə uyğun tapşırığı silir
            break;
        }
        case 5: {
            string keyword;
            cout << "Axtarış üçün açar sözü daxil edin: ";
            cin.ignore();
            getline(cin, keyword);
            manager.searchTasks(keyword); // Verilmiş açar sözə uyğun tapşırıqları axtarır
            break;
        }
        case 6: {
            int id, newPriority;
            cout << "Tapşırığın ID-sini daxil edin: ";
            cin >> id;
            cout << "Yeni prioritet (1-High, 2-Medium, 3-Low): ";
            cin >> newPriority;
            manager.updateTaskPriority(id, newPriority); // Tapşırığın prioritetini yeniləyir
            break;
        }
        case 7:
            cout << "Proqramdan çıxılır..." << endl; // Proqramdan çıxır
            break;
        default:
            cout << "Yanlış seçim! Yenidən cəhd edin." << endl; // Yanlış seçim bildirir
        }
    } while (choice != 7); // İstifadəçi çıxışı seçməyincə davam edir

    return 0;
}
