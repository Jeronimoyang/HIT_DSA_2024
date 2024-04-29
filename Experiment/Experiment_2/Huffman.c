#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define N 128
#define M 2 * N - 1
// 三叉链表存储结构
typedef struct {
    double weight;
    int lchild;
    int rchild;
    int parent;
} HTNODE;
typedef HTNODE HuffmanT[M];
// 编码表的存储结构
typedef struct {
    char ch;
    char bits[M];
    double frequency;
} CodeNode;
typedef CodeNode HuffmanCode[N];
// 最小堆存储结构
typedef struct {
    int key;
    double weight;
} Elementype;
typedef struct {
    Elementype data[M];
    int n;
} HEAP;

long long Number_Character;  // 字符总数
int Number_Tpye;             // 字符种类数
// 堆的初始化
void Heap_Init(HEAP *heap) { heap->n = 0; }
// 判断堆空
int Heap_Empty(HEAP *heap) { return (!heap->n); }
// 判断堆满
int Heap_Full(HEAP *heap) { return (heap->n == N - 1); }
// 结点插入(基于优先级队列)
void Heap_Insert(HEAP *heap, Elementype item) {
    int i;
    if (!Heap_Full(heap)) {
        heap->n++;
        i = heap->n;
        while ((i != 1) && (item.weight < heap->data[i / 2].weight)) {
            heap->data[i] = heap->data[i / 2];
            i /= 2;
        }
    }
    heap->data[i].key = item.key;
    heap->data[i].weight = item.weight;
}
// 删除最堆的最小项
Elementype Heap_DeleteMin(HEAP *heap) {
    int parent = 1;
    int child = 2;
    Elementype item, tmp;
    if (!Heap_Empty(heap)) {
        item = heap->data[1];
        tmp = heap->data[heap->n--];
        while (child <= heap->n) {
            if ((child < heap->n) &&
                (heap->data[child].weight > heap->data[child + 1].weight)) {
                child++;
            }
            if (tmp.weight <= heap->data[child].weight) {
                break;
            }
            heap->data[parent] = heap->data[child];
            parent = child;
            child *= 2;
        }
    }
    heap->data[parent] = tmp;
    return item;
}
// 读取英文文本，统计字符总数和字符种类数
void ReadText(HuffmanCode H) {
    int flag;
    int number_total, type_total;
    char Single_Character;
    int Character_Count[N] = {0};
    flag = 0;
    number_total = 0;
    type_total = 0;
    FILE *file = fopen("./Input/InputText.txt", "r");
    if (file == NULL) {
        printf("打开文件失败\n");
        exit(1);
    }
    while ((Single_Character = fgetc(file)) != EOF) {
        if (isascii(Single_Character)) {
            Character_Count[(int)Single_Character]++;
            number_total++;
        }
    }
    fclose(file);
    for (int i = 0; i < N; i++) {
        if (Character_Count[i]) {
            H[flag].ch = i;
            H[flag].frequency = (double)Character_Count[i] / number_total;
            flag++;
            type_total++;
        }
    }
    Number_Character = number_total;
    Number_Tpye = type_total;
}
// 哈夫曼树初始化
void InitHT(HuffmanCode H, HuffmanT T) {
    for (int i = 0; i < Number_Tpye; i++) {
        T[i].weight = H[i].frequency;
    }
    for (int i = 0; i < M; i++) {
        T[i].parent = -1;
        T[i].lchild = -1;
        T[i].rchild = -1;
    }
}
// 找到两个最小项(基于三叉链表)
void SelecMin(HuffmanT T, int n, int *p1, int *p2) {
    int i, j, temp;
    for (i = 0; i < n; i++) {
        if (T[i].parent == -1) {
            *p1 = i;
            break;
        }
    }
    for (j = i + 1; j < n; j++) {
        if (T[j].parent == -1) {
            *p2 = j;
            break;
        }
    }
    for (i = 0; i < n; i++) {
        if ((T[*p1].weight > T[i].weight) && (T[i].parent == -1) &&
            (*p2 != i)) {
            *p1 = i;
        }
    }
    for (j = 0; j < n; j++) {
        if ((T[*p2].weight > T[j].weight) && (T[j].parent == -1) &&
            (*p1 != j)) {
            *p2 = j;
        }
    }
    if (T[*p1].weight > T[*p2].weight) {
        temp = *p1;
        *p1 = *p2;
        *p2 = temp;
    }
}
// 构造哈夫曼树(基于三叉链表)
void CreatHT(HuffmanCode H, HuffmanT T) {
    int p1, p2, n;
    n = Number_Tpye;
    InitHT(H, T);
    for (int i = n; i < 2 * n - 1; i++) {
        SelecMin(T, i, &p1, &p2);
        T[p1].parent = T[p2].parent = i;
        T[i].lchild = p1;
        T[i].rchild = p2;
        T[i].weight = T[p1].weight + T[p2].weight;
    }
}
// 哈夫曼编码算法的实现
void CharSetHuffmanEncoding(HuffmanCode H, HuffmanT T) {
    int c, p, i;
    char cd[Number_Tpye];
    int start;
    cd[Number_Tpye] = '\0';
    for (i = 0; i < Number_Tpye; i++) {
        start = Number_Tpye;
        c = i;
        while ((p = T[c].parent) >= 0) {
            cd[--start] = (T[p].lchild == c) ? '0' : '1';
            c = p;
        }
        strcpy(H[i].bits, &cd[start]);
    }
}
// 利用哈夫曼树进行编码，存储成压缩文件
void Compressed(HuffmanCode H, HuffmanT T) {
    char Single_Character;
    FILE *file;
    file = fopen("./Input/InputText.txt", "r");
    if (!file) {
        printf("打开文件失败\n");
        exit(1);
    }
    FILE *bitfile;
    bitfile = fopen("./Output//Output.Huffman", "wb");
    if (!bitfile) {
        printf("打开文件失败\n");
        exit(1);
    }
    // 压入字符种类数
    fwrite(&Number_Tpye, sizeof(int), 1, bitfile);
    // 压入各字符
    for (int i = 0; i < Number_Tpye; i++) {
        fwrite(&H[i].ch, sizeof(char), 1, bitfile);
    }
    // 压入哈夫曼树节点
    for (int i = Number_Tpye; i < 2 * Number_Tpye - 1; i++) {
        fwrite(&T[i].lchild, sizeof(unsigned char), 1, bitfile);
        fwrite(&T[i].rchild, sizeof(unsigned char), 1, bitfile);
    }
    // 压入字符数
    fwrite(&Number_Character, sizeof(Number_Character), 1, bitfile);
    int flag;
    int bitflag;
    int i;
    unsigned char bit = 0;
    bitflag = 0;
    while ((Single_Character = fgetc(file)) != EOF) {
        for (i = 0; i < Number_Tpye; i++) {
            if (H[i].ch == Single_Character) {
                break;
            }
        }
        for (flag = 0; H[i].bits[flag]; flag++) {
            if (H[i].bits[flag] == '0') {
                bit = bit << 1;
            } else {
                bit = (bit << 1) + 1;
            }
            bitflag++;
            if (bitflag == 8) {
                fwrite(&bit, sizeof(unsigned char), 1, bitfile);
                bitflag = 0;
                bit = 0;
            }
        }
    }
    if (bitflag) {
        bit = bit << (8 - bitflag);
        fwrite(&bit, sizeof(unsigned char), 1, bitfile);
        fwrite(&bitflag, sizeof(unsigned char), 1, bitfile);
    }
    fclose(file);
    fclose(bitfile);
}
// 将哈夫曼编码文件译码为文本文件
void Decode(HuffmanCode H, HuffmanT T) {
    int type_total;
    long long number_total;
    FILE *bfile = fopen("./Output/Output.Huffman", "rb");
    FILE *file = fopen("./Output/OutputText.txt", "w");
    if (!bfile) {
        printf("打开文件失败\n");
        exit(1);
    }
    // 读取字符种类数
    fread(&type_total, sizeof(type_total), 1, bfile);
    // 读取各字符
    for (int i = 0; i < type_total; i++) {
        fread(&H[i].ch, sizeof(H[i].ch), 1, bfile);
    }
    // 读取哈夫曼树节点
    for (int i = type_total; i < 2 * type_total - 1; i++) {
        unsigned char p1, p2;
        fread(&p1, sizeof(p1), 1, bfile);
        fread(&p2, sizeof(p2), 1, bfile);
        T[i].lchild = (int)p1;
        T[i].rchild = (int)p2;
    }
    // 读取字符数
    fread(&number_total, sizeof(number_total), 1, bfile);
    printf("这篇文章有 %lld 个字符，共 %d 种字符种类数。\n", number_total,
           type_total);
    unsigned char b1;
    fread(&b1, sizeof(b1), 1, bfile);
    int i = 0;
    int j = 2 * type_total - 2;
    int total = 0;
    while (total < number_total) {
        if (((b1 >> (7 - i)) & 1))
            j = T[j].rchild;
        else
            j = T[j].lchild;
        i++;
        if (j < type_total) {
            fprintf(file, "%c", H[j].ch);
            total++;
            j = 2 * type_total - 2;
        }
        if (i == 8) {
            i = 0;
            fread(&b1, sizeof(b1), 1, bfile);
        }
    }
    fclose(bfile);
    fclose(file);
}
// 计算哈夫曼树的编码长度和编码文件的压缩率
void Calculate(HuffmanCode H, HuffmanT T) {
    double lenth = 0;
    for (int i = 0; i < Number_Tpye; i++) {
        lenth = lenth + strlen(H[i].bits) * H[i].frequency;
    }
    printf("哈夫曼树编码长度为:%lf\n", lenth);
    double ratio_theoretical;
    double ratio_real;
    ratio_theoretical = 1 - lenth / 8;
    printf("编码文件的理论压缩率为:%lf\n", ratio_theoretical);
    struct _stat text;
    struct _stat bittext;
    double Size_Text;
    double Size_BitText;
    _stat("./Input/InputText.txt", &text);
    _stat("./Output/Output.Huffman", &bittext);
    Size_Text = text.st_size;
    Size_BitText = bittext.st_size;
    ratio_real = Size_BitText / Size_Text;
    printf("编码文件的真实压缩率为:%lf\n", ratio_real);
}
// 创建堆结构
void CreatHeap(HuffmanCode H, HEAP *heap) {
    Heap_Init(heap);
    for (int i = 0; i < Number_Tpye; i++) {
        Elementype new_node;
        new_node.key = i;
        new_node.weight = H[i].frequency;
        Heap_Insert(heap, new_node);
    }
}
// 找到两个最小项(基于优先级队列)
void SelecMin_Heap(HEAP *heap, int *p1, int *p2) {
    *p1 = Heap_DeleteMin(heap).key;
    *p2 = Heap_DeleteMin(heap).key;
}
// 构造哈夫曼树(基于优先级队列)
void CreatHT_Heap(HuffmanCode H, HuffmanT T) {
    int p1, p2, n;
    n = Number_Tpye;
    HEAP heap;
    InitHT(H, T);
    CreatHeap(H, &heap);
    for (int i = n; i < 2 * n - 1; i++) {
        Elementype new_node;
        SelecMin_Heap(&heap, &p1, &p2);
        T[p1].parent = T[p2].parent = i;
        T[i].lchild = p1;
        T[i].rchild = p2;
        T[i].weight = T[p1].weight + T[p2].weight;
        new_node.key = i;
        new_node.weight = T[i].weight;
        Heap_Insert(&heap, new_node);
    }
}
// 主函数
int main() {
    HuffmanCode H;
    HuffmanT T;
    HuffmanCode H_decode;
    HuffmanT T_decode;
    while (1) {
        int Function_Options;
        printf(
            "请选择功能实现:1.编码(基于三叉链表);2.编码(基于优先级队列);3."
            "压缩文本;"
            "4.译码并计算编码信息;0.退出\n");
        scanf("%d", &Function_Options);
        if (Function_Options == 1) {
            ReadText(H);
            CreatHT(H, T);
            CharSetHuffmanEncoding(H, T);
            printf("这个文本有%d个字符,有%d种字符", Number_Character,
                   Number_Tpye);
            printf("文本中各字符的哈夫曼编码及其频率:\n");
            for (int i = 0; i < Number_Tpye; i++) {
                printf("字符%c    编码:%s    频率:%lf\n", H[i].ch, H[i].bits,
                       H[i].frequency);
            }
        } else if (Function_Options == 2) {
            ReadText(H);
            CreatHT_Heap(H, T);
            CharSetHuffmanEncoding(H, T);
            printf("这个文本有%d个字符,有%d种字符", Number_Character,
                   Number_Tpye);
            printf("文本中各字符的哈夫曼编码及其频率:\n");
            for (int i = 0; i < Number_Tpye; i++) {
                printf("字符%c    编码:%s    频率:%lf\n", H[i].ch, H[i].bits,
                       H[i].frequency);
            }
        } else if (Function_Options == 3) {
            Compressed(H, T);
        } else if (Function_Options == 4) {
            Decode(H_decode, T_decode);
            Calculate(H, T);
        } else if (Function_Options == 0) {
            return 0;
        } else {
            printf("输入值非法,请重新输入\n");
        }
    }
    return 0;
}