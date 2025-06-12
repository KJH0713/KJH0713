#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MEMBERS 5
#define MAX_MENTORS 8

// 밀리웨이즈 멤버 닉네임 배열
char *milliways_members[MAX_MEMBERS] = {"GOEUN", "WONCHUL", "YOUNGJIN", "HYEKYUNG", "ARTHUR"};

// 연습생 능력치 저장 배열
int trainee_ability[MAX_MEMBERS];
int trainee_id[MAX_MEMBERS];

// 멘토 구조체 정의
typedef struct {
    int id;  // 1~8 사이 고유 ID
    char name[20];
    int mentee_id;  // 매칭된 연습생 ID
} Mentor;

Mentor mentors[MAX_MENTORS];
int mentor_count = 0;

// 닉네임을 정수로 바꾸는 함수
int parseIntMember(char *nickname) {
    int sum = 0;
    for (int i = 0; i < strlen(nickname); i++) {
        sum += (int)nickname[i];
    }
    return sum;
}

// 능력치를 랜덤으로 반환하는 함수
int getRandomAbility() {
    return 100 + rand() % 901; // 100~1000 사이 값
}

// 연습생 정보 초기화
void initTrainees() {
    for (int i = 0; i < MAX_MEMBERS; i++) {
        trainee_id[i] = parseIntMember(milliways_members[i]);
        trainee_ability[i] = getRandomAbility();
    }
}

// 멘토 등록 함수
void registerMentors() {
    printf("\n-- 멘토 등록 --\n");
    for (int i = 0; i < MAX_MENTORS; i++) {
        mentors[i].id = i + 1;
        printf("%d번 멘토 이름을 입력하세요: ", i + 1);
        scanf("%s", mentors[i].name);
        mentors[i].mentee_id = -1; // 초기화
    }
    mentor_count = MAX_MENTORS;
}

// 멘토링 매칭 함수
void matchMentoring() {
    printf("\n-- 멘토링 매칭 --\n");
    for (int i = 0; i < MAX_MEMBERS; i++) {
        int mentor_id = (trainee_id[i] % MAX_MENTORS) + 1; // 1~8 사이
        for (int j = 0; j < mentor_count; j++) {
            if (mentors[j].id == mentor_id) {
                mentors[j].mentee_id = trainee_id[i];
                break;
            }
        }
    }

    // 출력
    printf("\n-- 매칭 결과 --\n");
    for (int i = 0; i < MAX_MEMBERS; i++) {
        int mentor_id = (trainee_id[i] % MAX_MENTORS) + 1;
        char *mentor_name = NULL;
        for (int j = 0; j < mentor_count; j++) {
            if (mentors[j].id == mentor_id) {
                mentor_name = mentors[j].name;
                break;
            }
        }
        printf("연습생 %-10s (ID: %d) → 멘토 %-10s (ID: %d)\n",
               milliways_members[i], trainee_id[i], mentor_name, mentor_id);
    }
}

// 트레이닝 메뉴 확장
void trainingMenu() {
    while (1) {
        printf("\n=== 훈련 메뉴 ===\n");
        printf("1. 체력과 지식\n");
        printf("2. 자기관리와 팀워크\n");
        printf("0. 뒤로가기\n");
        printf("메뉴 선택: ");

        char choice[10];
        scanf("%s", choice);

        if (strcmp(choice, "1") == 0) {
            printf("(체력과 지식 메뉴 실행됨)\n");
            // 기존 체력 코드 실행 위치
        } else if (strcmp(choice, "2") == 0) {
            while (1) {
                printf("\n-- 자기관리와 팀워크 --\n");
                printf("A. 멘토링\n");
                printf("0. 뒤로가기\n");
                printf("선택: ");

                char sub[10];
                scanf("%s", sub);
                if (strcmp(sub, "A") == 0 || strcmp(sub, "a") == 0) {
                    initTrainees();
                    registerMentors();
                    matchMentoring();
                } else if (strcmp(sub, "0") == 0) {
                    break;
                } else {
                    printf("잘못된 입력입니다.\n");
                }
            }
        } else if (strcmp(choice, "0") == 0) {
            break;
        } else {
            printf("잘못된 입력입니다.\n");
        }
    }
}

// 메인 메뉴
int main() {
    srand(time(NULL));
    while (1) {
        printf("\n=== 마그라테아 프로그램 ===\n");
        printf("I. 오디션 관리\n");
        printf("II. 훈련\n");
        printf("III. 데뷔\n");
        printf("0 또는 Q/q 입력 시 종료\n");
        printf("메뉴를 선택하세요: ");

        char input[10];
        scanf("%s", input);

        if (strcmp(input, "0") == 0 || strcmp(input, "Q") == 0 || strcmp(input, "q") == 0) {
            printf("프로그램을 종료합니다.\n");
            break;
        } else if (strcmp(input, "I") == 0 || strcmp(input, "i") == 0) {
            printf("(오디션 관리 메뉴 실행됨)\n");
        } else if (strcmp(input, "II") == 0 || strcmp(input, "ii") == 0) {
            trainingMenu();
        } else if (strcmp(input, "III") == 0 || strcmp(input, "iii") == 0) {
            printf("(데뷔 메뉴 실행됨)\n");
        } else {
            printf("잘못된 입력입니다. 다시 선택해주세요.\n");
        }
    }
    return 0;
}
