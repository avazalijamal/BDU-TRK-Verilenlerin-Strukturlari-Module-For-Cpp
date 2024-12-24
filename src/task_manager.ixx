export module task_manager; // Modulu elan edir

#include <iostream>         // Giriş-çıxış üçün
#include <queue>            // Priority queue (prioritet sırası) üçün
#include <unordered_set>    // ID-ləri saxlamaq üçün
#include <unordered_map>    // Ətraflı məlumatları saxlamaq üçün
#include <string>           // Mətn tipini istifadə etmək üçün
#include <atomic>           // Avtomatik ID yaradılması üçün
#include <fstream>          // Fayl oxuma və yazma üçün

using namespace std;

// Tapşırıq strukturu
struct Task {
    int id;               // Tapşırığın unikal ID-si
    string description;   // Tapşırığın təsviri
    int priority;         // Tapşırığın prioriteti (1: High, 2: Medium, 3: Low)

    // Prioritet sırasını müəyyən etmək üçün müqayisə operatoru
    bool operator<(const Task& other) const {
        return priority > other.priority; // Min-Heap qurulması üçün
    }
};

// Tapşırıq idarəetmə class-ı
export class TaskManager {
private:
    priority_queue<Task> taskQueue;      // Tapşırıqları prioritetlə saxlamaq üçün
    unordered_set<int> taskIds;         // Unikal ID-lərin toplusu
    unordered_map<int, string> taskDetails; // Tapşırıq haqqında əlavə məlumatlar
    atomic<int> idCounter{1};           // Avtomatik ID yaratmaq üçün
    const string saveFile = "tasks.txt"; // Tapşırıqların saxlanacağı fayl

public:
    TaskManager() { loadTasksFromFile(); } // Constructor: Fayldan tapşırıqları yükləyir
    ~TaskManager() { saveTasksToFile(); }  // Destructor: Tapşırıqları fayla yazır

    int generateId() { return idCounter++; } // Yeni unikal ID yaradır

    // Yeni tapşırıq əlavə etmək üçün funksiya
    void addTask(const string& description, int priority, const string& details) {
        int id = generateId();                  // Yeni ID yaradılır
        taskQueue.push({id, description, priority}); // Tapşırıq növbəyə əlavə edilir
        taskIds.insert(id);                     // ID `unordered_set`-ə əlavə edilir
        taskDetails[id] = details;              // Ətraflı məlumat saxlanır
        cout << "Tapşırıq əlavə olundu: " << description << " (ID: " << id << ", Prioritet: " << priority << ")" << endl;
    }

    // Tapşırığı silmək üçün funksiya
    void deleteTask(int id) {
        if (taskIds.find(id) == taskIds.end()) { // ID mövcud olub-olmadığını yoxlayır
            cout << "Tapşırıq tapılmadı: ID " << id << endl;
            return;
        }
        taskIds.erase(id);                      // ID silinir
        taskDetails.erase(id);                  // Ətraflı məlumat silinir
        cout << "Tapşırıq silindi: ID " << id << endl;
    }

    // Prioritet sırasına görə tapşırığı icra etmək (çıxarmaq)
    void executeTask() {
        if (taskQueue.empty()) {               // Növbənin boş olub-olmadığını yoxlayır
            cout << "Heç bir tapşırıq yoxdur!" << endl;
            return;
        }
        Task topTask = taskQueue.top();        // Ən yüksək prioritetli tapşırıq alınır
        taskQueue.pop();                       // Tapşırıq növbədən çıxarılır
        taskIds.erase(topTask.id);             // ID silinir
        taskDetails.erase(topTask.id);         // Ətraflı məlumat silinir
        cout << "Tapşırıq icra edildi: " << topTask.description << " (ID: " << topTask.id << ")" << endl;
    }

    // Mövcud tapşırıqları göstərmək üçün funksiya
    void showTasks() {
        if (taskQueue.empty()) {               // Növbənin boş olub-olmadığını yoxlayır
            cout << "Tapşırıq yoxdur!" << endl;
            return;
        }
        priority_queue<Task> tempQueue = taskQueue; // Müvəqqəti növbə yaradılır
        cout << "Tapşırıqlar (Prioritet sırasına görə):" << endl;
        while (!tempQueue.empty()) {           // Bütün tapşırıqlar çap olunur
            Task task = tempQueue.top();
            tempQueue.pop();
            cout << "- ID: " << task.id << ", Təsvir: " << task.description
                 << ", Prioritet: " << task.priority
                 << ", Ətraflı: " << taskDetails[task.id] << endl;
        }
    }

    // Açar sözə əsasən tapşırıqları axtarmaq üçün funksiya
    void searchTasks(const string& keyword) {
        priority_queue<Task> tempQueue = taskQueue; // Müvəqqəti növbə yaradılır
        cout << "Axtarış nəticələri (" << keyword << "):" << endl;
        bool found = false;                         // Uyğun tapşırıq tapılıb-tapılmadığını yoxlayır
        while (!tempQueue.empty()) {
            Task task = tempQueue.top();
            tempQueue.pop();
            if (task.description.find(keyword) != string::npos || taskDetails[task.id].find(keyword) != string::npos) {
                cout << "- ID: " << task.id << ", Təsvir: " << task.description
                     << ", Ətraflı: " << taskDetails[task.id] << endl;
                found = true;
            }
        }
        if (!found) cout << "Heç bir uyğun tapşırıq tapılmadı." << endl;
    }

    // Tapşırığın prioritetini yeniləmək üçün funksiya
    void updateTaskPriority(int id, int newPriority) {
        if (taskIds.find(id) == taskIds.end()) { // ID mövcud olub-olmadığını yoxlayır
            cout << "Tapşırıq tapılmadı: ID " << id << endl;
            return;
        }
        priority_queue<Task> tempQueue;
        while (!taskQueue.empty()) {            // Növbədən tapşırığı çıxarır və prioritetini dəyişir
            Task task = taskQueue.top();
            taskQueue.pop();
            if (task.id == id) {
                task.priority = newPriority;    // Yeni prioritet təyin edilir
                cout << "Tapşırığın prioriteti yeniləndi: ID " << id << ", Yeni Prioritet: " << newPriority << endl;
            }
            tempQueue.push(task);
        }
        taskQueue = tempQueue;                  // Yenilənmiş növbə geri təyin edilir
    }

    // Tapşırıqları faylda saxlamaq üçün funksiya
    void saveTasksToFile() {
        ofstream file(saveFile);
        if (!file.is_open()) {
            cerr << "Faylı açmaq mümkün olmadı!" << endl;
            return;
        }
        priority_queue<Task> tempQueue = taskQueue;
        while (!tempQueue.empty()) {
            Task task = tempQueue.top();
            tempQueue.pop();
            file << task.id << "|" << task.description << "|" << task.priority << "|" << taskDetails[task.id] << endl;
        }
        file.close(); // Fayl bağlanır
    }

    // Tapşırıqları fayldan yükləmək üçün funksiya
    void loadTasksFromFile() {
        ifstream file(saveFile);
        if (!file.is_open()) return; // Fayl mövcud deyilsə, heç bir əməliyyat edilmir
        string line;
        while (getline(file, line)) {
            size_t pos1 = line.find('|');
            size_t pos2 = line.find('|', pos1 + 1);
            size_t pos3 = line.find('|', pos2 + 1);

            int id = stoi(line.substr(0, pos1));
            string description = line.substr(pos1 + 1, pos2 - pos1 - 1);
            int priority = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
            string details = line.substr(pos3 + 1);

            taskQueue.push({id, description, priority}); // Növbəyə tapşırıq əlavə edilir
            taskIds.insert(id);                         // ID saxlanılır
            taskDetails[id] = details;                  // Ətraflı məlumat saxlanılır
            if (id >= idCounter) idCounter = id + 1;    // ID-nin növbəti qiyməti müəyyən edilir
        }
        file.close();
    }
};
