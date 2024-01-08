#include "MS6205.h"

extern HWND hWnd, hWndEdit, hWndPortNumber;

uint8_t isOpened = 0;

void openPortByNumber() {
LPTSTR portNumberText = new TCHAR[4];
GetDlgItemText(hWnd,PORT_NUMBER,portNumberText,4);
openPort(portNumberText);
delete[] portNumberText;
Sleep(3000);
isOpened = 1;
}

void prepareAndSendPacket(string s, uint8_t line) {
while(!WriteCOM(STX));;
uint8_t len = s.length() + 2;
while(!WriteCOM(len));;
while(!WriteCOM(line));;
for(int i = 0; i < len - 2; i++) {
    while(!WriteCOM(s[i]));;
}
while(!WriteCOM(ETX));;
}

void resetDisplay() {
if(!isOpened) openPortByNumber();
prepareAndSendPacket(" ", 0xFF);
}

void sendData() {
resetDisplay();
uint8_t len = 0;
uint8_t symbCount = 0;
string s;
if(!isOpened) openPortByNumber();
for(uint8_t j = 0; j < 10; j++) {
HWND currentText = GetDlgItem(hWnd,TO_LCD_1+j);
len = GetWindowTextLength(currentText);
LPTSTR toLCD = new TCHAR[len];
GetWindowText(currentText,toLCD,len+1);
if(len > 16) symbCount = 16;
else symbCount = len;
for(int i = 0; i < symbCount; i++) {
            uint8_t currentSymbol = toLCD[i];
            if(currentSymbol <= 0x7F) {
                    s += currentSymbol;
            }
            else if(currentSymbol >= 0xC0 && currentSymbol <= 0xDF) {
                    s += codetable[currentSymbol - 0xC0];
            }
            else s+= ' ';
    }
prepareAndSendPacket(s,j);
delete[] toLCD;
s = "";
CloseHandle(currentText);
}
}

void clearInput() {
for(int i = 0; i < 10; i++) {
HWND hText = GetDlgItem(hWnd,TO_LCD_1 + i);
SendMessage(hText,EM_SETSEL,0,-1);
SendMessage(hText,WM_CLEAR,0,0);
CloseHandle(hText);
}
}
