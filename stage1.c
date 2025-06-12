#include <stdio.h>
#include <string.h>
#include <locale.h>

#define TRAINING_COUNT 8

// 훈련 통과 상태 저장 배열
char trainingStatus[TRAINING_COUNT] = { 0 };  // 'P' 또는 'F' 또는 0

// 줄바꿈 문자 제거 함수
void trimNewline(char *str) {
    str[strcspn(str, "\n")] = 0;
}

// 오디션 관리 메뉴 (임시 구현)
void auditionMenu() {
    printf("\n[오디션 관리 메뉴]\n(현재 기능 없음, 뒤로 돌아갑니다)\n");
}

// 데뷔 메뉴 (임시 구현)
void debutMenu() {
    printf("\n[데뷔 메뉴]\n(현재 기능 없음, 뒤로 돌아갑니다)\n");
}

// 훈련 메뉴
void trainingMenu() {
    char input[10];
    while (1) {
        printf("\n=== 훈련 프로그램 ===\n");
        for (int i = 0; i < TRAINING_COUNT; i++) {
            printf("%d. ", i + 1);
            switch (i + 1) {
                case 1: printf("체력과 지식"); break;
                case 2: printf("자기관리 및 팀워크"); break;
                case 3: printf("언어 및 발음"); break;
                case 4: printf("보컬"); break;
                case 5: printf("댄스"); break;
                case 6: printf("비주얼 및 이미지"); break;
                case 7: printf("연기 및 무대 퍼포먼스"); break;
                case 8: printf("팬 소통"); break;
            }
            if (trainingStatus[i] == 'P') printf(" [통과]");
            else if (trainingStatus[i] == 'F') printf(" [실패]");
            printf("\n");
        }
        printf("0. 상위 메뉴로 돌아가기\n");
        printf("훈련 번호를 선택하세요: ");
        fgets(input, sizeof(input), stdin);
        trimNewline(input);

        if (strcmp(input, "0") == 0) break;

        int choice = atoi(input);
        if (choice < 1 || choice > 8) {
            printf("잘못된 선택입니다.\n");
            continue;
        }

        if (trainingStatus[choice - 1] == 'P') {
            printf("이미 통과한 훈련입니다.\n");
            continue;
        }

        // 1~2단계 순서 검증
        if (choice == 2 && trainingStatus[0] != 'P') {
            printf("1단계를 먼저 통과해야 합니다.\n");
            continue;
        }

        // 3~8단계는 1, 2단계를 모두 통과한 경우만
        if (choice >= 3 && (trainingStatus[0] != 'P' || trainingStatus[1] != 'P')) {
            printf("1, 2단계를 모두 통과해야 선택할 수 있습니다.\n");
            continue;
        }

        // 평가 과정
        char yn[10];
        printf("평가 결과를 입력하시겠습니까? (Y/N): ");
        fgets(yn, sizeof(yn), stdin);
        trimNewline(yn);
        if (strcmp(yn, "Y") == 0 || strcmp(yn, "y") == 0) {
            char result[10];
            printf("훈련을 마치고 인증에 통과했나요? (P/F): ");
            fgets(result, sizeof(result), stdin);
            trimNewline(result);
            if (strcmp(result, "P") == 0 || strcmp(result, "p") == 0) {
                trainingStatus[choice - 1] = 'P';
                printf("훈련 %d단계를 통과했습니다!\n", choice);
            } else {
                trainingStatus[choice - 1] = 'F';
                printf("훈련 %d단계에서 실패했습니다.\n", choice);
            }
        } else {
            printf("훈련 메뉴로 돌아갑니다.\n");
        }
    }
}

// 메인 메뉴
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

        if (strcmp(input, "I") == 0 || strcmp(input, "i") == 0) {
            auditionMenu();
        } else if (strcmp(input, "II") == 0 || strcmp(input, "ii") == 0) {
            trainingMenu();
        } else if (strcmp(input, "III") == 0 || strcmp(input, "iii") == 0) {
            debutMenu();
        } else if (strcmp(input, "0") == 0 || strcmp(input, "Q") == 0 || strcmp(input, "q") == 0 || input[0] == '\0') {
            printf("프로그램을 종료합니다.\n");
            break;
        } else {
            printf("잘못된 입력입니다.\n");
        }
    }
}

int main() {
    setlocale(LC_ALL, "");  // 한글 출력 위한 설정
    mainMenu();
    return 0;
}
