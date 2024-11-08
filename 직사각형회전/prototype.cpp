#include <stdio.h>
#include <math.h>
#include <windows.h>

#define WIDTH 20       // 콘솔 창 너비
#define HEIGHT 20      // 콘솔 창 높이
#define WIDTH_RECT 5   // 직사각형 가로 길이 (한 변의 절반 길이)
#define HEIGHT_RECT 10 // 직사각형 세로 길이 (한 변의 절반 길이)
#define ANGLE_STEP 10  // 각도 증가량 (회전 속도)

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// 2D 벡터 정의
typedef struct {
    float x, y, w;  // x, y 좌표와 동차 좌표 w
} vec3;

// 3x3 행렬 정의
typedef struct {
    float m[3][3];
} Matrix3x3;

// 회전 행렬 생성
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

// 벡터와 행렬의 곱셈
vec3 Mul(vec3 a, Matrix3x3 b) {
    vec3 result;
    result.x = b.m[0][0] * a.x + b.m[0][1] * a.y + b.m[0][2] * a.w;
    result.y = b.m[1][0] * a.x + b.m[1][1] * a.y + b.m[1][2] * a.w;
    result.w = a.w;
    return result;
}

// 화면 지우기 함수
void clearScreen() {
    system("cls");
}

// 꽉 찬 직사각형을 콘솔에 출력
void drawFilledRectangle(float angle) {
    clearScreen();
    char screen[HEIGHT][WIDTH]; // 화면을 2D 배열로 정의

    // 화면 초기화
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            screen[y][x] = ' ';
        }
    }

    // 직사각형 초기 꼭짓점 정의 (중심 기준)
    vec3 vertices[4] = {
        {-WIDTH_RECT, -HEIGHT_RECT, 1}, { WIDTH_RECT, -HEIGHT_RECT, 1},
        { WIDTH_RECT, HEIGHT_RECT, 1}, {-WIDTH_RECT, HEIGHT_RECT, 1}
    };

    // 회전 변환 행렬 생성
    Matrix3x3 rotation = createRotationMatrix(angle);

    // 회전 후 좌표 계산
    vec3 rotatedVertices[4];
    for (int i = 0; i < 4; i++) {
        rotatedVertices[i] = Mul(vertices[i], rotation);
    }

    // 직사각형 내부 그리기
    for (int y = -HEIGHT_RECT; y <= HEIGHT_RECT; y++) {
        for (int x = -WIDTH_RECT; x <= WIDTH_RECT; x++) {
            // 변환된 좌표 계산
            vec3 point = { (float)x, (float)y, 1 };
            vec3 rotatedPoint = Mul(point, rotation);

            // 중심 좌표에 맞춰 위치 조정
            int screenX = (int)(rotatedPoint.x + WIDTH / 2);
            int screenY = (int)(rotatedPoint.y + HEIGHT / 2);

            // 화면 내에 있으면 '*'로 표시
            if (screenX >= 0 && screenX < WIDTH && screenY >= 0 && screenY < HEIGHT) {
                screen[screenY][screenX] = '*';
            }
        }
    }

    // 화면 출력
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%c", screen[y][x]);
        }
        printf("\n");
    }
}

int main() {
    for (float angle = 0; angle < 360; angle += ANGLE_STEP) {
        drawFilledRectangle(angle);   // 현재 각도로 회전된 꽉 찬 직사각형을 그림
        Sleep(100);                   // 0.1초 대기 (애니메이션 효과)
    }
    return 0;
}
