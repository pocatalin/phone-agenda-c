#include <stdio.h>
#include <string.h>




struct contact {
    char name[50];
    char phone[20];
    char email[50];
};


struct contact contacts[100];
int num_contacts = 0;


void read_contacts() {
    FILE *file = fopen("phone.txt", "r");
    if (file == NULL) {
        return;
    }
    while (!feof(file) && num_contacts < 100) {
        struct contact c;
        fscanf(file, "%[^,],%[^,],%[^\n]\n", c.name, c.phone, c.email);
        contacts[num_contacts++] = c;
    }
    fclose(file);
}


void save_contacts() {
    FILE *file = fopen("phone.txt", "w");
    if (file == NULL) {
        printf("Error saving contacts.\n");
        return;
    }
    for (int i = 0; i < num_contacts; i++) {
        struct contact c = contacts[i];
        fprintf(file, "%s,%s,%s\n", c.name, c.phone, c.email);
    }
    fclose(file);
}


void print_contacts() {
    printf("Contacts:\n");
    for (int i = 0; i < num_contacts; i++) {
        struct contact c = contacts[i];
        printf("%s | %s | %s\n", c.name, c.phone, c.email);
    }
}


void add_contact() {
    if (num_contacts == 100) {
        printf("Max contacts reached.\n");
        return;
    }
    struct contact c;
    printf("Enter contact name: ");
    scanf("%s", c.name);
    printf("Enter phone number: ");
    scanf("%s", c.phone);
    printf("Enter email address: ");
    scanf("%s", c.email);
    contacts[num_contacts++] = c;
    printf("Contact added.\n");
}


void delete_contact() {
    char name[50];
    printf("Enter the name of the contact to delete: ");
    scanf("%s", name);
    int found = 0;
    for (int i = 0; i < num_contacts; i++) {
        if (strcasecmp(name, contacts[i].name) == 0) {
            for (int j = i; j < num_contacts - 1; j++) {
                contacts[j] = contacts[j + 1];
            }
            num_contacts--;
            found = 1;
            printf("Contact deleted.\n");
            break;
        }
    }
    if (!found) {
        printf("Contact not found.\n");
    }
}

void search_contact() {
    printf("Enter contact name to search: ");
    char name[50];
    scanf("%s", name);
    int index = -1;
    for (int i = 0; i < num_contacts; i++) {
        if (strcmp(contacts[i].name, name) == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("Contact not found.\n");
        return;
    }
    printf("Contact found.\n");
    printf("%s | %s | %s\n", contacts[index].name, contacts[index].phone, contacts[index].email);
}

void update_contact() {
    char name[100];
    printf("Enter the name of the contact to update: ");
    scanf("%s", name);
    int found = 0;
    for (int i = 0; i < num_contacts; i++) {
        if (strcasecmp(name, contacts[i].name) == 0) {
            printf("Enter the new phone number: ");
            scanf("%s", contacts[i].phone);
            printf("Enter the new email address: ");
            scanf("%s", contacts[i].email);
            found = 1;
            printf("Contact updated.\n");
            break;
        }
    }
    if (!found) {
        printf("Contact not found.\n");
    }
}

int main() {
    read_contacts();
    int choice = 0;
    while (choice != 5) {
        printf("\nPhone Contact Manager\n");
        printf("1. View contacts\n");
        printf("2. Add contact\n");
        printf("3. Update contact\n");
        printf("4. Delete contact\n");
        printf("5. Search contact\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                print_contacts();
                break;
            case 2:
                add_contact();
                save_contacts();
                break;
            case 3:
                update_contact();
                save_contacts();
                break;
            case 4:
                delete_contact();
                save_contacts();
                break;
            case 5:
                search_contact();
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    }


    return 0;
}
