#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tab {
    int pageID;
    char URL[200];
    struct Tab *next;
} Tab;

Tab *currentTab = NULL;
Tab *head = NULL;
int tabCount = 0;

// Function to open URL in default browser
void openInBrowser(const char *url) {
    char command[300];
    char fullURL[250];

    // Ensure the URL starts with http:// or https://
    if (strncmp(url, "http://", 7) != 0 && strncmp(url, "https://", 8) != 0) {
        sprintf(fullURL, "https://%s", url);
    } else {
        strcpy(fullURL, url);
    }

#ifdef _WIN32
    sprintf(command, "start %s", fullURL);   // Windows
#elif __APPLE__
    sprintf(command, "open %s", fullURL);    // macOS
#else
    sprintf(command, "xdg-open %s", fullURL); // Linux
#endif

    system(command);
}

void visitNewPage() {
    Tab *newTab = (Tab *)malloc(sizeof(Tab));
    newTab->pageID = ++tabCount;

    printf("Enter URL: ");
    scanf("%s", newTab->URL);

    newTab->next = NULL;

    if (head == NULL) {
        head = newTab;
        currentTab = newTab;
    } else {
        Tab *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newTab;
        currentTab = newTab;
    }

    printf("New page opened: %s with Page ID: %d\n", newTab->URL, newTab->pageID);

    // Actually open in browser
    openInBrowser(newTab->URL);
}

void showCurrentTab() {
    if (currentTab != NULL) {
        printf("Current Tab: %s (Page ID: %d)\n", currentTab->URL, currentTab->pageID);
    } else {
        printf("No tabs open.\n");
    }
}

void goBack() {
    if (head == NULL || currentTab == head) {
        printf("No previous tab.\n");
        return;
    }

    Tab *temp = head;
    while (temp->next != NULL && temp->next != currentTab) {
        temp = temp->next;
    }

    if (temp != NULL) {
        currentTab = temp;
        printf("Went back to tab: %s (Page ID: %d)\n", currentTab->URL, currentTab->pageID);
        openInBrowser(currentTab->URL);
    }
}

void goForward() {
    if (currentTab == NULL || currentTab->next == NULL) {
        printf("No forward tab.\n");
        return;
    }

    currentTab = currentTab->next;
    printf("Went forward to tab: %s (Page ID: %d)\n", currentTab->URL, currentTab->pageID);
    openInBrowser(currentTab->URL);
}

void closeCurrentTab() {
    if (currentTab == NULL) {
        printf("No tab to close.\n");
        return;
    }

    if (currentTab == head) {
        head = head->next;
        free(currentTab);
        currentTab = head;
    } else {
        Tab *temp = head;
        while (temp->next != currentTab) {
            temp = temp->next;
        }
        temp->next = currentTab->next;
        free(currentTab);
        currentTab = temp->next;
    }

    printf("Closed the current tab.\n");
}

void showHistory() {
    if (head == NULL) {
        printf("No browsing history.\n");
        return;
    }

    Tab *temp = head;
    printf("Browsing History:\n");
    while (temp != NULL) {
        printf("Page ID: %d, URL: %s\n", temp->pageID, temp->URL);
        temp = temp->next;
    }
}

int main() {
    int choice;

    while (1) {
        printf("\n1. Visit a new page\n");
        printf("2. Go back\n");
        printf("3. Go forward\n");
        printf("4. Show current tab\n");
        printf("5. Close current tab\n");
        printf("6. Show history\n");
        printf("7. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                visitNewPage();
                break;
            case 2:
                goBack();
                break;
            case 3:
                goForward();
                break;
            case 4:
                showCurrentTab();
                break;
            case 5:
                closeCurrentTab();
                break;
            case 6:
                showHistory();
                break;
            case 7:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
