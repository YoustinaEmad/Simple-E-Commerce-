#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct product product;
typedef struct Category Category;
typedef struct store store;

struct product
{
    int price;
    char Name[30];
    int quantity;
};

struct Category
{
    char name[30];
    product *Products;
    int numOfProducts;
};

struct store
{
    Category *categories;
    int numOfCategories;
};

void SetColor(int ForgC)
{
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}

void displayMenu(int selectedOption)
{
    system("cls");

    printf("--------------WELCOME TO OUR STORE----------------\n");
    for (int i = 1; i <= 6; i++)
    {
        if (i == selectedOption )
        {
            SetColor(12);
            printf("> ");
        }
        else
        {
            SetColor(15);
            printf("  ");
        }

        if (i == 1)
            printf("1) Add category\n");
        else if (i == 2)
            printf("2) Add product\n");
        else if (i == 3)
            printf("3) Sell product\n");
        else if (i == 4)
            printf("4) Move product from category to another\n");
        else if (i == 5)
            printf("5) Display\n");
        else if (i == 6)
            printf("6) Exit\n");
    }
}

void Initialize(store *superMarket)
{
    superMarket->numOfCategories = 0;
    superMarket->categories = NULL;
}

void AddCategory(store *superMarket)
{
    char categoryName[30];
    printf("Please enter the category name: ");
    scanf(" %[^\n]s", categoryName);

    for (int i = 0; i < superMarket->numOfCategories; i++) {
        if (strcasecmp(categoryName, superMarket->categories[i].name) == 0) {
            printf("Sorry this category already exists...\n");
            return;
        }
    }

    Category newCategory;
    strcpy(newCategory.name, categoryName);
    newCategory.numOfProducts = 0;
    newCategory.Products = NULL;

    superMarket->categories = realloc(superMarket->categories, (superMarket->numOfCategories + 1) * sizeof(Category));
    superMarket->categories[superMarket->numOfCategories] = newCategory;
    superMarket->numOfCategories++;

    printf("Do you want to add any products in this category ? (please enter n if you don't want and y if you want) : ");
    char productNeed;
    scanf(" %c",&productNeed);
    if (productNeed == 'y')
    {
        while (1)
        {
            char productName[30];
            int productPrice;
            int productQuantity;

            printf("Please enter the product name: ");
            scanf(" %[^\n]s", productName);
        for (int i = 0; i < superMarket->categories[i].numOfProducts; i++) {
            if (strcasecmp(productName, superMarket->categories[i].Products[i].Name) == 0) {
            printf("Sorry this product already exists...\n");
            return;
                 }
            }

            printf("Please enter the product price: ");
            scanf("%d", &productPrice);
            while(productPrice<=0)
          {
        printf("Please Enter positive value : ");
        scanf("%d", &productPrice);
          }

            printf("Please enter the product quantity: ");
            scanf("%d", &productQuantity);
            while(productQuantity<=0)
           {
        printf("Please Enter positive value : ");
        scanf("%d", &productQuantity);
        }

            Category *category = &(superMarket->categories[superMarket->numOfCategories - 1]);

            category->numOfProducts++;
            category->Products = realloc(category->Products, category->numOfProducts * sizeof(product));

            product prod;
            strcpy(prod.Name, productName);
            prod.price = productPrice;
            prod.quantity = productQuantity;

            category->Products[category->numOfProducts - 1] = prod;

            printf("Product added successfully\n");
            printf("Do you want to add another product? (Enter n for No, y for Yes): ");
            char addAnotherProduct;
            scanf(" %c", &addAnotherProduct);

            if (addAnotherProduct == 'n')
            {
                printf("Category added successfully.\n");
                break;

            }
            else if(addAnotherProduct !='y')
            {
                printf("Your choice is not available...But your category Added successfully\n");
                break;
            }
        }
    }
    else if(productNeed=='n')
    {
        printf("Category added successfully.\n");
    }
    else if(productNeed !='y'||'n'){
        printf("Your choice is not available...But your category Added successfully\n");
    }
}
void AddProduct(store *superMarket)
{
    if (superMarket->numOfCategories == 0)
    {
        printf("No categories available. Please add a category first.\n");
        return;
    }

    char productName[30];
    int productPrice;
    int productQuantity;
    int categoryIndex;

    printf("Please enter the product name: ");
    scanf(" %[^\n]s", productName);
     for (int i = 0; i < superMarket->categories[i].numOfProducts; i++) {
        if (strcasecmp(productName, superMarket->categories[i].Products[i].Name) == 0) {
            printf("Sorry this product already exists...\n");
            return;
        }
    }

    printf("Please enter the product price: ");
    scanf("%d", &productPrice);

    while(productPrice<=0)
    {
        printf("Please Enter positive value : ");
        scanf("%d", &productPrice);
    }

    printf("Please enter the product quantity: ");
    scanf("%d", &productQuantity);

    while(productQuantity<=0)
    {
        printf("Please Enter positive value : ");
        scanf("%d", &productQuantity);
    }

    printf("Please select a category:\n");

    for (int i = 0; i < superMarket->numOfCategories; i++)
    {
        printf("%d) %s\n", i + 1, superMarket->categories[i].name);
    }

    scanf("%d", &categoryIndex);

    categoryIndex--;

    if (categoryIndex < 0 || categoryIndex >= superMarket->numOfCategories)
    {
        printf("Invalid category selection.\n");
        return;
    }


    Category *category = &(superMarket->categories[categoryIndex]);

    category->numOfProducts++;

    category->Products = realloc(category->Products, category->numOfProducts * sizeof(product));

    product prod;
    strcpy(prod.Name, productName);
    prod.price = productPrice;
    prod.quantity = productQuantity;

    category->Products[category->numOfProducts - 1] = prod;

    printf("Product added successfully.\n");
}
void Display(store *superMarket)
{
    for (int i = 0; i < superMarket->numOfCategories; i++)
    {
        Category *category = &(superMarket->categories[i]);
        printf("Category: %s\n", category->name);

        if (category->numOfProducts == 0)
        {
            printf("No products available in this category.\n");
            continue;
        }

        for (int j = 0; j < category->numOfProducts; j++)
        {
            product *prod = &(category->Products[j]);
            int totalPrice = prod->price * prod->quantity;
            printf("Product: %s | Price: %d | Quantity: %d | Total Price: %d\n", prod->Name, prod->price, prod->quantity, totalPrice);
        }
    }
}

void SellProduct(store *superMarket)
{
    if (superMarket->numOfCategories == 0)
    {
        printf("No categories available. Please add a category first.\n");
        return;
    }

    printf("Please select a category:\n");
    for (int i = 0; i < superMarket->numOfCategories; i++)
    {
        printf("%d) %s\n", i + 1, superMarket->categories[i].name);
    }

    int categoryIndex;
    scanf("%d", &categoryIndex);
    categoryIndex--;

    if (categoryIndex < 0 || categoryIndex >= superMarket->numOfCategories)
    {
        printf("Invalid category selection.\n");
        return;
    }

    Category *category = &(superMarket->categories[categoryIndex]);

    if (category->numOfProducts == 0)
    {
        printf("No products available in this category.\n");
        return;
    }

    printf("Please select a product to sell:\n");
    for (int j = 0; j < category->numOfProducts; j++)
    {
        printf("%d) %s\n", j + 1, category->Products[j].Name);
    }

    int productIndex;
    scanf("%d", &productIndex);
    productIndex--;

    if (productIndex < 0 || productIndex >= category->numOfProducts)
    {
        printf("Invalid product selection.\n");
        return;
    }

    product *selectedProduct = &(category->Products[productIndex]);

    if (selectedProduct->quantity == 0)
    {
        printf("No quantity available for the selected product.\n");
        return;
    }

    int sellQuantity;
    printf("Enter the quantity to sell (available quantity: %d): ", selectedProduct->quantity);
    scanf("%d", &sellQuantity);

    if (sellQuantity <= 0 || sellQuantity > selectedProduct->quantity)
    {
        printf("Invalid quantity.\n");
        return;
    }

    selectedProduct->quantity -= sellQuantity;

    printf("Product sold successfully. Remaining quantity: %d\n", selectedProduct->quantity);
}

void MoveProduct(store *superMarket)
{
    if (superMarket->numOfCategories == 0) {
        printf("No categories available. Please add a category first.\n");
        return;
    }

    char productName[30];
    int sourceCategoryIndex, destinationCategoryIndex;

    printf("Please enter the product name: ");
    scanf(" %[^\n]s", productName);

    printf("Please select the source category:\n");
    for (int i = 0; i < superMarket->numOfCategories; i++) {
        printf("%d) %s\n", i + 1, superMarket->categories[i].name);
    }
    scanf("%d", &sourceCategoryIndex);
    sourceCategoryIndex--;

    if (sourceCategoryIndex < 0 || sourceCategoryIndex >= superMarket->numOfCategories) {
        printf("Invalid source category selection.\n");
        return;
    }

    Category *sourceCategory = &(superMarket->categories[sourceCategoryIndex]);

    int productIndex = -1;
    for (int i = 0; i < sourceCategory->numOfProducts; i++) {
        if (strcmp(sourceCategory->Products[i].Name, productName) == 0) {
            productIndex = i;
            break;
        }
    }

    if (productIndex == -1) {
        printf("Product not found in the source category.\n");
        return;
    }

    printf("Please select the destination category:\n");
    for (int i = 0; i < superMarket->numOfCategories; i++) {
        if (i == sourceCategoryIndex) {
            continue;
        }
        printf("%d) %s\n", i + 1, superMarket->categories[i].name);
    }
    scanf("%d", &destinationCategoryIndex);
    destinationCategoryIndex--;

    if (destinationCategoryIndex < 0 || destinationCategoryIndex >= superMarket->numOfCategories) {
        printf("Invalid destination category selection.\n");
        return;
    }

    Category *destinationCategory = &(superMarket->categories[destinationCategoryIndex]);

    destinationCategory->numOfProducts++;
    destinationCategory->Products = realloc(destinationCategory->Products, destinationCategory->numOfProducts * sizeof(product));
    destinationCategory->Products[destinationCategory->numOfProducts - 1] = sourceCategory->Products[productIndex];

    for (int i = productIndex; i < sourceCategory->numOfProducts - 1; i++) {
        sourceCategory->Products[i] = sourceCategory->Products[i + 1];
    }
    sourceCategory->numOfProducts--;
    sourceCategory->Products = realloc(sourceCategory->Products, sourceCategory->numOfProducts * sizeof(product));

    printf("Product moved successfully.\n");

}

void FreeMemory(store *superMarket)
{
    for (int i = 0; i < superMarket->numOfCategories; i++)
    {
        free(superMarket->categories[i].Products);
    }
    free(superMarket->categories);
}

int main()
{
    int selectedOption = 1;
    int choice=0;
    store mystore;
    Initialize(&mystore);

    while (choice != 6)
    {
        displayMenu(selectedOption);

        char ch = getch();
        if (ch == -32)
        {
            ch = getch();
            if (ch == 72)
            {
                selectedOption--;
                if (selectedOption < 1)
                    selectedOption = 6;
            }
            else if (ch == 80)
            {
                selectedOption++;
                if (selectedOption > 6)
                    selectedOption = 1;
            }
        }
        else if (ch == 13)
        {
            choice=selectedOption;
            switch (choice)
            {
            case 1:
                system("cls");
                printf("--------------ADD CATEGORY----------------\n");
                AddCategory(&mystore);
                break;
            case 2:
                system("cls");
                printf("--------------ADD PRODUCT----------------\n");
                AddProduct(&mystore);
                break;
            case 3:
                system("cls");
                printf("--------------SELL PRODUCT----------------\n");
                SellProduct(&mystore);
                break;
            case 4:
                system("cls");
                printf("--------------MOVE PRODUCT----------------\n");
                MoveProduct(&mystore);
                break;
            case 5:
                system("cls");
                printf("--------------DISPLAY CATEGORIES----------------\n");
                Display(&mystore);
                break;
            case 6:
                system("cls");
                printf("--------------EXIT----------------\n");
                break;
            }
            system("pause");
        }
    }

    FreeMemory(&mystore);
    return 0;
}
