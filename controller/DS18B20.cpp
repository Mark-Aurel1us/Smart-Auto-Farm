// DS18B20.cpp - датчик температуры

// ПРИМЕР ИСПОЛЬЗОВАНИЯ:
/*
    float temperature = DS18B20_readTemperature();
    
    if (!isnan(temperature)) 
    {
        Serial.print("Температура: ");
        Serial.print(temperature);
        Serial.println(" °C");
    }
    else 
    {
        Serial.println("Ошибка измерения!");
    }
*/

// НЕОБХОДИМЫЕ НАСТРОЙКИ В SETUP:
/*
    void setup() 
    {
        Serial.begin(115200);
    }
*/

//--------------------------------------------------
// КОНФИГУРАЦИЯ
//--------------------------------------------------
#include <OneWire.h>

const int ONEWIRE_BUS = -1;       // Пин для шины 1-Wire (GPIO22)
const int TEMP_READ_DELAY = 1000; // Задержка измерения (мс)

//--------------------------------------------------
// ГЛОБАЛЬНЫЕ ОБЪЕКТЫ
//--------------------------------------------------
OneWire oneWire(ONEWIRE_BUS);

//--------------------------------------------------
// ФУНКЦИИ
//--------------------------------------------------
float DS18B20_readTemperature() 
{
    if (ONEWIRE_BUS == -1) 
    {
        Serial.println("Ошибка: пин не назначен!");
        return NAN;
    }

    byte data[12];
    byte addr[8];
    byte type_s = 0;
    byte cfg = 0;

    // Поиск датчика
    if (!oneWire.search(addr)) 
    {
        Serial.println("Датчики не найдены");
        oneWire.reset_search();
        return NAN;
    }

    // Проверка CRC
    if (OneWire::crc8(addr, 7) != addr[7]) 
    {
        Serial.println("Ошибка CRC");
        return NAN;
    }

    // Определение типа датчика
    switch (addr[0]) 
    {
        case 0x10:
            type_s = 1; // DS18S20/DS1822
            break;
        case 0x28:
        case 0x22:
            type_s = 0; // DS18B20
            break;
        default:
            Serial.println("Неизвестный тип датчика");
            return NAN;
    }

    // Запуск измерения
    oneWire.reset();
    oneWire.select(addr);
    oneWire.write(0x44, 1);
    delay(TEMP_READ_DELAY);

    // Чтение данных
    oneWire.reset();
    oneWire.select(addr);
    oneWire.write(0xBE);

    for (byte i = 0; i < 9; i++) 
    {
        data[i] = oneWire.read();
    }

    // Обработка сырых данных
    int16_t raw = (data[1] << 8) | data[0];
    
    if (type_s == 1) 
    {
        raw = raw << 3;
        if (data[7] == 0x10) raw = (raw & 0xFFF0) + 12 - data[6];
    }
    else 
    {
        cfg = (data[4] & 0x60);
        switch (cfg) 
        {
            case 0x00: raw &= ~7; break; // 9 бит
            case 0x20: raw &= ~3; break; // 10 бит
            case 0x40: raw &= ~1; break; // 11 бит
            default:   raw &= ~0; break; // 12 бит
        }
    }

    return static_cast<float>(raw) / 16.0f;
}