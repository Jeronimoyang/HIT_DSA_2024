#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int number;
int poly_number;
typedef struct polynode {
    float coef;
    int exp;
    struct polynode *link;
} polynode;
typedef polynode *polypointer;
// 末端插入接入新结点
void Attch(float c, int e, polypointer d) {
    polypointer x = (polypointer)malloc(sizeof(polypointer));
    x->coef = c;
    x->exp = e;
    x->link = NULL;
    d->link = x;
    d = x;
}
// 从文件中读取多项式
polypointer Read_polypointer(FILE *file) {
    polypointer p = (polypointer)malloc(sizeof(polypointer));
    polypointer d = p;
    p->link = NULL;
    float c;
    int e;
    char symbol;
    symbol = fgetc(file);
    if (symbol == '-') {
        rewind(file);
        fscanf(file, "%c%fx^%d", &symbol, &c, &e);
        Attch(-c, e, d);
        d = d->link;
    } else {
        rewind(file);
        fscanf(file, "%fx^%d", &c, &e);
        Attch(c, e, d);
        d = d->link;
    }
    while (fscanf(file, "%c%fx^%d", &symbol, &c, &e) != EOF) {
        if (symbol == '-') {
            Attch(-c, e, d);
            d = d->link;
        } else if (symbol == '+') {
            Attch(c, e, d);
            d = d->link;
        }
    }
    return p;
}
// 对多项式按指数降幂排序
polypointer Sort_polypointer(polypointer p) {
    polypointer pre, q, end;
    end = NULL;
    pre = p;
    while ((p->link->link) != end) {
        pre = p;
        q = p->link;
        while (q->link != end) {
            if (q->exp < q->link->exp) {
                pre->link = q->link;
                q->link = q->link->link;
                pre->link->link = q;
                q = pre->link;
            }
            q = q->link;
            pre = pre->link;
        }
        end = q;
    }
    return p;
}
// 排查多项式中的系数为0的项
polypointer Select_zero(polypointer p) {
    polypointer q;
    q = p;
    while (q->link != NULL) {
        if (q->link->coef == 0) {
            q->link = q->link->link;
        } else {
            q = q->link;
        }
    }
    return p;
}
// 多项式加法
polypointer Add(polypointer a, polypointer b) {
    polypointer p, q, d, c;
    float y;
    p = a->link;
    q = b->link;
    c = (polypointer)malloc(sizeof(polypointer));
    d = c;
    while ((p != NULL) && (q != NULL)) {
        if (p->exp == q->exp) {
            y = p->coef + q->coef;
            if (y) {
                Attch(y, p->exp, d);
                d = d->link;
                p = p->link;
                q = q->link;
            } else if (y == 0) {
                p = p->link;
                q = q->link;
            }
        } else if (p->exp > q->exp) {
            Attch(p->coef, p->exp, d);
            d = d->link;
            p = p->link;
        } else if (p->exp < q->exp) {
            Attch(q->coef, q->exp, d);
            d = d->link;
            q = q->link;
        }
    }
    while (p != NULL) {
        Attch(p->coef, p->exp, d);
        d = d->link;
        p = p->link;
    }
    while (q != NULL) {
        Attch(q->coef, q->exp, d);
        d = d->link;
        q = q->link;
    }
    d = NULL;
    return c;
}
// 多项式减法
polypointer Subtract(polypointer a, polypointer b) {
    polypointer p, q, d, c;
    float y;
    p = a->link;
    q = b->link;
    c = (polypointer)malloc(sizeof(polypointer));
    d = c;
    while ((p != NULL) && (q != NULL)) {
        if (p->exp == q->exp) {
            y = p->coef - q->coef;
            if (y) {
                Attch(y, p->exp, d);
                d = d->link;
                p = p->link;
                q = q->link;
            } else if (y == 0) {
                p = p->link;
                q = q->link;
            }
        } else if (p->exp > q->exp) {
            Attch(p->coef, p->exp, d);
            d = d->link;
            p = p->link;
        } else if (p->exp < q->exp) {
            Attch(-q->coef, q->exp, d);
            d = d->link;
            q = q->link;
        }
    }
    while (p != NULL) {
        Attch(p->coef, p->exp, d);
        d = d->link;
        p = p->link;
    }
    while (q != NULL) {
        Attch(-q->coef, q->exp, d);
        d = d->link;
        q = q->link;
    }
    d = NULL;
    return c;
}
// 多项式乘法
polypointer Multiply(polypointer a, polypointer b) {
    polypointer p, q, d, c, flag;
    float y;
    int z;
    int key = 0;
    p = a->link;
    q = b->link;
    c = (polypointer)malloc(sizeof(polypointer));
    c->link = NULL;
    d = c;
    while (p != NULL) {
        while (q != NULL) {
            key = 0;
            y = p->coef * q->coef;
            z = p->exp + q->exp;
            flag = c->link;
            while (flag != NULL) {
                if (z == flag->exp) {
                    key = 1;
                    flag->coef = flag->coef + y;
                }
                flag = flag->link;
            }
            if (key == 0) {
                Attch(y, z, d);
                d = d->link;
            }
            q = q->link;
        }
        q = b->link;
        p = p->link;
    }
    c = Sort_polypointer(c);
    c = Select_zero(c);
    return c;
}
// 计算多项式在x0处数值(秦九韶算法)
float Calculate(polypointer p, float x) {
    p = p->link;
    int volume = p->exp;
    float array[volume + 1];
    memset(array, 0, volume + 1);
    while (p != NULL) {
        array[p->exp] = p->coef;
        p = p->link;
    }
    float sum = array[volume];
    for (int i = volume; i > 0; i--) {
        sum = x * sum + array[i - 1];
    }
    return sum;
}
// 打印多项式
void Output(polypointer p) {
    polypointer first;
    p = p->link;
    first = p;
    while (p != NULL) {
        if (p != first) {
            if (p->coef > 0) {
                printf("+");
            }
        }
        printf("%fx^%d", p->coef, p->exp);
        p = p->link;
    }
    printf("\n");
}
// 将多项式写出文件中
void Write(polypointer p) {
    if (!p) {
        printf("输入出现错误\n");
    }
    p = p->link;
    FILE *file = NULL;
    file = fopen("output.txt", "a");
    if (number == 1) {
        fprintf(file, "多项式1+多项式2为:\n");
    } else if (number == 2) {
        fprintf(file, "多项式1-多项式2为:\n");
    } else if (number == 3) {
        fprintf(file, "多项式1*多项式2为:\n");
    }
    fclose(file);
    file = fopen("output.txt", "a");
    char symbol;
    symbol = getc(file);
    if (symbol == '-') {
        rewind(file);
        fprintf(file, "-%fx^%d", p->coef, p->exp);
    } else {
        rewind(file);
        fprintf(file, "%fx^%d", p->coef, p->exp);
    }
    p = p->link;
    while (p != NULL) {
        if (p->coef < 0) {
            fprintf(file, "%fx^%d", p->coef, p->exp);
        } else {
            fprintf(file, "+%fx^%d", p->coef, p->exp);
        }
        p = p->link;
    }
    fprintf(file, "\n");
    fclose(file);
}
// 将多项式在x0处的数值写入文件
void Write_x0(polypointer p, float x0, float result_calculate) {
    FILE *file = NULL;
    file = fopen("output.txt", "a");
    if (poly_number == 1) {
        fprintf(file, "多项式1在x0=%f上的值为%f\n", x0, result_calculate);
    }
    if (poly_number == 2) {
        fprintf(file, "多项式2在x0=%f上的值为%f\n", x0, result_calculate);
    }
    fclose(file);
}

int main() {
    polypointer intput_1, intput_2;
    FILE *f1 = fopen("intput_1.txt", "r");
    FILE *f2 = fopen("intput_2.txt", "r");
    if (f1 == NULL) {
        printf("未成功打开文件intput_1.txt\n");
        exit(1);
    } else {
        intput_1 = Read_polypointer(f1);
        fclose(f1);
    }
    if (f2 == NULL) {
        printf("未成功打开文件intput_2.txt\n");
        exit(1);
    } else {
        intput_2 = Read_polypointer(f2);
        fclose(f2);
    }
    intput_1 = Sort_polypointer(intput_1);
    intput_2 = Sort_polypointer(intput_2);
    FILE *file = NULL;
    file = fopen("output.txt", "a");
    fprintf(file, "多项式1为:\n");
    fclose(file);
    Write(intput_1);
    file = fopen("output.txt", "a");
    fprintf(file, "多项式2为:\n");
    fclose(file);
    Write(intput_2);
    polypointer result[5] = {NULL};
    float result_calculate;
    while (1) {
        printf(
            "请选择要实现的功能：1.多项式加法；2.多项式减法；3.多项式乘法；4."
            "计算多项式在特定点的值；0.退出\n");
        scanf("%d", &number);
        if (number == 1) {
            printf("多项式1和多项式2分别为：\n");
            Output(intput_1);
            Output(intput_2);
            result[1] = Add(intput_1, intput_2);
            printf("相加后的结果多项式为：\n");
            Output(result[1]);
            Write(result[1]);
        } else if (number == 2) {
            printf("多项式1和多项式2分别为：\n");
            Output(intput_1);
            Output(intput_2);
            result[2] = Subtract(intput_1, intput_2);
            printf("相减后的结果多项式为：\n");
            Output(result[2]);
            Write(result[2]);
        } else if (number == 3) {
            printf("多项式1和多项式2分别为：\n");
            Output(intput_1);
            Output(intput_2);
            result[3] = Multiply(intput_1, intput_2);
            printf("相乘后的多项式为：\n");
            Output(result[3]);
            Write(result[3]);
        } else if (number == 4) {
            printf("多项式1和多项式2分别为：\n");
            Output(intput_1);
            Output(intput_2);
            printf("请选择待计算的多项式：1.多项式1；2.多项式2\n");
            scanf("%d", &poly_number);
            if (poly_number == 1) {
                printf("请输入点x0的数值：\n");
                float x0;
                scanf("%f", &x0);
                result_calculate = Calculate(intput_1, x0);
                printf("多项式1在x0=%f上的值为%f\n", x0, result_calculate);
                Write_x0(intput_1, x0, result_calculate);
            } else if (poly_number == 2) {
                printf("请输入点x0的数值：\n");
                float x0;
                scanf("%f", &x0);
                result_calculate = Calculate(intput_2, x0);
                printf("多项式1在x0=%f上的值为%f\n", x0, result_calculate);
                Write_x0(intput_1, x0, result_calculate);
            } else {
                printf("输入值非法");
            }
        } else if (number == 0) {
            break;
        } else {
            printf("输入值非法");
        }
    }
    return 0;
}