#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Page
{
    char url[51];
    struct Page *prev;
    struct Page *next;
} Page;

Page *current = NULL;

// Create a new page
Page* createPage(char url[])
{
    Page *p = (Page*)malloc(sizeof(Page));

    strcpy(p->url, url);
    p->prev = NULL;
    p->next = NULL;

    return p;
}

// Free all forward history
void freeForward(Page *node)
{
    if(node == NULL)
        return;

    Page *temp = node->next;

    while(temp != NULL)
    {
        Page *next = temp->next;
        free(temp);
        temp = next;
    }

    node->next = NULL;
}

// Visit a new page
void visit(char url[])
{
    if(current == NULL)
    {
        current = createPage(url);
        return;
    }

    freeForward(current);

    Page *newPage = createPage(url);

    newPage->prev = current;
    current->next = newPage;

    current = newPage;
}

// Move back
void back()
{
    if(current == NULL || current->prev == NULL)
    {
        printf("NO_BACK\n");
        return;
    }

    current = current->prev;

    printf("%s\n", current->url);
}

// Move forward
void forward()
{
    if(current == NULL || current->next == NULL)
    {
        printf("NO_FORWARD\n");
        return;
    }

    current = current->next;

    printf("%s\n", current->url);
}

// Print current page
void printCurrent()
{
    if(current == NULL)
    {
        printf("NONE\n");
        return;
    }

    printf("%s\n", current->url);
}

// Free complete history
void freeHistory()
{
    if(current == NULL)
        return;

    // Move to first page
    while(current->prev != NULL)
        current = current->prev;

    while(current != NULL)
    {
        Page *temp = current;
        current = current->next;
        free(temp);
    }
}

int main()
{
    int q;

    scanf("%d", &q);

    while(q--)
    {
        char command[20];

        scanf("%s", command);

        if(strcmp(command, "VISIT") == 0)
        {
            char url[51];
            scanf("%s", url);
            visit(url);
        }

        else if(strcmp(command, "BACK") == 0)
        {
            back();
        }

        else if(strcmp(command, "FORWARD") == 0)
        {
            forward();
        }

        else if(strcmp(command, "CURRENT") == 0)
        {
            printCurrent();
        }
    }

    freeHistory();

    return 0;
}