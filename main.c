#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct carte{
    char titlu[100];
    char autor[100];
    int nr_pag;
};

struct carte in_memory[100];
//int in_memory_length;

void add_book(struct carte book, int selected)
{
    FILE *fptr;
    int index = 1;
    char s[256];
    switch(selected) {
        case 0:
            fptr = fopen("C:\\Users\\Aryana\\CLionProjects\\untitled\\read.txt", "r");
            while (fgets(s,sizeof(s),fptr))
                index++;
            fclose(fptr);

            fptr = fopen("C:\\Users\\Aryana\\CLionProjects\\untitled\\read.txt", "a");
            fprintf(fptr,"%d.%s.%s.%d\n", index, book.titlu, book.autor, book.nr_pag);
            break;
        case 1:
            fptr = fopen("C:\\Users\\Aryana\\CLionProjects\\untitled\\currently_reading.txt", "r");
            while (fgets(s,sizeof(s),fptr))
                index++;
            fclose(fptr);

            fptr = fopen("C:\\Users\\Aryana\\CLionProjects\\untitled\\currently_reading.txt", "a");
            fprintf(fptr,"%d.%s.%s.%d\n",index, book.titlu, book.autor, book.nr_pag);
            break;
        case 2:
            fptr = fopen("C:\\Users\\Aryana\\CLionProjects\\untitled\\want_to_read.txt", "r");
            while (fgets(s,sizeof(s),fptr))
                index++;
            fclose(fptr);

            fptr = fopen("C:\\Users\\Aryana\\CLionProjects\\untitled\\want_to_read.txt", "a");
            fprintf(fptr,"%d.%s.%s.%d\n", index, book.titlu, book.autor, book.nr_pag);
            break;
        default:
            break;
    }
    fclose(fptr);
}

void display_books(int selected)
{
    char s[256], s2[256];
    FILE *fptr;
    char *p;
    switch(selected){
        case 0:
            fptr = fopen("C:\\Users\\Aryana\\CLionProjects\\untitled\\read.txt", "r");
            if(fptr == NULL)
                printf("file not open");
            while (fgets(s,sizeof(s),fptr))
            {
                strcpy(s2, s);
                p = strtok(s2, ".");
                printf("%s. ",p);
                p = strtok(NULL, ".");
                printf("%s\n",p);
                p = strtok(NULL, ".");
                printf("by %s\n",p);
                p = strtok(NULL, ".");
                printf("Nr. of pages: %s\n",p);

            }
            break;
        case 1:
            fptr = fopen("C:\\Users\\Aryana\\CLionProjects\\untitled\\currently_reading.txt", "r");
            if(fptr == NULL)
                printf("file not open");
            while (fgets(s,sizeof(s),fptr))
            {
                strcpy(s2, s);
                p = strtok(s2, ".");
                printf("%s. ",p);
                p = strtok(NULL, ".");
                printf("%s\n",p);
                p = strtok(NULL, ".");
                printf("by %s\n",p);
                p = strtok(NULL, ".");
                printf("Nr. of pages: %s\n",p);
            }
            break;
        case 2:
            fptr = fopen("C:\\Users\\Aryana\\CLionProjects\\untitled\\want_to_read.txt", "r");
            if(fptr == NULL)
                printf("file not open");
            while (fgets(s,sizeof(s),fptr))
            {
                strcpy(s2, s);
                p = strtok(s2, ".");
                printf("%s. ",p);
                p = strtok(NULL, ".");
                printf("%s\n",p);
                p = strtok(NULL, ".");
                printf("by %s\n",p);
                p = strtok(NULL, ".");
                printf("Nr. of pages: %s\n",p);
            }
            break;
        default:
            break;
    }
    fclose(fptr);
}

void upload_books(int selected, struct carte retinute[], int *in_memory_length) {
    FILE *fptr;
    switch (selected) {
        case 0:
            fptr = fopen("C:\\Users\\Aryana\\CLionProjects\\untitled\\read.txt", "r");
            break;
        case 1:
            fptr = fopen("C:\\Users\\Aryana\\CLionProjects\\untitled\\currently_reading.txt", "r");
            break;
        case 2:
            fptr = fopen("C:\\Users\\Aryana\\CLionProjects\\untitled\\want_to_read.txt", "r");
            break;
        default:
            break;
    }
    if(fptr == NULL)
        printf("file not open");

    char *p;
    char s[256], s2[256];
    *in_memory_length = 0;
    while (fgets(s,sizeof(s),fptr))
    {
        struct  carte book;
        p = strcpy(s2,s);
        p = strtok(s2, ".");
        p = strtok(NULL, ".");
        strcpy(book.titlu, p);
        p = strtok(NULL,".");
        strcpy(book.autor, p);
        p = strtok(NULL,".");
        book.nr_pag = atoi(p);
        retinute[(*in_memory_length)++] = book;
    }
    fclose(fptr);
}

void edit_book(char new_value[100], int selected_list, int index, int selected_value)
{
    struct carte carti[100];
    int nr_carti;
    upload_books(selected_list,carti,&nr_carti);

    index--;
    switch(selected_value)
    {
        case 0:
            strcpy(carti[index].titlu, new_value);
            break;
        case 1:
            strcpy(carti[index].autor, new_value);
            break;
        case 2:
            carti[index].nr_pag = atoi(new_value);
            break;
        default:
            break;
    }

    FILE *fptr;
    switch(selected_list){
        case 0:
            fptr = fopen("C:\\Users\\Aryana\\CLionProjects\\untitled\\read.txt", "w");
            break;
        case 1:
            fptr = fopen("C:\\Users\\Aryana\\CLionProjects\\untitled\\currently_reading.txt", "w");
            break;
        case 2:
            fptr = fopen("C:\\Users\\Aryana\\CLionProjects\\untitled\\want_to_read.txt", "w");
            break;
        default:
            break;
    }

    for (int i=0; i<nr_carti;i++)
        fprintf(fptr,"%d.%s.%s.%d\n",(i+1), carti[i].titlu, carti[i].autor, carti[i].nr_pag);
    fclose(fptr);
}

void delete_book(char title[100], int selected)
{
    struct carte carti[100];
    int nr_carti;
    upload_books(selected, carti, &nr_carti);

    for(int i=0;i<nr_carti;i++)
    {
        if(strcmp(carti[i].titlu, title) == 0)
        {
            nr_carti--;
            for(int j=i;j<nr_carti;j++)
                carti[j] = carti[j+1];
        }
    }

    FILE *fptr;
    switch(selected){
        case 0:
            fptr = fopen("C:\\Users\\Aryana\\CLionProjects\\untitled\\read.txt", "w");
            break;
        case 1:
            fptr = fopen("C:\\Users\\Aryana\\CLionProjects\\untitled\\currently_reading.txt", "w");
            break;
        case 2:
            fptr = fopen("C:\\Users\\Aryana\\CLionProjects\\untitled\\want_to_read.txt", "w");
            break;
        default:
            break;
    }
    for (int i=0; i<nr_carti;i++)
        fprintf(fptr,"%d.%s.%s.%d\n",(i+1), carti[i].titlu, carti[i].autor, carti[i].nr_pag);
    fclose(fptr);
}

struct carte read_book()
{
    struct carte book;
    char s[100];
    printf("Title:");
    gets(s);
    strcpy(book.titlu, s);
    printf("Author:");
    gets(s);
    strcpy(book.autor, s);
    printf("Number of pages:");
    gets(s);
    book.nr_pag = atoi(s);
    return book;
}

void done();

void pressed_0() //add book
{
    int selected;
    char s[2];
    struct carte book;
    book = read_book();
    printf("Where do you want to store the book?\n");
    printf("0. Read list\n");
    printf("1. Currently reading list\n");
    printf("2. Want to read list\n");
    gets(s);
    selected = atoi(s);
    add_book(book,selected);
    printf("Your book was added succesfully!\n");
    done();
}

void pressed_1() //Display one list
{
    int selected;
    char s[2];
    printf("What list would you like to display?\n");
    printf("0. Read list\n");
    printf("1. Currently reading list\n");
    printf("2. Want to read list\n");
    gets(s);
    selected = atoi(s);
    display_books(selected);
    done();

}

void pressed_2() //delete a book
{
    int selected_list;
    char s1[2], s2[256];
    printf("From what list would you like to delete a book?\n");
    printf("0. Read list\n");
    printf("1. Currently reading list\n");
    printf("2. Want to read list\n");
    gets(s1);
    selected_list = atoi(s1);
    printf("What book would you like to delete? (enter title)\n");
    gets(s2);
    delete_book(s2, selected_list);
    printf("Book deleted succesfully\n");
    done();
}

void pressed_3()
{
    int selected_list, selected_value, index;
    char s1[2], s2[2], s3[2], new_value[256];
    printf("From what list would you like to edit?\n");
    printf("0. Read list\n");
    printf("1. Currently reading list\n");
    printf("2. Want to read list\n");
    gets(s1);
    selected_list = atoi(s1);
    printf("What book would you like to change?(enter index)\n");
    gets(s2);
    index = atoi(s2);
    printf("What would you like to change to this book?\n");
    printf("0. Title\n");
    printf("1. Author\n");
    printf("2. Number of pages\n");
    gets(s3);
    selected_value = atoi(s3);
    printf("Please type your edit\n");
    gets(new_value);
    edit_book(new_value, selected_list, index, selected_value);
    printf("Edit saved succesfully\n");  // problem 1;
    done();
}

void menu()
{
    printf("Press the button for what you want to do:\n");
    printf("0. Add book to a list\n");
    printf("1. Display one list\n");
    printf("2. Delete a book\n");
    printf("3. Edit a book from the lists\n");
    int pressed;
    char s[2];
    gets(s);
    pressed = atoi(s);
    switch(pressed)
    {
        case 0:
            pressed_0();
            break;
        case 1:
            pressed_1();
            break;
        case 2:
            pressed_2();
            break;
        case 3:
            pressed_3();
            break;
    }
}

void done()
{
    char s[2];
    int selected;
    printf("Press 0 to go to menu or press 1 to exit\n");
    gets(s);
    selected = atoi(s);
    if(selected == 0)
        menu();
}

int main()
{
    //struct carte a = read_book(), b = read_book(), c = read_book(), d = read_book(), e = read_book(), f = read_book();
//    add_book(a,0);
//    add_book(b,0);
//    add_book(c,2);
//    add_book(d,1);
//    add_book(e,1);
//    add_book(f,2);

    printf("This is a book collection software. You have three book lists at your disposal.\n");
    printf("The read list consists of books that you have read so far. The currently reading list contains books that you are reading right now. The want to read list is made of books that you wish to read in the future.\n\n");
    menu();
    return 0;
}