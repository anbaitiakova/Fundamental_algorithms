#include <iostream>
#define SIZE 8
class Solve
{
public:
    virtual void setQueen(int a) = 0;
};

class Solve_Recursive: public Solve
{
public:
    int chess_board[SIZE][SIZE] = {0};
    int results_count = 0;
    Solve_Recursive() = default;

    void showBoard()
    {
        for(int a = 0; a < SIZE; ++a)
        {
            for(int b = 0; b < SIZE; ++b)
            {
                std::cout << ((chess_board[a][b]) ? "Q " : ". ");
            }
            std::cout << '\n';
        }
    }

    bool checkQueen(int a, int b)
    {
        for(int i = 0; i < a; ++i)
        {
            if(chess_board[i][b])
            {
                return false;
            }
        }

        for(int i = 1; i <= a && b-i >= 0; ++i)
        {
            if(chess_board[a - i][b - i])
            {
                return false;
            }
        }

        for(int i = 1; i <= a && b+i < SIZE; i++)
        {
            if(chess_board[a - i][b + i])
            {
                return false;
            }
        }

        return true;
    }

    void setQueen(int a) override
    {
        if(a == SIZE)
        {
            showBoard();
            std::cout << "Result recursive: " << ++results_count << "\n\n";
            return;
        }

        for(int i = 0; i < SIZE; ++i)
        {
            if(checkQueen(a, i))
            {
                chess_board[a][i] = 1;
                setQueen(a + 1);
                chess_board[a][i] = 0;
            }
        }
        return;
    }
    ~Solve_Recursive() = default;
};

class Solve_Iterative: public Solve
{
public:
    struct queen
    {
        int x, y;
        queen(int m_x = 0, int m_y = 0)
        {
            x = m_x;
            y = m_y;
        }
    };

    void Fill(int** pole)
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++) pole[i][j] = 0;
        }
    }

    void Show_Board(int** pole)
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                if(pole[i][j] == 0)
                    std::cout << ". ";
                else std::cout << "Q ";
            }
            std::cout << std::endl;
        }
    }

    bool Check_Queen(queen ferz, queen* all_ferz, int N)
    {
        for (int i = 0; i < N; i++)
        {
            int dx = abs(ferz.x - all_ferz[i].x);
            int dy = abs(ferz.y - all_ferz[i].y);
            if (dx == 0 || dy == 0 || (dx  == dy)) return true;
        }
        return false;
    }

    void setQueen(int a) override
    {
        int solution = 0, count_queens = 0;
        int** field = new int*[SIZE];
        for (int i = 0; i < SIZE; i++)
            field[i] = new int[SIZE];
        queen* all_queens = new queen[SIZE];
        Fill(field);

        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                queen temp(j, i);
                bool result = Check_Queen(temp, all_queens, count_queens);
                if (!result)
                {
                    field[i][j] = 1;
                    all_queens[count_queens].x = j;
                    all_queens[count_queens].y = i;
                    count_queens++;
                    if (count_queens == SIZE)
                    {
                        std::cout <<"Result iterative: "<< solution + 1 << std::endl;
                        Show_Board(field);
                        std::cout << std::endl;

                        solution++;
                        field[all_queens[count_queens - 1].y][all_queens[count_queens - 1].x] = 0;
                        i = all_queens[count_queens - 1].y;
                        j = all_queens[count_queens - 1].x;
                        count_queens--;
                        if((j + 1) == SIZE && count_queens != 0)
                        {
                            field[all_queens[count_queens - 1].y][all_queens[count_queens - 1].x] = 0;
                            i = all_queens[count_queens - 1].y;
                            j = all_queens[count_queens - 1].x;
                            count_queens--;
                        }
                        continue;
                    }
                    break;
                }
                else if ((j + 1) == SIZE)
                {
                    field[all_queens[count_queens - 1].y][all_queens[count_queens - 1].x] = 0;
                    i = all_queens[count_queens - 1].y;
                    j = all_queens[count_queens - 1].x;
                    count_queens--;
                    if ((j+1) == SIZE && count_queens != 0)
                    {
                        field[all_queens[count_queens - 1].y][all_queens[count_queens - 1].x] = 0;
                        i = all_queens[count_queens - 1].y;
                        j = all_queens[count_queens - 1].x;
                        count_queens--;
                    }
                }
            }
        }

        for (int i = 0; i < SIZE; i++) delete field[i];
        delete[] field;
        delete[] all_queens;
    }

};