#include <iostream>
#include <windows.h>

using namespace std;

class cell
{
private:
    bool mine;
    bool border;
    bool hidden;
    int MinesAround;
    int x;
    int y;

public:
    cell()
    {
        this->x = 0;
        this->y = 0;
        this->MinesAround = 0;
        this->mine = 0;
        this->border = 0;
        this->hidden = 0;
    }

    cell(int x, int y, bool mine, bool border, bool hidden, int MinesAround)
    {
        this->x = x;
        this->y = y;
        this->mine = mine;
        this->border = border;
        this->hidden = hidden;
        this->MinesAround = MinesAround;
    }

    void SetCell(int x, int y, bool mine, bool border, bool hidden, int MinesAround) // Сеттер
    {
        this->x = x;
        this->y = y;
        this->mine = mine;
        this->border = border;
        this->hidden = hidden;
        this->MinesAround = MinesAround;
    }

    void SetHidden(bool hidden)                // Сеттер hidden
    { 
        this->hidden = hidden;
    }

    void SetMinesAround(int MinesAround)       // Сеттер MinesAround
    {
        this->MinesAround = MinesAround;
    }

    int GetX()                                 // Геттер координаты X
    {
        return x;
    }

    int GetY()                                 // Геттер координаты Y
    {
        return y;
    }
    
    bool GetMine()                             // Геттер того является ли объект миной
    {
        return mine;
    }

    bool GetBorder()                           // Геттер того является ли объект границей
    {
        return border;
    }

    bool GetHidden()                           // Геттер того является ли объект спрятанным
    {
        return hidden;
    }

    int GetMinesAround()                       // Геттер MinesAround
    {
        return MinesAround;
    }

};

int CheckNeighbours(cell **obj, int posX, int posY)
{
    int MineCounter = 0;

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (obj[posX + j][posY + i].GetMine())
            {
                MineCounter++;
            }
        }
    }

    return MineCounter;
}



int main()
{
    setlocale(LC_ALL, "RUS");                              // Определяем русский язык
    system("title Сапер");                                 // Определяем заголовок приложения

    int const FieldSizeX = 11;
    int const FieldSizeY = 11;
    int x;
    int y;
    bool mineExploded = 0;
    bool win = 0;

    cell arr[FieldSizeX][FieldSizeY];


    // ----------------------------------------- Генерация массива поля -----------------------------------------

    for (int i = 0; i < FieldSizeX; i++)
    {
        for (int j = 0; j < FieldSizeY; j++)
        {
            if (i == 0 || i == 10 || j == 0 || j == 10)      // Установка краевых мин
            {
                arr[i][j].SetCell(i, j, 0, 1, 1, 10);         // позицияX, позицияY, Мина, Граница, Скрыто, Мин вокруг
            }
            else
            {
                if (rand() % 10)                             // Установка мин в поле
                {
                    arr[i][j].SetCell(i, j, 0, 0, 1, 10);
                }
                else
                {
                    arr[i][j].SetCell(i, j, 1, 0, 1, 10);
                }
            }
        }
    }


    // ----------------------------------------- Очистка экрана и вывод масива -----------------------------------

    while(true)
    {
        system("cls");

        for (int i = 0; i < FieldSizeX; i++)
        {
            for (int j = 0; j < FieldSizeY; j++)
            {
                HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
                COORD cursorPos;

                // Установить каретку в нужное место, выбрать написать знак в соответствии с типом объекта нужного цвета
                cursorPos.X = (short)arr[i][j].GetX() *2;
                cursorPos.Y = (short)arr[i][j].GetY();
                SetConsoleCursorPosition(hStdOut, cursorPos);

                if (arr[i][j].GetHidden() && !(i == 0 || j == 0 || i == 10 || j == 10 ))
                {
                    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                    cout << "*";
                }
                else
                {
                    if (arr[i][j].GetBorder() && i == 0)                        // Особое обозначение для ряда Y
                    {
                        if (j == 0)
                        {
                            SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY / 2);
                            cout << " ";
                        }
                        else if (j == 10)
                        {
                            SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY / 2);
                            cout << "Y";
                        }
                        else
                        {
                            SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY / 2);
                            cout << j;
                        }
                    }

                    else if (arr[i][j].GetBorder() && j == 0)                   // Особое обозначение для ряда X
                    {
                        if (i == 0)
                        {
                            SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY / 2);
                            cout << " ";
                        }
                        else if (i == 10)
                        {
                            SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY / 2);
                            cout << "X";
                        }
                        else
                        {
                            SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY / 2);
                            cout << i;
                        }
                    }

                    else if (arr[i][j].GetBorder() && i == 10)                  // Особое обозначение для ряда Y = 10
                    {
                        SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY / 2);
                        cout << " ";
                    }

                    else if (arr[i][j].GetBorder() && j == 10)                  // Особое обозначение для ряда X = 10
                    {
                        SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY / 2);
                        cout << " ";
                    }


                    else if (arr[i][j].GetMine())
                    {
                        SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
                        cout << "M";
                    }

                    else
                    {
                        if (arr[i][j].GetMinesAround() >= 10)
                        {
                            SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                            cout << " ";
                        }
                        else
                        {
                            if (arr[i][j].GetMinesAround() == 0)
                            {
                                SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                                cout << " ";
                            }
                            else
                            {
                                SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                                cout << arr[i][j].GetMinesAround();
                            }
                        }
                    }
                }
            }
        }
        // Вернуть каретку в 1,11 с белым цветом
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD cursorPos;
        cursorPos.X = 0;
        cursorPos.Y = 11;
        SetConsoleCursorPosition(hStdOut, cursorPos);
        SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

        // ------------------------------- Проверка на то взорвана ли мина в прошлой иттерации -----------------------------------

        if (mineExploded == 1)
        {
            break;
        }

        // ----------------------------------------- Запрос данных от пользователя -----------------------------------


        // Запрос ячейки
        cout << "\nВведи координату по x: ";
        cin >> x;
        cout << "Введи координату по y: ";
        cin >> y;

        // Проверка на то поппал ли я на мину, если попал то произойдет вызод после обновления экрана. А если не попал на мину то клетка откроется
        if (arr[x][y].GetMine())
        {
            arr[x][y].SetHidden(0);
            win = 0;
            mineExploded = 1;
        }
        else
        {
            arr[x][y].SetHidden(0);                      // Открыть ячейку

            int MineCounter = 0;
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    if (arr[x + j][y + i].GetMine())
                    {
                        MineCounter++;
                    }
                }
            }
            arr[x][y].SetMinesAround(MineCounter);       // Записать в ячейку количество мин вокруг нее
        }
    }

    if (win == 0)
    {
        cout << "Мина! " << endl
             << "Игра проиграна!" << endl << endl;
    }
    else
    {
        cout << "Победа!" << endl << endl;
    }

    system("Pause");
}

