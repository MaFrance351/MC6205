#include <iostream>

using namespace std;

HANDLE hSerial;

uint8_t openPort(char * portNumber) {
    char sPortName[10];
    sprintf (sPortName, "COM%s", portNumber);
    hSerial = ::CreateFile(sPortName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if(!GetCommState(hSerial, &dcbSerialParams)){
        MessageBox(NULL, TEXT("���� ����� ��� ����������!"), TEXT("Error"), MB_ICONERROR);
        exit(0);
    }
    dcbSerialParams.BaudRate = CBR_115200;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    if(!SetCommState(hSerial, &dcbSerialParams)){
        MessageBox(NULL, TEXT("���� ����� ��� ����������!"), TEXT("Error"), MB_ICONERROR);
        exit(0);
    }
    return 1;
}

void closePort() {
CloseHandle(hSerial);
}

uint8_t ReadCOM(uint8_t & sReceivedByte) {
    DWORD iSize;
     ReadFile(hSerial, &sReceivedByte, 1, &iSize, 0);  // �������� 1 ����
    return iSize;
    }

DWORD WriteCOM(uint8_t data) {
    DWORD dwBytesWritten;    // ��� ����� ���������� ���������� ���������� ����
    DWORD dwSize = 1;
    WriteFile(hSerial, &data, dwSize, &dwBytesWritten, NULL);
    return dwBytesWritten;
}
