#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Структура для представления узла списка
typedef struct Node {
    char *word;           // указатель на слово
    struct Node *next;    // указатель на следующий узел
} Node;

// Функция для создания нового узла списка
Node *createNode(char *word) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    newNode->word = strdup(word);  // копируем слово в новый узел
    newNode->next = NULL;
    return newNode;
}

// Функция для добавления узла в конец списка
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

// Функция для удаления слов длиной менее N и более M символов
Node *removeWords(Node *head, int N, int M) {
    Node *current = head;
    Node *prev = NULL;

    while (current != NULL) {
        int wordLength = strlen(current->word);
        if (wordLength < N || wordLength > M) {
            // Удаляем текущий узел
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
            // Переходим к следующему узлу
            prev = current;
            current = current->next;
        }
    }

    return head;
}

// Функция для вывода списка
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

// Основная функция
int main() {
    printf("Enter lines (Ctrl+C to complete entry):\n");

    Node *head = NULL;  // начальный узел списка
    char c;
    char currentWord[100];
    int currentIndex = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n') {
            // Завершение текущего слова и добавление в конец списка
            currentWord[currentIndex] = '\0';
            head = appendToEnd(head, currentWord);
            currentIndex = 0;
        } else {
            // Добавление символа к текущему слову
            currentWord[currentIndex++] = c;
        }
    }

    // Завершение последнего слова
    if (currentIndex > 0) {
        currentWord[currentIndex] = '\0';
        head = appendToEnd(head, currentWord);
    }

    // Вывод исходной строки
    printf("Source line: \"");
    printList(head);
    printf("\"");

    // Удаление слов длиной менее N и более M символов
    int N, M;
    printf("\nEnter N and M to delete words (separated by a space): ");
    scanf("%d %d", &N, &M);

    head = removeWords(head, N, M);

    // Вывод результата
    printf("\nThe resulting string: \"");
    printList(head);
    printf("\"");

    // Освобождение памяти
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp->word);
        free(temp);
    }

    return 0;
}
