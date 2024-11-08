#include <stdio.h>
#include <math.h>
#include <windows.h>

#define WIDTH 40       // �ܼ� â �ʺ�
#define HEIGHT 20      // �ܼ� â ����
#define WIDTH_RECT 5   // ���簢�� ���� ���� (�� ���� ���� ����)
#define HEIGHT_RECT 11 // ���簢�� ���� ���� (�� ���� ���� ����)
#define ANGLE_STEP 12  // ���� ������ (ȸ�� �ӵ�)

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct {
    float x, y, w;
} vec3;

typedef struct {
    float m[3][3];
} Matrix3x3;

char screen[HEIGHT][WIDTH];

void clearScreen() {
    system("cls");
}

Matrix3x3 createRotationMatrix(float angle) {
    Matrix3x3 mat;
    float radian = angle * (float)M_PI / 180.0f;
    mat.m[0][0] = cosf(radian);
    mat.m[0][1] = -sinf(radian);
    mat.m[0][2] = 0.0f;
    mat.m[1][0] = sinf(radian);
    mat.m[1][1] = cosf(radian);
    mat.m[1][2] = 0.0f;
    mat.m[2][0] = 0.0f;
    mat.m[2][1] = 0.0f;
    mat.m[2][2] = 1.0f;
    return mat;
}


vec3 Mul(vec3 a, Matrix3x3 b) {
    vec3 result;
    result.x = b.m[0][0] * a.x + b.m[0][1] * a.y + b.m[0][2] * a.w;
    result.y = b.m[1][0] * a.x + b.m[1][1] * a.y + b.m[1][2] * a.w;
    result.w = a.w;
    return result;
}

void initializeScreen() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            screen[y][x] = ' ';
        }
    }
}

// �� �� ���簢���� �ֿܼ� ���
void drawFilledRectangle(float angle) {
    initializeScreen();
    clearScreen();

    // ���簢�� �ʱ� ������ ���� (�߽� ����)
    vec3 vertices[4] = {
        {-WIDTH_RECT, -HEIGHT_RECT, 1}, { WIDTH_RECT, -HEIGHT_RECT, 1},
        { WIDTH_RECT, HEIGHT_RECT, 1}, {-WIDTH_RECT, HEIGHT_RECT, 1}
    };

    Matrix3x3 rotation = createRotationMatrix(angle);

    for (float y = -HEIGHT_RECT; y <= HEIGHT_RECT; y += 0.5) {  // ���� ����
        for (float x = -WIDTH_RECT; x <= WIDTH_RECT; x += 0.5) { // ���� ����
            vec3 point = { x, y, 1 };
            vec3 rotatedPoint = Mul(point, rotation);

            int screenX = (int)(rotatedPoint.x + WIDTH / 2);
            int screenY = (int)(rotatedPoint.y + HEIGHT / 2);

            if (screenX >= 0 && screenX < WIDTH && screenY >= 0 && screenY < HEIGHT) {
                screen[screenY][screenX] = '*';
            }
        }
    }

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%c", screen[y][x]);
        }
        printf("\n");
    }
}

int main() {
    for (float angle = 0; angle < 360; angle += ANGLE_STEP) {
        drawFilledRectangle(angle);
        Sleep(100);
    }
    return 0;
}