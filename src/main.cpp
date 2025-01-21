/*
    main.cpp
    Приложение, демонстрирующее работу библиотеки для записи сообщений с разными уровнями важности в журнал
*/

#include "logging.h"
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

// Функция для определения уровня важности по введенным параметрам. Возвращает уровень важности типа Priority.
Priority setPriority(string word, Priority def_level = Priority::info)
{
    Priority level;
    if (word == "info")
    {
        level = Priority::info;
    }
    else if (word == "warning")
    {
        level = Priority::warning;
    }
    else if (word == "error")
    {
        level = Priority::error;
    }
    else
    {
        // пользователь не ввел уровень важности
        level = def_level;
        cout << "Вы не ввели уровень важности. Уровень важности будет установлен по умолчанию." << endl;
    }
    return level;
}

// Функции для получения сообщения и уровня важности из консоли
void logFunction(Logging &logger, mutex &mtx, Priority &def_level)
{
    string message, word;
    Priority level;
    bool running = true;
    while (running)
    {
        cout << "Введите сообщение: ";
        getline(cin, message);
        cout << "Введите уровень важности (необязательно): ";
        getline(cin, word);
        mtx.lock(); // Блокировка мьютекса
        try
        {
            logger.log(message, setPriority(word, def_level));
        }
        catch (const exception &e)
        {
            cerr << "Ошибка при записи сообщения в журнал: " << e.what() << endl;
        }
        cout << "- Введите `level`, чтобы поменять уровень важности по умолчанию;" << endl
             << "- Введите `exit`, чтобы выйти." << endl
             << "Или нажмите ENTER, чтобы продолжить." << endl;
        string key;
        getline(cin, key);
        if (key == "exit")
        {
            cout << "Выход." << endl;
            running = false;
        }
        else if (key == "level")
        {
            cout << "Введите уровень важности по умолчанию: ";
            getline(cin, word);
            def_level = setPriority(word, def_level);
            logger.setDefaultLevel(def_level);

        }
        else if (key == "\n")
        {
            continue;
        }
        mtx.unlock(); // Разблокировка мьютекса
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cerr << "Недостаточно аргументов." << endl;
        return 1;
    }

    string logFileName = argv[1];

    Priority defaultLogLevel = setPriority(argv[2]);

    // инициализация экземпляра класса библиотеки
    Logging logger(logFileName, defaultLogLevel);

    mutex mtx;

    // поток для записи сообщения в журнал
    thread logThread(logFunction, ref(logger), ref(mtx), ref(defaultLogLevel));

    logThread.join();

    return 0;
}