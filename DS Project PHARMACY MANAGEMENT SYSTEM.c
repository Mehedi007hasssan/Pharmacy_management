#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct Medicine
{
    int slNo; // Serial number
    char name[100];
    char manufacturer[100];
    float price;
    int quantity;
    char location[100];
    struct Medicine* next;
} Medicine;

Medicine* createMedicine(int slNo, char name[], char manufacturer[], float price, int quantity, char location[])
{
    Medicine* newMedicine = (Medicine*)malloc(sizeof(Medicine));
    newMedicine->slNo = slNo;
    strcpy(newMedicine->name, name);
    strcpy(newMedicine->manufacturer, manufacturer);
    newMedicine->price = price;
    newMedicine->quantity = quantity;
    strcpy(newMedicine->location, location);
    newMedicine->next = NULL;
    return newMedicine;
}

void addMedicine(Medicine** inventory, char name[], char manufacturer[], float price, int quantity, char location[])
{
    int slNo = 1; // Default starting serial number

    // Finding the last serial number in the inventory
    if (*inventory != NULL)
    {
        Medicine* current = *inventory;
        while (current->next != NULL)
        {
            slNo++;
            current = current->next;
        }
        slNo++; // Increment for the next serial number
    }

    Medicine* newMedicine = createMedicine(slNo, name, manufacturer, price, quantity, location);
    if (*inventory == NULL)
    {
        *inventory = newMedicine;
    }
    else
    {
        Medicine* current = *inventory;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newMedicine;
    }
}


void searchMedicine(Medicine* inventory, char name[])
{
    Medicine* current = inventory;
    while (current != NULL)
    {
        if (strcmp(current->name, name) == 0)
        {
            printf("\n\n\n");
            printf("Medicine found:\n");
            printf("Serial No.: %d\n", current->slNo);
            printf("Name: %s\n", current->name);
            printf("Manufacturer: %s\n", current->manufacturer);
            printf("Price: %.2f\n", current->price);
            printf("Quantity: %d\n", current->quantity);
            printf("Location: %s\n", current->location);
            printf("\n\n\n");
            return;
        }
        current = current->next;
    }
    printf("\n\n\n");
    printf("                                ************\n");
    printf("                                |       Medicine not found...    |\n");
    printf("                                ************\n");
    printf("\n\n\n");
}

void deleteMedicineBySLNo(Medicine** inventory, int slNo) {
    if (*inventory == NULL) {
        printf("Inventory is empty.\n");
        return;
    }

    Medicine* current = *inventory;
    Medicine* prev = NULL;
    while (current != NULL) {
        if (current->slNo == slNo) {
            if (prev == NULL) {
                *inventory = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("\n\n\n");
            printf("                                ************\n");
            printf("                                |Medicine deleted successfully...|\n");
            printf("                                ************\n");
            printf("\n\n\n");
            // Update serial numbers after deletion
            updateSerialNumbers(*inventory);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Medicine with SL No. %d not found.\n", slNo);
}

void updateSerialNumbers(Medicine* inventory) {
    if (inventory == NULL) {
        return;
    }

    Medicine* current = inventory;
    int slNo = 1; // Starting serial number
    while (current != NULL) {
        current->slNo = slNo;
        slNo++;
        current = current->next;
    }
}

void displayInventory(Medicine* inventory)
{
    if (inventory == NULL)
    {
        printf("\n\n\n");
        printf("                                *********\n");
        printf("                                |Inventory is empty...|\n");
        printf("                                *********\n");
        printf("\n\n\n");
        return;
    }

    // Print table headers
    printf("\n\n\n");
    printf("\n=================================================================================================================\n");
    printf("| %-6s | %-20s | %-40s | %-10s | %-8s | %-10s |\n", "SL No.", "Name", "Manufacturer", "Tk Price", "Quantity", "Location");
    printf("=================================================================================================================\n");

    // Print each medicine entry
    Medicine* current = inventory;
    while (current != NULL)
    {
        printf("| %-6d | %-20s | %-40s | Tk %-6.2f  | %-8d | %-10s |\n", current->slNo, current->name, current->manufacturer, current->price, current->quantity, current->location);
        current = current->next;
    }

    // Print table footer
    printf("=================================================================================================================\n");
    printf("\n\n\n");
}

void freeInventory(Medicine** inventory)
{
    Medicine* current = *inventory;
    while (current != NULL)
    {
        Medicine* next = current->next;
        free(current);
        current = next;
    }
    *inventory = NULL;
}

void updateMedicineBySLNo(Medicine* inventory, int slNo, float newPrice, int newQuantity, char newLocation[])
{
    if (inventory == NULL)
    {
        printf("\n\n\n");
        printf("                                *********\n");
        printf("                                |Inventory is empty...|\n");
        printf("                                *********\n");
        printf("\n\n\n");
        return;
    }

    Medicine* current = inventory;
    int count = 0;
    while (current != NULL)
    {
        count++;
        if (count == slNo)
        {
            current->price = newPrice;
            current->quantity = newQuantity;
            strcpy(current->location, newLocation);
            printf("\n\n\n");
            printf("Medicine with SL No. %d updated successfully.\n", slNo);
            printf("\n\n\n");
            return;
        }
        current = current->next;
    }
    printf("\n\n\n");
    printf("Medicine with SL No. %d not found.\n", slNo);
    printf("\n\n\n");
}

int main()
{
    char username[100], password[100];
    int loginAttempts = 0;
    int loggedIn = 0; // Flag to track if logged in


    // Login Page
    while (loginAttempts < 3 && !loggedIn)
    {
        printf("\n\n\n");
        printf("                                ************\n");
        printf("                                *      Login to the System       *\n");
        printf("                                ************\n");
        printf("                                |      1. Login as Admin         |\n");
        printf("                                |      2. Quit                   |\n");
        printf("                                ************\n");
        printf("\n\n\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);

        switch(choice)
        {
        case 1:
            printf("Enter username: ");
            scanf("%s", username);
            printf("Enter password: ");

int i = 0;
            char ch;
            while ((ch = _getch()) != '\r')   // _getch() reads a single character without echoing it
            {
                if (ch == '\b' && i > 0)   // Handle backspace
                {
                    i--;
                    printf("\b \b"); // Erase the last character
                }
                else if (ch != '\b')
                {
                    password[i++] = ch;
                    printf("*");
                }
            }
            password[i] = '\0'; // Null-terminate the password
            printf("\n");

            if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0)
            {

                printf("Login successful!\n");

                loggedIn = 1; // Set flag to indicate successful login
            }
            else
            {
                printf("\n\n\n");
                printf("                                ******************\n");
                printf("                                | Invalid username or password. Please try again...|\n");
                printf("                                ******************\n");
                printf("\n\n\n");
                loginAttempts++;
            }
            break;
        case 2:
            printf("Exiting The Program");
                for (int i = 0; i < 20000000; i++)
                {
                    i++;
                    i--;
                }
                printf(".");
                for (int i = 0; i < 20000000; i++)
                {
                    i++;
                    i--;
                }
                printf(".");
                for (int i = 0; i < 20000000; i++)
                {
                    i++;
                    i--;
                }
                printf(".\n");
            return 1;
            break;
        default:
            printf("\n\n\n");
            printf("                                **************\n");
            printf("                                | Invalid choice.Please try again... |\n");
            printf("                                **************\n");
            printf("\n\n\n");
            break;
        }

        if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0)
        {
            break;
        }
    }

    if (loginAttempts == 3)
    {
        printf("\n\n\n");
        printf("                                *****************\n");
        printf("                                |Too many login attempts. Exiting the program.|\n");
        printf("                                *****************\n");
        printf("\n\n\n");
        return 1;
    }

    if (loggedIn)   // Display menu only if logged in
    {
        Medicine* inventory = NULL;
        int choice, slNo;
        char name[100], manufacturer[100], location[100];
        float price;
        int quantity;
        addMedicine(&inventory, "Paracetamol", "Square Pharmaceuticals Ltd.", 10.50, 100, "Shelf-1");
addMedicine(&inventory, "Amoxicillin", "Renata Limited", 25.75, 50, "Shelf-1");
addMedicine(&inventory, "Omeprazole", "ACI Limited", 15.30, 80, "Shelf-1");
addMedicine(&inventory, "Ciprofloxacin", "Incepta Pharmaceuticals Ltd.", 18.90, 60, "Shelf-1");
addMedicine(&inventory, "Aspirin", "Beximco Pharmaceuticals Ltd.", 8.25, 120, "Shelf-1");
addMedicine(&inventory, "Diclofenac", "Square Pharmaceuticals Ltd.", 12.75, 70, "Shelf-2");
addMedicine(&inventory, "Metformin", "Renata Limited", 20.50, 90, "Shelf-2");
addMedicine(&inventory, "Atorvastatin", "ACI Limited", 30.25, 40, "Shelf-2");
addMedicine(&inventory, "Azithromycin", "Incepta Pharmaceuticals Ltd.", 28.90, 55, "Shelf-2");
addMedicine(&inventory, "Ibuprofen", "Beximco Pharmaceuticals Ltd.", 9.75, 80, "Shelf-2");

do
        {
        printf("\n");
        printf("                                *****************\n");
        printf("                                |     Medicine Inventory Management System    |\n");
        printf("                                *****************\n");
        printf("                                |          1. Display Inventory               |\n");
        printf("                                |          2. Add Medicine                    |\n");
        printf("                                |          3. Search Medicine                 |\n");
        printf("                                |          4. Delete Medicine                 |\n");
        printf("                                |          5. Update Medicine                 |\n");
        printf("                                |          6. Quit                            |\n");
        printf("                                *****************\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
                displayInventory(inventory);
                break;

            case 2:
                printf("Enter medicine name: ");
                scanf("%s", name);
                printf("Enter manufacturer: ");
                scanf("%s", manufacturer);
                printf("Enter price: ");
                scanf("%f", &price);
                printf("Enter quantity: ");
                scanf("%d", &quantity);
                printf("Enter location: ");
                scanf("%s", location);
                addMedicine(&inventory, name, manufacturer, price, quantity, location); // Serial number will be updated later
                printf("\n\n\n");
                printf("                                **************\n");
                printf("                                |   Medicine added successfully...   |\n");
                printf("                                **************\n");
                printf("\n\n\n");

break;
            case 3:
                printf("Enter medicine name to search: ");
                scanf("%s", name);
                searchMedicine(inventory, name);
                break;
            case 4:
                printf("Enter serial number of medicine to delete: ");
                scanf("%d", &slNo);
                deleteMedicineBySLNo(&inventory, slNo);
                break;
            case 5:
                printf("Enter serial number of medicine to update: ");
                scanf("%d", &slNo);
                printf("Enter new price: ");
                scanf("%f", &price);
                printf("Enter new quantity: ");
                scanf("%d", &quantity);
                printf("Enter new location: ");
                scanf("%s", location);
                updateMedicineBySLNo(inventory, slNo, price, quantity, location);
                break;
            case 6:
                printf("Exiting");
                for (int i = 0; i < 20000000; i++)
                {
                    i++;
                    i--;
                }
                printf(".");
                for (int i = 0; i < 20000000; i++)
                {
                    i++;
                    i--;
                }
                printf(".");
                for (int i = 0; i < 20000000; i++)
                {
                    i++;
                    i--;
                }
                printf(".\n");
                break;
            default:
                printf("\n\n\n");
                printf("                                *************\n");
                printf("                                | Invalid choice. Please try again... |\n");
                printf("                                *************\n");
            printf("\n\n\n");
            break;
        }
    }
    while (choice != 6);
    freeInventory(&inventory);
}
return 0;

}
