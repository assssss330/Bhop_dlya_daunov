#pragma once
/* <����������> */
//���������� ��� ����������� ��� ����������. ��� �������� � �������� ��� �� ����� � �������� ������ �� ���.
#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <iostream>
#include <fcntl.h>
#include <io.h>

using namespace std;//����� ����� �� ������� � ��������� ������������ �� std

/* <������� ����������> */
//������� � ��������� ���������� � ������. 
//��� ����������� ��� ���� ����� ����� �� ���� ������: https://raw.githubusercontent.com/frk1/hazedumper/master/csgo.json
DWORD dwForceJump = 86306812;
DWORD dwLocalPlayer = 14209740;
DWORD m_fFlags = 260;

//����� ������������� ���������� � ������� �� ����� ���������� ������ ��� ������
DWORD pID = NULL;//id �������� ��� ��������� ������
HANDLE Handle = NULL;//���� ������� � ����������� ����� ���� ����
HWND csgow = NULL;//���������� � ������� �� ������� ���� �� ��
DWORD Client = NULL;//���������� � ������� �� ������� client.dll
DWORD lPlayer;//������ ������ ���������� ������

//���������� ��� �������� �� ����� �� ���� � ���� �� �� ������� ������
int jump = 6;//������������� �������� �������� ���� ��� ������ � ��������������� ����������� ��������
int onGrownd;

//� �� �������� ���������� ��� ��������� ������ �������
bool enabled_or_suspended = true;
bool mode = false;

/* <�������> */
void MODREC() {
    //��������� pID � �������� ������
    do {
        HWND csgow = FindWindowA(0, "Counter-Strike: Global Offensive"); //����� ����
        if (!csgow)
            continue;
        GetWindowThreadProcessId(csgow, &pID);//��������� pID
        Handle = OpenProcess(PROCESS_ALL_ACCESS, false, pID);//��������� ����� ��� ������ � ���������
        Sleep(50);
    } while (!Handle);

    //������ ������ ���� ������� �������� ����
    HANDLE ModulList = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pID);//���� ������� �������� ������ �������

    //��������� ������ ������
    //����� �� �������� ��� ���� ���������� ��� ������ � ������� client.dll
    MODULEENTRY32 mEntry;//������ ������
    mEntry.dwSize = sizeof(mEntry);
    do //��������� �������� ����������� ������ client.dll
    {
        
        if (!wcscmp(mEntry.szModule, L"client.dll")) //������� ������, ���� client.dll, ��:
        {
            CloseHandle(ModulList);//��������� HANDLE
            Client = (DWORD)mEntry.modBaseAddr; //�������� ����� ������ � ���������� � ����������
            break;
        }
    } while (Module32Next(ModulList, &mEntry));//��������� � ���������� ������
}


//���� ������
void BHOP() {

    std::cout << ">>> Bhop had started.";
    while (true)//����������� ���� ���������� ��� ���������� �������� � ������ ��������
    {
        //������� �������� �� ������� ������ �� ����������
        //���� ����������� ��� �������� �������� ��������, �� �� ����������� ���������� ������� ������ ��������
        if (GetAsyncKeyState(VK_F2)) //���������� ����
        {
            enabled_or_suspended = false;
        }

        if (GetAsyncKeyState(VK_F1)) //������ ����
        {
            enabled_or_suspended = true;
        }

        if (GetAsyncKeyState(VK_F8)) //��������� ��� �����
        {
            mode = false;
        }

        if (GetAsyncKeyState(VK_F7)) //�������� ��� �����
        {
            mode = true;
        }

        if (GetAsyncKeyState(VK_SPACE)) // ���� ������ ������, �������� ����
        {
            //����� ����� ��� �������� �������� � �������� ������ ��� �������� ����� ������� � ������ �����
            //��������� ������� �� ������
            if (enabled_or_suspended == true) //���� ��������
            {
                //�������� � ��������� ������ � �����, ��� �������������� �������(�� ����� ������������� ����� �����)
                ReadProcessMemory(Handle, (LPVOID)(Client + dwLocalPlayer), &lPlayer, sizeof(DWORD), 0);//������� ����� ���������� ������(����� ������ ���������)

                //��������� �������� ������, ���� true, �� �������� � ��� ������, ���� false, �� � ������ ��� ������
                if (mode == false)
                {
                    //�������� � ��������� ������ � �����, ��� �������������� �������(�� ����� ������������� ����� �����)
                    ReadProcessMemory(Handle, (LPVOID)(lPlayer + m_fFlags), &onGrownd, sizeof(int), 0);//������� �� ����� �� ����� 

                    if (onGrownd == 257 || onGrownd == 263)//�� ����� �� �����(257 - �� �����, 263 - ������)
                    {
                        WriteProcessMemory(Handle, (LPVOID)(Client + dwForceJump), (LPCVOID)&jump, sizeof(int), 0);//����� � ������ ��� ����� ��������
                    }
                }
                
                if (mode == true) 
                {
                    
                }
            }
        }
    }
    CloseHandle(Handle);//��������� HANDLE
}



void StartScript()//������� ������� �������, ������ ��� ������� �� ����� ��������� � cpp �����
{
    //�� � �������� ������: ������� ���� �������� �������
    //������� �� ����� ������� �����
    //������� \n - �������� ������� �� ��������� ������ ������� ��� � ��������� ���� �����
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
    //����� ������� ������ ��������
    std::cout << ">>> Loading script...\n";
    std::cout << ">>> Reading memory...\n";
    //�������������� ������ �������
    MODREC();
    std::cout << ">>> Starting bhop...\n";
    //�������������� ������ �������
    BHOP();//��������� ����� ���� ��� ������ �������� ��������� � �������, �� ������ ��� ����������� ����������
}





/*
* PS. 
* ���� ����� ����� ���� ��������������� ������ � ����������� �� ������ ��� � ���, ������� ����� � ������� � ������ ��������� � ��������� ���� ����.
* ����� �� ������ ��� ���������� ��� �� ��� ��� ����� ���� �� ������ �� ���� ������������� �������, � ��� �� ���� ���� �� ��� ������� ���
* �� � �� ��������: ������� ������! ���� � ������� ���� ������� - �����!
*/