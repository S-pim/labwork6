#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ��������� ��� ������������� ���� ������
typedef struct Node {
    char *word;           // ��������� �� �����
    struct Node *next;    // ��������� �� ��������� ����
} Node;

// ������� ��� �������� ������ ���� ������
Node *createNode(char *word) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    newNode->word = strdup(word);  // �������� ����� � ����� ����
    newNode->next = NULL;
    return newNode;
}

// ������� ��� ���������� ���� � ����� ������
Node *appendToEnd(Node *head, char *word) {
    if (head == NULL) {
        return createNode(word);
    }

    Node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = createNode(word);
    return head;
}

// ������� ��� �������� ���� ������ ����� N � ����� M ��������
Node *removeWords(Node *head, int N, int M) {
    Node *current = head;
    Node *prev = NULL;

    while (current != NULL) {
        int wordLength = strlen(current->word);
        if (wordLength < N || wordLength > M) {
            // ������� ������� ����
            Node *temp = current;
            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            current = current->next;
            free(temp->word);
            free(temp);
        } else {
            // ��������� � ���������� ����
            prev = current;
            current = current->next;
        }
    }

    return head;
}

// ������� ��� ������ ������
void printList(Node *head) {
    while (head != NULL) {
        printf("%s", head->word);
        if (head->next != NULL) {
            printf(" ");
        }
        head = head->next;
    }
    printf("\n");
}

// �������� �������
int main() {
    printf("Enter lines (Ctrl+C to complete entry):\n");

    Node *head = NULL;  // ��������� ���� ������
    char c;
    char currentWord[100];
    int currentIndex = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n') {
            // ���������� �������� ����� � ���������� � ����� ������
            currentWord[currentIndex] = '\0';
            head = appendToEnd(head, currentWord);
            currentIndex = 0;
        } else {
            // ���������� ������� � �������� �����
            currentWord[currentIndex++] = c;
        }
    }

    // ���������� ���������� �����
    if (currentIndex > 0) {
        currentWord[currentIndex] = '\0';
        head = appendToEnd(head, currentWord);
    }

    // ����� �������� ������
    printf("Source line: \"");
    printList(head);
    printf("\"");

    // �������� ���� ������ ����� N � ����� M ��������
    int N, M;
    printf("\nEnter N and M to delete words (separated by a space): ");
    scanf("%d %d", &N, &M);

    head = removeWords(head, N, M);

    // ����� ����������
    printf("\nThe resulting string: \"");
    printList(head);
    printf("\"");

    // ������������ ������
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp->word);
        free(temp);
    }

    return 0;
}
