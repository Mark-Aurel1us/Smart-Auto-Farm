// YF-S401.cpp - датчик расхода жидкости

// ПРИМЕР ИСПОЛЬЗОВАНИЯ:
/*
    if (waitForLitrs(2.0)) 
    {
        Serial.println("Налито 2 литра");
    }
    else 
    {
        Serial.println("Ошибка: превышен таймаут!");
    }
*/

// НЕОБХОДИМЫЕ НАСТРОЙКИ В SETUP:
/*
    void setup() 
    {
        Serial.begin(115200);
        pinMode(FLOW_SENSOR_PIN, INPUT);
        attachInterrupt(
            digitalPinToInterrupt(FLOW_SENSOR_PIN), 
            flowRatePulse, 
            RISING
        );
    }
*/

//--------------------------------------------------
// КОНФИГУРАЦИЯ
//--------------------------------------------------
const int FLOW_SENSOR_PIN = -1;       // Пин датчика (GPIO25 с поддержкой прерываний)
const int PULSES_PER_LITER = 450;     // Калибровочный коэффициент (импульсов/литр)
const unsigned long TIMEOUT_MS = 60000; // Таймаут измерения (60 секунд)

//--------------------------------------------------
// ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ
//--------------------------------------------------
volatile int pulseCount = 0;          // Счетчик импульсов (прерывание)
int lastPulseValue = 0;               // Для отслеживания изменений

//--------------------------------------------------
// ФУНКЦИИ
//--------------------------------------------------
void flowRatePulse() 
{
    pulseCount++; // Вызывается при каждом обороте датчика
}

bool waitForLitrs(float liters) 
{
    if (FLOW_SENSOR_PIN == -1) 
    {
        Serial.println("Ошибка: пин не назначен!");
        return NAN;
    }

    unsigned long startTime = millis(); // Запись времени старта
    int targetPulses = liters * PULSES_PER_LITER; // Целевое количество импульсов
    pulseCount = 0; // Сброс счетчика
    
    while (true) 
    {
        // Проверка таймаута
        if (millis() - startTime > TIMEOUT_MS) 
        {
            Serial.println("Таймаут!");
            return false;
        }
        
        // Безопасное чтение счетчика
        noInterrupts();
        int currentPulses = pulseCount;
        interrupts();
        
        // Проверка наличия новых импульсов
        if (currentPulses != lastPulseValue) 
        {
            lastPulseValue = currentPulses;
            Serial.print("Импульсы: ");
            Serial.println(currentPulses);
        }
        
        // Проверка достижения цели
        if (currentPulses >= targetPulses) 
        {
            return true;
        }
        
        delay(100); // Задержка между проверками
    }
}