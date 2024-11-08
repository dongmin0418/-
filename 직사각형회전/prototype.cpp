#include <stdio.h>
#include <math.h>
#include <windows.h>

#define WIDTH 20       // �ܼ� â �ʺ�
#define HEIGHT 20      // �ܼ� â ����
#define WIDTH_RECT 5   // ���簢�� ���� ���� (�� ���� ���� ����)
#define HEIGHT_RECT 10 // ���簢�� ���� ���� (�� ���� ���� ����)
#define ANGLE_STEP 10  // ���� ������ (ȸ�� �ӵ�)

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// 2D ���� ����
typedef struct {
    float x, y, w;  // x, y ��ǥ�� ���� ��ǥ w
} vec3;

// 3x3 ��� ����
typedef struct {
    float m[3][3];
} Matrix3x3;

// ȸ�� ��� ����
Matrix3x3 createRotationMatrix(float angle) {
    Matrix3x3 mat;
    float radian = angle * M_PI / 180.0;
    mat.m[0][0] = cos(radian);
    mat.m[0][1] = -sin(radian);
    mat.m[0][2] = 0;
    mat.m[1][0] = sin(radian);
    mat.m[1][1] = cos(radian);
    mat.m[1][2] = 0;
    mat.m[2][0] = 0;
    mat.m[2][1] = 0;
    mat.m[2][2] = 1;
    return mat;
}

// ���Ϳ� ����� ����
vec3 Mul(vec3 a, Matrix3x3 b) {
    vec3 result;
    result.x = b.m[0][0] * a.x + b.m[0][1] * a.y + b.m[0][2] * a.w;
    result.y = b.m[1][0] * a.x + b.m[1][1] * a.y + b.m[1][2] * a.w;
    result.w = a.w;
    return result;
}

// ȭ�� ����� �Լ�
void clearScreen() {
    system("cls");
}

// �� �� ���簢���� �ֿܼ� ���
void drawFilledRectangle(float angle) {
    clearScreen();
    char screen[HEIGHT][WIDTH]; // ȭ���� 2D �迭�� ����

    // ȭ�� �ʱ�ȭ
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            screen[y][x] = ' ';
        }
    }

    // ���簢�� �ʱ� ������ ���� (�߽� ����)
    vec3 vertices[4] = {
        {-WIDTH_RECT, -HEIGHT_RECT, 1}, { WIDTH_RECT, -HEIGHT_RECT, 1},
        { WIDTH_RECT, HEIGHT_RECT, 1}, {-WIDTH_RECT, HEIGHT_RECT, 1}
    };

    // ȸ�� ��ȯ ��� ����
    Matrix3x3 rotation = createRotationMatrix(angle);

    // ȸ�� �� ��ǥ ���
    vec3 rotatedVertices[4];
    for (int i = 0; i < 4; i++) {
        rotatedVertices[i] = Mul(vertices[i], rotation);
    }

    // ���簢�� ���� �׸���
    for (int y = -HEIGHT_RECT; y <= HEIGHT_RECT; y++) {
        for (int x = -WIDTH_RECT; x <= WIDTH_RECT; x++) {
            // ��ȯ�� ��ǥ ���
            vec3 point = { (float)x, (float)y, 1 };
            vec3 rotatedPoint = Mul(point, rotation);

            // �߽� ��ǥ�� ���� ��ġ ����
            int screenX = (int)(rotatedPoint.x + WIDTH / 2);
            int screenY = (int)(rotatedPoint.y + HEIGHT / 2);

            // ȭ�� ���� ������ '*'�� ǥ��
            if (screenX >= 0 && screenX < WIDTH && screenY >= 0 && screenY < HEIGHT) {
                screen[screenY][screenX] = '*';
            }
        }
    }

    // ȭ�� ���
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%c", screen[y][x]);
        }
        printf("\n");
    }
}

int main() {
    for (float angle = 0; angle < 360; angle += ANGLE_STEP) {
        drawFilledRectangle(angle);   // ���� ������ ȸ���� �� �� ���簢���� �׸�
        Sleep(100);                   // 0.1�� ��� (�ִϸ��̼� ȿ��)
    }
    return 0;
}
