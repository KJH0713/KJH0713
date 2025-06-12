#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_MEMBERS 5
#define MAX_DAYS 6
#define MAX_ROUTINE_LEN 100

char* milliways_members[MAX_MEMBERS] = {"고은", "원철", "영진", "혜경", "아서"};
char* health_scores[MAX_MEMBERS][8];
char* days[MAX_DAYS] = {"월", "화", "수", "목", "금", "토"};
char* exercise_types[5][3] = {
    {"러닝", "자전거", "빠른 걷기"},
    {"푸시업", "스쿼트", ""},
    {"레그 프레스", "레그 컬", ""},
    {"철봉", "풀업 바", ""},
    {"플랭크", "크런치", ""}
};
char member_routine[MAX_MEMBERS][MAX_DAYS][MAX_ROUTINE_LEN];

void parseScores(char* input, char* nickname) {
    int memberIndex = -1;
    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(milliways_members[i], nickname) == 0) {
            memberIndex = i;
            break;
        }
    }
    if (memberIndex == -1) {
        printf("존재하지 않는 멤버입니다.\n");
        return;
    }

    char* token = strtok(input, ",");
    int i = 0;
    while (token && i < 7) {
        health_scores[memberIndex][i] = strdup(token);
        token = strtok(NULL, ",");
        i++;
    }
    health_scores[memberIndex][7] = nickname;
    printf("%s님의 체력 정보가 저장되었습니다.\n", nickname);
}

void setHealth() {
    char input[200];
    char nickname[50];
    printf("멤버 닉네임을 입력하세요: ");
    scanf("%s", nickname);
    getchar();
    printf("1마일 러닝, 스프린트, 푸시업, 스쿼트, 팔굽혀펴기, 수영, 무게들기 값을 쉼표로 구분하여 입력하세요:\n");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    parseScores(input, nickname);
}

void getHealth() {
    char nickname[50];
    printf("멤버 닉네임을 입력하세요 (전체 조회는 'all'): ");
    scanf("%s", nickname);

    if (strcmp(nickname, "all") == 0) {
        for (int i = 0; i < MAX_MEMBERS; i++) {
            printf("%s: ", milliways_members[i]);
            for (int j = 0; j < 7; j++) {
                printf("%s ", health_scores[i][j] ? health_scores[i][j] : "N/A");
            }
            printf("\n");
        }
    } else {
        int found = 0;
        for (int i = 0; i < MAX_MEMBERS; i++) {
            if (strcmp(nickname, milliways_members[i]) == 0) {
                found = 1;
                printf("%s: ", nickname);
                for (int j = 0; j < 7; j++) {
                    printf("%s ", health_scores[i][j] ? health_scores[i][j] : "N/A");
                }
                printf("\n");
                break;
            }
        }
        if (!found) printf("해당 닉네임이 존재하지 않습니다.\n");
    }
}

void setExerciseRoutine() {
    char name[50];
    int memberIndex = -1;
    printf("멤버 이름을 입력하세요: ");
    scanf("%s", name);

    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(milliways_members[i], name) == 0) {
            memberIndex = i;
            break;
        }
    }
    if (memberIndex == -1) {
        printf("존재하지 않는 멤버입니다.\n");
        return;
    }

    int coreUsed = 0;
    for (int d = 0; d < MAX_DAYS; d++) {
        char aerobic[50], strength[50];
        printf("[%s요일] 유산소 운동을 선택하세요 (러닝/자전거/빠른 걷기): ", days[d]);
        scanf("%s", aerobic);
        printf("[%s요일] 근력 또는 코어 운동을 선택하세요 (푸시업/스쿼트/레그 프레스/레그 컬/철봉/풀업 바/플랭크/크런치): ", days[d]);
        scanf("%s", strength);

        if (strcmp(strength, "플랭크") == 0 || strcmp(strength, "크런치") == 0) {
            if (coreUsed) {
                printf("코어 운동은 한 번만 선택할 수 있습니다. 다른 운동을 입력하세요.\n");
                d--; continue;
            } else coreUsed = 1;
        }

        snprintf(member_routine[memberIndex][d], MAX_ROUTINE_LEN, "%s + %s", aerobic, strength);
    }
    printf("%s님의 기초 운동 루틴이 설정되었습니다.\n", name);
}

void getExerciseRoutine() {
    char name[50];
    int memberIndex = -1;
    printf("운동 루틴을 조회할 멤버 이름을 입력하세요: ");
    scanf("%s", name);

    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(milliways_members[i], name) == 0) {
            memberIndex = i;
            break;
        }
    }
    if (memberIndex == -1) {
        printf("존재하지 않는 멤버입니다.\n");
        return;
    }

    printf("[%s님의 운동 루틴]\n", name);
    for (int d = 0; d < MAX_DAYS; d++) {
        printf("%s요일: %s\n", days[d], member_routine[memberIndex][d][0] ? member_routine[memberIndex][d] : "설정 안됨");
    }
}

void trainingMenu() {
    while (1) {
        printf("\n== 훈련 메뉴 ==\n1. 체력과 지식\n2. 자기관리 및 팀워크\n0. 상위 메뉴\n선택: ");
        char choice[10];
        scanf("%s", choice);

        if (strcmp(choice, "1") == 0) {
            while (1) {
                printf("\n[1. 체력과 지식]\nA. 체력 상태 입력\nB. 체력 상태 조회\nC. 기초 운동 루틴 설정\nD. 기초 운동 루틴 조회\n0. 상위 메뉴\n선택: ");
                char sub[10];
                scanf("%s", sub);
                if (strcmp(sub, "A") == 0 || strcmp(sub, "a") == 0) setHealth();
                else if (strcmp(sub, "B") == 0 || strcmp(sub, "b") == 0) getHealth();
                else if (strcmp(sub, "C") == 0 || strcmp(sub, "c") == 0) setExerciseRoutine();
                else if (strcmp(sub, "D") == 0 || strcmp(sub, "d") == 0) getExerciseRoutine();
                else if (strcmp(sub, "0") == 0) break;
            }
        } else if (strcmp(choice, "0") == 0) break;
    }
}

void mainMenu() {
    while (1) {
        printf("\n=== 마그라테아 프로그램 ===\nI. 오디션 관리\nII. 훈련\nIII. 데뷔\n0 또는 Q/q 입력 시 종료\n메뉴를 선택하세요: ");
        char input[10];
        scanf("%s", input);
        if (strcmp(input, "II") == 0 || strcmp(input, "2") == 0) trainingMenu();
        else if (strcmp(input, "0") == 0 || strcmp(input, "Q") == 0 || strcmp(input, "q") == 0) break;
    }
}

int main() {
    mainMenu();
    return 0;
}
