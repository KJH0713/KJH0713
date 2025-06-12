#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MEMBERS 5
#define MAX_MENTORS 8
#define MAX_QUESTIONS 5
#define MAX_SESSIONS 10

// 밀리웨이즈 멤버 닉네임 배열
char *milliways_members[MAX_MEMBERS] = {"GOEUN", "WONCHUL", "YOUNGJIN", "HYEKYUNG", "ARTHUR"};

// 연습생 능력치 저장 배열
int trainee_ability[MAX_MEMBERS];
int trainee_id[MAX_MEMBERS];
int trainee_health[MAX_MEMBERS];

// 멘토 구조체 정의
typedef struct {
    int id;  // 1~8 사이 고유 ID
    char name[20];
    int mentee_id;  // 매칭된 연습생 ID
} Mentor;

Mentor mentors[MAX_MENTORS];
int mentor_count = 0;

// 트라우마 구조체
typedef struct {
    char nickname[20];
    int age;
    char trauma[100];
} TraumaInfo;

TraumaInfo trauma_data[MAX_MEMBERS];

// 질문 구조체
typedef struct {
    int id;
    char question[200];
} Question;

Question trauma_questions[MAX_QUESTIONS] = {
    {1, "어떤 상황에서 그 트라우마를 경험하셨나요?"},
    {2, "해당 상황이 어떻게 당신의 일상생활과 감정에 어떤 영향을 미치고 있는지 말씀해주세요."},
    {3, "이 트라우마를 어떻게 극복하려고 노력하셨나요?"},
    {4, "트라우마와 관련하여 어떤 감정을 느끼고 계신가요?"},
    {5, "트라우마를 극복하기 위해 어떤 지원이 필요한 것으로 생각하시나요?"}
};

// 상담 구조체
typedef struct {
    char nickname[20];
    char question[200];
    char answer[101];
} CounselingSession;

CounselingSession sessions[MAX_SESSIONS];
int session_count = 0;

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

// 체력을 랜덤으로 반환하는 함수
int getRandomHealth() {
    return 500 + rand() % 501; // 500~1000 사이 값
}

// 연습생 정보 초기화
void initTrainees() {
    for (int i = 0; i < MAX_MEMBERS; i++) {
        trainee_id[i] = parseIntMember(milliways_members[i]);
        trainee_ability[i] = getRandomAbility();
        trainee_health[i] = getRandomHealth();

        // 트라우마 구조체 초기화
        strcpy(trauma_data[i].nickname, milliways_members[i]);
        trauma_data[i].age = 18 + rand() % 5;
        strcpy(trauma_data[i].trauma, "");
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

// 체력 조회 함수
void showHealthStatus() {
    printf("\n-- 연습생 체력 상태 --\n");
    for (int i = 0; i < MAX_MEMBERS; i++) {
        printf("%-10s: 체력 %d\n", milliways_members[i], trainee_health[i]);
    }
}

// 트라우마 입력
void inputTrauma() {
    char nickname[20];
    while (1) {
        printf("닉네임 입력 (종료하려면 'exit'): ");
        scanf("%s", nickname);
        if (strcmp(nickname, "exit") == 0) break;

        int found = -1;
        for (int i = 0; i < MAX_MEMBERS; i++) {
            found = (strcmp(trauma_data[i].nickname, nickname) == 0) ? i : found;
        }
        if (found >= 0) {
            printf("트라우마 내용을 입력하세요: ");
            getchar();
            fgets(trauma_data[found].trauma, sizeof(trauma_data[found].trauma), stdin);
            trauma_data[found].trauma[strcspn(trauma_data[found].trauma, "\n")] = 0;
        } else {
            printf("존재하지 않는 닉네임입니다.\n");
        }
    }
}

// 상담 세션
void counselingSession() {
    printf("\n-- 트라우마 입력된 멤버 목록 --\n");
    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strlen(trauma_data[i].trauma) > 0)
            printf("- %s\n", trauma_data[i].nickname);
    }
    char name[20];
    printf("상담할 닉네임 입력: ");
    scanf("%s", name);

    int found = -1;
    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(trauma_data[i].nickname, name) == 0 && strlen(trauma_data[i].trauma) > 0) {
            found = i;
            break;
        }
    }
    if (found < 0) {
        printf("입력한 닉네임은 트라우마 정보가 없습니다.\n");
        return;
    }

    int used[5] = {0};
    int count = 0;
    while (count < 3) {
        int q = rand() % MAX_QUESTIONS;
        if (used[q]) continue;
        used[q] = 1;
        printf("Q: %s\n", trauma_questions[q].question);
        getchar();
        char answer[101];
        fgets(answer, sizeof(answer), stdin);
        answer[strcspn(answer, "\n")] = 0;

        if (strlen(answer) == 0 || strlen(answer) > 100) {
            printf("잘못된 입력입니다. 다시 입력하세요.\n");
            continue;
        }

        strcpy(sessions[session_count].nickname, name);
        strcpy(sessions[session_count].question, trauma_questions[q].question);
        strcpy(sessions[session_count].answer, answer);
        session_count++;
        count++;
    }

    printf("\n-- 상담 완료 멤버 목록 --\n");
    for (int i = 0; i < session_count; i++) {
        printf("- %s\n", sessions[i].nickname);
    }

    printf("결과 확인할 닉네임 입력: ");
    scanf("%s", name);
    printf("\n[상담 결과: %s]\n", name);
    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(trauma_data[i].nickname, name) == 0) {
            printf("트라우마: %s\n", trauma_data[i].trauma);
            break;
        }
    }
    for (int i = 0; i < session_count; i++) {
        if (strcmp(sessions[i].nickname, name) == 0) {
            printf("Q: %s\nA: %s\n", sessions[i].question, sessions[i].answer);
        }
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
            initTrainees();
            showHealthStatus();
        } else if (strcmp(choice, "2") == 0) {
            while (1) {
                printf("\n-- 자기관리와 팀워크 --\n");
                printf("A. 멘토링\n");
                printf("B. 트라우마 관리\n");
                printf("0. 뒤로가기\n");
                printf("선택: ");

                char sub[10];
                scanf("%s", sub);
                if (strcmp(sub, "A") == 0 || strcmp(sub, "a") == 0) {
                    initTrainees();
                    registerMentors();
                    matchMentoring();
                } else if (strcmp(sub, "B") == 0 || strcmp(sub, "b") == 0) {
                    while (1) {
                        printf("\n-- 트라우마 관리 --\n");
                        printf("1. 트라우마 입력\n");
                        printf("2. 상담 세션\n");
                        printf("0. 뒤로가기\n");
                        printf("선택: ");

                        char trauma_menu[10];
                        scanf("%s", trauma_menu);
                        if (strcmp(trauma_menu, "1") == 0) {
                            inputTrauma();
                        } else if (strcmp(trauma_menu, "2") == 0) {
                            counselingSession();
                        } else if (strcmp(trauma_menu, "0") == 0) {
                            break;
                        } else {
                            printf("잘못된 입력입니다.\n");
                        }
                    }
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
