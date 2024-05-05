#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 生成指定范围内的随机整数
int generateRandomNumber(int max) {
    return rand() % (max + 1);
}

// 生成指定数量的随机运算符
char* generateOperators(int numOperators) {
    char operators[] = {'+', '-', '*', '/'};
    char* selectedOperators = (char*)malloc(numOperators * sizeof(char));
    
    for (int i = 0; i < numOperators; i++) {
        selectedOperators[i] = operators[rand() % 4];
    }
    
    return selectedOperators;
}

// 生成算术表达式
void generateExpression(int numOperands, int maxNumber, int numOperators, int allowDecimal, int addParentheses, FILE* fp) {
    char* operators = generateOperators(numOperators);
    int parenthesesIndex = rand() % numOperators; // 随机选择一个位置添加括号
    
    printf("题目：");
    if(fp != NULL) {
        fprintf(fp, "题目：");
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
    
    // 获取用户输入
    printf("请输入要生成的题目数量：");
    scanf("%d", &numQuestions);
    
    printf("请输入最大数：");
    scanf("%d", &maxNumber);
    
    printf("请输入运算符的个数：");
    scanf("%d", &numOperators);
    
    printf("是否允许小数？（1-是，0-否）：");
    scanf("%d", &allowDecimal);
    
    // 当运算符个数为3或4时，询问是否添加括号
    if (numOperators == 3 || numOperators == 4) {
        printf("是否添加括号以改变运算优先级？（1-是，0-否）：");
        scanf("%d", &addParenthesesChoice);
    } else {
        addParenthesesChoice = 0; // 运算符个数不为3或4时，默认不添加括号
    }
    
    printf("请选择输出方式（1-输出到控制台，2-输出到文件）：");
    scanf("%d", &outputChoice);
    
    // 根据用户选择打开文件或准备打印到控制台
    if (outputChoice == 2) {
        fp = fopen("questions.txt", "w");
        if (fp == NULL) {
            printf("无法创建文件！");
            return 1;
        }
    }
    
    // 根据当前时间初始化随机数生成器
    srand(time(NULL));
    
    // 生成题目
    for (int i = 0; i < numQuestions; i++) {
        if (outputChoice == 1) {
            // 输出到控制台
            generateExpression(numOperators + 1, maxNumber, numOperators, allowDecimal, addParenthesesChoice, NULL);
        } else if (outputChoice == 2) {
            // 输出到文件
            generateExpression(numOperators + 1, maxNumber, numOperators, allowDecimal, addParenthesesChoice, fp);
        } else {
            printf("无效的输出选择！");
            return 1;
        }
    }
    
    // 关闭文件
    if (fp != NULL) {
        fclose(fp);
        printf("题目已写入文件 questions.txt\n");
    }
    
    return 0;
}

