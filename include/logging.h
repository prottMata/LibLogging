/*
    logging.h
    Заголовочный файл библиотеки для записи сообщений с разными уровнями важности в журнал
*/

#pragma once

#ifndef LOGGING_H
#define LOGGING_H

#include <string>
#include <fstream>

// Перечисление уровней важности
enum class Priority {info, warning, error};

// Объявление класса Logging
class Logging {
private:
    std::string m_filename; // Имя файла журнала
    Priority m_default_level; // Уровень важности по умолчанию
    std::string getTimeStamp(); // Функция для получения текущего времени
public:
    // Конструктор для инициализации журнала с заданными именем файла и уровнем важности по умолчанию
    Logging(const std::string& filename, Priority default_level);
    // Функция для установления уровеня важности по умолчанию
    void setDefaultLevel(Priority level); 
    // Функция для записи сообщения и уровеня важности в журнал
    void log(const std::string& message, Priority level); 
};

#endif 