#include <iostream>
#include <windows.h> // For console buffer and to allow for the sleep function
#include <string>    // For string manipulation
#include <conio.h>   // For user inputs
#include <stdlib.h>  // For random seed
#include <time.h>    // For random seed
#include <vector>    // For storing information on the snake's position

bool menu_stop = false;
bool game_stop = false;
bool game_ending = false;

// General Setup for the Menu
int game_speed = 2;
const int HEIGHT = 20;
const int WIDTH = 30;
const int GAME_NAME_HEIGHT = 7;
const int GAME_START_HEIGHT = 9;
const int GAME_SPEED_HEIGHT = 12;
const int GAME_AUTHOR_HEIGHT = 18;
const std::string GAME_NAME = "CONSOLE SNAKE!"; // 14 symbols
const std::string GAME_START = "PRESS SPACE!"; // 12 symbols
const std::string GAME_SPEED_1 = "Game Speed: <";
const std::string GAME_SPEED_2 = ">";
const std::string GAME_AUTHOR = "SI-JA 2020"; // 10 symbols

// General Setup for the Game
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
int snake_x, snake_y, snake_prev_x, snake_prev_y, fruit_x, fruit_y, snake_len, score;
enum eDirection { STOP, LEFT, RIGHT, UP, DOWN };
eDirection dir;
std::vector<int> snake_full_X;
std::vector<int> snake_full_Y;

/// <summary>
/// Function found to hide the cursor on the screen
/// Reference: https://stackoverflow.com/questions/18028808/remove-blinking-underscore-on-console-cmd-prompt
/// </summary>
/// <param name="showFlag">Show or don't the blinking cursor</param>
void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

/// <summary>
/// Weird hack I've seen online to stop the console from flickering (?)
/// Use this instead of system("CLS")
/// Reference: https://www.sololearn.com/Discuss/1714796/how-to-update-console-without-flicker-in-c
/// </summary>
void ClearScreen()
{
    COORD cursorPosition;	
    cursorPosition.X = 0;	
    cursorPosition.Y = 0;	
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

/// <summary>
/// Input conditions for when the menu is active in the start screen.
/// </summary>
void MenuInput()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 75: // Left arrow key
            if (1 < game_speed && game_speed <= 3)
            {
                game_speed -= 1;
            }
            break;
        case 77: // Right arrow key
            if (1 <= game_speed && game_speed < 3)
            {
                game_speed += 1;
            }
            break;
        case 32: // Spacebar
            menu_stop = true;
            break;
        }
    }
}

/// <summary>
/// A menu that runs when the game starts.
/// </summary>
void Menu()
{
    ClearScreen();
    // Draw the boarder and the whole menu
    for (int i = 0; i < HEIGHT; i++)
    {
        if (i == 0 || i == HEIGHT - 1)
        {
            for (int j = 0; j < WIDTH; j++)
            {
                SetConsoleTextAttribute(hConsole, 15);
                std::cout << "#";
                SetConsoleTextAttribute(hConsole, 15);
            }
            std::cout << std::endl;
        }
        else
        {
            for (int j = 0; j < WIDTH; j++)
            {
                if (j == 0)
                {
                    SetConsoleTextAttribute(hConsole, 15);
                    std::cout << "#";
                    SetConsoleTextAttribute(hConsole, 15);
                }
                else if (j == WIDTH - 1)
                {
                    std::cout << "#" << std::endl;
                }
                else if (i == GAME_NAME_HEIGHT && j == 8)
                {
                    SetConsoleTextAttribute(hConsole, 14);
                    std::cout << GAME_NAME;
                    j += GAME_NAME.length() - 1; 
                    SetConsoleTextAttribute(hConsole, 15);
                }
                else if (i == GAME_START_HEIGHT && j == 9)
                {
                    SetConsoleTextAttribute(hConsole, 14);
                    std::cout << GAME_START;
                    j += GAME_START.length() - 1;
                    SetConsoleTextAttribute(hConsole, 15);
                }
                else if (i == GAME_AUTHOR_HEIGHT && j == 10)
                {
                    SetConsoleTextAttribute(hConsole, 14);
                    std::cout << GAME_AUTHOR;
                    j += GAME_AUTHOR.length() - 1;
                    SetConsoleTextAttribute(hConsole, 15);
                }
                else if (i == GAME_SPEED_HEIGHT && j == 7)
                {
                    SetConsoleTextAttribute(hConsole, 14);
                    std::cout << GAME_SPEED_1 << game_speed << GAME_SPEED_2;
                    j += GAME_SPEED_1.length() + GAME_SPEED_2.length();
                    SetConsoleTextAttribute(hConsole, 15);
                }
                else
                {
                    SetConsoleTextAttribute(hConsole, 15);
                    std::cout << " ";
                }
            }  
        }
    }
}

void GenerateFruitPosition()
{
    do
    {
        fruit_x = (rand() % WIDTH - 4) + 2;
        fruit_y = (rand() % HEIGHT - 4) + 2;
    } while (!(fruit_x != 0 && fruit_x != HEIGHT - 1 && fruit_y != 0 && fruit_y != WIDTH - 1));
}

/// <summary>
/// Main Setup that takes place when the game launches after the menu screen
/// </summary>
void Setup()
{
    srand(time(NULL));
    dir = STOP;
    snake_x = WIDTH / 2;
    snake_y = HEIGHT / 2;
    snake_prev_x = snake_x;
    snake_prev_y = snake_y;
    snake_full_X.push_back(snake_x);
    snake_full_Y.push_back(snake_y);
    GenerateFruitPosition();
    snake_len = 1;
    score = 0;
}

/// <summary>
/// Function to draw the Screen for when the game operates
/// </summary>
void Draw()
{
    ClearScreen();
    for (int i = 0; i < HEIGHT; i++)
    {
        if (i == 0 || i == HEIGHT - 1)
        {
            for (int j = 0; j < WIDTH; j++)
            {
                SetConsoleTextAttribute(hConsole, 15);
                std::cout << "#";
            }
            std::cout << std::endl;
        }
        else
        {
            for (int j = 0; j < WIDTH; j++)
            {
                if (j == 0)
                {
                    SetConsoleTextAttribute(hConsole, 15);
                    std::cout << "#";
                }
                else if (j == WIDTH - 1)
                {
                    SetConsoleTextAttribute(hConsole, 15);
                    std::cout << "#" << std::endl;
                }
                else if (i == fruit_y && j == fruit_x)
                {
                    SetConsoleTextAttribute(hConsole, 10);
                    std::cout << "@";
                    SetConsoleTextAttribute(hConsole, 15);
                }
                else
                {
                    bool value_printed = false;
                    for (int k = 0; k < snake_len; k++)
                    {
                        if (snake_full_X[k] == j && snake_full_Y[k] == i)
                        {
                            if (k == 0)
                            {
                                SetConsoleTextAttribute(hConsole, 12);
                                std::cout << "X";
                                value_printed = true;
                                SetConsoleTextAttribute(hConsole, 15);
                            }
                            else
                            {
                                SetConsoleTextAttribute(hConsole, 12);
                                std::cout << "x";
                                value_printed = true;
                                SetConsoleTextAttribute(hConsole, 15);
                            }
                        }
                    }
                    if (!value_printed)
                    {
                        std::cout << " ";
                    }
                }
            }
        }
    }
    std::cout << "\nSCORE: " << score << std::endl;
    std::cout << "Press 'X' to quit" << std::endl;
    std::cout << "Press 'Z' to reset the fruit" << std::endl;
}

/// <summary>
/// Main input for the game.
/// </summary>
void GameInput()
{
    if (_kbhit())
    {
        switch (_getch()) 
        {
            case 75:
                if (dir == RIGHT)
                {
                    break;
                }
                dir = LEFT;
                break;
            case 77:
                if (dir == LEFT)
                {
                    break;
                }
                dir = RIGHT;
                break;
            case 72:
                if (dir == DOWN)
                {
                    break;
                }
                dir = UP;
                break;
            case 80:
                if (dir == UP)
                {
                    break;
                }
                dir = DOWN;
                break;
            case 'x':
                game_stop = true;
                break;
            case 'z':
                GenerateFruitPosition();
                break;
        }
    }
}

/// <summary>
/// Logic of our game controls and the snake movements.
/// </summary>
void Logic()
{
    // Account for movement direction
    switch (dir)
    {
        case LEFT:
            snake_x--;
            break;
        case RIGHT:
            snake_x++;
            break;
        case UP:
            snake_y--;
            break;
        case DOWN:
            snake_y++;
            break;
        default:
            break;
    }

    // Account for collision with walls or not
    if (snake_x == 0 || snake_x == WIDTH - 1 || snake_y == 0 || snake_y == HEIGHT - 1)
    {
        game_stop = true;
    }

    snake_full_X[0] = snake_x;
    snake_full_Y[0] = snake_y;

    // Account for increasing in size tail and changing internal coordinates
    for (int i = snake_full_X.size() - 1; i > 0; i--)
    {
        snake_full_X[i] = snake_full_X[i - 1];
    }

    for (int i = snake_full_Y.size() - 1; i > 0; i--)
    {
        snake_full_Y[i] = snake_full_Y[i - 1];
    }

    // Account for when the snake gets the fruit
    if (snake_x == fruit_x && snake_y == fruit_y)
    {
        snake_len++;
        snake_full_X.push_back(snake_prev_x);
        snake_full_Y.push_back(snake_prev_y);
        score += 5 + (snake_len / 4) * 10;
        GenerateFruitPosition();
    }

    snake_prev_x = snake_x;
    snake_prev_y = snake_y;
}

/// <summary>
/// Draw and end screen for the player with options to quit, restart the game or go to the main menu.
/// </summary>
void DrawEndScreen()
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
    const int LINE_1 = HEIGHT / 4;
    const int LINE_2 = LINE_1 + 1;
    const int LINE_3 = LINE_2 + 1;
    const int LINE_4 = LINE_3 + 1;
    const int LINE_5 = LINE_4 + 1;
    const int LINE_6 = LINE_5 + 1;
    for (int i = 0; i < HEIGHT; i++)
    {
        if (LINE_1 == i)
        {
            for (int j = 0; j < WIDTH; j++)
            {
                std::cout << "#";
            }
            std::cout << std::endl;
        }
        if (LINE_2 == i)
        {
            std::cout << "#TO PLAY AGAIN PRESS SPACEBAR" << std::endl;
        }
        if (LINE_3 == i)
        {
            std::cout << "#      TO QUIT PRESS 'Z'" << std::endl;
        }
        if (LINE_4 == i)
        {
            std::cout << "#TO GO TO THE MENU PRESS 'X'" << std::endl;
        }
        if (LINE_5 == i)
        {
            for (int j = 0; j < WIDTH; j++)
            {
                std::cout << "#";
            }
            std::cout << std::endl;
        }
        if (LINE_6 == i)
        {
            std::cout << "#      YOUR SCORE: " << score <<  std::endl;
        }
        std::cout << std::endl;
    }
}

void EndingInput()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case ' ':
            game_ending = true;
            break;
        case 'z':
            game_ending = true;
            break;
        case 'x':
            game_ending = true;
            break;
        }
    }
}

int main()
{
    ShowConsoleCursor(false);

    // Set Up Game with the Menu
    do 
    {
        Menu();
        MenuInput();
    } while (!menu_stop);
    system("CLS");

    Setup();
    // Play The Actual Game
    do
    {
        Draw();
        GameInput();
        Logic();
        Sleep(15 * (4 - game_speed));
    } while (!game_stop);

    // Show the ending screen
    do
    {
        DrawEndScreen();
        EndingInput();
    } while (!game_ending);
    system("CLS");
    std::cout << "My man, you expect too much from this game" << std::endl;
    std::cout << "Although, thank you for playing!" << std::endl;
    system("PAUSE");
}