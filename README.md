# MC6205
Управление советским плазменным дисплеем МС6205 при помощи Arduino и ПК
Эта программа позволяет подключить данный раритет к обычному компьютеру. В отличие от более старой Neon Light, она не требует для работы ныне дефицитного ПК с LPT-портом.
Схема подключения идентична той, что используется в оригинальном Neon Light (как и сама программа, она тоже приложена тут), но адаптирована под Arduino и сдвиговый регистр 74HC595N.
| Линия    | Вывод Arduino | Вывод панели|
| -------- | ------- | --------|
| Шина данных  | Подключена к регистру    | 
| Шина адреса | Подключена к регистру     |
| CLOCK регистра  | D3    |
|DATA регистра | D4 |
LATCH регистра | D5 |
Общий сброс | D6 | 18А |
Строб адреса | D7 | 16А |
Строб данных | D8 | 16Б |
С1 | 5 В | 6А |
С2 | 5 В | 6Б |
Прогон | Земля | 30A |

Программа собрана под ОС Windows при помощи CodeBlocks (MinGW).
