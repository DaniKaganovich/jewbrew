// Последнее обновление 2017-05-31 by Phisik
// Основной файл конфигурации, здесь выбираем номер версии и меняем ненужные параметры
// По хорошему - пины здесь менять не желательно, лучше это делать по #if-#endif в файле pins.h,
// это сформировало бы порядок в назначении пинов и легкость в поиске "пересечений"

// Не менять местами поряд включения файлов!
#include "settings.h"

// После того, как известны настройки, подключаем библиотеки
#include <OneWire.h>
#include <EEPROM.h> 

#if USE_I2C_LCD
	#include <Wire.h>
	#include <LiquidCrystal_I2C.h>
#else
	#include <LiquidCrystal.h>
#endif // USE_I2C_LCD

#if USE_WDT
	#include <avr/wdt.h>
#endif



// NB! Пины зависят от Settings.h
// Пока пины ниже могут переопределяться, потому включаем этот файл раньше выбора версии
#include "pins.h"

#define SIMPLED_VERSION 0       // Признак того, насколько упрощена версия
                                // 0 - стандартная
                                // 1 - с твердотельным реле в качестве регулятора мощности по брезинхему, с датчиком ASC712 30A в качестве датчика напряжения в сети
                                // с двумя релейным модуля для управления клапанами отбором голов и хвостов и товарного спирта.
                                // LCD keypad shield в качестве кнопок и экрана.
                                // 2 - то же, что и 1, но с цифровыми датчиками уровня спирта, голов, разлития жидкости
                                // 3 - то же, что и 2, но только с одним датчиком уровня спирта без датчика голов и разлития жидкости.
                                // 4 - то же что и 3, но с датчиком напряжения на трансформаторе.
                                // 5 - это почти нулевая версия, но разгон и двигатель управляются реле с низким уровнем и используется LCD keypad shield в качестве дисплея и кнопок.
                                // 6-  то же что и 5 но с поддержкой НПГ, с расчетом фактической мощности через датчик тока..
                                // 7 - slave конороллер, управляемый через внешние пины.
                                // 8 - То же что и 2, но с аналоговыми датчиками уровня спирта, голов, разлития жидкости.
                                // 9 - То же что и 5, но с расчетом фактической мощности через датчик тока.
                                // 20 - эксперимент с трехфазным нестабилизированным контроллером.
                                // 30 - то же что и 5 но с измененными пинами
                                
                                
#if SIMPLED_VERSION>=1
                                     // Пятая версия это почти нулевая
    #define USE_MPX5010_SENSOR 0     // Не используем MPX5010DP
    
    #if SIMPLED_VERSION!=5 && SIMPLED_VERSION!=6 && SIMPLED_VERSION!=8 && SIMPLED_VERSION!=9 && SIMPLED_VERSION<30
        #define PEREGREV_ON      1     // Не используем защиту клапанов от перегрева
        #define PER_KLP_OPEN     100   // Клапана на воду постоянно открыты
        #define PER_KLP_CLOSE    0     // из контанты NAPR_PEREGREV 150 
        #define USE_ALARM_UROVEN 0     // Нужно ли использовать датчик уровня в приемной емкости ардуино
        #define USE_ALARM_VODA   0     // Нужно ли использовать датчик разлития воды ардуино
        #define UROVEN_ALARM     1     // Датчик уровня переводим в цифровой режим
    #endif

    #define USE_GAS_SENSOR 0        // Пин для анализа датчика загазованности (спирта)
    #define UROVEN_GAS_SENSOR 1     // уровень газа переводим в цифровой режим
    
    #if SIMPLED_VERSION!=6
        #define USE_NPG_UROVEN_SENSORS 0         // Отключаем датчик НПГ если не SIMPLED 6
    #else
        #define USE_NPG_UROVEN_SENSORS 1         // Включаем датчик НПГ если не SIMPLED 6
    #endif
    
    #define USE_BRESENHAM_ASC712 1         // Надо ли исполозовать датчик тока
    #define PIN_READI  A2         // Аналоговый Пин для чтения тока 
    
    #if USE_12V_PWM==1
        #define PEREGREV_ON 1  // Использовать режим работы клапана в режиме защиты от перегрева. 1- использовать, 0-нет.
    #endif

#endif

// Версия урощена 2 - то же, то упрощенная версия, но с цифровыми датчиками уровня голов, спирта, разлития воды
#if SIMPLED_VERSION==2
    #define USE_ALARM_UROVEN 1  // Нужно ли использовать датчик уровня в приемной емкости ардуино 
                                // 2, нужно использовать как признак стопа ректификации.
    #define USE_ALARM_VODA   1  // Нужно ли использовать датчик разлития воды ардуино
#endif

#if SIMPLED_VERSION==3
    #define USE_ALARM_UROVEN 2  // Нужно ли использовать датчик уровня в приемной емкости ардуино 2 - датчик используется как уровень при котором останавливается отбор, но не останавливается ректификация
    #define USE_ALARM_VODA   0  // Нужно ли использовать датчик разлития воды ардуино
    #define KLP_HIGH         0           // В простой версии 3 реле с низким уровнем включения
#endif

#if SIMPLED_VERSION==4
    #define USE_ALARM_UROVEN   2  // Нужно ли использовать датчик уровня в приемной емкости ардуино 2 - датчик используется как уровень при котором останавливается отбор, но не останавливается ректификация
    #define USE_ALARM_VODA     0  // Нужно ли использовать датчик разлития воды ардуино
    #define KLP_HIGH           0              // В простой версии 3 реле с низким уровнем включения
    #define USE_BRESENHAM_ASC712         0        // Надо ли использовать датчик тока
#endif

#if SIMPLED_VERSION==5 || SIMPLED_VERSION==6 || SIMPLED_VERSION==7 || SIMPLED_VERSION==8 || SIMPLED_VERSION==9 || SIMPLED_VERSION==20 || SIMPLED_VERSION>=30
    #define PIN_DS18B20      2    // датчики температуры подключены к PIN 2 (для удобства пайки)
    #define PIN_TRIAC        10    // Управление симистором реализовано через PIN 10 (для удобств пайки)
    #define PIN_MPX5010      A1      // Пин датчика давления MPX5010DP к А1 (для удобства пайки)
    
    
    #define USE_ALARM_UROVEN 2  // Нужно ли использовать датчик уровня в приемной емкости ардуино 2 - датчик используется как уровень при котором останавливается отбор, но не останавливается ректификация
    #define USE_ALARM_VODA   1  // Нужно ли использовать датчик разлития воды ардуино
    #define KLP_HIGH         1              // В простой версии 5 вместо реле на клапана используются симисторы.
    #define USE_BRESENHAM_ASC712       0        // Надо ли исполозовать датчик тока
    #define RELAY_HIGH       0         // Какой сигнал подавать на релейные выходы мешалки и разгона 
    #define KLP_HLD          2      // Номер клапана холодильника (для дистилляции), такой же, как и дефлегматор.
    #define KLP_DEFL_D       4    // Номер клапана дефлегматора дистиллятора - такой же, как и номер клапана отбора спирта, поскольку клапан отбора спирта не используется при дистилляции.
    
    // Версия Slave-регулятора мощности.
    #if SIMPLED_VERSION==7
         #undef PIN_MPX5010       A1      // Пин датчика давления MPX5010DP к А1 (для удобства пайки)
    
        #define USE_ALARM_UROVEN  0 // Нужно ли использовать датчик уровня в приемной емкости ардуино 2 - датчик используется как уровень при котором останавливается отбор, но не останавливается ректификация
        #define USE_ALARM_VODA    0 // Нужно ли использовать датчик разлития воды ардуино
        #define USE_SLAVE         1       // Переводим контроллер в Slave - режим
    #endif

    // Версия с датчиком тока (в основном это для отладки на моем оборудовании подключил датчик тока на A1)
    #if SIMPLED_VERSION==8
        #define PIN_READI      A4         // Аналоговый Пин для чтения тока 
        #define USE_BRESENHAM_ASC712     1         // Надо ли исполозовать датчик тока
        #define PEREGREV_ON    0        // Отключаем защиту от перегрева клапанов.
        #define PER_KLP_OPEN   100 // Клапана на воду постоянно открыты
        #define PER_KLP_CLOSE  0  // из контанты NAPR_PEREGREV 150 
    #endif
    
    #if SIMPLED_VERSION==6 || SIMPLED_VERSION==9 || SIMPLED_VERSION==7 || SIMPLED_VERSION==5 || SIMPLED_VERSION==15
        #define PIN_READI A4         // Аналоговый Пин для чтения тока 
    #endif
    
    #if SIMPLED_VERSION>=30
        #define PIN_READI      A4 
        #define PIN_ALL_OFF    32  // Пин, при подаче напряжения на который вырыбаеся вообще все (например выключается УЗО) (может работать и без него)
        #define PIN_TRIAC      36    // Управление симистором реализовано через PIN 36 (для удобства пайки)
        #define PIN_MIXER      38
        #define PIN_RZG_ON     34
        #define RELAY_HIGH     1         // Релейные выходы не используем, вместо них при необходимости симисторное управление.
        #define KLP_NPG        4      // Номер клапана для управления НПГ (при дистилляции) 
        #define KLP_VODA       3      // Номер клапана для управления общей подачей воды в систему
        #define KLP_DEFL       0      // Номер клапана для подачи воды в дефлегматор
        #define KLP_DEFL_D     0    // Номер клапана для подачи воды в дефлегматор (при дистилляции с дефлегматором с паровым отбором)
        #define KLP_GLV_HVS    1  // Номер клапана отбора головных и хвостовых фракций 
        #define KLP_BARDA      2  
        #define KLP_HLD        0      // Номер клапана холодильника (для дистилляции), такой же, как и дефлегматор.
        #define KLP_DEFL_D     2    // Номер клапана дефлегматора дистиллятора - такой же, как и номер клапана отбора спирта, поскольку клапан отбора спирта не используется при дистилляции.
        #define KLP_SR         2      // Номер клапана отбора ректификата
        #define KLP_PB         4      // Номер клапана для слива польского буфера
        
        
        #if NUM_PHASE>1
            #undef  PIN_MPX5010       A9      // Пин датчика давления MPX5010DP
            #define PER_KLP_OPEN      100 // Клапана на воду постоянно открыты
            #define PER_KLP_CLOSE     0  // из контанты NAPR_PEREGREV 150 
            #define USE_ALARM_UROVEN  0  // Нужно ли использовать датчик уровня в приемной емкости ардуино
            #define USE_ALARM_VODA    0  // Нужно ли использовать датчик разлития воды ардуино
            #define PEREGREV_ON       0  // Не используем защиту клапанов от перегрева
        #endif
    #endif
    
    
    #if SIMPLED_VERSION==20
        #define USE_ALARM_UROVEN  0 // Нужно ли использовать датчик уровня в приемной емкости ардуино 2 - датчик используется как уровень при котором останавливается отбор, но не останавливается ректификация
        #define USE_ALARM_VODA    0 // Нужно ли использовать датчик разлития воды ардуино
        #define PIN_MPX5010       A1      // Пин датчика давления MPX5010DP к А1 (для удобства пайки)
    #endif
#endif






                                