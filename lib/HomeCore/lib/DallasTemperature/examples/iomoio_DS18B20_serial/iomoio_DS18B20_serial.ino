// Видеообзоры и уроки работы с ARDUINO на YouTube-канале IOMOIO: https://www.youtube.com/channel/UCmNXABaTjX_iKH28TTJpiqA

#include <OneWire.h>                  // Подключаем библиотеку для взаимодействия с устройствами, работающими на шине и по протоколу 1-Wire
#include <DallasTemperature.h>        // Подключаем библиотеку с функциями для работы с DS18B20 (запросы, считывание и преобразование возвращаемых данных)

#define ONE_WIRE_BUS 2                // Указываем пин подключения data-вывода датчика температуры
#define term_power 4                  // Указываем пин подключения питания датчика температуры

OneWire oneWire(ONE_WIRE_BUS);        // Сообщаем библиотеке об устройстве, работающем по протоколу 1-Wire
DallasTemperature sensors(&oneWire);  // Связываем функции библиотеки DallasTemperature с нашим 1-Wire устройством (DS18B20)

void setup(void)
{
  Serial.begin(9600);             // Запускаем вывод данных на серийный порт
  sensors.begin();                // Запускаем библиотеку измерения температуры
  pinMode(term_power, OUTPUT);    // Определяем пин подключения питания датчика температуры
}


float temperature() { // Измеряем температуру 10 секунд
  digitalWrite(term_power, HIGH);                // Включаем питание датчика температуры
  delay(100);                                    // Задержка перед первым измерением 
  sensors.requestTemperatures();                 // Запрос на измерение температуры (1-й ошибочный)
  delay(500);                                    // Задержка перед поторным измерением
  sensors.requestTemperatures();                 // Запрос на измерение температуры (повторный)
  float t = float(sensors.getTempCByIndex(0));   // Получаем значение температуры
  digitalWrite(term_power, LOW);                 // Отключаем питание датчика температуры
  delay(9400);                                   // Задержка, чтобы датчик не нагревался от частых измерений
  return(t);                                     // Возвращаем значение температуры в место вызова функции
}

void loop(void)
{
  Serial.println(temperature(),1);                // Выводим текущее значение температуры датчика, округленное до десятых
}
