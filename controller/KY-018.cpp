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

    delay(1000);
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
const int BRIGHTNESS_PIN = 4;        // Аналоговый пин (GPIO32)
const float ADC_REF_VOLTAGE = 3.3f;   // Опорное напряжение ESP32
const int BRIGHTNESS_ADC_RESOLUTION = 4095;      // 12-битный АЦП

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
    int invertedValue = BRIGHTNESS_ADC_RESOLUTION - rawValue;
    
    // Преобразование в проценты
    return invertedValue * 100 / BRIGHTNESS_ADC_RESOLUTION;
}