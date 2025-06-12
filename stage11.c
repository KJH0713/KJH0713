#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMBER_COUNT 5
#define TEST_COUNT 7

// 유틸 함수: 개행 문자 제거
void trimNewline(char* str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

// 멤버 구조체 정의
typedef struct {
    char name[30];
    char nickname[30];
} Member;

Member milliways_members[MEMBER_COUNT] = {
    {"고은", "eun"},
    {"원철", "won"},
    {"영진", "jin"},
    {"혜경", "hye"},
    {"아서", "arthur"}
};

// 체력 테스트 항목 이름
const char* health_tests[TEST_COUNT] = {
    "1마일 러닝", "스프린트", "푸시업", "스쿼트", "팔굽혀 펴기", "수영", "무게 들기"
};

// 체력 점수 배열
float health_scores[MEMBER_COUNT][TEST_COUNT] = {0};

// 체력 상태 입력 함수
void setHealth() {
    char input[256];
    char nickname[30];
    printf("\n[A. 체력 상태 입력]\n");
    printf("입력 형식: 닉네임,1마일,스프린트,푸시업,스쿼트,팔굽혀펴기,수영,무게들기\n");
    printf("예: jin,9.2,14.1,2.5,3.0,3.2,6.5,1.6\n");
    printf("입력하세요: ");
    fgets(input, sizeof(input), stdin);
    trimNewline(input);

    char* token = strtok(input, ",");
    if (!token) {
        printf("닉네임이 비어있습니다.\n");
        return;
    }

    strcpy(nickname, token);

    int memberIndex = -1;
    for (int i = 0; i < MEMBER_COUNT; i++) {
        if (strcmp(nickname, milliways_members[i].nickname) == 0) {
            memberIndex = i;
            break;
        }
    }

    if (memberIndex == -1) {
        printf("존재하지 않는 닉네임입니다.\n");
        return;
    }

    for (int i = 0; i < TEST_COUNT; i++) {
        token = strtok(NULL, ",");
        if (!token) {
            printf("입력이 부족합니다. %d개 항목이 필요합니다.\n", TEST_COUNT);
            return;
        }
        health_scores[memberIndex][i] = atof(token);
    }

    printf("'%s'님의 체력 상태가 저장되었습니다.\n", nickname);
}

// 체력 상태 조회 함수
void getHealth() {
    char input[30];
    printf("\n[B. 체력 상태 조회]\n");
    printf("1. 전체 조회: all\n");
    printf("2. 특정 멤버 전체 항목 조회: 닉네임 입력\n");
    printf("3. 특정 멤버 특정 항목 조회: 닉네임/항목번호 (1~7)\n");
    printf("입력하세요: ");
    fgets(input, sizeof(input), stdin);
    trimNewline(input);

    if (strcmp(input, "all") == 0) {
        for (int i = 0; i < MEMBER_COUNT; i++) {
            printf("[%s] ", milliways_members[i].nickname);
            for (int j = 0; j < TEST_COUNT; j++) {
                printf("%.2f ", health_scores[i][j]);
            }
            printf("\n");
        }
    } else if (strchr(input, '/') != NULL) {
        char* nickname = strtok(input, "/");
        char* numStr = strtok(NULL, "/");

        int memberIndex = -1, testIndex = -1;
        for (int i = 0; i < MEMBER_COUNT; i++) {
            if (strcmp(nickname, milliways_members[i].nickname) == 0) {
                memberIndex = i;
                break;
            }
        }
        testIndex = atoi(numStr) - 1;

        if (memberIndex == -1 || testIndex < 0 || testIndex >= TEST_COUNT) {
            printf("닉네임이나 항목 번호가 유효하지 않습니다.\n");
            return;
        }

        printf("[%s - %s]: %.2f\n", nickname, health_tests[testIndex], health_scores[memberIndex][testIndex]);

    } else {
        int memberIndex = -1;
        for (int i = 0; i < MEMBER_COUNT; i++) {
            if (strcmp(input, milliways_members[i].nickname) == 0) {
                memberIndex = i;
                break;
            }
        }

        if (memberIndex == -1) {
            printf("존재하지 않는 닉네임입니다.\n");
            return;
        }

        printf("[%s] 체력 데이터:\n", input);
        for (int i = 0; i < TEST_COUNT; i++) {
            printf("%s: %.2f\n", health_tests[i], health_scores[memberIndex][i]);
        }
    }
}

// 체력과 지식 메뉴 (1단계)
void trainingStage1Menu() {
    char sub[10];
    while (1) {
        printf("\n[1. 체력과 지식]\n");
        printf("A. 체력 상태 입력\n");
        printf("B. 체력 상태 조회\n");
        printf("0. 이전 메뉴로\n");
        printf("선택: ");
        fgets(sub, sizeof(sub), stdin);
        trimNewline(sub);

        if (strcmp(sub, "A") == 0 || strcmp(sub, "a") == 0) {
            setHealth();
        } else if (strcmp(sub, "B") == 0 || strcmp(sub, "b") == 0) {
            getHealth();
        } else if (strcmp(sub, "0") == 0) {
            break;
        } else {
            printf("잘못된 선택입니다.\n");
        }
    }
}

// 훈련 메뉴
void trainingMenu() {
    char input[10];
    while (1) {
        printf("\n[II. 훈련 메뉴]\n");
        printf("1. 체력과 지식\n");
        printf("0. 이전 메뉴로\n");
        printf("선택: ");
        fgets(input, sizeof(input), stdin);
        trimNewline(input);

        if (strcmp(input, "1") == 0) {
            trainingStage1Menu();
        } else if (strcmp(input, "0") == 0) {
            break;
        } else {
            printf("잘못된 입력입니다.\n");
        }
    }
}

// 주 메뉴
void mainMenu() {
    char input[10];
    while (1) {
        printf("\n=== 마그라테아 프로그램 ===\n");
        printf("I. 오디션 관리\n");
        printf("II. 훈련\n");
        printf("III. 데뷔\n");
        printf("0 또는 Q/q 입력 시 종료\n");
        printf("메뉴를 선택하세요: ");
        fgets(input, sizeof(input), stdin);
        trimNewline(input);

        if (strcmp(input, "0") == 0 || strcmp(input, "Q") == 0 || strcmp(input, "q") == 0) {
            printf("프로그램을 종료합니다.\n");
            break;
        } else if (strcmp(input, "II") == 0 || strcmp(input, "2") == 0) {
            trainingMenu();
        } else {
            printf("잘못된 입력입니다.\n");
        }
    }
}

int main() {
    mainMenu();
    return 0;
}
