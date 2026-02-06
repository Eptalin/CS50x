#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

// Number of menu items
#define NUM_ITEMS 10

// Menu itmes have item name and price
typedef struct
{
    string item;
    float price;
} menu_item;

// Array of menu items
menu_item menu[NUM_ITEMS];

// Add items to menu
void add_items(void);

// Calculate total cost
float get_cost(string item);

int main(void)
{
    add_items();

    printf("\nWelcome to Beach Burger Shack!\n");
    printf("Choose from the following menu to order. Press enter when done.\n\n");

    for (int i = 0; i < NUM_ITEMS; i++)
    {
        printf("%s: $%.2f\n", menu[i].item, menu[i].price);
    }
    printf("\n");

    float total = 0;
    while (true)
    {
        string item = get_string("Enter a food item: ");
        if (strlen(item) == 0)
        {
            printf("\n");
            break;
        }

        total += get_cost(item);
    }

    printf("Your total cost is: $%.2f\n", total);
}

// Add at least the first four items to the menu array
// Bad design, but used to demonstrate global variables, 
// the lifetime of string literals, and struct assignment.
void add_items(void)
{
    menu_item temp[NUM_ITEMS] = {
        {"Burger", 9.50},
        {"Vegan Burger", 11.00},
        {"Hot Dog", 5.00},
        {"Cheese Dog", 7.00},
        {"Fries", 5.00},
        {"Cheese Fries", 6.00},
        {"Cold Pressed Juice", 7.00},
        {"Cold Brew", 3.00},
        {"Water", 2.00},
        {"Soda", 2.00},
    };
    
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        menu[i] = temp[i];
    }
    return;
}

// Search through the menu array to find an item's cost
float get_cost(string item)
{
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        if (strcmp(item, menu[i].item) == 0)
        {
            return menu[i].price;
        }
    }
    return 0.0;
}
