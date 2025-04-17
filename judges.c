#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_JUDGES 100
#define BUFFER_SIZE 512

char judges_array[MAX_JUDGES][BUFFER_SIZE];

int is_valid_judge_input(const char *input) {
    const char *required_fields[] = {
        "이름:", "성별:", "소속:", "직함:", "전문분야:", "메일:", "전화:"
    };
    for (int i = 0; i < 7; i++) {
        if (strstr(input, required_fields[i]) == NULL) {
            return 0; // 필드가 하나라도 없으면 잘못된 입력
        }
    }
    return 1;
}

void parse_and_print_judge_info(const char *data, int index) {
    char buffer[BUFFER_SIZE];
    snprintf(buffer, BUFFER_SIZE, "%s", data);

    char *token = strtok(buffer, ",");
    printf("[심사위원 %d]\n", index + 1);
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, ",");
    }
    printf("-----------------------------------\n");
}

int main() {
    char project_name[100];
    int total_judges, selected_members;

    printf("####################################\n");
    printf("#      심사위원 명단 데이터 입력       #\n");
    printf("####################################\n");

    printf("> 참여 프로젝트: ");
    fgets(project_name, sizeof(project_name), stdin);
    project_name[strcspn(project_name, "\n")] = '\0';  // 개행 제거

    printf("> 심사 총 인원: ");
    scanf("%d", &total_judges);
    getchar(); // 개행 제거

    printf("> 선발 멤버 수: ");
    scanf("%d", &selected_members);
    getchar(); // 개행 제거

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("%d명의 심사위원 정보 입력을 시작합니다.\n", total_judges);
    printf("++++++++++++++++++++++++++++++++++++\n");

    int i = 0;
    while (i < total_judges) {
        printf("*심사위원 %d: ", i + 1);
        fgets(judges_array[i], BUFFER_SIZE, stdin);
        judges_array[i][strcspn(judges_array[i], "\n")] = '\0';

        if (!is_valid_judge_input(judges_array[i])) {
            printf(">> 필수 항목이 누락되었습니다. 다시 입력하세요.\n");
            continue;
        }
        i++;
    }

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("심사위원 정보 입력이 끝났습니다.\n");
    printf("++++++++++++++++++++++++++++++++++++\n");

    char choice;
    printf("\"%s 심사위원 정보를 확인할까요? (Y/N): \"", project_name);
    scanf(" %c", &choice);

    if (choice == 'Y') {
        printf("####################################\n");
        printf("#        심사위원 데이터 출력        #\n");
        printf("####################################\n");

        for (int j = 0; j < total_judges; j++) {
            parse_and_print_judge_info(judges_array[j], j);
        }
    } else {
        printf("프로그램을 종료합니다.\n");
    }

    return 0;
}
