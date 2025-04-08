#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//202411292 박준건, 윈도우
#define SIZE 100000
#define TEST 100000

// 링크드 리스트 구조체
typedef struct SinglyLinkedList {
    int data;
    struct SinglyLinkedList* next;
} SinglyLinkedList;

// 함수 선언
void array_insert(int* arr, int data, int position, int* size);
int array_delete(int* arr, int position, int* size);

int isNull(void* ptr);
void SLL_insert(SinglyLinkedList** Header, int data, int position, int capacity);
SinglyLinkedList* SLL_traverse(SinglyLinkedList* Header, int index);
int SLL_count(SinglyLinkedList* Header);
int SLL_delete(SinglyLinkedList** Header, int index, int size);
void SLL_deleteLinkedList(SinglyLinkedList* Header);

// 1-1 100000개의 튜플 삽입 (링크드 리스트)
void insert_many_tuples_SLL() {
    clock_t start, end;
    SinglyLinkedList* test = NULL;
    start = clock();

    for (int i = 0; i < SIZE; i++) {
        SLL_insert(&test, i + 1, 0, i);
    }

    end = clock();
    printf("[1-1] 링크드 리스트 인서트 시간 Time: %d millisec\n", end - start);
}

// 1- 1100000개의 튜플 삽입 (배열)
void insert_many_tuples_Arr() {
    clock_t start, end;
    int testArr[SIZE * 2] = { 0 };
    int* test = testArr;
    int size = 0;
    start = clock();

    for (int i = 0; i < SIZE; i++) {
        array_insert(test, i, i, &size);
    }

    end = clock();
    printf("[1-1] 배열 인서트 시간 Time: %d millisec\n", end - start);
}

// 1-2 랜덤 액세스 (링크드 리스트)
void random_access_SLL() {
    SinglyLinkedList* test = NULL;
    for (int i = 0; i < SIZE; i++) {
        SLL_insert(&test, i + 1, i, i);
    }

    clock_t start, end;
    start = clock();

    int index;
    long long sum = 0;
    for (int i = 0; i < SIZE; i++) {
        index = ((double)rand() / RAND_MAX) * (SIZE - 1);
        sum += SLL_traverse(test, index)->data;
    }

    end = clock();
    printf("[1-2] 링크드 리스트 랜덤 엑세스 시간 Time: %d millisec\n", end - start);
}

// 1-2 랜덤 액세스 (배열)
void random_access_Arr() {
    int testArr[SIZE * 2] = { 0 };
    int* test = testArr;
    int size = 0;

    for (int i = 0; i < SIZE; i++) {
        array_insert(test, i, i, &size);
    }

    clock_t start, end;
    start = clock();

    int index;
    long long sum = 0;
    for (int i = 0; i < SIZE; i++) {
        index = ((double)rand() / RAND_MAX) * (SIZE - 1);
        sum += test[index];
    }

    end = clock();
    printf("[1-2] 배열 랜덤 엑세스 시간 Time: %d millisec\n", end - start);
}

// 1-3 랜덤 삭제 (링크드 리스트)
void random_delete_SLL() {
    clock_t start, end;
    SinglyLinkedList* test = NULL;

    for (int i = 0; i < SIZE; i++) {
        SLL_insert(&test, i + 1, i, i);
    }

    start = clock();

    int index;
    int current_size = SIZE;
    while (current_size > 0) {
        index = ((double)rand() / RAND_MAX) * (current_size - 1);
        SLL_delete(&test, index, current_size);
        current_size--;
    }

    end = clock();
    printf("[1-3] 링크드리스트 랜덤 삭제 시간 Time: %d millisec\n", end - start);
}

// 1-3 랜덤 삭제 (배열)
void random_delete_Arr() {
    int testArr[SIZE * 2] = { 0 };
    int* test = testArr;
    int size = 0;

    for (int i = 0; i < SIZE; i++) {
        array_insert(test, i, i, &size);
    }

    clock_t start, end;
    start = clock();

    int index;
    for (int i = 0; i < SIZE; i++) {
        index = ((double)rand() / RAND_MAX) * (size - 1);
        array_delete(test, index, &size);
    }

    end = clock();
    printf("[1-3] 배열 랜덤 삭제 시간 Time: %d millisec\n", end - start);
}
// 2-1 TEST개의 튜플에서 하나 삽입 (링크드 리스트)
void insert_to_many_tuples_SLL() {
    clock_t start, end;
    SinglyLinkedList* test = NULL;
    int capacity = 0;
    for (int i = 0; i < TEST; i++) {
        SLL_insert(&test, i + 1, 0, i);
        capacity++;
    }
    start = clock();

    SLL_insert(&test, capacity + 1, 0, capacity); 

    end = clock();
    printf("[2-1] 링크드 리스트 %d개의 요소에서 인서트 시간 Time: %d millisec\n",  TEST, end - start);
}

// 1- 1100000개의 튜플 삽입 (배열)
void insert_to_many_tuples_Arr() {
    clock_t start, end;
    int testArr[TEST*2] = { 0 };
    int* test = testArr;
    int size = 0;
    for (int i = 0; i < TEST; i++) {
        array_insert(test, i, i, &size);
    }
    start = clock();
    array_insert(test, size + 1, size, &size);
    
    end = clock();
    printf("[2-1] 배열 %d개의 요소에서 인서트 시간 Time: %d millisec\n", TEST, end - start);
}
//2-1, 튜플 개수에 따른 제거 시간 링크드리스트
void delete_to_many_tuples_SLL() {
    clock_t start, end;
    SinglyLinkedList* test = NULL;
    int capacity = 0;
    for (int i = 0; i < TEST; i++) {
        SLL_insert(&test, i + 1, 0, i);
        capacity++;
    }
    start = clock();
    int index = ((double)rand() / RAND_MAX) * (capacity - 1);
    SLL_delete(&test, index, capacity);
   
    end = clock();
    printf("[2-1] 링크드 리스트 %d개의 요소에서 제거 시간 Time: %d millisec\n", TEST, end - start);
}

// 2-1 튜플 개수에 따른 제거 시간 어레이
void delete_to_many_tuples_Arr() {
    clock_t start, end;
    int testArr[TEST * 2] = { 0 };
    int* test = testArr;
    int size = 0;
    for (int i = 0; i < TEST; i++) {
        array_insert(test, i, i, &size);
    }
    start = clock();
    int index = ((double)rand() / RAND_MAX) * (size - 1);
    array_delete(test, index, &size);

    end = clock();
    printf("[2-1] 배열 %d개의 요소에서 제거 시간 Time: %d millisec\n", TEST, end - start);
}
// 메인 함수
int main() {
    delete_to_many_tuples_Arr();
    delete_to_many_tuples_SLL();
    return 0;
}

// Linked List 관련 함수
void SLL_insert(SinglyLinkedList** Header, int data, int position, int capacity) {
    int length = capacity;

    if (length == 0) {
        *Header = (SinglyLinkedList*)malloc(sizeof(SinglyLinkedList));
        (*Header)->data = data;
        (*Header)->next = NULL;
        return;
    }

    int LastIndex = length - 1;
    if (position == 0) {
        SinglyLinkedList* newList = (SinglyLinkedList*)malloc(sizeof(SinglyLinkedList));
        newList->data = data;
        newList->next = *Header;
        *Header = newList;
    }
    else if (position == length) {
        SinglyLinkedList* insertList = SLL_traverse(*Header, LastIndex);
        insertList->next = (SinglyLinkedList*)malloc(sizeof(SinglyLinkedList));
        insertList->next->data = data;
        insertList->next->next = NULL;
    }
    else if (position > length) {
        printf("SLL_insert Error: length보다 더 큰 값을 입력하셨습니다\n");
        return;
    }
    else {
        SinglyLinkedList* insertList = SLL_traverse(*Header, position - 1);
        SinglyLinkedList* newList = (SinglyLinkedList*)malloc(sizeof(SinglyLinkedList));
        newList->data = data;
        newList->next = insertList->next;
        insertList->next = newList;
    }
}

int SLL_count(SinglyLinkedList* Header) {
    int count = 0;
    while (Header != NULL) {
        count++;
        Header = Header->next;
    }
    return count;
}

int SLL_delete(SinglyLinkedList** Header, int index, int size) {
    int lastIndex = size - 1;
    int value;

    if (index > lastIndex) {
        printf("범위 밖의 데이터 삭제 시도\n");
        return 0;
    }
    else if (index == 0 && size == 1) {
        value = (*Header)->data;
        free(*Header);
        *Header = NULL;
        return value;
    }
    else if (index == lastIndex) {
        SinglyLinkedList* frontPtr = SLL_traverse(*Header, lastIndex - 1);
        SinglyLinkedList* DeletePtr = frontPtr->next;
        value = DeletePtr->data;
        free(DeletePtr);
        frontPtr->next = NULL;
    }
    else if (index == 0) {
        SinglyLinkedList* DeletePtr = *Header;
        *Header = (*Header)->next;
        value = DeletePtr->data;
        free(DeletePtr);
    }
    else {
        SinglyLinkedList* frontPtr = SLL_traverse(*Header, index - 1);
        SinglyLinkedList* DeletePtr = frontPtr->next;
        frontPtr->next = DeletePtr->next;
        value = DeletePtr->data;
        free(DeletePtr);
    }

    return value;
}

SinglyLinkedList* SLL_traverse(SinglyLinkedList* Header, int index) {
    for (int i = 0; i < index && Header != NULL; i++) {
        Header = Header->next;
    }
    return Header;
}

void SLL_deleteLinkedList(SinglyLinkedList* Header) {
    SinglyLinkedList* current = Header;
    while (current != NULL) {
        SinglyLinkedList* next = current->next;
        free(current);
        current = next;
    }
}

// 배열 관련 함수
void array_insert(int* arr, int data, int position, int* size) {
    if (position >= *size) {
        arr[*size] = data;
        (*size)++;
        return;
    }

    for (int i = *size; i > position; i--) {
        arr[i] = arr[i - 1];
    }

    arr[position] = data;
    (*size)++;
}

int array_delete(int* arr, int position, int* size) {
    int data = arr[position];
    for (int i = position; i < (*size) - 1; i++) {
        arr[i] = arr[i + 1];
    }
    (*size)--;
    return data;
}

int isNull(void* ptr) {
    return ptr == NULL;
}
