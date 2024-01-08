#include <windows.h>
#include "Serial.cpp"
#include "MS6205.h"
#include "MS6205.cpp"

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

HWND hWnd;
HWND hWndEdit;
HWND hWndPortNumber;


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     LPSTR nCmdLine, int nCmdShow)
{
  LPTSTR windowClass = TEXT("WinApp");
  LPTSTR windowTitle = TEXT("Neon Light UART");
  WNDCLASSEX wcex;

  wcex.cbClsExtra = 0;
  wcex.cbSize = sizeof(WNDCLASSEX);
  wcex.cbWndExtra = 0;
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
  wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
  wcex.hInstance = hInstance;
  wcex.lpfnWndProc = WndProc;
  wcex.lpszClassName = windowClass;
  wcex.lpszMenuName = NULL;
  wcex.style = CS_HREDRAW | CS_VREDRAW;
  if (!RegisterClassEx(&wcex))
  {
    MessageBox(NULL, TEXT("RegisterClassEx Failed!"), TEXT("Error"),
               MB_ICONERROR);
    return EXIT_FAILURE;
  }

  if (!(hWnd = CreateWindow(windowClass, windowTitle, WS_OVERLAPPEDWINDOW,
                            CW_USEDEFAULT, CW_USEDEFAULT, 300,
                            400, NULL, NULL, hInstance, NULL)))
  {
    MessageBox(NULL, TEXT("CreateWindow Failed!"), TEXT("Error"), MB_ICONERROR);
    return EXIT_FAILURE;
  }

  HWND  hWndEdit1 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT("œ–»¬≈“"),
                               WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 20, 170,
                               25, hWnd, HMENU(TO_LCD_1), NULL, NULL);
  HWND  hWndEdit2 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT("Ã»–"),
                               WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 50, 170,
                               25, hWnd, HMENU(TO_LCD_2), NULL, NULL);
  HWND  hWndEdit3 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT("›À≈ “–ŒÕ» ¿"),
                               WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 80, 170,
                               25, hWnd, HMENU(TO_LCD_3), NULL, NULL);
  HWND  hWndEdit4 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT("Ã—6205"),
                               WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 110, 170,
                               25, hWnd, HMENU(TO_LCD_4), NULL, NULL);
  HWND  hWndEdit5 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT("MAFRANCE351"),
                               WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 140, 170,
                               25, hWnd, HMENU(TO_LCD_5), NULL, NULL);
  HWND  hWndEdit6 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(""),
                               WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 170, 170,
                               25, hWnd, HMENU(TO_LCD_6), NULL, NULL);
  HWND  hWndEdit7 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(""),
                               WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 200, 170,
                               25, hWnd, HMENU(TO_LCD_7), NULL, NULL);
  HWND  hWndEdit8 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(""),
                               WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 230, 170,
                               25, hWnd, HMENU(TO_LCD_8), NULL, NULL);
  HWND  hWndEdit9 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(""),
                               WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 260, 170,
                               25, hWnd, HMENU(TO_LCD_9), NULL, NULL);
  HWND  hWndEdit10 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(""),
                               WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 290, 170,
                               25, hWnd, HMENU(TO_LCD_10), NULL, NULL);
  hWndPortNumber = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT("1"),
                               WS_CHILD | WS_VISIBLE, 200, 50, 60,
                               20, hWnd, HMENU(PORT_NUMBER), NULL, NULL);
  HWND hWndPortNumberMsg = CreateWindowW(L"STATIC", L"Serial port:",
                               WS_CHILD | WS_VISIBLE, 200, 20, 100,
                               20, hWnd, NULL, NULL, NULL);
  HWND hWndSend = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("BUTTON"), TEXT("Send"),
                               WS_CHILD | WS_VISIBLE, 200, 80, 60,
                               20, hWnd, HMENU(SEND), NULL, NULL);
  HWND hWndReset = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("BUTTON"), TEXT("Reset"),
                               WS_CHILD | WS_VISIBLE, 200, 110, 60,
                               20, hWnd, HMENU(RESET), NULL, NULL);
  HWND hWndClear = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("BUTTON"), TEXT("Clear"),
                               WS_CHILD | WS_VISIBLE, 200, 140, 60,
                               20, hWnd, HMENU(CLEAR), NULL, NULL);

  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);

  MSG msg;

  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return EXIT_SUCCESS;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  switch (msg)
  {
  case WM_PAINT:

      break;
  case WM_COMMAND:
  if(wParam == SEND) sendData();
  else if(wParam == RESET) resetDisplay();
  else if(wParam == CLEAR) clearInput();
  break;
  case WM_DESTROY:
    closePort();
    PostQuitMessage(EXIT_SUCCESS);
  default:
    return DefWindowProc(hWnd, msg, wParam, lParam);
  }
  return FALSE;
}
