﻿/*
* Скрипт был написанн DexPy_Liquid, не для копипасты и дальнейшей продажи, скрипт   является  бессплатным
* опен-сорс кодом, на основе которого можно узнать как пишутся скрипты такого типа и написать что-то своё.
*
* В скрипте написанн универсальный бхоп для игры ксго. Содержит разные режимы работы, первый сделан
* по типу хугирейна, а второй по типу ауто хот кей, оба режима можно переключать между собой прямо
* во время игры. Также прямо во время игры можно отключить или же включить скрипт в зависимости от
* игровой ситуации.
*
* Свои благодарности автору, разумеется если они есть, можно выразить в виде создания полностью
* графического интерфейса для этого скрипта.
*
* Скоро будет новый скрипт, но уже более дизбалансный чем бхоп...
*/

/*
* Все функции и впринципе весь код мы будем писать в файле заголовка "components.h", так как этот файл потом можно будет 
* добавить куда угодно и будет в дальнейшем проще переносить его в графическую оболочку.
* 
* Для начала создадим этот файл в папке "Исходные файлы". Как создавать файл заголовка и для чего он нужен я объяснять не
* буду, если вы не знаете этого лучше найдите в интернете уроки по с++ и изучите это там, и только после возвращайтесь к 
* этому коду. Дальнейшие инструкции будут в самом коде. если вы не понимаете что делает какая-то из функций, загуглите в
* интернете, не исключино что на данный момент разработчики поменяли какие-то файлы или пути к ним и этот код не работает,
* а без понимания что в коде вы никогда не вернёте его в рабочее состояние.
*/

#include "components.h" //подключаем наш файл заголовка, все остальные подключения будем делать в файле заголовка.

int main() //создаём главную функцию без которой код на с++ работать не будет
{
	StartScript();//инициализируем нашу фунцию с запуском банихопа
}