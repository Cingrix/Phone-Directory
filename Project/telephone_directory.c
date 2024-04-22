#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
struct contact
{
    char fname[15];
    char lname[15];
    long long int mobile_no;
    char tag[15];
};
typedef struct contact contact;

// A utility function to add contact into the directory
void add_contact()
{
    system("cls");
    FILE *fptr;
    contact cn;
    fptr = fopen("PhoneBook", "a");

    printf("\n<Fill details>\n");

    printf("Enter First Name : ");
    scanf("%s", &cn.fname);

    printf("Enter last Name : ");
    scanf("%s", &cn.lname);

    printf("\nEnter Mobile Number : ");
    scanf("%lld", &cn.mobile_no);

    printf("\nEnter Tag : ");
    scanf("%s", &cn.tag);

    fwrite(&cn, sizeof(contact), 1, fptr);

    fclose(fptr);

    printf("Enter any key to continue.");
    getch();
    system("cls");
}
// A utility function to print the no.of contacts in the directory

int directory_info()
{
    FILE *fptr;

    fptr = fopen("PhoneBook", "r");
    fseek(fptr, 0, SEEK_END);

    return ftell(fptr) / sizeof(contact);
}
// A utility function to know how many contacts are saved within a specified tag in the directory
int tag_info(char tag[])
{
    int num = 0;
    FILE *fptr;
    contact cn;
    fptr = fopen("PhoneBook", "r");

    while (fread(&cn, sizeof(contact), 1, fptr))
    {
        if (strcmp(strlwr(cn.tag), strlwr(tag)) == 0)
            num++;
    }
    return num;
}

int compare_contacts(const void *a, const void *b)
{
    contact *contactA = (contact *)a;
    contact *contactB = (contact *)b;
    int result = strcmp(contactA->fname, contactB->fname);
    if (result == 0)
    {
        return strcmp(contactA->lname, contactB->lname);
    }
    return result;
}

void sort_contacts_name()
{
    FILE *file;
    contact *contacts = NULL;
    int count = 0;

    // Open the file for reading
    file = fopen("PhoneBook", "r");
    if (file == NULL)
    {
        printf("File not found.\n");
        return;
    }

    // Count the number of contacts in the file
    fseek(file, 0, SEEK_END);
    count = ftell(file) / sizeof(contact);
    rewind(file);

    // Allocate memory for the contacts
    contacts = (contact *)malloc(count * sizeof(contact));
    if (contacts == NULL)
    {
        printf("Memory allocation failed.\n");
        fclose(file);
        return;
    }

    // Read contacts from the file
    fread(contacts, sizeof(contact), count, file);
    fclose(file);

    // Sort the contacts based on first name and last name
    qsort(contacts, count, sizeof(contact), compare_contacts);

    // Rewrite the sorted contacts back into the file
    file = fopen("PhoneBook", "w");
    if (file == NULL)
    {
        printf("File not found.\n");
        free(contacts);
        return;
    }
    fwrite(contacts, sizeof(contact), count, file);
    fclose(file);

    free(contacts);
}

// A utility function to display the contacts
void display()
{
    system("cls");
    FILE *fptr;
    contact cn;
    int mode, count = 1, i, n;
    fptr = fopen("PhoneBook", "r");

    n = directory_info();
    printf("---------------------------------------------------------------------\n");
    printf("|Total Number of contacts : %2d                                      |\n", n);
    printf("---------------------------------------------------------------------");
    printf("\n|%-3s| %-15s%-15s%-20s%-12s|\n", "Sno", "First Name", "Last Name", "Contact Number", "Tag");
    printf("---------------------------------------------------------------------");

    sort_contacts_name();
    while (fread(&cn, sizeof(contact), 1, fptr))
    {
        printf("\n|%-d| %-15s%-15s%-20lld%-12s|", count++, cn.fname, cn.lname, cn.mobile_no, cn.tag);
    }

    printf("\n---------------------------------------------------------------------\n");

    fclose(fptr);

    printf("\n\nEnter any key to continue : ");
    getch();
    system("cls");
}
// This is a utility function which displays all the contacts which are saved within a specified tag
void display_by_tag()
{
    system("cls");
    char tag[20];
    FILE *fptr;
    contact cn;
    int count = 1, n;
    fptr = fopen("PhoneBook", "r");
    fflush(stdin);
    printf("Enter Tag : ");
    scanf("%s", tag);

    n = tag_info(tag);
    printf("---------------------------------------------------------------------\n");
    printf("|Total Number of contacts : %2d                                      |\n", n);
    printf("---------------------------------------------------------------------");
    printf("\n|%-3s| %-15s%-15s%-20s%-12s|\n", "Sno", "First Name", "Last Name", "Contact Number", "Tag");
    printf("---------------------------------------------------------------------");

    while (fread(&cn, sizeof(contact), 1, fptr))
    {
        if (strcmp(strlwr(cn.tag), strlwr(tag)) == 0)
            printf("\n|%-d| %-15s%-15s%-20lld%-12s|", count++, cn.fname, cn.lname, cn.mobile_no, cn.tag);
    }

    printf("\n---------------------------------------------------------------------\n");

    fclose(fptr);
    fflush(stdin);
    printf("\n\nEnter any key to continue : ");
    getch();
    system("cls");
}

// A utility function to modify a cotact
void modify_contact()
{
    system("cls");
    FILE *fptr, *fptr1;
    contact cn;
    char fname[15];
    char lname[15];
    char modify;
    int found = 0;

    fptr = fopen("PhoneBook", "r");
    fptr1 = fopen("helper", "w");

    printf("Enter the name of Contact to modify:\n");
    printf("Enter First name: ");
    scanf("%s", &fname);
    printf("Enter Last name: ");
    scanf("%s", &lname);
    fflush(stdin);

    while (fread(&cn, sizeof(contact), 1, fptr))
    {
        if (strcmp(strlwr(cn.fname), strlwr(fname)) == 0 && strcmp(strlwr(cn.lname), strlwr(lname)) == 0)
        {
            found = 1;
            printf("\nModify First Name?<y/n> : ");
            scanf("%c", &modify);
            fflush(stdin);
            if (modify == 'y' || modify == 'Y')
            {
                printf("Enter New First name : ");
                scanf("%s", &cn.fname);
                fflush(stdin);
            }
            printf("\nModify Last Name?<y/n> : ");
            scanf("%c", &modify);
            fflush(stdin);
            if (modify == 'y' || modify == 'Y')
            {
                printf("Enter New Last name : ");
                scanf("%s", &cn.lname);
                fflush(stdin);
            }
            printf("\nModify Mobile Number? <y/n> : ");
            scanf("%c", &modify);
            fflush(stdin);
            if (modify == 'y' || modify == 'Y')
            {
                printf("Enter New Mobile Number : ");
                scanf("%lld", &cn.mobile_no);
                fflush(stdin);
            }
            printf("\nModify Tag? <y/n> : ");
            scanf("%c", &modify);
            fflush(stdin);
            if (modify == 'y' || modify == 'Y')
            {
                printf("Enter New Tag : ");
                scanf("%s", &cn.tag);
                fflush(stdin);
            }
        }
        fwrite(&cn, sizeof(contact), 1, fptr1);
    }
    fclose(fptr);
    fclose(fptr1);

    if (found == 1)
    {
        fptr1 = fopen("helper", "r");
        fptr = fopen("PhoneBook", "w");

        while (fread(&cn, sizeof(contact), 1, fptr1))
            fwrite(&cn, sizeof(contact), 1, fptr);

        printf("\nContact Modified Successfully\n");
    }
    else
        printf("Contact not found");

    fclose(fptr);
    fclose(fptr1);

    printf("\n\nEnter any key to continue : ");
    getch();
    system("cls");
}

int compare(const void *a, const void *b)
{
    const contact *contactA = (const contact *)a;
    const contact *contactB = (const contact *)b;
    
    if (contactA->mobile_no < contactB->mobile_no) return -1;
    if (contactA->mobile_no > contactB->mobile_no) return 1;
    
    return 0; // If both mobile numbers are equal
}

// Function to sort the elements of the file based on mobile_no
void sort_contacts()
{
    FILE *fptr;
    contact *contacts;
    int num_contacts, i;

    // Open file for reading
    fptr = fopen("PhoneBook", "r");
    if (fptr == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    // Determine number of contacts in the file
    fseek(fptr, 0, SEEK_END);
    num_contacts = ftell(fptr) / sizeof(contact);
    rewind(fptr);

    // Allocate memory for contacts array
    contacts = (contact *)malloc(num_contacts * sizeof(contact));
    if (contacts == NULL)
    {
        printf("Memory allocation failed\n");
        fclose(fptr);
        return;
    }

    // Read contacts from file into array
    fread(contacts, sizeof(contact), num_contacts, fptr);

    // Close file
    fclose(fptr);

    // Sort contacts array based on mobile_no
    qsort(contacts, num_contacts, sizeof(contact), compare);

    // Open file for writing
    fptr = fopen("PhoneBook", "w");
    if (fptr == NULL)
    {
        printf("Error opening file\n");
        free(contacts);
        return;
    }

    // Write sorted contacts array back to file
    fwrite(contacts, sizeof(contact), num_contacts, fptr);

    // Close file
    fclose(fptr);

    // Free memory allocated for contacts array
    free(contacts);

    
}

// A utility function to search for the info of a specified contact
void search_contact()
{
    system("cls");
    FILE *fp;
    contact cn;
    int c, flag = 0;
    fp = fopen("PhoneBook", "r");
    if (fp == NULL)
    {
        printf("\nError in opening\n");
        exit(1);
    }
    printf("\n------------------------------------\n");
    printf("***SEARCH MENU***\n");
    printf("----------------------------------------\n");
    printf("1. Search by name\n2. Search by Phone number\n");
    printf("Enter your choice : ");
    scanf("%d", &c);
    fflush(stdin);
    if (c == 1)
    {
        char fname[30], lname[30];
        printf("Enter the name to be searched for:\n");
        printf("Enter first name : ");
        scanf("%s", &fname);
        printf("Enter last name : ");
        scanf("%s", &lname);
        fflush(stdin);
        while (fread(&cn, sizeof(cn), 1, fp) == 1)
        {

            if (strcmp(strlwr(cn.fname), strlwr(fname)) == 0 && strcmp(strlwr(cn.lname), strlwr(lname)) == 0)
            {
                flag = 1;
                printf("\nDetail information about %s\n", fname);
                printf("---------------------------------------------------------------------\n");
                printf("\n|%-15s%-15s%-20s%-12s|\n", "First Name", "Last Name", "Contact Number", "Tag");
                printf("---------------------------------------------------------------------");
                printf("\n|%-15s%-15s%-20lld%-12s|\n", cn.fname, cn.lname, cn.mobile_no, cn.tag);
                break;
            }
        }
        if (flag == 0)
        {
            printf("\nSearch not found\n");
            fclose(fp);
        }
    }
    else if (c == 2)
    {
        int flag = 0, num_contacts, low = 0, high, mid, choice;
        long long int phone;

        // Determine the number of contacts in the file
        fseek(fp, 0, SEEK_END);
        num_contacts = ftell(fp) / sizeof(contact);
        rewind(fp);
        high = num_contacts - 1;

        // Sort contacts based on mobile_no (required for binary search)
        sort_contacts();

        printf("\n------------------------------------\n");
        printf("***SEARCH MENU***\n");
        printf("----------------------------------------\n");
        printf("Enter phone number to search: ");
        scanf("%lld", &phone);

        // Perform binary search
        while (low <= high)
        {
            mid = (low + high) / 2;
            fseek(fp, mid * sizeof(contact), SEEK_SET);
            fread(&cn, sizeof(contact), 1, fp);

            if (cn.mobile_no == phone)
            {
                flag = 1;
                printf("\nDetail information about %lld", phone);
                printf("\n---------------------------------------------------------------------\n");
                printf("\n|%-15s%-15s%-20s%-12s|\n", "First Name", "Last Name", "Contact Number", "Tag");
                printf("---------------------------------------------------------------------\n");
                printf("|%-15s%-15s%-20lld%-12s|\n", cn.fname, cn.lname, cn.mobile_no, cn.tag);
                break;
            }
            else if (cn.mobile_no < phone)
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }

        // Display message if contact not found
        if (flag == 0)
        {
            printf("\nSearch not found\n");
        }
    }
    else
    {
        printf("Wrong Choice!!");
        fclose(fp);
    }
    printf("Enter any key to continue:");
    getch();
    system("cls");
}

// A utility function to delete a contact from the directory
void delete_contact()
{
    contact cn;
    FILE *fptr, *fptr1;
    int flag;
    system("cls");
    fptr = fopen("PhoneBook", "r");
    if (fptr == NULL)
    {
        printf("CONTACT'S DATA NOT ADDED YET");
    }
    else
    {
        fptr1 = fopen("helper", "w+");
        if (fptr1 == NULL)
            printf("Error in opening the file");
        else
        {

            int choice;
            printf("\n----------------------------------------");
            printf("\n***DELETION MENU***\n");
            printf("----------------------------------------\n");
            printf("1.Deletion through mobile number\n2.Deletion through name\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            if (choice == 1)
            {
                long long int mobile_no;
                printf("Enter CONTACT's mobile_no:");
                scanf("%lld", &mobile_no);
                fflush(stdin);
                while (fread(&cn, sizeof(cn), 1, fptr) == 1)
                {
                    if (mobile_no != cn.mobile_no)
                    {
                        fwrite(&cn, sizeof(cn), 1, fptr1);
                    }
                    if (mobile_no == cn.mobile_no)
                    {
                        flag = 1;
                    }
                }
            }
            else if (choice == 2)
            {
                char fname[25], lname[25];
                printf("Enter CONTACT's fname: ");
                scanf("%s", &fname);
                printf("Enter CONTACT's lname: ");
                scanf("%s", &lname);
                fflush(stdin);
                while (fread(&cn, sizeof(cn), 1, fptr) == 1)
                {
                    if (strcmp(strlwr(cn.fname), strlwr(fname)) != 0 || strcmp(strlwr(cn.lname), strlwr(lname)) != 0)
                    {
                        fwrite(&cn, sizeof(cn), 1, fptr1);
                    }
                    if (strcmp(strlwr(cn.fname), strlwr(fname)) == 0 && strcmp(strlwr(cn.lname), strlwr(lname)) == 0)
                    {
                        flag = 1;
                    }
                }
            }
            else
            {
                printf("\nWrong choice!\nEnter any key to continue");
                getch();
                system("cls");
            }

            fclose(fptr);
            fclose(fptr1);
            if (flag != 1)
            {
                printf("NO CONTACT'S RECORD TO DELETE!\n");
            }
            else
            {
                fptr1 = fopen("helper", "r");
                fptr = fopen("PhoneBook", "w");
                while (fread(&cn, sizeof(contact), 1, fptr1))
                    fwrite(&cn, sizeof(contact), 1, fptr);
                printf("\nContact Deleted Successfully\n");
            }
            fclose(fptr1);
            fclose(fptr);
        }
    }
    printf("Enter any key:");
    getch();
    system("cls");
}

// Driver code
int main()
{
    int operation = 1;

    while (operation)
    {
        printf("\n1 : Create Contact\n");
        printf("2 : Display Directory\n");
        printf("3 : Display by tags\n");
        printf("4 : Modify Contact\n");
        printf("5 : Search Contact\n");
        printf("6 : Delete Contact\n");
        printf("7 : Exit Program\n");
        printf("\nChoose Operation : ");
        scanf("%d", &operation);

        switch (operation)
        {
        case 1:
            add_contact();
            break;
        case 2:
            display();
            break;
        case 3:
            display_by_tag();
            break;
        case 4:
            modify_contact();
            break;
        case 5:
            search_contact();
            break;
        case 6:
            delete_contact();
            break;
        case 7:
            exit(1);
            break;
        default:
            system("cls");
            printf("\nInvalid Operation !!");
            printf("\nEnter 1 to 7 only");
            printf("\n Enter any key to continue");
            getch();
            system("cls");
        }
    }

    return 0;
}