// DHT22.cpp - датчик влажности и температуры

// ПРИМЕР ИСПОЛЬЗОВАНИЯ:
/*
    float humidity = DHT22_readHumidity();
    float temperature = DHT22_readTemperature();
    
    if (!isnan(humidity) && !isnan(temperature)) 
    {
        Serial.print("Влажность: ");
        Serial.print(humidity);
        Serial.print("% | Температура: ");
        Serial.print(temperature);
        Serial.println("°C");
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
        dht.begin();
    }
*/

//--------------------------------------------------
// КОНФИГУРАЦИЯ
//--------------------------------------------------
#include <DHT.h>
#define DHT_TYPE DHT22       // Тип датчика
const int DHT_PIN = -1;      // Пин подключения (GPIO4)
const int READ_DELAY = 2000; // Интервал между измерениями (мс)

//--------------------------------------------------
// ГЛОБАЛЬНЫЕ ОБЪЕКТЫ
//--------------------------------------------------
DHT dht(DHT_PIN, DHT_TYPE);

//--------------------------------------------------
// ФУНКЦИИ
//--------------------------------------------------
float DHT22_readHumidity() 
{
    if (DHT_PIN == -1) 
    {
        Serial.println("Ошибка: пин не назначен!");
        return NAN;
    }
    
    float h = dht.readHumidity();
    
    if (isnan(h)) 
    {
        Serial.println("Ошибка чтения влажности!");
        return NAN;
    }
    
    return h;
}

float readTemperature() 
{
    if (DHT_PIN == -1) 
    {
        Serial.println("Ошибка: пин не назначен!");
        return NAN;
    }
    
    float t = dht.readTemperature();
    
    if (isnan(t)) 
    {
        Serial.println("Ошибка чтения температуры!");
        return NAN;
    }
    
    return t;
}

