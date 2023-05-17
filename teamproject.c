#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct boardContent{
    char title[100];             // 게시글 제목
    char contents[500];          // 게시글 내용
    char writerName[30];        // 글쓴이 이름
    char writtenDate[20];       // 작성된 시간
} content;

/*
구현할 함수

1. 회원가입 / 로그인
https://goodanice.tistory.com/15

2. CRUD
1) 읽기
2) 쓰기
3) 수정
4) 삭제
5) 저장
6) 불러오기

3. 댓글
마일리지 (게시글 작성, 추천 등)
*/

int selectMenu(); // 메뉴 선택 함수
int addContent(); // 게시글 추가 함수
void showContent(); // 추가된 게시글 호출 함수
void listContent(); // 추가된 게시글의 내용 호출 함수
void modifyContent(); // 게시글 수정 함수
int cancelContent(); // 게시글 삭제 함수
void saveData(); // 저장 함수
int loadData(); // 불러오기 함수

int main(){
    int count = 0, index = 0, menu;
    content *cp[100];

/*
    count = loadData(cp);
*/

    while(1){
    menu = selectMenu();
    if(menu == 0){
        printf("프로그램을 종료합니다."); 
        break;
    }
    else if(menu == 2){
        cp[index] = (content *)malloc(sizeof(content));
        count += addContent(cp[index++]);
        }
    else if(menu == 1|| menu == 3 || menu == 4){        //  2로 추가된 데이터가 없을 경우 1,3,4를 하면 되돌아가기
        if(count <= 0){
            printf("데이터가 존재하지 않습니다.\n"); continue;
        }
    }
    if(menu == 1) showContent(cp, index);
    else if(menu == 3) modifyContent(cp, index);
    else if(menu == 4){
    int num = cancelContent(cp, index);
                if (num == 0) {
                printf("=> 취소 됨\n");
                continue;
            }
        free(cp[num-1]);
        cp[num-1] = NULL;
        count--;
        printf("\n성공적으로 제거하였습니다.\n");
        }
    else if(menu == 5){
        saveData(cp, index);
    }
    
}

}

int selectMenu(){
    int menu;

    printf("*********** 함께 코딩해요 ***********\n");
    printf("1. 게시글 조회\n");
    printf("2. 추가\n");
    printf("3. 수정\n");
    printf("4. 삭제\n");
    printf("5. 저장\n");
    printf("0. 종료\n");
    printf("************************************\n");
    scanf("%d", &menu);
    return menu;
}

int addContent(content *cp){
    printf("표기될 작성자의 이름을 입력해 주세요.\n");
    getchar();
    scanf("%[^\n]s", cp->writerName);
    printf("제목을 입력해 주세요.\n");
    getchar();
    scanf("%[^\n]s", cp->title);
    printf("내용을 입력해 주세요.\n");
    getchar();
    scanf("%[^\n]s", cp->contents);

    time_t now; 
    time(&now);
    struct tm *tm_info = localtime(&now);
    strftime(cp->writtenDate, sizeof(cp->writtenDate), "%Y-%m-%d %H:%M:%S", tm_info); // 게시글이 작성된 시각 가져오기

    return 1;
}

void listContent(content *cp[], int count){
    printf("번호   제목                 작성시각             작성자 \t(삭제 시 0번을 눌러 취소)\n");
    for (int i = 0; i < count; i++) {
        if (cp[i] == NULL) continue;
        printf("%-5d  %-20s %-20s %s\n", i + 1, cp[i]->title, cp[i]->writtenDate, cp[i]->writerName);
    }
}

void showContent(content *cp[], int count){
    int num;
    listContent(cp, count);
    scanf("%d", &num);
    printf("\n제목 : %s\t 작성자 %s\n\n", cp[num-1]->title, cp[num-1]->writerName);
    printf("%s\n", cp[num-1]->contents);
    printf("\nEnter를 눌러서 진행해주세요...");
    while(getchar() != '\n');        // 엔터를 누르기 전까지 메뉴로 돌아가지 않음
    getchar();                       // 입력 버퍼 제거
}

void modifyContent(content *cp[], int count){
    int num;
    listContent(cp, count);
    printf("몇 번을 수정 하시겠습니까?");
    scanf("%d", &num);

    printf("표기될 작성자의 이름을 입력해 주세요.\n");
    getchar();
    scanf("%[^\n]s", cp[num-1]->writerName);
    printf("제목을 입력해 주세요.\n");
    getchar();
    scanf("%[^\n]s", cp[num-1]->title);
    printf("내용을 입력해 주세요.\n");
    getchar();
    scanf("%[^\n]s", cp[num-1]->contents);

    time_t now; 
    time(&now);
    struct tm *tm_info = localtime(&now);
    strftime(cp[num-1]->writtenDate, sizeof(cp[num-1]->writtenDate), "%Y-%m-%d %H:%M:%S", tm_info); // 게시글이 작성된 시각 가져오기
}

int cancelContent(content *cp[], int count){
    int no;
    listContent(cp, count);
    printf("몇 번을 삭제 하시겠습니까?");
    scanf("%d", &no);
    return no;
}

void saveData(content *cp[], int count)
{
    FILE *fp;
    fp = fopen("boardContent.txt", "wt");

    for(int i = 0; i < count; i++){
        if(cp[i]->writerName == NULL) continue;
        fprintf(fp, "%s %s %s %s\n" , cp[i]->title, cp[i]->contents, cp[i]->writerName, cp[i]->writtenDate);
    }
    fclose(fp);
    printf("=> 성공적으로 저장하였습니다.\n");
}

/*

int loadData(content *cp[]) {
    FILE *fp;
    fp = fopen("boardContent.txt", "r");
    if (fp == NULL) {
        printf("데이터 파일을 열 수 없습니다.\n");
        return 0;
    }

    return count;
}

*/
