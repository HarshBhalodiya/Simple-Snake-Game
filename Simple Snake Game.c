#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // For _kbhit() and _getch()
#include <windows.h> // For Sleep()

#define WIDTH 20
#define HEIGHT 20

int snakeX, snakeY, foodX, foodY, score;
int snakeLength;
int tailX[100], tailY[100]; // max snake length
enum direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
enum direction dir;

void setup() {
    snakeX = WIDTH / 2;
    snakeY = HEIGHT / 2;
    do{
        foodX = rand() % WIDTH;
        foodY = rand() % HEIGHT;
    } while (foodX == snakeX && foodY == snakeY); // Ensure food does not spawn on the snake
    score = 0;
    snakeLength = 0;
    dir = RIGHT;  // Set initial direction to RIGHT
}

void draw() {
    system("cls"); // Clear console
    for (int i = 0; i < WIDTH + 2; i++)
        printf("#"); // wall on the uper side
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0){
                printf("# "); // Wall on the left
            }
            else if (i == snakeY && j == snakeX){
                printf("O"); // Snake head
            }
            else if (i == foodY && j == foodX){
                printf("@"); // Food
            }
            else {
                int isTail = 0;
                for (int k = 0; k < snakeLength; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printf("o"); // Snake tail
                        isTail = 1;
                    }
                }
                if (!isTail)
                    printf(" ");
            }
            if (j == WIDTH - 1)
                printf("#"); // Wall on the right 
        }
        printf("\n");
    }

    for (int i = 0; i < WIDTH + 2; i++){
        printf("#"); // wall on the down side
    }
    printf("\nScore : %d\n", score);
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'l': dir = LEFT; 
            break; // for left move
            case 'r': dir = RIGHT; 
            break; // for right move
            case 'u': dir = UP; 
            break; // for up move
            case 'd': dir = DOWN; 
            break; // for down move
            case 'z': dir = STOP;
            break; //for stop the game
        }
    }
}

void logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = snakeX;
    tailY[0] = snakeY;

    for (int i = 1; i < snakeLength; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X; 
        prevY = prev2Y;
    }

    switch (dir) {
        case LEFT: snakeX--; 
        break;
        case RIGHT: snakeX++; 
        break;
        case UP: snakeY--; 
        break;
        case DOWN: snakeY++; 
        break;
        default: 
        break;
    }

    if (snakeX >= WIDTH) {
        snakeX = 0; 
    }
    else if (snakeX < 0) {
        snakeX = WIDTH - 1;
    }
    if (snakeY >= HEIGHT) {
        snakeY = 0; 
    }
    else if (snakeY < 0) {
        snakeY = HEIGHT - 1;
    }

    for (int i = 0; i < snakeLength; i++){
        if (tailX[i] == snakeX && tailY[i] == snakeY){
            dir = STOP; // Collision with self
            break;
        }
    }

    if (snakeX == foodX && snakeY == foodY) {
        score++;
        foodX = rand() % WIDTH;
        foodY = rand() % HEIGHT;
        snakeLength++;
    }
}

int main() {
    setup();
    while (dir != STOP) {
        draw();
        input();
        logic();
        Sleep(100); // Sleep to control speed

        if(score % 5 == 0 && score != 0){
            Sleep(100 - (score / 5)); // Incrrase speed
        }
        else {
            Sleep(100); // Regular sleep time
        }
    }
    
    printf("Snake Position: (%d, %d)\n", snakeX, snakeY);
    printf("Food Position: (%d, %d)\n", foodX, foodY);
    
    return 0;
}