// Последнее обновление 2018-08-19 by Phisik
// Файл содержит дефолтные настройки системы
// Часть настроек меняется в файле configuration.h при выборе версий, внимательно с этим!


#define PR_REWRITE_EEPROM 0 // Константа, которая содержит признак необходимости перезаписи энергонезависимой памяти (1-254). 
                            // При запуске программы, значение 0-го байта ЕЕПРОМ сравнивается с этим значением, 
                            // и если они не совпадают, тогда энергонезависимая памиять переписывается текущими значениями переменных
                            // То есть для значений переменных из скетча в контроллер, ее значение надо поменять например с 9 до 10.

//#define TEST        // Раскомметировать, если нужно получать всяческие тестовые значения через Serial1
//#define TESTMEM     // Раскомметировать, если нужно получать всяческие тестовые значения через Serial1
//#define TESTGSM     // Раскомметировать, если нужно дублировать входящюю информацияю из GSM_SERIAL (сотового телефона) в Serial1 (для отладки)//.
//#define TESTGSM1    // Раскомметировать, если нужно дублировать входящюю информацияю из GSM_SERIAL (сотового телефона) в Serial1 (для отладки)
//#define TESTRM 1    // Раскомметировать, если нужно получать тестовые значения регулятора мощности через Serial1
//#define TESTERR     // Раскомметировать, если нужно получать тестовые значения ошибок через Serial1

//#define DEBUG // Режим отладки, в этом режиме не считываются значения датчиков температуры, а они передаются через монитор порта в ардуине
                // в формате: сколько прибавить секунд, Температура датчика 0, Температура датчика 1,Температура датчика 2
                // например: 60,820,810,800
                //  (монитор порта надо настроить так, чтобы он выдавал возврат каретки и перевод строки) 

//=======================================================================================================
// Phisik: настройка UART для работы с периферией

#define DEBUG_SERIAL			 Serial  // Куда выводить отладку
#define DEBUG_SERIAL_BAUDRATE	 115200	

#define GSM_SERIAL				 Serial2  // Порт, к которому подключена ESP, важно, чтобы не пересекалось с MQTT_SERIAL
#define GSM_SERIAL_BAUDRATE		 115200	  // Ставим максимальную, при которой еще нет ошибок связи
#define USE_GSM_WIFI             0  // Phisik: Отключаем wifi & gsm за ненадобностью, сэкономим часть памяти, удалив лишние переменные и повысив стабильность + уменьшим код на ~5%
									// NB! Это оригинальная реализация WiFi, не зависящая от MQTT и работающая с проприетарным сервером

#define MQTT_SERIAL				 Serial3  // Порт, к которому подключена ESP, важно, чтобы не пересекалось с GSM_SERIAL
#define MQTT_SERIAL_BAUDRATE	 250000   // Ставим максимальную, при которой еще нет ошибок связи
#define USE_MQTT_BROKER          1  // MQTT protocol by max506 & limon
                                    // В этом режиме для ESP надо использовать прошивку от limon или мою

#define MQTT_SERIAL_PING_CHECK   0  // Phisik: Попытка наладить связь между контроллерами при обрыве.
									//         Работает, если вообще работает, только с моей прошивкой для ESP
									//         С другими прошивками будет только мешать!
									
//=======================================================================================================
// НАСТРОЙКА ЭКРАНА И КНОПОК

// Phisik 2018-07-24: добавил I2C экран. 
// Оригинал здесь http://forum.homedistiller.ru/msg.php?id=13320675
#define USE_LCD_KEYPAD_SHIELD 1		// 1 - использовать стандартный шильд с кнопками - один пин A0 на все кнопки 
									// 0 - каждая кнопка привязана к своему пину
#define USE_I2C_LCD		0			// + много свободных пинов, - много лишних проводов
#define LCD_I2C_ADDRESS 0x27		// У каждого экспандера свой адрес. Используйте сканнер I2C.

// Поскольку у людей разные экраны, то лучше мы сделаем тут макрос
#define LCD_WIDTH  16
#define LCD_HEIGHT 2

// предполагаем 2 байта на символ, в международной кодировке (UTF8 может быть 1-4 байта на символ)
#define LCD_BUFFER_SIZE  (LCD_WIDTH*2+2)

//=======================================================================================================
// ОБЩИЕ НАСТРОЙКИ

#define USE_WDT			0		// Поставить 1, если использовать встроенный wath dog
#define BEEP_LONG		20      // Длительность сигнала оповещения о состояниях процесса
#define DEBOUNCE_CYCLES 15      // Число отсчетов таймера для устранения дребезга кнопок, 
								// Phisik: было 20, и, как по мне, то кнопки тормозили

#define NUM_PHASE		0		// Phisik: видимо, число подведенных фаз

// Phisik: Отключаем всякие надоедливые пищалки
#define NO_LOW_POWER_WARNING	 0
#define NO_DETECT_ZERO_WARNING   0  
#define NO_PAGE_BEEP			 0  // Не пищать на 0ой странице

#define USE_MPX5010_SENSOR       0  // Phisik: раньше использовалось условие #ifdef PIN_MPX5010, 
									// из-за чего приходилось постоянно следить чтобы пин не был определен

#define USE_NPG_UROVEN_SENSORS   0  // Phisik: раньше использовалось условие #ifdef NPG_UROVEN_PIN,  
									// из-за чего приходилось постоянно следить чтобы пин не был определен

#define USE_BRESENHAM_ASC712	 0   // Надо ли регулировать мощность по алгоритму Брезенхема, используя пропуск полупериодов и только датчик
									 // Если USE_BRESENHAM_ASC712 = 0, то осуществляется фазовое регулирование
									 // Использование датчика тока при фазовом регулировании определяется переменной CorrectASC712
#define SENSITIVE_ASC712	   135   // Чувствительность датчика тока (показаний АЦП ардуино на 10 ампер тока 135 для 30А датчика, 205 для 20А датчика 82)
  
#define CNT_PERIOD       4			// Количество полу-периодов для обсчета среднеквадратичного

#define USE_DIFAVTOMAT   0			// Константа, которая показывает, используется ли дифавтомат в работе системы
									// нужно для того, чтобы при нормальном завершении процесса
									// при плановом отключении дифавтомата не выдавалась тревога.

#define RELAY_HIGH       1			// Какой сигнал подавать на релейные выходы мешалки и разгона 
#define ALL_OFF_HIGH     1			// Какой сигнал подавать на выход ALL_OFF

#define MAX_COUNT_PROVODIMOST_SR 6  // Количество срабатываний датчика, по достижении которых можно точно сказать, что головы закончились
                                    // Каждое значение - это 5 секунд, то есть в данном случае датчик должен показывать 30 секунд проводимость менее 20

// Update 2018-05-09
// Phisik: этот параметр определяет нужно ли менять температуру стабилизации колонны, если она долго не меняется
// Это связано необходимостью учитывать изменение атмосферного давления. При повышении давления, ситуацию в принципе 
// спасет TimeRestabKolonna, а вот при понижении давления температура уплывает вниз, из-за чего "эффективная" дельта
// становится больше и хвосты можно пропустить. Если у вас есть датчик давления - оно вам скорее всего не надо.
#define ADJUST_COLUMN_STAB_TEMP		0 

#if ADJUST_COLUMN_STAB_TEMP
	// Как часто будем проверять изменение температуры
	const long  tStabCheckPeriod = 10000; // ms
	// С каким весом будем добавлять новую
	const long  tStabTimeConstant = 480; // 360 * 10сек ~ 1 час
	// Множитель для усреднения посчитаем один раз, чтобы не тратить время в loop()
	const float tStabAverageDivisor = 1+1.0/tStabTimeConstant;
#endif

//=======================================================================================================
// НАСТРОЙКА КЛАПАНОВ

// Клапана для управления ШИМ подключены, начиная с PIN 22
// Всего максимум 5 клапанов, то есть на пины с 22 по 26 реализован
// программный ШИМ по количество полупериодов с контролем нуля.

// Phisik:  Не используйте 220В клапана и "ШИМ по количество полупериодов с контролем нуля" - 
//			рано или поздно кого-нибудь прибьет! 
//			Используйте 12ти вольтовые клапана и USE_12V_PWM = 1 для защиты от перегрева

#define KLP_HIGH 1				// Уровень на выходе для сработки клапана
								// Для клапанов с низким уровнем управления поменять 0 на 1
#define PEREGREV_ON 1			// Защита от перегрева клапанов, 1- использовать, 0-нет.
#define USE_12V_PWM 0			// Phisik: Признак того, что надо использовать защиту от перегрева 12В клапанов 

#if PEREGREV_ON==0
    #define PER_KLP_OPEN  1 // клапана открываем через полу-период (аналог диода), чтобы не перегревались и
    #define PER_KLP_CLOSE 1 // чтобы не было гидроударов
#else
    #define PER_KLP_OPEN  1000 // клапана на воду переводим в фазовое управление, чтобы раз в 10 секунд на них подавалось полное напряжение, а затем напряжение
    #define PER_KLP_CLOSE 0    // из контанты U_PEREGREV 150 
#endif

#define MAX_KLP		 5      // Количество клапанов, которыми надо управлять по ШИМ. 

#define KLP_NPG      0      // Номер клапана для управления НПГ при дистилляции 
#define KLP_VODA     1      // Номер клапана для управления общей подачей воды в систему
#define KLP_DEFL     2      // Номер клапана для подачи воды в дефлегматор
#define KLP_DEFL_D   2      // Номер клапана для подачи воды в дефлегматор при дистилляции с дефлегматором с паровым отбором
#define KLP_HLD      3      // Номер клапана холодильника для дистилляции
#define KLP_PB       0      // Номер клапана для слива польского буфера
#define KLP_GLV_HVS  3      // Номер клапана отбора головных и хвостовых фракций
#define KLP_SR       4      // Номер клапана отбора ректификата

// Phisik: С клапаном барды был косяк. Он включался в 129 процессе и мешал тестам клапанов
// см. alarm.cpp 201 строчка if (IspReg==112 || IspReg==129)
// Т.к. барду за меня никто не сливает, то клапан отключил, внимательно здесь!
#define KLP_BARDA    0 // 4  // Номер клапана слива барды


//=======================================================================================================
// АВАРИЙНАЯ СИГНАЛИЗАЦИЯ

#define USE_ALARM_UROVEN 2  // Нужно ли использовать датчик уровня в приемной емкости ардуино 
							//  1 - останавливать процесс при налолнении емкости, в т.ч. ректификацию
                            //  2 - останавливать отбор, но не останавливать ректификацию (остальные процессы останавливаются) 

#define USE_ALARM_VODA   1		// Нужно ли использовать датчик разлития воды ардуино
#define UROVEN_ALARM     1		// Уровень сигнала, достижение котогого свидетельсвует о срабатывании аналогового датчика. 
								// В обычном состоянии он выведен на значение около 1000 для датчиков на уменьшение напряжения
                                // или на значение около 0-10 для датчиков на увеличение напряжения
								// Для цифрового датчика используем 1

#define COUNT_ALARM				6	// Сколько должно держаться значение уровня, чтобы сработало предупреждение каждое значение - это полсекунды.
#define COUNT_ALARM_VODA		60	// Сколько должно держаться значение разлития воды, чтобы сработала тревога каждое значение - это полсекунды.
#define COUNT_ALARM_UROVEN		200	// Сколько должно держаться значение уровня, чтобы сработала тревога по уровню в приемной емкости каждое значение - это полсекунды.
#define COUNT_ALARM_UROVEN_FR	60	// Сколько должно держаться значение уровня, чтобы сработала тревога по уровню в приемной емкости при фракционной перегонке каждое значение - это полсекунды.

#ifdef DEBUG
    #define COUNT_ALARM_UROVEN 20 // Сколько должно держаться значение уровня, чтобы сработала тревога по уровню в приемной емкости каждое значение - это полсекунды.
#endif

#define MAX_COUNT_NPG_ALARM 60     // Количество сработок осушения или переполнения, чтобы достоверно детектировать состояние НПГ (каждое значение -полсекунды)                                   

// Газовый сенсор
#define USE_GAS_SENSOR           0     // Надо ли использовать датчик загазованности
#define UROVEN_GAS_SENSOR        700   // Уровень сигнала, достижение которого свидетельствует о срабатывании датчика спиртового пара
#define COUNT_GAS_SENSOR         6     // Сколько должно держаться значение уровня, чтобы сработала тревога каждое значение - это полсекунды.
#define TIME_PROGREV_GAS_SENSOR  60    // Время для прогрева датчика спиртовых паров газа.

//=======================================================================================================
// ДАТЧИКИ ТЕМПЕРАТУРЫ

#define MAX_DS1820		5

// Phisik: update 2018-07-25
// Номера датчиков теперь приведены в порядок. Если датчики определяются не в том порядке, меняем числа тут

#define TEMP_KUB       0    // Номер датчика  термометра в кубе
#define TEMP_RK20      1    // Номер датчика термометра в РК 20 см от насадки
#define TEMP_TSA       2    // Номер термометра в трубке связи с атмосферой
#define TEMP_DEFL      TEMP_RK20    // Номер датчика  термометра в дефлегматоре
#define TEMP_TERMOSTAT 0    // Номер датчика  термометра термостата
#define TEMP_RAZVAR    0    // Номер датчика  термометра для разваривания зерновых

#define MAX_TEMP_TSA    650	  // Максимальная температура в датчике ТСА
#define MAX_ERR_DS18    120   // После тридцати глюков подряд (а это тридцать секунд) от датчиков температуры, считаем, что процесс надо остановить.
#define MAX_ERR_MPX5010 120   // После 120 значений датчика давления подряд (а это 60 секунд) от датчиков температуры, считаем, что процесс надо остановить.

#define MAX_INDEX_INPUT 540

#define MAX_INDEX_BY_PERIOD 90
#define MIN_INDEX_BY_PERIOD 75

//=======================================================================================================
// РЕДАКТИРОВАНИЕ МЕНЮ

// Added by Phisik on 2017-08-15
// Здесь можно отключить ненужные нам пункты в меню

// NB! Пункты 129, 130 всегда должны быть в конце! Пункт 100 - вначале!
//     Это связано с обработчиком нажатий в файле keyboard.cpp, строки 600-630

#define MENU_ITEMS 21 
const bool menuEnableFlag[MENU_ITEMS] = {
  1,    // case 100:  Установка параметров  // Не отключается!
  1,    // case 101:  Displaying   // Отключается, но отключать не стОит
  1,    // case 102:  Термостат    
  1,    // case 103:  Регулятор мощности
  1,    // case 104:  Первый (недробный) отбор
  0,    // case 105:  Отбор голов
  0,    // case 106:  Второй дробный отбор
  0,    // case 107:  Третий дробный отбор 
  0,    // case 108:  Затор зерно
  1,    // case 109:  Ректификация
  0,    // case 110:  Дистилляция с дефлегматором
  0,    // case 111:  НДРФ
  0,    // case 112:  NBK
  0,    // case 113:  Разваривание мучно-солодового затора (без варки).
  0,    // case 114:  Разваривание с чиллером и миксером
  1,    // case 115:  Таймер + регулятор мощности
  0,    // case 116:  Пивоварня - клон браумастера
  0,    // case 117:  Фракционная перегонка
  0,    // case 118:  Ректификация Фракционная
  1,    // case 129:  Тест клапанов // Не отключается!   
  0     // case 130:  Внешнее управление
};

//=======================================================================================================
// РЕДАКТИРОВАНИЕ МЕНЮ НАСТРОЕК

// Здесь можно отключить ненужные нам пункты в меню настроек
#define SETTINGS_ITEMS 69

// Edited by Phisik on 2017-08-16
// Обновил алгоритм зацикливания. Теперь не надо задавать LAST_ITEM/FIRST_ITEM
// Просто расставить  1/0

const bool settingsEnableFlag[SETTINGS_ITEMS] = {
   0,    //  200: "Max_t_Tst=%5i"
   1,    //  201: "Power TEN=%5u"
   1,    //  202: "Power Reg=%5u"
   0,    //  203: "ParamUSART=%u"
   USE_GSM_WIFI,    //  204: "ParamGSM=%u"
   0,    //  205: "dtTermostat=%3i"
   1,    //  206: "Temp 1 Nedrobn Distill=%3i"
   0,    //  207: "Temp 2 Drobn Distill=%3i"
   0,    //  208: "Temp 3 Drobn Distill=%3i"
   1,    //  209: "Temp Razgon Rect (+Kub,-Kol)=%3i"
   1,    //  210: "Power Rectif=%3i"
   1,    //  211: "Vvod Popravok ds18b20 "
   0,    //  212: "Temp Okon Otbor Glv Rectif=%3i"
   1,    //  213: "CHIM Otbor GLV Rectif=%5u"
   1,    //  214: "%% CHIM Otbor GLV Rectif=%3i"
   1,    //  215: "CHIM Otbor SR Rectif=%5u"
   1,    //  216: "Delta Otbor SR Rectif=%3u"
   1,    //  217: "Temp Okon Otbor SR Rectif=%3i"
   1,    //  218: "Temp Okon Rectif=%3i"
   0,    //  219: "Power GLV simple Distill=%4i"
   1,    //  220: "Power simple Distill=%4i"
   0,    //  221: "Temp Begin Dist (+Def -Kub)=%3i"
   0,    //  222: "Temp Distill With Defl=%3i"
   0,    //  223: "Delta Distill With Defl=%3i"
   0,    //  224: "Temp Kub Okon DistWithDefl=%3i"
   0,    //  225: "BeepEndProc=%1u"
   0,    //  226: "BeepStateProc=%1u"
   0,    //  227: "BeepKeyPress=%1u"
   0,    //  228: "Power Razvar Zerno=%4i"
   0,    //  229: "Power Varka Zerno=%4i"
   0,    //  230: "Period Refresh Server(sec)=%3u"
   1,    //  231: "U Peregrev=%3uV"
   0,    //  232: "Urv Barda=%4i Barda(%4u)"
   1,    //  233: "Provod SR=%4i"
   1,    //  234: "Time Stab (+/-) Kolonna=%5isec"
   0,    //  235: "Edit T & CHIM Count CHIM=%3i"
   1,    //  236: "Auto - CHIM=%3i"
   1,    //  237: "Auto + CHIM=%3i"
   1,    //  238: "Time Auto + CHIM=%5isec"
   1,    //  239: "Time reStab(+/-) Kolonna=%5isec"
   0,    //  240: "Beer Pause Count =%3i"
   1,    //  241: "Power correct ASC712 =%3i"
   USE_GSM_WIFI,    //  242: "Server adr= %3u.%3u.%3u.%3u"
   USE_GSM_WIFI,    //  243: "Server port= %u"
   USE_GSM_WIFI,    //  244: "ID Device= %s"
   USE_GSM_WIFI,    //  245: "My Phone= %s"
   0,    //  246: "Alarm Pressure MPX5010=%i"
   0,    //  247: "Use Avtonom HLD=%i"
   0,    //  248: "Time Open BRD=%i"
   0,    //  249: "PID Paramters %4i %4i %4i"
   1,    //  250: "min %% CHIM  Otbor SR=%2i"
   1,    //  251: "Edit Temp Stab Rectif=%3i"
   1,    //  252: "Beg %% CHIM  Otbor SR=%2i"
   0,    //  253: "Popr MPX=%4i %4i/%4i"   
   0,    //  254: "Power NBK=%4i"
   USE_GSM_WIFI,    //  255: "Wi-Fi AP= %s"
   USE_GSM_WIFI,    //  256: "Wi-Fi Password= %s"
   0,    //  257: "Fraction Dist Count =%3i"
   0,    //  258: "Fraction Rectif Count =%3i"
   0,    //  259: "Temp Zasyp Zator=%3i"
   0,    //  260: "Temp Osahariv Zator=%3i"
   0,    //  261: "Temp Brogenia Zator=%3i"
   0,    //  262: "PhasePW %5i= %4i+%4i+%4i"
   0,    //  263: "Phase%% %3i= %3i + %3i + %3i"
   0,    //  264: "min Pressure NBK=%3i+%3i=%3i"
   0,    //  265: "delta Pressure NBK=%3i+%3i=%3i"
   0,    //  266: "time Pressure NBK=%3i"
   0,    //  267: "Upravl Nasos NBK=%3i"
   0     //  268: "%% otbor Tsarga Paster(+/-)=%3i"
};

// =======================================================================================================
// ОТКЛЮЧЕНИЕ ЭКРАНОВ

// Здесь можно отключить ненужные нам экраны
#define SCREEN_ITEMS 11

// Edited by Phisik on 2018-07-03
// Просто расставить  1/0

const bool screenEnableFlag[SCREEN_ITEMS] = {
	1, // 1
	1, // 2
	0, // 3
	0, // 4
	1, // 5
	0, // 6
	1, // 7
	1, // 8
	0, // 9
	0, // 10
	0  // 11
};