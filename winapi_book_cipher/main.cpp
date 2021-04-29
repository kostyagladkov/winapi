#include "lib.h"

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

HWND hText, hKey, hOut;
HMENU hMenu;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow){

    WNDCLASSW wc = {0};

    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;    // Color for window (here its default)
    wc.hCursor = LoadCursor(NULL,IDC_ARROW);    // Loads cursor
    wc.hInstance = hInst;
    wc.lpszClassName = L"myWindowClass";
    wc.lpfnWndProc = WindowProcedure;           // WindowProcedure handles the window

    if(!RegisterClassW(&wc))
        return -1;

    CreateWindowW(L"myWindowClass", L"11", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 800, 650,
                  NULL, NULL, NULL, NULL);

    MSG msg = {0};

    while(GetMessage(&msg, NULL, NULL, NULL)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp){

    switch (msg){
        case WM_COMMAND:
            switch(wp){
                case FILE_MENU_EXIT:
                    DestroyWindow(hWnd);
                    break;
                case FILE_MENU_NEW:
                    MessageBeep(MB_ICONINFORMATION);
                    break;
                case ENCRYPT:{

                    char text_holder[500];
                    char to_find_holder[50];
                    GetWindowText(hText, text_holder, 500);
                    GetWindowText(hKey, to_find_holder, 50);

                    int new_lines = how_many_lines(text_holder);
                    int line_length = max_length_of_line(text_holder);

                    char** matrix = (char**)malloc(sizeof(char*) * line_length);
                    for (int i = 0; i < line_length; i++){
                        matrix[i] = (char*)malloc(sizeof(char) * new_lines);
                    }

                    matrix_filler(matrix, text_holder);

                    string result_enc = encrypt(matrix, new_lines, line_length, to_find_holder);

                    char result[result_enc.length() + 1];

                    for (int i = 0; i < result_enc.length() + 1; i++){
                        result[i] = result_enc[i];
                    }

                    for (int i = 0; i < line_length; i++){
                        free(matrix[i]);
                    }
                    free(matrix);

                    for (int i = strlen(to_find_holder) * 4; i < strlen(result); i++){
                        result[i] = ' ';
                    }

                    SetWindowText(hOut, result);

                    break;
                }
                case DECRYPT:{

                    char text_holder[500];
                    char to_find_holder[50];
                    GetWindowText(hText, text_holder, 500);
                    GetWindowText(hKey, to_find_holder, 50);

                    int new_lines = how_many_lines(text_holder);
                    int line_length = max_length_of_line(text_holder);

                    char** matrix = (char**)malloc(sizeof(char*) * line_length);
                    for (int i = 0; i < line_length; i++){
                        matrix[i] = (char*)malloc(sizeof(char) * new_lines);
                    }

                    matrix_filler(matrix, text_holder);

                    string result_dec = decrypt(matrix, new_lines, line_length, to_find_holder);

                    char result[result_dec.length() + 1];

                    for (int i = 0; i < result_dec.length() + 1; i++){
                        result[i] = result_dec[i];
                    }

                    for (int i = 0; i < line_length; i++){
                        free(matrix[i]);
                    }
                    free(matrix);

                    SetWindowText(hOut, result);

                    break;
                }
            }
            break;
        case WM_CREATE:
            AddMenus(hWnd);
            AddControls(hWnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProcW(hWnd, msg, wp, lp);
    }

}

void AddMenus(HWND hWnd){

//    hMenu = CreateMenu();
//    HMENU hFileMenu = CreateMenu();
//    HMENU hSubMenu = CreateMenu();
//
//    AppendMenu(hSubMenu, MF_STRING, NULL, "SubMenu Item");
//
//    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, "New");
//    AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR)hSubMenu, "Open SubMenu");
//    AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
//    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, "Exit");
//
//    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");
//    AppendMenu(hMenu, MF_STRING, NULL, "Help");
//
//    SetMenu(hWnd, hMenu);

}

void AddControls(HWND hWnd){

    CreateWindowW(L"Static", L"Стих: ", WS_VISIBLE | WS_CHILD, 50, 35, 100, 38, hWnd, NULL, NULL, NULL);
    hText = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE, 100, 25, 165, 200, hWnd, NULL, NULL, NULL);

    CreateWindowW(L"Static", L"Слово: ", WS_VISIBLE | WS_CHILD, 290, 35, 98, 38, hWnd, NULL, NULL, NULL);
    hKey = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 350, 25, 165, 38, hWnd, NULL, NULL, NULL);

    CreateWindowW(L"Button", L"Зашифровка",  WS_VISIBLE | WS_CHILD, 60, 260, 195, 38, hWnd, (HMENU)ENCRYPT, NULL, NULL);
    CreateWindowW(L"Button", L"Разшифровка",  WS_VISIBLE | WS_CHILD, 400, 260, 195, 38, hWnd, (HMENU)DECRYPT, NULL, NULL);

    hOut = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 125, 320, 350, 150, hWnd, NULL, NULL, NULL);

}
