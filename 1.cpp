/*
Вариант 3
Написать программу, моделирующую управление каталогом в файловой системе. Для каждого файла в каталоге содержатся следующие сведения: имя файла, дата создания, количество обращений к файлу.
Программа должна обеспечивать:
□ начальное формирование каталога файлов;
□ вывод каталога файлов;
□ удаление файлов, дата создания которых раньше заданной;
□ выборку файла с наибольшим количеством обращений.
Выбор моделируемой функции должен осуществляться с помощью меню. Для представления каталога использовать контейнерный класс lis t из STL
*/
#include <iostream>
#include <list>
#include <string>
#include <ctime>

using namespace std;

struct File {
    string name;
    time_t creationDate;
    int accessCount;
};

class Directory {
private:
    list<File> files;

public:
    void addFile(const string& name) {
        File newFile;
        newFile.name = name;
        time(&newFile.creationDate);
        newFile.accessCount = 0;
        files.push_back(newFile);
    }

    void deleteFilesOlderThan(const time_t& date) {
        auto it = files.begin();
        while (it != files.end()) {
            if (it->creationDate < date) {
                it = files.erase(it);
            }
            else {
                ++it;
            }
        }
    }

    void displayFiles() {
        cout << "Содержимое каталога:" << endl;
        for (const auto& file : files) {
            char buffer[26];
            ctime_s(buffer, sizeof(buffer), &file.creationDate);
            cout << "Имя: " << file.name << ", Дата создания: " << buffer
                << "Количество обращений: " << file.accessCount << endl;
        }
    }

    void selectMostAccessedFile() {
        if (files.empty()) {
            cout << "Каталог пуст." << endl;
            return;
        }

        auto mostAccessedFile = files.begin();
        for (auto it = files.begin(); it != files.end(); ++it) {
            if (it->accessCount > mostAccessedFile->accessCount) {
                mostAccessedFile = it;
            }
        }

        cout << "Самый часто используемый файл: " << mostAccessedFile->name << ", Количество обращений: "
            << mostAccessedFile->accessCount << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Ru");
    Directory directory;

    int choice;
    do {
        cout << "Меню:" << endl;
        cout << "1. Добавить файл" << endl;
        cout << "2. Удалить файлы старше указанной даты" << endl;
        cout << "3. Отобразить файлы" << endl;
        cout << "4. Выбрать наиболее часто используемый файл" << endl;
        cout << "5. Выйти" << endl;
        cout << "Введите ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string fileName;
            cout << "Введите имя файла: ";
            cin >> fileName;
            directory.addFile(fileName);
            break;
        }
        case 2: {
            time_t date;
            cout << "Введите дату в секундах с начала эпохи: ";
            cin >> date;
            directory.deleteFilesOlderThan(date);
            break;
        }
        case 3: {
            directory.displayFiles();
            break;
        }
        case 4: {
            directory.selectMostAccessedFile();
            break;
        }
        case 5: {
            cout << "Завершение программы." << endl;
            break;
        }
        default:
            cout << "Неверный выбор. Пожалуйста, введите число от 1 до 5." << endl;
        }
    } while (choice != 5);

    return 0;
}
