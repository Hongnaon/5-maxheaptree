#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// �� ����ü
typedef struct {
    int data[MAX_SIZE];
    int size;
} TreeNode;

// �ִ� �� �ʱ�ȭ
void InitMaxHeap(TreeNode* root) {
    root->size = 0;
}

// ���� ���� ���¸� ����մϴ�.
void PrintHeap(TreeNode* root) {
    for (int i = 0; i < root->size; i++) {
        printf("%d ", root->data[i]);
    }
    printf("\n");
}

// �ִ� ���� ���� �ֽ��ϴ�.
int InsertMaxHeap(TreeNode* root, int value, int Step) {
    // ���� �� ���� ����� ���.
    if (root->size >= MAX_SIZE) {
        printf("�� ���� ��\n");
        return 0;
    }

    int index = root->size; // ���ο� ���� �ε���
    root->data[index] = value; // value �� �Է�
    root->size++; // ���� ũ�⸦ ���� ��Ŵ.

    int move = 0; // �̵� Ƚ���� �ʱ�ȭ��.
    if (Step) {
        PrintHeap(root); // �� �Է� �� ���� ���� ���¸� �����.
    }

    // �θ�� ���ϴ� ����~~
    while (index > 0) {
        int parent = (index - 1) / 2; // �θ��� �ε����� �����.
        if (root->data[parent] < root->data[index]) { // �դ��� �ڽĺ��� ������ ��ȯ�մϴ�.
            int temp = root->data[parent];
            root->data[parent] = root->data[index];
            root->data[index] = temp;
            index = parent; 
            move++;

            if (Step) {
           
                PrintHeap(root); // ��ȯ�ϰ��� ���� ���¸� ���.
            }
        }
        else {
            break;
        }
    }
    

    return move; // �� �� ���������� ��ȯ
}

// �ִ� �� ��� ���� �Լ�
int DeleteMaxHeap(TreeNode* root) {
    if (root->size == 0) { // ����� �� ���.

        printf("�� �������\n");
        return 0;
    }

    root->data[0] = root->data[root->size - 1]; // ���������� ��Ʈ�� �̵�.
    root->size--; // ���� ũ�� ����

    int index = 0;
    int moves = 0;
    PrintHeap(root); // ���� �� ���� ���¸� ���.

    //�ڽİ� ���� �ִ� �� Ư���� ����
    while (index * 2 + 1 < root->size) {
        int leftChild = index * 2 + 1; // �����ڽ�
        int rightChild = index * 2 + 2; // �������ڽ�
        int largerChild = leftChild; // ū �ڽ��� �ʱ�ȭ

        // ������ �ڽ��� �� Ŭ ��
        if (rightChild < root->size && root->data[rightChild] > root->data[leftChild]) {
            largerChild = rightChild;
        }

        // �θ� ū �ڽĺ��� ���� ��
        if (root->data[index] < root->data[largerChild]) {
            int temp = root->data[index];
            root->data[index] = root->data[largerChild];
            root->data[largerChild] = temp;

            index = largerChild;
            moves++;

            PrintHeap(root); // ��ȯ�ϰ��� �� ���� ���.
        }
        else {
            break; // ���� Ư��(�� ū ��尡 �� ��(��Ʈ))�� �����Ǹ� ����.
        }
    }


    return moves;
}

// �� ���� ������ ���
void PrintHeapLevelOrder(TreeNode* root) {
    if (root->size == 0) { // ���
        printf("�� �������.\n");
        return;
    }

    int level = 0; // ���� ����
    int count = 1; // ���� �������� ����� ��� ����
    int index = 0; // ���� �ε���

    printf("Ʈ�� ������ ��� \n");
    // �ε����� ��ũ�⺸�� ����������
    while (index < root->size) {
        printf("[%d] ", level + 1);

        for (int i = 0; i < count && index < root->size; i++) {
            printf("%d ", root->data[index]);
            index++;
        }
        printf("\n");

        level++;
        count *= 2; // ���� �������� ����� ��尳���� ����.
    }
}

// ����� �������̽� ���.
void RunUserInterface(TreeNode* root) {
    char choice;
    int value, move; 

    while (1) {
        printf("\n============================\n");
        printf(" ��  i : ��� �߰�       �� \n");
        printf(" ��  d : ��� ����       �� \n");
        printf(" ��  p : ������ ���     ��\n");
        printf(" ��  c : ����            ��\n");
        printf("=============================\n");

        printf("�޴� �Է�: ");
        scanf(" %c", &choice); // �Է¹���

        switch (choice) {
        case 'i':
            printf("�߰��� �� �Է�: ");
            scanf("%d", &value); // �߰��� �� �Է¹���
            move = InsertMaxHeap(root, value, 1); 
            printf("��� �̵� Ƚ��: %d\n", move);
            break;

        case 'd':
            move = DeleteMaxHeap(root);
            printf("��� �̵� Ƚ��: %d\n", move);
            break;

        case 'p':
            PrintHeapLevelOrder(root);
            break;

        case 'c':
            printf("���α׷� ����.\n");
            return;

        default:
            printf("�߸��� �Է�.\n");
        }
    }
}

// �ִ� �� ����
TreeNode* generateMaxHeapTree(int inputData[], int size) {
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    InitMaxHeap(root);

    // �Է��� �����ͷ� ���� ����.
    for (int i = 0; i < size; i++) {
        InsertMaxHeap(root, inputData[i], 0);
    }

    return root; 
}

int main() {
    int inputData[] = { 90, 89, 70, 36, 75, 63, 65, 21, 18, 13 }; // ������� x
    int size = sizeof(inputData) / sizeof(inputData[0]);

    //Ʈ������, *root�� Ʈ���� ������ ��ȯ
    TreeNode* root = generateMaxHeapTree(inputData, size);

    RunUserInterface(root);

    free(root);
    return 0;
}
