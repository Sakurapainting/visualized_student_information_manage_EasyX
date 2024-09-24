#define _CRT_SECURE_NO_WARNINGS 1
#pragma warning(disable:6031)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>
#include <conio.h>
#include <string>


#define MAX_STUNUM 30             //ĳ��ѧ����಻����30��
#define MAX_COURSENUM 6           //���Կ�Ŀ��಻����6��
#define MAX_NAMENUM 20            //ѧ�������ַ���������20

// ����ṹ��
typedef struct {
    char name[MAX_NAMENUM];
    long id;
    float score[MAX_COURSENUM];
} Student;

Student students[MAX_STUNUM];    //����ѧ���ṹ������

struct button {
	int x,y;
    int width;
    int height;
    COLORREF color;
    char* pText;
}; 

//��ʼ����ť�����Ժ���
struct button* createbutton(int x, int y, int width, int height, COLORREF color, const char* pText) {
	struct button* pB = (struct button*)malloc(sizeof(struct button));
    if (pB) {                           
        pB->x = x;
        pB->y = y;
        pB->width = width;
        pB->height = height;
        pB->color = color;
        pB->pText = (char*)malloc(strlen(pText) + 1);
        if (pB->pText != NULL) {
            strcpy(pB->pText, pText);
            return pB;
        }
        else {
			free(pB);
			return NULL;
		}
    }
    else {
		return NULL;
	}
}
//���ư�ť����
void drawbutton(struct button* pB) {
	setfillcolor(pB->color);                //���ð�ť��ɫ
    settextstyle(20, 0, "����");          //���������С
    setlinecolor(BLACK);        //���ñ߿���ɫ
    settextcolor(BLACK);		//����������ɫ
    setbkmode(TRANSPARENT);                 //���ñ���͸��
	fillrectangle(pB->x, pB->y, pB->x + pB->width, pB->y + pB->height);  //���ư�ť    
	outtextxy(pB->x + 10, pB->y + 10, pB->pText);  //�����ť����
}
//�ж�����Ƿ��ڰ�ť��
int IsInButton(struct button* pB, MOUSEMSG m) {
    if (pB->x <= m.x && m.x <= pB->x + pB->width && pB->y <=m.y && m.y <= pB->height + pB->y) {
        pB->color = RED;  //����ڰ�ť��ʱ��ť��ɫ���
		return 1;
	}
    pB->color = YELLOW;  
	return 0;
}
//�ж���갴��
int clickbutton(struct button* pB, MOUSEMSG m) {
    if (IsInButton(pB, m) && m.uMsg == WM_LBUTTONDOWN) {
		return 1;
	}
	return 0;
}


int REAL_STUNUM = 0;              //ʵ��ѧ������
int REAL_COURSENUM = 0;           //ʵ�ʿ�Ŀ����
int match_id = -1;                 //��ѯѧ����������
int match_name = -1;               //��ѯѧ����������

float stu_sumscore[MAX_STUNUM];     //ÿ��ѧ�����ܷ�, ��input���ȼ���� �����ѯ��������
float stu_averscore[MAX_STUNUM];     //ÿ��ѧ����ƽ����

float sum_score[MAX_COURSENUM];
float aver_score[MAX_COURSENUM];

float A_PER[MAX_COURSENUM] = { 0 }, B_PER[MAX_COURSENUM] = { 0 }, C_PER[MAX_COURSENUM] = { 0 };
float D_PER[MAX_COURSENUM] = { 0 }, E_PER[MAX_COURSENUM] = { 0 };
//��������
void Input_record();
void Cal_total_aver_score();
void Cal_total_aver_score_ofstudent();
void Sort_order_score(int (*compare)(float a, float b));
void Sort_order_id(int (*compare)(float a, float b));
void Sort_in_dictionary_order_by_name();
void Search_by_number();
void Search_by_name();
void Statistic_analysis();
void List_record();
void Write_to_a_file();
void Read_from_a_file();
void c1_display();
void c2_display();
void c3_display();
void c4_display();
void c5_display();
void c6_display();
void c7_display();
void c8_display();
void c9_display();
void c10_display();
void c11_display();
void c12_display();
void c13_display();

int Ascending(float a, float b) {
    return a > b;                   //�������� ����a>b���� �򽻻�
}
int Descending(float a, float b) {
    return a < b;                   //���ڽ��� ����a<b���� �򽻻�
}

void swap(float* a, float* b) {  //��ָ�뽻�������е�Ԫ��
    float temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void swap_id(long* a, long* b) {  //��ָ�뽻��id�����е�Ԫ��
    long temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void choice(int num) {       //�����û�����ѡ��Switch��ͬ����
    switch (num) {
    case 1:
        c1_display();
        break;
    case 2:
        c2_display();
        break;
    case 3:
        c3_display();
        break;
    case 4:
        c4_display();
        break;
    case 5:
        c5_display();
        break;
    case 6:
        c6_display();
        break;
    case 7:
        c7_display();
        break;
    case 8:
        c8_display();
        break;
    case 9:
        c9_display();
        break;
    case 10:
        c10_display();
        break;
    case 11:
        c11_display();
        break;
    case 12:
        c12_display();
        break;
    case 13:
        c13_display();
        break;
    case 0:
        exit(0);
    }
}

void Input_record() {
    int i;
    printf("\nInput Record:\n");
    printf("How many students?(number<=30)\n");
    scanf("%d", &REAL_STUNUM);
    printf("How many courses?(number<=6)\n");
    scanf("%d", &REAL_COURSENUM);
    if (REAL_STUNUM > MAX_STUNUM) {
        printf("������������30! ������ֹ");
        exit(1);
    }
    if (REAL_COURSENUM > MAX_COURSENUM) {
        printf("�����Ŀ������6! ������ֹ");
        exit(1);
    }
    for (i = 0; i < REAL_STUNUM; i++) {
        int j;
        printf("Enter id and name of NUM.%d\n", i + 1);
        scanf("%ld %s", &students[i].id, students[i].name);
        for (j = 0; j < REAL_COURSENUM; j++) {
            printf("Enter score of course NUM.%d of student NUM.%d\n", j + 1, i + 1);
            scanf("%f", &students[i].score[j]);
            stu_sumscore[i] += students[i].score[j];
        }
    }
}

// void Input_record(){
//     printf("Please enter the student's information in the following format:\n");
//     printf("ID Name Score1 Score2 ... ScoreN(ÿ�������м䴩��һ���ո�)\n");
//     int i = 0;
//     char input[256];
//     if(fgets(input, sizeof(input), stdin) != NULL){  // ���û�ж�ȡ��EOF
//         sscanf(input, "%ld %s", &students[REAL_STUNUM].id, students[REAL_STUNUM].name);  // ��ȡѧ����ID������
//         char *p = strchr(input, ' ');  // �ҵ���һ���ո�
//         if(p != NULL){  // ����ҵ��˵�һ���ո�
//             p = strchr(p + 1, ' ');  // �ҵ��ڶ����ո�
//             if(p != NULL){  // ����ҵ��˵ڶ����ո�
//                 for(i = 0; i < REAL_COURSENUM; i++){  // ��ȡѧ����ÿ�ſγ̵ĳɼ�
//                     p = strchr(p + 1, ' ');  // �ҵ���һ���ո�
//                     if(p == NULL){  // ���û���ҵ���һ���ո�
//                         break;
//                     }
//                     sscanf(p, "%f", &students[REAL_STUNUM].score[i]);  // ��ȡ�ɼ�
//                 }
//             }
//         }
//     }

//     // ����ѧ�����ܷ�
//     stu_sumscore[REAL_STUNUM] = 0;
//     for(i = 0; i < REAL_COURSENUM; i++){
//         stu_sumscore[REAL_STUNUM] += students[REAL_STUNUM].score[i];
//     }

//     REAL_STUNUM++;
// }

void Cal_total_aver_score() {
    int i, j, k;
    int flag = 1;
    printf("\nCalculate total and average score of course:\n");
    for (j = 0; j < REAL_COURSENUM; j++) {
        sum_score[j] = 0;                                //�ֳܷ�ʼ��
        for (i = 0; i < REAL_STUNUM; i++) {
            sum_score[j] += students[i].score[j];                          //ÿ�ſγ̵��ܷ�
        }
    }
    for (k = 0; k < REAL_COURSENUM; k++) {
        if (sum_score[k] == 0) {
            do {
                printf("�ƺ��ɼ�����, �Ƿ��������? ����1:����, 0:����\n");
                scanf("%d", &flag);
                if (flag == 0) {
                    exit(0);
                }
            } while (flag != 1 && flag != 0);
        }
        aver_score[k] = sum_score[k] / REAL_STUNUM;               //ÿ�ſγ̵�ƽ����
    }

    printf("%-10s%-10s\n", "Total", "Average");  // ����ֺܷ�ƽ���ֵı��⣬ÿ������ռ10���ַ����

    // ����ָ���
    for (i = 0; i < 30; i++) {
        printf("-");
    }
    printf("\n");

    for (i = 0; i < REAL_COURSENUM; i++) {
        printf("%-10.2f%-10.2f\n", sum_score[i], aver_score[i]);  // ���ÿ�ſγ̵��ֺܷ�ƽ���֣�ÿ��ռ10���ַ���ȣ�����2λС��

    }
}

void Cal_total_aver_score_ofstudent() {
    int i, j;
    for (i = 0; i < REAL_STUNUM; i++) {
        stu_sumscore[i] = 0;
        for (j = 0; j < REAL_COURSENUM; j++) {
            stu_sumscore[i] += students[i].score[j];  // ����ÿ��ѧ�����ܷ�
        }
        stu_averscore[i] = stu_sumscore[i] / REAL_COURSENUM;  // ����ÿ��ѧ����ƽ����    
    }

    printf("%-10s%-20s%-10s%-10s\n", "Id", "Name", "Total", "Average");  // ����ֺܷ�ƽ���ֵı��⣬ÿ������ռ10���ַ����

    // ����ָ���
    for (i = 0; i < 30; i++) {
        printf("-");
    }
    printf("\n");

    for (i = 0; i < REAL_STUNUM; i++) {
        printf("%-10ld%-20s", students[i].id, students[i].name);  // ���ѧ����ID��������ÿ��ռ10���ַ����
        printf("%-10.2f%-10.2f", stu_sumscore[i], stu_averscore[i]);  // ���ÿstudent���ֺܷ�ƽ���֣�ÿ��ռ10���ַ���ȣ�����2λС��
        printf("\n");
    }
}

void Sort_order_score(int (*compare)(float a, float b)) {
    printf("\nSort in descending order by score:\n");
    int i, j;
    for (i = 0; i < REAL_STUNUM - 1; i++) {
        for (j = 0; j < REAL_STUNUM - 1 - i; j++) {
            if ((*compare)(stu_sumscore[j], stu_sumscore[j + 1])) {  // ���ǰһ��ѧ�����ܷ�С�ں�һ��ѧ�����ܷ֣��򽻻����ǵ�λ��
                long temp_id = students[j].id;
                char temp_name[20];
                strcpy(temp_name, students[j].name);
                float temp_score[MAX_COURSENUM];
                memcpy(temp_score, students[j].score, sizeof(float) * REAL_COURSENUM);
                float temp_sumscore = stu_sumscore[j];

                students[j].id = students[j + 1].id;
                strcpy(students[j].name, students[j + 1].name);
                memcpy(students[j].score, students[j + 1].score, sizeof(float) * REAL_COURSENUM);
                stu_sumscore[j] = stu_sumscore[j + 1];

                students[j + 1].id = temp_id;
                strcpy(students[j + 1].name, temp_name);
                memcpy(students[j + 1].score, temp_score, sizeof(float) * REAL_COURSENUM);
                stu_sumscore[j + 1] = temp_sumscore;
            }
        }
    }

    // ���������ѧ����Ϣ
    printf("\nSort and Order by Score:\n");
    printf("%-10s%-20s", "ID", "Name");  // ���ID�������ı��⣬ÿ������ռ10���ַ����
    for (j = 0; j < REAL_COURSENUM; j++) {
        printf("%-10s", "Score");  // ���ÿ�ſγ̵ĳɼ��ı��⣬ÿ������ռ10���ַ����
    }
    printf("%-10s\n", "Sum");  // ����ֵܷı��⣬ռ10���ַ����

    // ����ָ���
    for (i = 0; i < 10 * (REAL_COURSENUM + 3); i++) {
        printf("-");
    }
    printf("\n");

    for (i = 0; i < REAL_STUNUM; i++) {
        printf("%-10ld%-20s", students[i].id, students[i].name);  // ���ѧ����ID��������ÿ��ռ10���ַ����
        for (j = 0; j < REAL_COURSENUM; j++) {
            printf("%-10.2f", students[i].score[j]);  // ���ѧ����ÿ�ſγ̵ĳɼ���ÿ���ɼ�ռ10���ַ���ȣ�����2λС��
        }
        printf("%-10.2f\n", stu_sumscore[i]);  // ���ѧ�����ܷ֣�ռ10���ַ���ȣ�����2λС��
    }
}

void Sort_order_id(int (*compare)(float a, float b)) {
    int i, j;
    for (i = 0; i < REAL_STUNUM - 1; i++) {
        for (j = 0; j < REAL_STUNUM - 1 - i; j++) {
            if (students[j].id > students[j + 1].id) {  // ���ǰһ��ѧ����ID���ں�һ��ѧ����ID���򽻻����ǵ�λ��
                long temp_id = students[j].id;
                char temp_name[20];
                strcpy(temp_name, students[j].name);
                float temp_score[MAX_COURSENUM];
                memcpy(temp_score, students[j].score, sizeof(float) * REAL_COURSENUM);
                float temp_sumscore = stu_sumscore[j];

                students[j].id = students[j + 1].id;
                strcpy(students[j].name, students[j + 1].name);
                memcpy(students[j].score, students[j + 1].score, sizeof(float) * REAL_COURSENUM);
                stu_sumscore[j] = stu_sumscore[j + 1];

                students[j + 1].id = temp_id;
                strcpy(students[j + 1].name, temp_name);
                memcpy(students[j + 1].score, temp_score, sizeof(float) * REAL_COURSENUM);
                stu_sumscore[j + 1] = temp_sumscore;
            }
        }
    }

    // ���������ѧ����Ϣ
    printf("\nSort and Order by ID:\n");
    printf("%-10s%-20s", "ID", "Name");  // ���ID�������ı��⣬ÿ������ռ10���ַ����
    for (j = 0; j < REAL_COURSENUM; j++) {
        printf("%-10s", "Score");  // ���ÿ�ſγ̵ĳɼ��ı��⣬ÿ������ռ10���ַ����
    }
    printf("%-10s\n", "Sum");  // ����ֵܷı��⣬ռ10���ַ����

    // ����ָ���
    for (i = 0; i < 10 * (REAL_COURSENUM + 3); i++) {
        printf("-");
    }
    printf("\n");

    for (i = 0; i < REAL_STUNUM; i++) {
        printf("%-10ld%-20s", students[i].id, students[i].name);  // ���ѧ����ID��������ÿ��ռ10���ַ����
        for (j = 0; j < REAL_COURSENUM; j++) {
            printf("%-10.2f", students[i].score[j]);  // ���ѧ����ÿ�ſγ̵ĳɼ���ÿ���ɼ�ռ10���ַ���ȣ�����2λС��
        }
        printf("%-10.2f\n", stu_sumscore[i]);  // ���ѧ�����ܷ֣�ռ10���ַ���ȣ�����2λС��
    }
}

void Sort_in_dictionary_order_by_name() {
    int i, j;
    for (i = 0; i < REAL_STUNUM - 1; i++) {
        for (j = 0; j < REAL_STUNUM - 1 - i; j++) {
            if (strcmp(students[j].name, students[j + 1].name) > 0) {  // ���ǰһ��ѧ�����������ں�һ��ѧ�����������򽻻����ǵ�λ��
                long temp_id = students[j].id;                        //�����൱�ڴ���swap��id��name��score��sumscore���н���
                char temp_name[20];
                strcpy(temp_name, students[j].name);                // ����ѧ��������
                float temp_score[MAX_COURSENUM];
                memcpy(temp_score, students[j].score, sizeof(float) * REAL_COURSENUM);  // ����ѧ���ĳɼ�
                float temp_sumscore = stu_sumscore[j];

                students[j].id = students[j + 1].id;
                strcpy(students[j].name, students[j + 1].name);
                memcpy(students[j].score, students[j + 1].score, sizeof(float) * REAL_COURSENUM);
                stu_sumscore[j] = stu_sumscore[j + 1];

                students[j + 1].id = temp_id;
                strcpy(students[j + 1].name, temp_name);
                memcpy(students[j + 1].score, temp_score, sizeof(float) * REAL_COURSENUM);
                stu_sumscore[j + 1] = temp_sumscore;
            }
        }
    }
    // ���������ѧ����Ϣ
    printf("\nSort in dictionary order by name:\n");
    printf("%-10s%-20s", "ID", "Name");  // ���ID�������ı��⣬ÿ������ռ10���ַ����
    for (j = 0; j < REAL_COURSENUM; j++) {
        printf("%-10s", "Score");  // ���ÿ�ſγ̵ĳɼ��ı��⣬ÿ������ռ10���ַ����
    }
    printf("%-10s\n", "Sum");  // ����ֵܷı��⣬ռ10���ַ����

    // ����ָ���
    for (i = 0; i < 10 * (REAL_COURSENUM + 3); i++) {
        printf("-");
    }
    printf("\n");

    for (i = 0; i < REAL_STUNUM; i++) {
        printf("%-10ld%-20s", students[i].id, students[i].name);  // ���ѧ����ID��������ÿ��ռ10���ַ����
        for (j = 0; j < REAL_COURSENUM; j++) {
            printf("%-10.2f", students[i].score[j]);  // ���ѧ����ÿ�ſγ̵ĳɼ���ÿ���ɼ�ռ10���ַ���ȣ�����2λС��
        }
        printf("%-10.2f\n", stu_sumscore[i]);  // ���ѧ�����ܷ֣�ռ10���ַ���ȣ�����2λС��
    }
}

void Search_by_number() {
    long id;        //��ѧ�Ų�ѯ�ɼ� �� ����ѧ��
    printf("\nSearch by number:\n");
    int i, j;
    printf("Enter the id:\n");
    scanf("%d", &id);
    match_id = -1;  // ��ʼ��ƥ���ѧ��ID��������
    for (i = 0; i < REAL_STUNUM; i++) {
        if (students[i].id == id) {  // ����ҵ���ƥ���ѧ��ID
            match_id = i;
            printf("\nSearch Result:\n");
            printf("%-10s%-20s", "ID", "Name");  // ���ID�������ı��⣬ÿ������ռ10���ַ����
            for (j = 0; j < REAL_COURSENUM; j++) {
                printf("%-10s", "Score");  // ���ÿ�ſγ̵ĳɼ��ı��⣬ÿ������ռ10���ַ����
            }
            printf("%-10s\n", "Sum");  // ����ֵܷı��⣬ռ10���ַ����

            // ����ָ���
            for (j = 0; j < 10 * (REAL_COURSENUM + 3); j++) {
                printf("-");
            }
            printf("\n");

            printf("%-10ld%-20s", students[i].id, students[i].name);  // ���ѧ����ID��������ÿ��ռ10���ַ����
            for (j = 0; j < REAL_COURSENUM; j++) {
                printf("%-10.2f", students[i].score[j]);  // ���ѧ����ÿ�ſγ̵ĳɼ���ÿ���ɼ�ռ10���ַ���ȣ�����2λС��
            }
            printf("%-10.2f\n", stu_sumscore[i]);  // ���ѧ�����ܷ֣�ռ10���ַ���ȣ�����2λС��
            return;
        }
    }

    printf("\n----------\nNo student with the ID %ld was found.\n----------\n", id);
}

void Search_by_name() {
    char name[20];  //��������ѯ�ɼ� �� ��������
    printf("\nSearch by name:\n");
    int i, j;
    printf("Enter the name:\n");
    scanf("%s", name);
    name[strlen(name)] = '\0';  // ȷ���ַ����Կ��ַ�����
    match_name = -1;  // ��ʼ��ƥ���ѧ��������������
    for (i = 0; i < REAL_STUNUM; i++) {
        if (strcmp(students[i].name, name) == 0) {  // ����ҵ���ƥ���ѧ������
            match_name = i;
            printf("\nSearch Result:\n");
            printf("%-10s%-20s", "ID", "Name");  // ���ID�������ı��⣬ÿ������ռ10���ַ����
            for (j = 0; j < REAL_COURSENUM; j++) {
                printf("%-10s", "Score");  // ���ÿ�ſγ̵ĳɼ��ı��⣬ÿ������ռ10���ַ����
            }
            printf("%-10s\n", "Sum");  // ����ֵܷı��⣬ռ10���ַ����

            // ����ָ���
            for (j = 0; j < 10 * (REAL_COURSENUM + 3); j++) {
                printf("-");
            }
            printf("\n");

            printf("%-10ld%-20s", students[i].id, students[i].name);  // ���ѧ����ID��������ÿ��ռ10���ַ����
            for (j = 0; j < REAL_COURSENUM; j++) {
                printf("%-10.2f", students[i].score[j]);  // ���ѧ����ÿ�ſγ̵ĳɼ���ÿ���ɼ�ռ10���ַ���ȣ�����2λС��
            }
            printf("%-10.2f\n", stu_sumscore[i]);  // ���ѧ�����ܷ֣�ռ10���ַ���ȣ�����2λС��
            return;
        }
    }
    printf("\n----------\nNo student with the name %s was found.\n----------\n", name);
}

void Statistic_analysis() {
    printf("\nStatic analysis:\n");
    int i, j;
    int A_COUNT[MAX_COURSENUM] = { 0 }, B_COUNT[MAX_COURSENUM] = { 0 }, C_COUNT[MAX_COURSENUM] = { 0 };
    int D_COUNT[MAX_COURSENUM] = { 0 }, E_COUNT[MAX_COURSENUM] = { 0 };
    for (j = 0; j < REAL_COURSENUM; j++) {                 //����
        for (i = 0; i < REAL_STUNUM; i++) {
            if (students[i].score[j] <= 100 && students[i].score[j] >= 90) {
                A_COUNT[j]++;
            }
            if (students[i].score[j] < 90 && students[i].score[j] >= 80) {
                B_COUNT[j]++;
            }
            if (students[i].score[j] < 80 && students[i].score[j] >= 70) {
                C_COUNT[j]++;
            }
            if (students[i].score[j] < 70 && students[i].score[j] >= 60) {
                D_COUNT[j]++;
            }
            if (students[i].score[j] < 60) {
                E_COUNT[j]++;
            }
        }
        A_PER[j] = (float)A_COUNT[j] / REAL_STUNUM;                 //�������ͳ���
        B_PER[j] = (float)B_COUNT[j] / REAL_STUNUM;
        C_PER[j] = (float)C_COUNT[j] / REAL_STUNUM;
        D_PER[j] = (float)D_COUNT[j] / REAL_STUNUM;
        E_PER[j] = (float)E_COUNT[j] / REAL_STUNUM;

        printf("course NUM.%d: ����������%d, ��ռ�ٷֱ�%.2f%%\n", j + 1, A_COUNT[j], A_PER[j] * 100);
        printf("course NUM.%d: ����������%d, ��ռ�ٷֱ�%.2f%%\n", j + 1, B_COUNT[j], B_PER[j] * 100);
        printf("course NUM.%d: �е�������%d, ��ռ�ٷֱ�%.2f%%\n", j + 1, C_COUNT[j], C_PER[j] * 100);
        printf("course NUM.%d: ����������%d, ��ռ�ٷֱ�%.2f%%\n", j + 1, D_COUNT[j], D_PER[j] * 100);
        printf("course NUM.%d: ������������%d, ��ռ�ٷֱ�%.2f%%\n", j + 1, E_COUNT[j], E_PER[j] * 100);
    }
}

void List_record() {
    printf("\nList record:\n");
    int i, j;

    printf("%-10s%-20s", "ID", "Name");  // ���ID�������ı��⣬ÿ������ռ10���ַ����
    for (j = 0; j < REAL_COURSENUM; j++) {
        printf("%-10s", "Score");  // ���ÿ�ſγ̵ĳɼ��ı��⣬ÿ������ռ10���ַ����
    }
    printf("%-10s", "Sum");  // ����ֵܷı��⣬ռ10���ַ����
    printf("%-10s\n", "Aver");           //���ƽ���ֵı��⣬ռ10���ַ����
    // ����ָ���
    for (i = 0; i < 10 * (REAL_COURSENUM + 3); i++) {
        printf("-");
    }
    printf("\n");

    for (i = 0; i < REAL_STUNUM; i++) {
        printf("%-10ld%-20s", students[i].id, students[i].name);  // ���ѧ����ID��������ÿ��ռ10���ַ����
        for (j = 0; j < REAL_COURSENUM; j++) {
            printf("%-10.2f", students[i].score[j]);  // ���ѧ����ÿ�ſγ̵ĳɼ���ÿ���ɼ�ռ10���ַ���ȣ�����2λС��
        }
        printf("%-10.2f", stu_sumscore[i]);  // ���ѧ�����ܷ֣�ռ10���ַ���ȣ�����2λС��
        printf("%-10.2f\n", stu_averscore[i]);   // ���ѧ����ƽ���֣�ռ10���ַ���ȣ�����2λС��
    }
    printf("-------------------\n");
    printf("-------------------\n");
    printf("%-10s%-10s\n", "Total", "Average");  // ����ֺܷ�ƽ���ֵı��⣬ÿ������ռ10���ַ����

    // ����ָ���
    for (i = 0; i < 30; i++) {
        printf("-");
    }
    printf("\n");

    for (i = 0; i < REAL_COURSENUM; i++) {
        printf("%-10.2f%-10.2f\n", sum_score[i], aver_score[i]);  // ���ÿ�ſγ̵��ֺܷ�ƽ���֣�ÿ��ռ10���ַ���ȣ�����2λС��

    }
}
char lujin[128];
void Write_to_a_file() {
    printf("����·����\n");
    scanf("%s",lujin);                      //���û�ָ���洢·��
    FILE* file = fopen(lujin, "w");
    if (file == NULL) {
        printf("�޷����ļ�\n");
        return;
    }
    fprintf(file, "ѧ��������%d", REAL_STUNUM);
    fprintf(file, "��Ŀ������%d\n", REAL_COURSENUM);
    for (int i = 0; i < REAL_STUNUM; i++) {
        fprintf(file, "����: %s\n", students[i].name);
        fprintf(file, "ѧ��: %ld\n", students[i].id);
        fprintf(file, "����: ");
        for (int j = 0; j < REAL_COURSENUM; j++) {
            fprintf(file, "%.2f ", students[i].score[j]);
        }
        fprintf(file, "\n�ܷ�: %.2f\n", stu_sumscore[i]);
        fprintf(file, "ƽ����: %.2f\n\n", stu_averscore[i]);
        fflush(file);  // ����������д�����
    }
    printf("д���ļ��ɹ�\n");
    fclose(file);
}

void Read_from_a_file() {
    printf("��ȡ·����\n");
    scanf("%s", lujin);                      //���û�ָ��·��
    FILE* file = fopen(lujin, "r");
    if (file == NULL) {
        printf("�޷����ļ�\n");
        return;
    }

    fscanf(file, "ѧ��������%d", &REAL_STUNUM);
    fscanf(file, "��Ŀ������%d\n", &REAL_COURSENUM);
    for (int i = 0; i < REAL_STUNUM; i++) {
		fscanf(file, "����: %s\n", students[i].name);
		fscanf(file, "ѧ��: %ld\n", &students[i].id);
		fscanf(file, "����: ");
        for (int j = 0; j < REAL_COURSENUM; j++) {
			fscanf(file, "%f", &students[i].score[j]);
		}
		fscanf(file, "\n�ܷ�: %f\n", &stu_sumscore[i]);
		fscanf(file, "ƽ����: %f\n\n", &stu_averscore[i]);
		printf("����: %s\n", students[i].name);
		printf("ѧ��: %ld\n", students[i].id);
		printf("����: ");
        for (int j = 0; j < REAL_COURSENUM; j++) {
			printf("%.2f ", students[i].score[j]);
		}
		printf("\n�ܷ�: %.2f\n", stu_sumscore[i]);
		printf("ƽ����: %.2f\n\n", stu_averscore[i]);
	}

    printf("��ȡ�ļ��ɹ�\n");
    fclose(file);
}

//�޸�ѧ����Ϣ*

//�޸Ĳ���ѧ����Ϣ ǰ�ắ��
//void modi_infor() {
//    printf("��ѧ�� ���� ���� Ϊƾ�޸�Ŀ��ѧ����Ϣ��\n����1:ѧ��, 2:����\n");
//    unsigned int choi=0;
//    scanf("%d",&choi);
//    if (choi == 1 || choi == 2) {
//        if (choi == 1) {
//            Search_by_number();
//            printf("�ĵڼ��ƣ�\n");
//            int which_course = -1;
//            scanf("%d",&which_course);
//            if (which_course == -1) {
//                printf("wrong which_course\n");
//            }
//            else {
//                printf("�޸�Ϊ��\n"); 
//                float after_modi_score = -1;
//                scanf("%d", &which_course);
//                if (which_course == -1) {
//                    printf("wrong modi_score");
//                else {
//                    for (int i = 0; i < REAL_STUNUM;i++) {
//                        if(match_id == )
//                    }
//                }
//            }
//        }
//        if (choi == 2) {
//            Search_by_name();
//        }
//
//    }
//    else printf("wrong choice\n");
//} 

void menu_display() {
    initgraph(800, 600);
    IMAGE mm;
    loadimage(&mm, "background.png", 800, 600);

    struct button* c1 = createbutton(100, 200, 200, 50, YELLOW, "¼����Ϣ");
    struct button* c2 = createbutton(100, 250, 200, 50, YELLOW, "������ܷ�,����");
    struct button* c3 = createbutton(100, 300, 200, 50, YELLOW, "���ѧ���ܷ�,����");
    struct button* c4 = createbutton(100, 350, 200, 50, YELLOW, "ѧ���ֽܷ���");
    struct button* c5 = createbutton(100, 400, 200, 50, YELLOW, "ѧ���ܷ�����");
    struct button* c6 = createbutton(100, 450, 200, 50, YELLOW, "ѧ������");
    struct button* c7 = createbutton(100, 500, 200, 50, YELLOW, "����ĸ˳��");
    struct button* c8 = createbutton(100, 550, 200, 50, YELLOW, "��ѧ�ż���");
    struct button* c9 = createbutton(400, 200, 200, 50, YELLOW, "����������");
    struct button* c10 = createbutton(400, 250, 200, 50, YELLOW, "�������ηֲ�");
    struct button* c11 = createbutton(400, 300, 200, 50, YELLOW, "�г���Ϣ");
    struct button* c12 = createbutton(400, 350, 200, 50, YELLOW, "д���ļ�");
    struct button* c13 = createbutton(400, 400, 200, 50, YELLOW, "��ȡ�ļ�");
    struct button* c0 = createbutton(400, 450, 200, 50, YELLOW, "�˳�����");

    int choice_num = -1;
    while (1) {
        BeginBatchDraw();       // ��ʼ������ͼ
        putimage(0, 0, &mm);
        drawbutton(c1);
        drawbutton(c2);
        drawbutton(c3);
        drawbutton(c4);
        drawbutton(c5);
        drawbutton(c6);
        drawbutton(c7);
        drawbutton(c8);
        drawbutton(c9);
        drawbutton(c10);
        drawbutton(c11);
        drawbutton(c12);
        drawbutton(c13);
        drawbutton(c0);
        MOUSEMSG m = GetMouseMsg();
        if (clickbutton(c1, m)) {
            choice_num = 1;
            break;
        }
        if (clickbutton(c2, m)) {
            choice_num = 2;
            break;
        }
        if (clickbutton(c3, m)) {
            choice_num = 3;
            break;
        }
        if (clickbutton(c4, m)) {
            choice_num = 4;
            break;
        }
        if (clickbutton(c5, m)) {
            choice_num = 5;
            break;
        }
        if (clickbutton(c6, m)) {
            choice_num = 6;
            break;
        }
        if (clickbutton(c7, m)) {
            choice_num = 7;
            break;
        }
        if (clickbutton(c8, m)) {
            choice_num = 8;
            break;
        }
        if (clickbutton(c9, m)) {
            choice_num = 9;
            break;
        }
        if (clickbutton(c10, m)) {
            choice_num = 10;
            break;
        }
        if (clickbutton(c11, m)) {
            choice_num = 11;
            break;
        }
        if (clickbutton(c12, m)) {
            choice_num = 12;
            break;
        }
        if (clickbutton(c13, m)) {
            choice_num = 13;
            break;
        }
        if (clickbutton(c0, m)) {
            choice_num = 0;
            break;
        }

        EndBatchDraw();           // ����������ͼ           
    }
    closegraph();
    choice(choice_num);
}

void c1_display() {
    Input_record();
    initgraph(1240, 960);
    IMAGE mm;
    loadimage(&mm, "background.png", 1240, 960);
    struct button* back_to_menu = createbutton(0,0,200,50,YELLOW,"���ز˵�");
    while (1) {
        BeginBatchDraw();
        putimage(0, 0, &mm);
        drawbutton(back_to_menu);
        MOUSEMSG m = GetMouseMsg();
        outtextxy(0, 100, "¼��ɹ�");
        outtextxy(0,150,("ѧ��������"+ std::to_string(REAL_STUNUM)).c_str());
        outtextxy(0, 200, ("��Ŀ����" + std::to_string(REAL_COURSENUM)).c_str());
        if (clickbutton(back_to_menu, m)) {
            
            break;
        }
        EndBatchDraw();
    }

    closegraph();
    menu_display();
}
void c2_display() {
	Cal_total_aver_score();
	initgraph(1240, 960);
	IMAGE mm;
	loadimage(&mm, "background.png", 1240, 960);
	struct button* back_to_menu = createbutton(1040,910,200,50,YELLOW,"���ز˵�");
    while (1) {
		BeginBatchDraw();
		putimage(0, 0, &mm);
		drawbutton(back_to_menu);
		MOUSEMSG m = GetMouseMsg();
		outtextxy(0, 910, "����ɹ�");
		outtextxy(0, 0, "�����ܷ־���");
        for (int i = 0; i < REAL_COURSENUM; i++) {
			char course[20];
			sprintf(course, "Course %d", i + 1);
			outtextxy(10,20 + i * 20, course);
		}
		outtextxy(200, 0, "Total");
		outtextxy(300, 0, "Average");
        for (int i = 0; i < REAL_COURSENUM; i++) {
			char total[20];
			sprintf(total, "%.2f", sum_score[i]);
			outtextxy(200 , 20 + i * 20, total);
			char average[20];
			sprintf(average, "%.2f", aver_score[i]);
			outtextxy(300 , 20 + i * 20, average);
		}
        if (clickbutton(back_to_menu, m)) {
			break;
		}
		EndBatchDraw();
	}

	closegraph();
	menu_display();
        
}
void c3_display() {
    Cal_total_aver_score_ofstudent();
	initgraph(1240, 960);
	IMAGE mm;
	loadimage(&mm, "background.png", 1240, 960);
	struct button* back_to_menu = createbutton(1040,910,200,50,YELLOW,"���ز˵�");
    while (1) {
		BeginBatchDraw();
		putimage(0, 0, &mm);
		drawbutton(back_to_menu);
		MOUSEMSG m = GetMouseMsg();

		outtextxy(0, 910, "����ɹ�");
        outtextxy(0, 0, "��ѧ���ܷ־���");
        settextstyle(20, 0, "����");
        setbkmode(TRANSPARENT);

        outtextxy(10, 30, "ID");
        outtextxy(100, 30, "Name");
        for (int i = 0; i < REAL_COURSENUM; ++i) {
            char course[20];
            sprintf(course, "Course %d", i + 1);
            outtextxy(200 + i * 100, 30, course);
        }
        outtextxy(200 + REAL_COURSENUM * 100, 30, "Total");
        outtextxy(300 + REAL_COURSENUM * 100, 30, "Average");

        for (int i = 0; i < REAL_STUNUM; ++i) {
            char id[20];
            sprintf(id, "%ld", students[i].id);
            outtextxy(10, 50 + i * 20, id);

            outtextxy(100, 50 + i * 20, students[i].name);

            float total = 0;
            for (int j = 0; j < REAL_COURSENUM; ++j) {
                total += students[i].score[j];
                char score[20];
                sprintf(score, "%.2f", students[i].score[j]);
                outtextxy(200 + j * 100, 50 + i * 20, score);
            }

            char totalStr[20];
            sprintf(totalStr, "%.2f", total);
            outtextxy(200 + REAL_COURSENUM * 100, 50 + i * 20, totalStr);

            char averageStr[20];
            sprintf(averageStr, "%.2f", total / REAL_COURSENUM);
            outtextxy(300 + REAL_COURSENUM * 100, 50 + i * 20, averageStr);
        }

        if (clickbutton(back_to_menu, m)) {
			break;
		}
		EndBatchDraw();
	}

	closegraph();
	menu_display();
}
void c4_display() {
	Sort_order_score(Descending);
	initgraph(1240, 960);
	IMAGE mm;
	loadimage(&mm, "background.png", 1240, 960);
	struct button* back_to_menu = createbutton(1040,910,200,50,YELLOW,"���ز˵�");
    while (1) {
		BeginBatchDraw();
		putimage(0, 0, &mm);
		drawbutton(back_to_menu);
		MOUSEMSG m = GetMouseMsg();
		outtextxy(0, 910, "����ɹ�");
		outtextxy(0, 0, "ѧ���ֽܷ���");
		outtextxy(10, 30, "ID");
		outtextxy(100, 30, "Name");
        for (int i = 0; i < REAL_COURSENUM; ++i) {
			char course[20];
			sprintf(course, "Course %d", i + 1);
			outtextxy(200 + i * 100, 30, course);
		}
		outtextxy(200 + REAL_COURSENUM * 100, 30, "Total");
		outtextxy(300 + REAL_COURSENUM * 100, 30, "Average");

        for (int i = 0; i < REAL_STUNUM; ++i) {
			char id[20];
			sprintf(id, "%ld", students[i].id);
			outtextxy(10, 50 + i * 20, id);

			outtextxy(100, 50 + i * 20, students[i].name);

			float total = 0;
            for (int j = 0; j < REAL_COURSENUM; ++j) {
				total += students[i].score[j];
				char score[20];
				sprintf(score, "%.2f", students[i].score[j]);
				outtextxy(200 + j * 100, 50 + i * 20, score);
			}

			char totalStr[20];
			sprintf(totalStr, "%.2f", total);
			outtextxy(200 + REAL_COURSENUM * 100, 50 + i * 20, totalStr);

			char averageStr[20];
			sprintf(averageStr, "%.2f", total / REAL_COURSENUM);
			outtextxy(300 + REAL_COURSENUM * 100, 50 + i * 20, averageStr);
        }
        if (clickbutton(back_to_menu, m)) {
            break;
        }
        EndBatchDraw();

    }
    closegraph();
    menu_display();
}
void c5_display() {
    Sort_order_score(Ascending);
	initgraph(1240, 960);
	IMAGE mm;
	loadimage(&mm, "background.png", 1240, 960);
	struct button* back_to_menu = createbutton(1040,910,200,50,YELLOW,"���ز˵�");
    while (1) {
		BeginBatchDraw();
		putimage(0, 0, &mm);
		drawbutton(back_to_menu);
		MOUSEMSG m = GetMouseMsg();
		outtextxy(0, 910, "����ɹ�");
		outtextxy(0, 0, "ѧ���ܷ�����");
		outtextxy(10, 30, "ID");
		outtextxy(100, 30, "Name");
        for (int i = 0; i < REAL_COURSENUM; ++i) {
			char course[20];
			sprintf(course, "Course %d", i + 1);
			outtextxy(200 + i * 100, 30, course);
		}
		outtextxy(200 + REAL_COURSENUM * 100, 30, "Total");
		outtextxy(300 + REAL_COURSENUM * 100, 30, "Average");

        for (int i = 0; i < REAL_STUNUM; ++i) {
			char id[20];
			sprintf(id, "%ld", students[i].id);
			outtextxy(10, 50 + i * 20, id);

			outtextxy(100, 50 + i * 20, students[i].name);

			float total = 0;
            for (int j = 0; j < REAL_COURSENUM; ++j) {
				total += students[i].score[j];
				char score[20];
				sprintf(score, "%.2f", students[i].score[j]);
				outtextxy(200 + j * 100, 50 + i * 20, score);
			}

			char totalStr[20];
			sprintf(totalStr, "%.2f", total);
			outtextxy(200 + REAL_COURSENUM * 100, 50 + i * 20, totalStr);

			char averageStr[20];
			sprintf(averageStr, "%.2f", total / REAL_COURSENUM);
			outtextxy(300 + REAL_COURSENUM * 100, 50 + i * 20, averageStr);
        }
        if (clickbutton(back_to_menu, m)) {
			break;
		}
        EndBatchDraw();
    }
    closegraph();
    menu_display();
}
void c6_display() {
    Sort_order_id(Ascending);
    initgraph(1240, 960);
    IMAGE mm;
    loadimage(&mm, "background.png", 1240, 960);
    struct button* back_to_menu = createbutton(1040, 910, 200, 50, YELLOW, "���ز˵�");
    while (1) {
        BeginBatchDraw();
        putimage(0, 0, &mm);
        drawbutton(back_to_menu);
        MOUSEMSG m = GetMouseMsg();
        outtextxy(0, 910, "����ɹ�");
        outtextxy(0, 0, "ѧ������");
        outtextxy(10, 30, "ID");
        outtextxy(100, 30, "Name");
        for (int i = 0; i < REAL_COURSENUM; ++i) {
            char course[20];
            sprintf(course, "Course %d", i + 1);
            outtextxy(200 + i * 100, 30, course);
        }
        outtextxy(200 + REAL_COURSENUM * 100, 30, "Total");
        outtextxy(300 + REAL_COURSENUM * 100, 30, "Average");

        for (int i = 0; i < REAL_STUNUM; ++i) {
            char id[20];
            sprintf(id, "%ld", students[i].id);
            outtextxy(10, 50 + i * 20, id);

            outtextxy(100, 50 + i * 20, students[i].name);

            float total = 0;
            for (int j = 0; j < REAL_COURSENUM; ++j) {
                total += students[i].score[j];
                char score[20];
                sprintf(score, "%.2f", students[i].score[j]);
                outtextxy(200 + j * 100, 50 + i * 20, score);
            }

            char totalStr[20];
            sprintf(totalStr, "%.2f", total);
            outtextxy(200 + REAL_COURSENUM * 100, 50 + i * 20, totalStr);

            char averageStr[20];
            sprintf(averageStr, "%.2f", total / REAL_COURSENUM);
            outtextxy(300 + REAL_COURSENUM * 100, 50 + i * 20, averageStr);
        }
        if (clickbutton(back_to_menu, m)) {
            break;
        }
        EndBatchDraw();
    }
    closegraph();
    menu_display();
}
void c7_display() {
    Sort_in_dictionary_order_by_name();
	initgraph(1240, 960);
	IMAGE mm;
	loadimage(&mm, "background.png", 1240, 960);
	struct button* back_to_menu = createbutton(1040, 910, 200, 50, YELLOW, "���ز˵�");
    while (1) {
		BeginBatchDraw();
		putimage(0, 0, &mm);
		drawbutton(back_to_menu);
		MOUSEMSG m = GetMouseMsg();
		outtextxy(0, 910, "����ɹ�");
		outtextxy(0, 0, "����ĸ˳��");
		outtextxy(10, 30, "ID");
		outtextxy(100, 30, "Name");
        for (int i = 0; i < REAL_COURSENUM; ++i) {
			char course[20];
			sprintf(course, "Course %d", i + 1);
			outtextxy(200 + i * 100, 30, course);
		}
		outtextxy(200 + REAL_COURSENUM * 100, 30, "Total");
		outtextxy(300 + REAL_COURSENUM * 100, 30, "Average");

        for (int i = 0; i < REAL_STUNUM; ++i) {
			char id[20];
			sprintf(id, "%ld", students[i].id);
			outtextxy(10, 50 + i * 20, id);

			outtextxy(100, 50 + i * 20, students[i].name);

			float total = 0;
            for (int j = 0; j < REAL_COURSENUM; ++j) {
				total += students[i].score[j];
				char score[20];
				sprintf(score, "%.2f", students[i].score[j]);
				outtextxy(200 + j * 100, 50 + i * 20, score);
			}

			char totalStr[20];
			sprintf(totalStr, "%.2f", total);
			outtextxy(200 + REAL_COURSENUM * 100, 50 + i * 20, totalStr);

			char averageStr[20];
			sprintf(averageStr, "%.2f", total / REAL_COURSENUM);
			outtextxy(300 + REAL_COURSENUM * 100, 50 + i * 20, averageStr);
        }
        if (clickbutton(back_to_menu, m)) {
            break;
        }
        EndBatchDraw();
    }
    closegraph();
    menu_display();
}
void c8_display() {
    Search_by_number();
	initgraph(1240, 960);
	IMAGE mm;
	loadimage(&mm, "background.png", 1240, 960);
	struct button* back_to_menu = createbutton(1040, 910, 200, 50, YELLOW, "���ز˵�");
    while (1) {
		BeginBatchDraw();
		putimage(0, 0, &mm);
		drawbutton(back_to_menu);
		MOUSEMSG m = GetMouseMsg();
        if (match_id == -1) {
            outtextxy(0, 910, "��ѯʧ��");
            outtextxy(0, 0, "��ѧ�ż���");
            
            if (clickbutton(back_to_menu, m)) {
				break;
			}
            EndBatchDraw();
        }
        else {
            outtextxy(0, 910, "��ѯ�ɹ�");
            outtextxy(0, 0, "��ѧ�ż���");
            outtextxy(10, 30, "ID");
            outtextxy(100, 30, "Name");
            for (int i = 0; i < REAL_COURSENUM; ++i) {
                char course[20];
                sprintf(course, "Course %d", i + 1);
                outtextxy(200 + i * 100, 30, course);
            }
            outtextxy(200 + REAL_COURSENUM * 100, 30, "Total");
            outtextxy(300 + REAL_COURSENUM * 100, 30, "Average");


            char id[20];
            sprintf(id, "%ld", students[match_id].id);
            outtextxy(10, 50 + match_id * 20, id);

            outtextxy(100, 50 + match_id * 20, students[match_id].name);

            float total = 0;
            for (int j = 0; j < REAL_COURSENUM; ++j) {
                total += students[match_id].score[j];
                char score[20];
                sprintf(score, "%.2f", students[match_id].score[j]);
                outtextxy(200 + j * 100, 50 + match_id * 20, score);
            }

            char totalStr[20];
            sprintf(totalStr, "%.2f", total);
            outtextxy(200 + REAL_COURSENUM * 100, 50 + match_id * 20, totalStr);

            char averageStr[20];
            sprintf(averageStr, "%.2f", total / REAL_COURSENUM);
            outtextxy(300 + REAL_COURSENUM * 100, 50 + match_id * 20, averageStr);

            if (clickbutton(back_to_menu, m)) {
                break;
            }
            EndBatchDraw();
        }
		
    }

    closegraph();
    menu_display();
}
void c9_display() {
    Search_by_name();
	initgraph(1240, 960);
	IMAGE mm;
	loadimage(&mm, "background.png", 1240, 960);
	struct button* back_to_menu = createbutton(1040, 910, 200, 50, YELLOW, "���ز˵�");
    while (1) {
		BeginBatchDraw();
		putimage(0, 0, &mm);
		drawbutton(back_to_menu);
		MOUSEMSG m = GetMouseMsg();
        if (match_name == -1) {
            outtextxy(0, 910, "��ѯʧ��");
            outtextxy(0, 0, "����������");
            if (clickbutton(back_to_menu, m)) {
				break;
			}

            EndBatchDraw();

        }
        else {
            outtextxy(0, 910, "��ѯ�ɹ�");
            outtextxy(0, 0, "����������");
            outtextxy(10, 30, "ID");
            outtextxy(100, 30, "Name");
            for (int i = 0; i < REAL_COURSENUM; ++i) {
                char course[20];
                sprintf(course, "Course %d", i + 1);
                outtextxy(200 + i * 100, 30, course);
            }
            outtextxy(200 + REAL_COURSENUM * 100, 30, "Total");
            outtextxy(300 + REAL_COURSENUM * 100, 30, "Average");


            char id[20];
            sprintf(id, "%ld", students[match_name].id);
            outtextxy(10, 50 + match_name * 20, id);

            outtextxy(100, 50 + match_name * 20, students[match_name].name);

            float total = 0;
            for (int j = 0; j < REAL_COURSENUM; ++j) {
                total += students[match_name].score[j];
                char score[20];
                sprintf(score, "%.2f", students[match_name].score[j]);
                outtextxy(200 + j * 100, 50 + match_name * 20, score);
            }

            char totalStr[20];
            sprintf(totalStr, "%.2f", total);
            outtextxy(200 + REAL_COURSENUM * 100, 50 + match_name * 20, totalStr);

            char averageStr[20];
            sprintf(averageStr, "%.2f", total / REAL_COURSENUM);
            outtextxy(300 + REAL_COURSENUM * 100, 50 + match_name * 20, averageStr);

            if (clickbutton(back_to_menu, m)) {
                break;
            }
            EndBatchDraw();
        }
		
    }
    closegraph();
    menu_display();
}
void c10_display() {
    Statistic_analysis();
	initgraph(1240, 960);
	IMAGE mm;
	loadimage(&mm, "background.png", 1240, 960);
	struct button* back_to_menu = createbutton(1040, 910, 200, 50, YELLOW, "���ز˵�");
    while (1) {
		BeginBatchDraw();
		putimage(0, 0, &mm);
		drawbutton(back_to_menu);
		MOUSEMSG m = GetMouseMsg();
		outtextxy(0, 910, "ͳ�Ƴɹ�");
		outtextxy(0, 0, "�������ηֲ�");
		outtextxy(10, 30, "Course");
		outtextxy(200, 30, "A");
		outtextxy(300, 30, "B");
		outtextxy(400, 30, "C");
		outtextxy(500, 30, "D");
		outtextxy(600, 30, "E");

        for (int i = 0; i < REAL_COURSENUM; ++i) {
			char course[20];
			sprintf(course, "Course %d", i + 1);
			outtextxy(10, 50 + i * 20, course);

			char A[20];
			sprintf(A, "%.2f%%", A_PER[i] * 100);
			outtextxy(200, 50 + i * 20, A);

			char B[20];
			sprintf(B, "%.2f%%", B_PER[i] * 100);
			outtextxy(300, 50 + i * 20, B);

			char C[20];
			sprintf(C, "%.2f%%", C_PER[i] * 100);
			outtextxy(400, 50 + i * 20, C);

			char D[20];
			sprintf(D, "%.2f%%", D_PER[i] * 100);
			outtextxy(500, 50 + i * 20, D);

			char E[20];
			sprintf(E, "%.2f%%", E_PER[i] * 100);
			outtextxy(600, 50 + i * 20, E);
		}
        if (clickbutton(back_to_menu, m)) {
			break;
		}
		EndBatchDraw();
    }
    closegraph();
    menu_display();
}
void c11_display() {
    List_record();
	initgraph(1240, 960);
	IMAGE mm;
	loadimage(&mm, "background.png", 1240, 960);
	struct button* back_to_menu = createbutton(1040, 910, 200, 50, YELLOW, "���ز˵�");
    while (1) {
		BeginBatchDraw();
		putimage(0, 0, &mm);
		drawbutton(back_to_menu);
		MOUSEMSG m = GetMouseMsg();
		outtextxy(0, 910, "�г��ɹ�");
		outtextxy(0, 0, "�г���Ϣ");
		outtextxy(10, 30, "ID");
		outtextxy(100, 30, "Name");
        for (int i = 0; i < REAL_COURSENUM; ++i) {
			char course[20];
			sprintf(course, "Course %d", i + 1);
			outtextxy(200 + i * 100, 30, course);
		}
		outtextxy(200 + REAL_COURSENUM * 100, 30, "Total");
		outtextxy(300 + REAL_COURSENUM * 100, 30, "Average");

        for (int i = 0; i < REAL_STUNUM; ++i) {
			char id[20];
			sprintf(id, "%ld", students[i].id);
			outtextxy(10, 50 + i * 20, id);

			outtextxy(100, 50 + i * 20, students[i].name);

			float total = 0;
            for (int j = 0; j < REAL_COURSENUM; ++j) {
				total += students[i].score[j];
				char score[20];
				sprintf(score, "%.2f", students[i].score[j]);
				outtextxy(200 + j * 100, 50 + i * 20, score);
			}

			char totalStr[20];
			sprintf(totalStr, "%.2f", total);
			outtextxy(200 + REAL_COURSENUM * 100, 50 + i * 20, totalStr);

			char averageStr[20];
			sprintf(averageStr, "%.2f", total / REAL_COURSENUM);
			outtextxy(300 + REAL_COURSENUM * 100, 50 + i * 20, averageStr);

        }
        // �����ܷ־���
        outtextxy(0, 50 + REAL_STUNUM * 20, "�����ܷ־���");
        for (int i = 0; i < REAL_COURSENUM; i++) {
			char course[20];
			sprintf(course, "Course %d", i + 1);
			outtextxy(10, 70 + REAL_STUNUM * 20 + i * 20, course);
		}
        outtextxy(200, 50 + REAL_STUNUM * 20, "Total");
        outtextxy(300, 50 + REAL_STUNUM * 20, "Average");
        for (int i = 0; i < REAL_COURSENUM; i++) {
            char total[20];
            sprintf(total, "%.2f", sum_score[i]);
            outtextxy(200, 70 + REAL_STUNUM * 20 + i * 20, total);
            char average[20];
            sprintf(average, "%.2f", aver_score[i]);
            outtextxy(300, 70 + REAL_STUNUM * 20 + i * 20, average);

        }

        if (clickbutton(back_to_menu, m)) {
            break;
        }
        EndBatchDraw();
    }
    closegraph();
    menu_display();
}
void c12_display() {
    Write_to_a_file();
	initgraph(1240, 960);
	IMAGE mm;
	loadimage(&mm, "background.png", 1240, 960);
	struct button* back_to_menu = createbutton(1040, 910, 200, 50, YELLOW, "���ز˵�");
    while (1) {
		BeginBatchDraw();
		putimage(0, 0, &mm);
		drawbutton(back_to_menu);
		MOUSEMSG m = GetMouseMsg();
		outtextxy(0, 910, "д��ɹ�");
        if (clickbutton(back_to_menu, m)) {
			break;
		}
		EndBatchDraw();
	}
	closegraph();
	menu_display();

}
void c13_display() {
    Read_from_a_file();
    c11_display();

}
int main() {
    menu_display();
    return 0;
}