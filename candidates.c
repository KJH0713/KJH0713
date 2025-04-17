#include <stdio.h>
#include <stdlib.h>

#define NUM_CANDIDATES 6
#define NUM_FIELDS 11

// 후보자 정보 배열
char candidate01[NUM_FIELDS][200];
char candidate02[NUM_FIELDS][200];
char candidate03[NUM_FIELDS][200];
char candidate04[NUM_FIELDS][200];
char candidate05[NUM_FIELDS][200];
char candidate06[NUM_FIELDS][200];

// 후보자 배열을 포인터 배열로 관리
char (*candidates[NUM_CANDIDATES])[NUM_FIELDS][200] = {
    &candidate01, &candidate02, &candidate03, &candidate04, &candidate05, &candidate06
};

// 속성명 배열
const char *member_info[NUM_FIELDS] = {
    "성명", "생일", "성별", "메일", "국적", "BMI", "주스킬", "보조스킬", "TOPIK", "MBTI", "소개"
};

int main() {
    int i;
    printf("####################################\n");
    printf("     오디션 후보자 데이터 입력\n");
    printf("####################################\n");

    i = 0;
    while (i < NUM_CANDIDATES) {
        printf("%d번째 후보자의 정보를 입력합니다.\n", i + 1);
        printf("---------------------------------\n");

        for (int j = 0; j < NUM_FIELDS; j++) {
            printf("%d. %s: ", j + 1, member_info[j]);
            fgets((*candidates[i])[j], 200, stdin);
            // 개행 제거
            for (int k = 0; (*candidates[i])[j][k] != '\0'; k++) {
                if ((*candidates[i])[j][k] == '\n') {
                    (*candidates[i])[j][k] = '\0';
                    break;
                }
            }
        }
        printf("=================================\n");
        i++;
    }

    printf("\n####################################\n");
    printf("     오디션 후보자 데이터 조회\n");
    printf("####################################\n");
    printf("=============================================================================================\n");
    printf("성   명 | 생   일 | 성별 | 메   일            | 국적 | BMI | 주스킬 | 보조스킬 | TOPIK   | MBTI |\n");
    printf("=============================================================================================\n");

    for (int i = 0; i < NUM_CANDIDATES; i++) {
        // 기본 정보 출력
        printf("%-7s|%-9s|%-4s|%-20s|%-6s|%-5s|%-8s|%-10s|%-9s|%-6s|\n",
               (*candidates[i])[0], (*candidates[i])[1], (*candidates[i])[2],
               (*candidates[i])[3], (*candidates[i])[4], (*candidates[i])[5],
               (*candidates[i])[6], (*candidates[i])[7], (*candidates[i])[8],
               (*candidates[i])[9]);

        // 소개 구분선
        printf("---------------------------------------------------------------------------------------------\n");

        // 소개글 한 줄 출력
        printf("%s\n", (*candidates[i])[10]);

        // 구분선
        printf("---------------------------------------------------------------------------------------------\n");
    }

    return 0;
}
