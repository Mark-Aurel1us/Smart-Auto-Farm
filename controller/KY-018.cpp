// KY-018.cpp - датчик освещенности

// ПРИМЕР ИСПОЛЬЗОВАНИЯ:
/*
    float light = ReadLightLevel();

    if (!isnan(light)) 
    {
        Serial.print("Освещенность: ");
        Serial.print(light);
        Serial.println(" В");
    }
    else 
    {
        Serial.println("Ошибка при считывании освещенности!");
    }
*/

// НЕОБХОДИМЫЕ НАСТРОЙКИ В SETUP:
/*
    void setup() 
    {
        Serial.begin(115200);
        pinMode(BRIGHTNESS_PIN, INPUT);
    }
*/

//--------------------------------------------------
// КОНФИГУРАЦИЯ
//--------------------------------------------------
const int BRIGHTNESS_PIN = -1;        // Аналоговый пин (GPIO32)
const float ADC_REF_VOLTAGE = 3.3f;   // Опорное напряжение ESP32
const int ADC_RESOLUTION = 4095;      // 12-битный АЦП

//--------------------------------------------------
// ФУНКЦИИ
//--------------------------------------------------
float ReadLightLevel() 
{
    if (BRIGHTNESS_PIN == -1) 
    {
        Serial.println("Ошибка: пин не назначен!");
        return NAN;
    }
    
    int rawValue = analogRead(BRIGHTNESS_PIN);

    // Инверсия значения для датчиков с обратной логикой
    int invertedValue = ADC_RESOLUTION - rawValue;
    
    // Преобразование в вольты
    return invertedValue * (ADC_REF_VOLTAGE / ADC_RESOLUTION);
}