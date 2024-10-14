#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// 힙 구조체
typedef struct {
    int data[MAX_SIZE];
    int size;
} TreeNode;

// 최대 힙 초기화
void InitMaxHeap(TreeNode* root) {
    root->size = 0;
}

// 현재 힙의 상태를 출력합니다.
void PrintHeap(TreeNode* root) {
    for (int i = 0; i < root->size; i++) {
        printf("%d ", root->data[i]);
    }
    printf("\n");
}

// 최대 힙에 값을 넣습니다.
int InsertMaxHeap(TreeNode* root, int value, int Step) {
    // 힙이 꽉 차면 경고문을 띄움.
    if (root->size >= MAX_SIZE) {
        printf("힙 가득 참\n");
        return 0;
    }

    int index = root->size; // 새로운 값의 인덱스
    root->data[index] = value; // value 값 입력
    root->size++; // 힙의 크기를 증가 시킴.

    int move = 0; // 이동 횟수를 초기화함.
    if (Step) {
        PrintHeap(root); // 값 입력 전 힙의 현재 상태를 출력함.
    }

    // 부모와 비교하는 과정~~
    while (index > 0) {
        int parent = (index - 1) / 2; // 부모의 인덱스를 계산함.
        if (root->data[parent] < root->data[index]) { // 붐ㅎ가 자식보다 작으면 교환합니다.
            int temp = root->data[parent];
            root->data[parent] = root->data[index];
            root->data[index] = temp;
            index = parent; 
            move++;

            if (Step) {
           
                PrintHeap(root); // 교환하고나서 힙의 상태를 출력.
            }
        }
        else {
            break;
        }
    }
    

    return move; // 몇 번 움직였는지 반환
}

// 최대 값 노드 삭제 함수
int DeleteMaxHeap(TreeNode* root) {
    if (root->size == 0) { // 비었을 때 경고.

        printf("힙 비어있음\n");
        return 0;
    }

    root->data[0] = root->data[root->size - 1]; // 마지막값을 루트로 이동.
    root->size--; // 힙의 크기 감소

    int index = 0;
    int moves = 0;
    PrintHeap(root); // 삭제 전 힙의 상태를 출력.

    //자식과 비교해 최대 힙 특성을 유지
    while (index * 2 + 1 < root->size) {
        int leftChild = index * 2 + 1; // 왼쪽자식
        int rightChild = index * 2 + 2; // 오른쪽자식
        int largerChild = leftChild; // 큰 자식을 초기화

        // 오른쪽 자식이 더 클 때
        if (rightChild < root->size && root->data[rightChild] > root->data[leftChild]) {
            largerChild = rightChild;
        }

        // 부모가 큰 자식보다 작을 때
        if (root->data[index] < root->data[largerChild]) {
            int temp = root->data[index];
            root->data[index] = root->data[largerChild];
            root->data[largerChild] = temp;

            index = largerChild;
            moves++;

            PrintHeap(root); // 교환하고나서 힙 상태 출력.
        }
        else {
            break; // 힙의 특성(젤 큰 노드가 맨 위(루트))이 유지되면 종료.
        }
    }


    return moves;
}

// 힙 레벨 순서로 출력
void PrintHeapLevelOrder(TreeNode* root) {
    if (root->size == 0) { // 경고
        printf("힙 비어있음.\n");
        return;
    }

    int level = 0; // 지금 레벨
    int count = 1; // 지금 레벨에서 출력할 노드 개수
    int index = 0; // 지금 인덱스

    printf("트리 레벨별 출력 \n");
    // 인덱스가 힙크기보다 작을떄까지
    while (index < root->size) {
        printf("[%d] ", level + 1);

        for (int i = 0; i < count && index < root->size; i++) {
            printf("%d ", root->data[index]);
            index++;
        }
        printf("\n");

        level++;
        count *= 2; // 다음 레벨에서 출력할 노드개수를 증가.
    }
}

// 사용자 인터페이스 출력.
void RunUserInterface(TreeNode* root) {
    char choice;
    int value, move; 

    while (1) {
        printf("\n============================\n");
        printf(" ㅣ  i : 노드 추가       ㅣ \n");
        printf(" ㅣ  d : 노드 삭제       ㅣ \n");
        printf(" ㅣ  p : 레벨별 출력     ㅣ\n");
        printf(" ㅣ  c : 종료            ㅣ\n");
        printf("=============================\n");

        printf("메뉴 입력: ");
        scanf(" %c", &choice); // 입력받음

        switch (choice) {
        case 'i':
            printf("추가할 값 입력: ");
            scanf("%d", &value); // 추가할 값 입력받음
            move = InsertMaxHeap(root, value, 1); 
            printf("노드 이동 횟수: %d\n", move);
            break;

        case 'd':
            move = DeleteMaxHeap(root);
            printf("노드 이동 횟수: %d\n", move);
            break;

        case 'p':
            PrintHeapLevelOrder(root);
            break;

        case 'c':
            printf("프로그램 종료.\n");
            return;

        default:
            printf("잘못된 입력.\n");
        }
    }
}

// 최대 힙 생성
TreeNode* generateMaxHeapTree(int inputData[], int size) {
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    InitMaxHeap(root);

    // 입력한 데이터로 힙을 생성.
    for (int i = 0; i < size; i++) {
        InsertMaxHeap(root, inputData[i], 0);
    }

    return root; 
}

int main() {
    int inputData[] = { 90, 89, 70, 36, 75, 63, 65, 21, 18, 13 }; // 순서상관 x
    int size = sizeof(inputData) / sizeof(inputData[0]);

    //트리생성, *root에 트리를 생성해 반환
    TreeNode* root = generateMaxHeapTree(inputData, size);

    RunUserInterface(root);

    free(root);
    return 0;
}
