// HC-SR04.cpp - ультразвуковой датчик расстояния

// ПРИМЕР ИСПОЛЬЗОВАНИЯ:
/*
    float distance = getDistance();

    if (!isnan(distance)) 
    {
        Serial.print("Расстояние: ");
        Serial.print(distance);
        Serial.println(" см");
    }
    else 
    {
        Serial.println("Ошибка измерения!");
    }

    delay(1000);
*/

// НЕОБХОДИМЫЕ НАСТРОЙКИ В SETUP:
/*
    void setup() 
    {
        Serial.begin(115200);
        pinMode(TRIG_PIN, OUTPUT);
        pinMode(ECHO_PIN, INPUT);
    }
*/

//--------------------------------------------------
// КОНФИГУРАЦИЯ
//--------------------------------------------------
const int TRIG_PIN = -1;          // Пин TRIG (GPIO23)
const int ECHO_PIN = -1;          // Пин ECHO (GPIO22)
const int MAX_DISTANCE = 500;     // Максимальная измеряемая дистанция (см)
const unsigned long ULTRASONIC_TIMEOUT_US = 30000; // Таймаут измерения (30 мс ~ 5 м)

//--------------------------------------------------
// ФУНКЦИИ
//--------------------------------------------------
float getDistance() 
{
    if (TRIG_PIN == -1 || ECHO_PIN == -1) 
    {
        Serial.println("Ошибка: пины не назначены!");
        return NAN;
    }

    // Генерация ультразвукового импульса
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Измерение длительности отклика
    unsigned long duration = pulseIn(ECHO_PIN, HIGH, ULTRASONIC_TIMEOUT_US);

    // Обработка ошибок
    if (duration == 0) 
    {
        return NAN; // Превышен таймаут
    }

    // Расчет расстояния (29.1 = (340 м/с * 100 см/м) / 1e6 мкс/с / 2)
    float distance = duration * 0.0343 / 2.0f;

    // Проверка максимальной дистанции
    if (distance > MAX_DISTANCE) 
    {
        return NAN;
    }

    return distance;
}