// FC28.cpp - датчик влажности почвы

// ПРИМЕР ИСПОЛЬЗОВАНИЯ:
/*
    float moisture = readMoisture();
    
    if (!isnan(moisture)) 
    {
        Serial.print("Влажность почвы: ");
        Serial.println(moisture);
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
        pinMode(SOIL_PIN, INPUT);
    }
*/

//--------------------------------------------------
// КОНФИГУРАЦИЯ
//--------------------------------------------------

// ПЕРЕД РАБОТОЙ С ДАТЧИКАМИ ИХ НУЖНО ОТКАЛИБРОВАТЬ!!!!!
const int SOIL_PIN = -1;               // Аналоговый пин (GPIO34)
const int DRY_VALUE = 3600;            // Значение в сухом воздухе
const int WET_VALUE = 1500;            // Значение в воде
const int ADC_RESOLUTION = 4095;       // 12-битный АЦП ESP32

//--------------------------------------------------
// ФУНКЦИИ
//--------------------------------------------------
float readMoisture() 
{
    if (SOIL_PIN == -1) 
    {
        Serial.println("Ошибка: пин не назначен!");
        return NAN;
    }

    int rawValue = analogRead(SOIL_PIN);
    
    if (rawValue <= 0) 
    {
        Serial.println("Ошибка: нет данных с датчика");
        return NAN;
    }

    // Нормализация и инверсия значения
    float normalized = static_cast<float>(ADC_RESOLUTION) / rawValue;
    
    // Калибровка по известным значениям
    float calibrated = map(
        normalized * 1000, 
        static_cast<float>(ADC_RESOLUTION) / DRY_VALUE * 1000,
        static_cast<float>(ADC_RESOLUTION) / WET_VALUE * 1000,
        0, 
        100
    );
    
    return constrain(calibrated, 0, 100);
}