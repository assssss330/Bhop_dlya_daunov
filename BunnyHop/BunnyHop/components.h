#pragma once
/* <библиотеки> */
//подключаем все необходимые нам библиотеки. Для удобства я разделил код на блоки и подписал каждый из них.
#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <iostream>
#include <fcntl.h>
#include <io.h>

using namespace std;//чтобы потом не парится с указанием наследования от std

/* <главные переменные> */
//вначале я разместил переменные с путями. 
//Все необходимые вам пути можно взять по этой ссылке: https://raw.githubusercontent.com/frk1/hazedumper/master/csgo.json
DWORD dwForceJump = 86306812;
DWORD dwLocalPlayer = 14209740;
DWORD m_fFlags = 260;

//Далее расположились переменные в которые мы будем записывать нужные нам данные
DWORD pID = NULL;//id процесса для получения хендла
HANDLE Handle = NULL;//сюда запишем в последствии хендл окна ксго
HWND csgow = NULL;//переменная в которую мы запишем окно от кс
DWORD Client = NULL;//переменная в которую мы запишем client.dll
DWORD lPlayer;//адресс нашего локального игрока

//переменные для проверки на земле ли ирок и если да то сделать прыжок
int jump = 6;//универсальное значение битового поля для прыжка и автоматического возвращения значения
int onGrownd;

//И на последок переменные для изменения режима скрипта
bool enabled_or_suspended = true;
bool mode = false;

/* <функции> */
void MODREC() {
    //получение pID и открытие хендла
    do {
        HWND csgow = FindWindowA(0, "Counter-Strike: Global Offensive"); //поиск ксго
        if (!csgow)
            continue;
        GetWindowThreadProcessId(csgow, &pID);//получение pID
        Handle = OpenProcess(PROCESS_ALL_ACCESS, false, pID);//открываем хендл для работы с процессом
        Sleep(50);
    } while (!Handle);

    //делаем слепок всех модулей процесса ксго
    HANDLE ModulList = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pID);//сама функция делающая слепок модулей

    //получение адреса модуля
    //Здесь мы создадим ещё пару переменных для работы с модулем client.dll
    MODULEENTRY32 mEntry;//объект модуля
    mEntry.dwSize = sizeof(mEntry);
    do //получение значения конкретного модуля client.dll
    {
        
        if (!wcscmp(mEntry.szModule, L"client.dll")) //Сверяем модуль, если client.dll, то:
        {
            CloseHandle(ModulList);//закрываем HANDLE
            Client = (DWORD)mEntry.modBaseAddr; //Получаем адрес модуля и записываем в переменную
            break;
        }
    } while (Module32Next(ModulList, &mEntry));//переходим к следующему модулю
}


//бхоп скрипт
void BHOP() {

    std::cout << ">>> Bhop had started.";
    while (true)//бесконечный цикл подходящий для постоянной проверки и записи значений
    {
        //сделаем проверку на нажатие клавиш на клавиатуре
        //если необходимые нам значения проходят проверку, то мы присваиваем переменным режимов нужные значения
        if (GetAsyncKeyState(VK_F2)) //остановить бхоп
        {
            enabled_or_suspended = false;
        }

        if (GetAsyncKeyState(VK_F1)) //начать бхоп
        {
            enabled_or_suspended = true;
        }

        if (GetAsyncKeyState(VK_F8)) //выключить ахк режим
        {
            mode = false;
        }

        if (GetAsyncKeyState(VK_F7)) //включить ахк режим
        {
            mode = true;
        }

        if (GetAsyncKeyState(VK_SPACE)) // если нажали пробел, включаем бхоп
        {
            //далее когда все проверки пройдены и получены нужные нам значения можно перейти к самому бхопу
            //проверяем включен ли скрипт
            if (enabled_or_suspended == true) //сама проверка
            {
                //получаем и обновляем именно в цикле, для многоразовости скрипта(не нужно перезапускать после матча)
                ReadProcessMemory(Handle, (LPVOID)(Client + dwLocalPlayer), &lPlayer, sizeof(DWORD), 0);//запишем адрес локального игрока(адрес нашего персонажа)

                //проверяем значение режима, если true, то работать в ахк режиме, если false, то в режиме без ошибок
                if (mode == false)
                {
                    //получаем и обновляем именно в цикле, для многоразовости скрипта(не нужно перезапускать после матча)
                    ReadProcessMemory(Handle, (LPVOID)(lPlayer + m_fFlags), &onGrownd, sizeof(int), 0);//запишем на земле ли игрок 

                    if (onGrownd == 257 || onGrownd == 263)//на земле ли игрок(257 - на земле, 263 - присел)
                    {
                        WriteProcessMemory(Handle, (LPVOID)(Client + dwForceJump), (LPCVOID)&jump, sizeof(int), 0);//пишем в память что нужно прыгнуть
                    }
                }
                
                if (mode == true) 
                {
                    
                }
            }
        }
    }
    CloseHandle(Handle);//закрываем HANDLE
}



void StartScript()//функция запуска скрипта, именно эту функцию мы будем запускать в cpp файле
{
    //ну и осталась мелочь: сделать окно загрузки скрипта
    //выводим на экран обычнвй текст
    //символы \n - означают переход на следующюю строку консоли где и выводится весь текст
    std::cout <<
        "                #####   ##  ##  ##  ##  ##  ##  ##  ##  ##  ##   ####   #####\n"
        "                ##  ##  ##  ##  ### ##  ### ##   ####   ##  ##  ##  ##  ##  ##\n"
        "                #####   ##  ##  ## ###  ## ###    ##    ######  ##  ##  #####\n"
        "                ##  ##  ##  ##  ##  ##  ##  ##    ##    ##  ##  ##  ##  ##\n"
        "                #####    ####   ##  ##  ##  ##    ##    ##  ##   ####   ##\n\n "
        "                                   author: DexPy_Liquid\n"
        "                                   version:BunnyHop_11.9\n\n"
        " #############################################################################################\n"
        " |                                        WARNING!                                           |\n"
        " |                            To exit script close this window                               |\n"
        " |             Author of the script is not responseble how it will use people!               |\n"
//      " |                                          NOTE                                             |\n"
//      " |                            Our script can work in two modes:                              |\n"
//      " |                                     1. No-miss mode                                       |\n"
//      " |                               2. Ahk mode(doesn't works now)                              |\n"
        " |     Ahk mode works like simple ahk script, and no-miss mode works without any misstakes   |\n"
        " |                                       FAST KEYS:                                          |\n"
        " |                              F1           |            continue script                    |\n"
        " |                              F2           |            suspend script                     |\n"
      /*" |                              F7           |            start ahk mode                     |\n"
        " |                              F8           |            stop ahk mode                      |\n"*/
        " #############################################################################################\n";
    //здесь выводим стадии загрузки
    std::cout << ">>> Loading script...\n";
    std::cout << ">>> Reading memory...\n";
    //инициализируем первую функцию
    MODREC();
    std::cout << ">>> Starting bhop...\n";
    //инициализируем вторую функцию
    BHOP();//последняя часть инфы про стадии загрузки находится в функции, тк дальше она выполняется циклически
}





/*
* PS. 
* Если нашли какие либо орфографические ошибки в коментариях не пишите мне о них, коменты писал в попыхах и чекать написание в интернете лень было.
* Также не пишите мне пожалуйста про то что код можно было не делить на куча переодресаций функций, я сам об этом знаю но мне удобней так
* Ну и на последок: ИГРАЙТЕ ЧЕСТНО! ЧИТЫ И ВСЯКОГО РОДА СКРИПТЫ - ПЛОХО!
*/