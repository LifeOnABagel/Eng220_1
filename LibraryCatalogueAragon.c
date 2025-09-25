//Library Catalogue
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Book {
    char title[100];
    char author[5]; //only taking author initials for simplicity, set size to 5 to avoid overflow
    char genre[50];
    char ISBN[20];
    char date[20];
    bool availability;
    } Book;
    
void add_book(Book **books, int *count);
void search_book(Book **books, int *count);
void check_out_book(Book **books, int *count);
void return_book(Book **books, int *count);
bool check_availability(Book **books, int *count);
void recommend_books(Book **books, int *count);
void manage_reservation_queue(Book **books, int *count);
bool check_duplicate_book(Book **books, int *count);
    
int main(){
    struct Book *books = malloc(100 * sizeof(Book));
    if (!books) {
        printf("Memory allocation failed\n");
        return 1;
    }
    int count=0;
    printf("Hello There! Welcome to the Library!\n");
    printf("Select your prefered action.\n");
    while (1) {
    printf("\n    1. Add a book\n");
    printf("    2. Search for a book\n");
    printf("    3. Check out a book\n");
    printf("    4. Return a book\n");
    printf("    5. Check if a book is available\n");
    printf("    6. Recommend books\n");
    printf("    7. Check for duplicates\n");
    printf("    8. Exit Program\n");
    
    char choice;
    scanf(" %c", &choice);
    while (getchar() != '\n'); //prevents overflow into the functions

    switch (choice) {
        case '1':
            add_book(&books, &count);
            break;
        case '2':
            search_book(&books, &count);
            break;
        case '3':
            check_out_book(&books, &count);
            break;
        case '4':
            return_book(&books, &count);
            break;
        case '5':
            check_availability(&books, &count);
            break;
        case '6':
            recommend_books(&books, &count);
            break;
        case '7':
            check_duplicate_book(&books, &count);
            break;
        case '8':
            printf("Closing program...\n");
            free(books);
            return 0;
        default:
            printf("Invalid choice. Please choose again.\n");
            break;
        }
    }
        
    return 0;
    }
    

void add_book(struct Book **books, int *count) {
    
    printf("Enter book title: ");
    fgets((*books)[*count].title, sizeof((*books)[*count].title), stdin); //get all user values
    printf("Enter author initials: ");
    fgets((*books)[*count].author, sizeof((*books)[*count].author), stdin);
    printf("Enter genre: ");
    fgets((*books)[*count].genre, sizeof((*books)[*count].genre), stdin);
    printf("Enter ISBN: ");
    fgets((*books)[*count].ISBN, sizeof((*books)[*count].ISBN), stdin);
    printf("Enter publication date (xx/xx/xx): ");
    fgets((*books)[*count].date, sizeof((*books)[*count].date), stdin);

    (*books)[*count].availability = true; //if the book is added it must be availible
    (*count)++;
    //This function has a time complexity of O(1), since it does the same thing every time it's ran.
}

void search_book(struct Book **books, int *count) {
    if (*count == 0) {
        printf("The catalogue is empty. Please add a book.\n"); //error handling
        return;
    }

    char searchTitle[100];
    printf("Enter the title of the book you're searching for (Make sure the cases match):");
    fgets(searchTitle, sizeof(searchTitle), stdin);

    bool found = false; 
    for (int i = 0; i < *count; i++) {
        if (strcmp((*books)[i].title, searchTitle) == 0) { //if the title entered matches then the book was found
            printf("\nBook Found!\n");
            printf("Title: %s\n", (*books)[i].title);
            printf("Author: %s\n", (*books)[i].author);
            printf("Genre: %s\n", (*books)[i].genre);
            printf("ISBN: %s\n", (*books)[i].ISBN);
            printf("Publication Date: %s\n", (*books)[i].date);
            printf("Availability: %s\n", (*books)[i].availability ? "Available" : "Checked Out");
            found = true;
            break; 
        }
    }

    if (!found) {
        printf("Book was not found.\n");
    }
    //this function takes longer when more values are added because it scans through every value individually
    //O(n)
}

void check_out_book(struct Book **books, int *count) {
    if (*count == 0) {
        return;
    }

    char title[100];
    printf("Enter the title of the book you want to check out: ");
    fgets(title, sizeof(title), stdin);

    for (int i = 0; i < *count; i++) {
        if (strcmp((*books)[i].title, title) == 0) {
            if ((*books)[i].availability) {
                (*books)[i].availability = false;
                printf("'%s' successfully checked out.\n", (*books)[i].title);
            } else {
                printf("Sorry, '%s' is not available.\n", (*books)[i].title);
            }
            return;
        }
    }
    printf("Book not found.\n");
    //Same thing, this function scans each individual book for a match and grows slower when a value is added
    //O(n)
}

void return_book(struct Book **books, int *count) {
    if (*count == 0) {
        printf("No books :(\n");
        return;
    }

    char title[100];
    printf("Enter the title of the book to return: ");
    fgets(title, sizeof(title), stdin);

    for (int i = 0; i < *count; i++) {
        if (strcmp((*books)[i].title, title) == 0) {
            if (!(*books)[i].availability) {
                (*books)[i].availability = true;
                printf("Book '%s' has been returned.\n", (*books)[i].title);
            } else {
                printf("Book '%s' is already available.\n", (*books)[i].title);
            }
            return;
        }
    }
    printf("Book not found in the catalog.\n");
    //same as the last two functions, every time a book is added, this code gets slower
    //O(n)
}

bool check_availability(struct Book **books, int *count) {
    if (*count == 0) {
        return false;
    }

    char title[100];
    printf("Enter the title of the book to check: ");
    fgets(title, sizeof(title), stdin);

    for (int i = 0; i < *count; i++) {
        if (strcmp((*books)[i].title, title) == 0) {
            printf("Book '%s' is %s.\n", (*books)[i].title, (*books)[i].availability ? "Available" : "Checked Out");
            return (*books)[i].availability;
        }
    }
    printf("Book not found in the catalog.\n");
    return false;
}

void recommend_books(struct Book **books, int *count) {
    if (*count == 0) {
        return;
    }

    char genre[20];
    printf("Enter your preferred genre: ");
    fgets(genre, sizeof(genre), stdin);

    printf("\nRecommended books in '%s' genre:\n", genre);
    bool found = false;
    for (int i = 0; i < *count; i++) {
        if (strcmp((*books)[i].genre, genre) == 0) {
            printf("  - %s by %s (ISBN: %s)\n", (*books)[i].title, (*books)[i].author, (*books)[i].ISBN);
            found = true;
        }
    }

    if (!found) {
        printf("No books found in this genre.\n");
    }
}

bool check_duplicate_book(struct Book **books, int *count) {
    if (*count < 2) {
        printf("Not enough books, add more than one book.\n");
        return false;
    }

    bool duplicateFound = false;
    for (int i=0; i <*count; i++) {
        for (int j=i+1; j<*count; j++) {
            if (strcmp((*books)[i].title, (*books)[j].title) == 0) {
                printf("Duplicate found: '%s'\n", (*books)[i].title);
                duplicateFound = true;
            }
        }
    }

    if (!duplicateFound) {
        printf("No duplicate books found.\n");
    }

    return duplicateFound;
}
