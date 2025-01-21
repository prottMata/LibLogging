/* 
    logging.cpp
    Исходный файл библиотеки для записи сообщений с разными уровнями важности в журнал
*/

#include "logging.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>

Logging::Logging(const std::string &filename, Priority default_level) : m_filename(filename), m_default_level(default_level)
{}

// Функция принимает уроень важности и устанавлиет его по умолчанию
void Logging::setDefaultLevel(Priority level)
{
    m_default_level = level;
}

// Функция принимает в качестве аргументов строку сообщения и уровень важности
void Logging::log(const std::string &message, Priority level)
{
    if (level >= m_default_level)
    {
        // Открытие файла для записи
        std::ofstream m_outputFile(m_filename, std::ios_base::app);
        // Проверка на успешное открытие файла
        if (m_outputFile.is_open())
        {
            // Запись текущего времени в журнал 
            m_outputFile << getTimeStamp() << ' ';
            // Запись уровня важности в журнал в зависимости от параметра level
            switch (level)
            {
            case Priority::info:
                m_outputFile << "[INFO]";
                break;
            case Priority::warning:
                m_outputFile << "[WARNING]";
                break;
            case Priority::error:
                m_outputFile << "[ERROR]";
                break;
            }
            // Запись сообщения в журнал
            m_outputFile << ' ' << message << std::endl;
        }
        else
        {
            // Вывод сообщения об ошибке, если не удалось открыть файл
            std::cerr << "Невозможно открыть файл" << std::endl;
        }
        // Закрытие файла
        m_outputFile.close();
    }
}

// Функция возвращает текущую дату и время в формате, указанном в переменной format
std::string Logging::getTimeStamp()
{
    char format[] = "%Y-%m-%d %X"; // Формат времени означает YYYY-MM-DD HH:MM:SS
    char BufDT[20];
    // Запись текущего времени в переменную now
    auto now = std::chrono::system_clock::now();
    // Преобразование перменной now к типу time_t
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    // Получение информации о местном времени
    tm *now_struct = std::localtime(&now_c); 
    // Преобразование текущего системного времени в строку согласно заданному формату
    std::strftime(BufDT, 80, format, now_struct); 
    return std::string(BufDT);
}