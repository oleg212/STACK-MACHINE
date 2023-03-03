# STACK-MACHINE
##  stack-based CPU emulation

Программа эмулирует работу 0-адресной машины и исполняет скрипты написанные на аналоге ассемблера.
Пока что только логические и целочисленные операции.
Обработки исключений тоже нет, так что не ломайте ничего.

Машина работает со стеком, поэтому аргументы требуются только для операций работы с памятью и условного перехода, арифметические и логические не требуют операнд.


## Как пользоваться
Пишем свою программу в scripts1.txt без лишних строк, во время исполнения данные сохраняются в файл memory.txt, он обновляется после каждой операции, вроде как дебаг версия получается. Для удобства можно писать комментарии через #.

## Пример
![image](https://user-images.githubusercontent.com/55054037/222809286-1186aa9d-c3d8-4cbc-a78a-673c433a5c51.png)

## Инструкции

#### Арифметика
IADD - Взять два верхних элемента из стека, сложить, результат положить в стек.

ISUB - Взять два верхних элемента из стека, из предпоследнего вычесть последний, результат положить в стек.

IMUL, IDIV по аналогии

#### Логика
OR, AND - Взять два верхних элемента, произвести логическую операцию, положить в стек. Предполагается, что операнды принимают значения {0,1}

NOT - Взять верхний элемент, произвести логическое отрицание, положить в стек. Предполагается, что операнды принимают значения {0,1}


#### Условный переход
JMP A - берет значение с вершины стека. Если 1 - перемещается на строку A. Можно было бы и адрес перехода брать из стека, но это уже перебор наверно.

#### Сравнение

EQ - Взять два верхних элемента, вернуть 1 если они равны и 0 если нет

CL - (Compare: Less)

CG - (Compare: Greater)

CLE - (Compare: Less or Equal)

CGE - (Compare: Greater or Equal)

#### Работа с памятью

PUSHCONST A - положить в стек константу A (целое число)

GET Adr - Положить на вершину стека значение из памяти по адресу Adr

SET Adr - Взять верхний элемент стека и сохранить по адресу Adr


