#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ����ָ����Χ�ڵ��������
int generateRandomNumber(int max) {
    return rand() % (max + 1);
}

// ����ָ����������������
char* generateOperators(int numOperators) {
    char operators[] = {'+', '-', '*', '/'};
    char* selectedOperators = (char*)malloc(numOperators * sizeof(char));
    
    for (int i = 0; i < numOperators; i++) {
        selectedOperators[i] = operators[rand() % 4];
    }
    
    return selectedOperators;
}

// �����������ʽ
void generateExpression(int numOperands, int maxNumber, int numOperators, int allowDecimal, int addParentheses, FILE* fp) {
    char* operators = generateOperators(numOperators);
    int parenthesesIndex = rand() % numOperators; // ���ѡ��һ��λ���������
    
    printf("��Ŀ��");
    if(fp != NULL) {
        fprintf(fp, "��Ŀ��");
    }
    
    for (int i = 0; i < numOperands; i++) {
        if (i != 0) {
            printf(" %c ", operators[i - 1]);
            if (fp != NULL) {
                fprintf(fp, " %c ", operators[i - 1]);
            }
            if (addParentheses && i == parenthesesIndex + 1) {
                printf("(");
                if (fp != NULL) {
                    fprintf(fp, "(");
                }
            }
        }
        
        if (allowDecimal) {
            float operand = generateRandomNumber(maxNumber) + (float)generateRandomNumber(100) / 100;
            printf("%.2f", operand);
            if (fp != NULL) {
                fprintf(fp, "%.2f", operand);
            }
        } else {
            printf("%d", generateRandomNumber(maxNumber));
            if (fp != NULL) {
                fprintf(fp, "%d", generateRandomNumber(maxNumber));
            }
        }
    }
    
    if (addParentheses && parenthesesIndex != numOperators) {
        printf(")");
        if (fp != NULL) {
            fprintf(fp, ")");
        }
    }
    
    printf(" = ?\n");
    if (fp != NULL) {
        fprintf(fp, " = ?\n");
    }
    
    free(operators);
}

int main() {
    int numQuestions, maxNumber, numOperators, allowDecimal, outputChoice, addParenthesesChoice;
    FILE* fp = NULL;
    
    // ��ȡ�û�����
    printf("������Ҫ���ɵ���Ŀ������");
    scanf("%d", &numQuestions);
    
    printf("�������������");
    scanf("%d", &maxNumber);
    
    printf("������������ĸ�����");
    scanf("%d", &numOperators);
    
    printf("�Ƿ�����С������1-�ǣ�0-�񣩣�");
    scanf("%d", &allowDecimal);
    
    // �����������Ϊ3��4ʱ��ѯ���Ƿ��������
    if (numOperators == 3 || numOperators == 4) {
        printf("�Ƿ���������Ըı��������ȼ�����1-�ǣ�0-�񣩣�");
        scanf("%d", &addParenthesesChoice);
    } else {
        addParenthesesChoice = 0; // �����������Ϊ3��4ʱ��Ĭ�ϲ��������
    }
    
    printf("��ѡ�������ʽ��1-���������̨��2-������ļ�����");
    scanf("%d", &outputChoice);
    
    // �����û�ѡ����ļ���׼����ӡ������̨
    if (outputChoice == 2) {
        fp = fopen("questions.txt", "w");
        if (fp == NULL) {
            printf("�޷������ļ���");
            return 1;
        }
    }
    
    // ���ݵ�ǰʱ���ʼ�������������
    srand(time(NULL));
    
    // ������Ŀ
    for (int i = 0; i < numQuestions; i++) {
        if (outputChoice == 1) {
            // ���������̨
            generateExpression(numOperators + 1, maxNumber, numOperators, allowDecimal, addParenthesesChoice, NULL);
        } else if (outputChoice == 2) {
            // ������ļ�
            generateExpression(numOperators + 1, maxNumber, numOperators, allowDecimal, addParenthesesChoice, fp);
        } else {
            printf("��Ч�����ѡ��");
            return 1;
        }
    }
    
    // �ر��ļ�
    if (fp != NULL) {
        fclose(fp);
        printf("��Ŀ��д���ļ� questions.txt\n");
    }
    
    return 0;
}

