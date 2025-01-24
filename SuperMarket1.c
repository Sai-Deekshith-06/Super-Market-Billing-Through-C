/*
Super maeket billing management system usuing dll
*/
#include<stdio.h>   //printf(), scanf(), sizeof(),...
#include<stdlib.h>  //system(), malloc()
#include<string.h>  //strcpy(),
#include<conio.h>   //getch(),
#include<ctype.h>   //toupper(),

#define file "SM_data.txt"  //name of file, which contains the data of items in the store
#define sfile "sales.txt"   //name the file, which stores the paid bills 

struct itemDetails {
    int itemCode;
    char name[20];
    float mrp;
    float discount;
};

struct bill {
    int quantity;
    float amt;
    struct itemDetails item;
    struct bill *prev;
    struct bill *next;    
}*head,*tail;

char ch;

//1
void cartOperationsMenu();                      //displays a menu to insert/delete/display items of a cart
void addItemToCart();                           //inserts given item into the cart
int getItemDetailsFromFile(struct bill *node);  //to get the details of given serial no.
void removeItemFromCart();                      //to remove an item from the cart
void showItemNamesInBill();                     //to display all the items {s.no./name/amt}
void updateItemQuantity();                      //to edit the quantity of an item
//2
void displayBillDetails();                      //to display the bill
void finalizeBill(char *empName);                            //to finalize the bill
//4
int password();
void Newpassword();
void itemDatabaseMenu();                        //displays a menu to manage the data base which consists a list of items
void insertItemInDatabase();                    //to insert a new item in to the data base
void displayItemDatabase();                     //to display all the items in the data base
//5
void help();
void clearBillList();                           //to free the memory provided to dll, which stores the details of item


int main()
{
    char employName[50];
    char choice;
    printf("===========================Welcome===========================\n");
    printf("Enter your Name: ");
    scanf(" %[^\n]",employName);
    printf("Press any key to contiue...");
    _getch();
    menu:
    system("cls");
    printf("---------------------------Billing---------------------------\n");
    printf("1.Insert items\n2.Display Bill\n3.Cancel Bill\n4.Edit Items in Data base\n5.Help\n");
    printf("-------------------------------------------------------------\n");
    choice = getch();
    // scanf("%c",&choice);
    switch(choice){
        case '0':   clearBillList();
                    goto end;
        case '1':   cartOperationsMenu();       goto menu;
        case '2':   displayBillDetails();
        case '.':   finalizeBill(employName);   goto menu;
        case '3':   clearBillList();
                    goto cancel;
        case '4':   itemDatabaseMenu();         goto menu;
        case '5':   help();                     goto menu;
        default:    goto menu;
    }
    end:
    return 0;
    cancel:
    return 1;
}

void help(){
    printf("1.Billing Menu\n");
    printf("\t->Insert items: Add items to the shopping cart\n");
    printf("\t->Display Bill: View the current bill details\n");
    printf("\t->Cancel Bill: Clear the current bill\n");
    printf("\t->Edit Items in Database: Manage the database of available items\n");
    printf("2.Cart Menu\n");
    printf("\t->Add item: Insert a new item into the cart\n");
    printf("\t->Remove item: Delete an item from the cart\n");
    printf("\t->Edit Quantity: Change the quantity of an item in the cart\n");
    printf("\t->Back: Return to the main menu\n");
    printf("3.Database Menu\n");
    printf("\t->Insert item: Add a new item to the database\n");
    printf("\t->Display Database: View the list of all items in the database\n");
    printf("\t->Back: Return to the main menu\n");
    printf("4.Helpful Tips\n");
    printf("\t->Enter '0' or the provided key to exit the current menu\n");
    printf("\t->Enter '0' as the item code if an operation was selected by mistake\n");
    printf("\t->The bill is finalized when the total amount is displayed and the user confirms payment\n");
    printf("\t->Enter '.' in main menu to directly finallize the bill without displaying it.\n");
    printf("\t->Use the number keys to select menu options\n\n");
    printf("Press any key to continue...");
    ch=getch();
}

void clearBillList(){
    struct bill *temp;
    temp=head;
    if(head!=NULL){
        while(temp->next!=NULL){
            temp=temp->next;
            free(temp->prev);
        }
        free(temp);
        head=NULL;
        tail=NULL;
        printf("Memory freed\n");
    }
}


void itemDatabaseMenu()
{
    char choice;
    int attempts=3;
    // FILE *f1;
    // // f1 = fopen("Encrypted.bin", "wb");
    // f1 = fopen("Encryption.dat","wb");
    // char pass[] = "12345678";
    // fwrite(pass, strlen(pass), 1, f1);
    // fclose(f1);
    pass:
    if(attempts>0 && password())
    {   
        menu:
        system("cls");
        printf("---------------------------Data-Base---------------------------\n");
        printf("1.Insert item\n2.Display Database\n3.Back to Main Menu\n");
        // printf("1.Insert item\n2.Display File\n3.Back\n4.Remove item\n5.Edit item\n");
        printf("---------------------------------------------------------------\n");
        choice = getch();
        // scanf("%c",&choice);

        switch(choice)
        {
            case '0':
            case '3':   return;
            case '1':   insertItemInDatabase();  goto menu;
            case '2':   displayItemDatabase();   goto menu;
            case '4':   Newpassword();           goto menu;
            // case '4':   removeItem_file();  goto menu;
            // case '5':   editItem_file();    goto menu;
            default:    goto menu;
        }
    }else if(attempts>-10){
        printf("\nIncorrect Password, %d attempts left\n",--attempts);
        goto pass;
    }
    _getch();
}
void insertItemInDatabase()
{
    FILE *f1;
    f1 = fopen(file,"a+");
    struct bill new;

    printf("Enter the details:-\nName: ");
    scanf(" %[^\n]",new.item.name);
    fflush(stdin);
    printf("Code: ");
    scanf("%d",&new.item.itemCode);
    printf("M.R.P: ");
    scanf("%f",&new.item.mrp);
    printf("Discount: ");
    scanf("%f",&new.item.discount);

    fprintf(f1,"%d %.2f %.2f %s\n",new.item.itemCode,new.item.mrp,new.item.discount,new.item.name);
    fclose(f1);
}

void displayItemDatabase()
{
    FILE *f1;
    f1 = fopen(file,"r");
    if(f1==NULL){
        printf("Error in opening File\n");
        return;
    }
    
    struct bill temp;
    printf("S.no.\tName                 M.R.P      Discount\n");
    while(fscanf(f1,"%d %f %f %[^\n]s\n",&temp.item.itemCode,&temp.item.mrp,&temp.item.discount,temp.item.name)!=EOF)
    { 
        printf("%d\t",temp.item.itemCode);
        for(int i=printf("%s",temp.item.name);i<21;i++)
            printf(" ");
        printf("%.2f\t%.2f\n",temp.item.mrp,temp.item.discount);
    }
    printf("Press any key to continue...\n");
    ch=getch();
    // scanf("%c",&ch);
    fclose(f1);
}

void cartOperationsMenu()
{
    char choice;
    menu:
    system("cls");
    printf("----------------------------Cart----------------------------\n");
    printf("1.Add item\n2.Remove item\n3.Edit Quantity\n4.Back to Main Menu\n");
    printf("------------------------------------------------------------\n");
    choice = getch();
    // scanf("%c",&choice);

    switch(choice){
        case '1':   addItemToCart();        goto menu;
        case '2':   removeItemFromCart();   goto menu;
        case '3':   updateItemQuantity();   goto menu;
        case '0':   
        case '4':   return;
        default:    goto menu;
    }
}

void addItemToCart()
{
    struct bill *nn;
    nn = (struct bill*)malloc(sizeof(struct bill));
    if(nn==NULL){
        printf("Memory not allocated\n");
        return;
    }
    nn->next=NULL;
    nn->prev=tail;
    re_enter:
    printf("Item Code: ");
    scanf("%d",&nn->item.itemCode);
    if(!nn->item.itemCode)
        return;
    int val = getItemDetailsFromFile(nn);
    if(val==-1){
        free(nn);
        return;
    }else if(!val)
        goto re_enter;
    printf("Name: %s\nM.R.P: %.2f\nDiscount: %.2f\nQuantity: ",nn->item.name,nn->item.mrp,nn->item.discount);
    scanf("%d",&nn->quantity);
    if(!nn->quantity){
        free(nn);
        return;
    }
    nn->amt = nn->item.mrp*(1-nn->item.discount/100)*nn->quantity;

    if(head==NULL){
        head=nn;
        tail=nn;
    }else{
        tail->next=nn;
        tail=nn;
    }
}

int getItemDetailsFromFile(struct bill *node)
{
    FILE *f1;
    f1 = fopen(file,"r");
    if(f1==NULL){
        printf("Error in opening File\n");
        return -1;
    }
    struct bill *temp=(struct bill*)malloc(sizeof(struct bill));
    while(fscanf(f1,"%d %f %f %[^\n]s\n",&temp->item.itemCode,&temp->item.mrp,&temp->item.discount,temp->item.name)!=EOF)
    {
        if(node->item.itemCode==temp->item.itemCode)
        {
            strcpy(node->item.name, temp->item.name);
            node->item.mrp= temp->item.mrp;
            node->item.discount= temp->item.discount;
            printf("\n");
            fclose(f1);
            return 1;
        } 
    }
    printf("\n");
    printf("Item not found\n");
    ch=getch();
    // scanf("%c", &ch);
    fclose(f1);
    return 0;
}

void removeItemFromCart() {
    if (head == NULL) {
        printf("Cart is Empty\n");
        printf("Press any key to continue...\n");
        ch=getch();
        // scanf("%c", &ch);
        return;
    }
    int num;
    showItemNamesInBill();
    printf("Remove the item from list:-\nItem code: ");
    scanf("%d", &num);
    if(!num){
        return;
    }
    struct bill *temp = head;
    while (temp != NULL) {
        if (num == temp->item.itemCode) {
            if (temp == head) {
                head = temp->next;
            } else {
                temp->prev->next = temp->next;
            }
            if (temp == tail) {
                tail = temp->prev;
            } else {
                temp->next->prev = temp->prev;
            }
            free(temp);
            printf("Item removed from list\n");
            return;
        }
        temp = temp->next;
    }
    printf("Incorrect Item Code\n");
    printf("Press any key to continue...\n");
    ch=getch();
    // scanf("%c", &ch);
}

void displayBillDetails() {
    if(head==NULL){
        // printf("Cart is Empty\n");
        return;
    }
    struct bill *temp;
    temp=head;
    printf("S.no.\tName                 M.R.P   \tDiscount\tAmount\tQuantity\n");
    while(temp!=NULL)
    {
        printf("%d\t",temp->item.itemCode);
        for(int i=printf("%s",temp->item.name);i<21;i++)
            printf(" ");
        printf("%.2f\t%.2f %%\t\t%.2f\t%d\n",temp->item.mrp,temp->item.discount,temp->amt,temp->quantity);
        temp=temp->next;
    }
     
    // printf("Press any key to continue...\n");
    // ch=getch();
    // scanf("%c", &ch);
    return;
}

void updateItemQuantity(){
    if(head==NULL){
        printf("Cart is Empty\n");
        printf("Press any key to continue...\n");
        getch();
        return;
    }
    struct bill *temp;
    temp=head;
    displayBillDetails();
    int num;
    printf("Item Code: ");
    scanf("%d",&num);
    if(!num){
        printf("Press any key to continue...\n");
        getch();
        return;
    }
    while(temp!=NULL){
        if(temp->item.itemCode==num)
        {
            printf("New Quantity: ");
            scanf("%d",&temp->quantity);
            if(!temp->quantity){
                free(temp);
            }
            return;
        }
    }
    printf("Incorrect Item Code\n");
    printf("Press any key to continue...\n");
    ch=getch();
    // scanf(" %c",&ch);
}

void showItemNamesInBill()
{   
    if(head==NULL){
        printf("Cart is Empty\n");
        return;
    }
    struct bill *temp;  
    temp=head;
    printf("S no.\tName                    Amount\n");
    while(temp!=NULL){
        printf("%d\t",temp->item.itemCode);
        for(int i=printf("%s",temp->item.name);i<21;i++)
            printf(" ");
        printf("%.2f\n",temp->amt);
        temp=temp->next;
    }
     
    printf("Press any key to continue...\n");
    ch=getch();
    // scanf(" %c",&ch);
}

void finalizeBill(char *empName){
     
    if(head==NULL){
        printf("Cart is Empty\n");
        printf("Press any key to continue...\n");
        ch=getch();
        // scanf(" %c",&ch);
        return;
    }
    struct bill *temp;
    temp=head;
    float total=0;
    while(temp!=NULL){
        total+=temp->amt;
        temp=temp->next;
    }
    char status[4];
    printf("Total amount = %.2f\n",total);
    printf("Bill is paid(YES/NO): ");
    scanf(" %s",status);
    for(int i=0; status[i]!='\0' ;i++){
        status[i] = toupper(status[i]);
    }
    printf("%s\n",status);

    //to store the bill:-
    if(strcmp(status,"YES")==0)
    {
        FILE *f1;
        f1 = fopen(sfile,"a");
        struct bill *temp;
        temp=head;
        fprintf(f1,"S.no.\tName                 M.R.P   \tDiscount\tAmount\tQuantity\n");
        while(temp!=NULL)
        {
            fprintf(f1,"%d\t\t",temp->item.itemCode);
            for(int i=fprintf(f1,"%s",temp->item.name);i<21;i++)
                fprintf(f1," ");
            fprintf(f1,"%.2f\t\t%.2f %%\t\t%.2f\t  %d\n",temp->item.mrp,temp->item.discount,temp->amt,temp->quantity);
            temp=temp->next;
        }
        fprintf(f1,"\n\t->\tTotal amount = %.2f",total);
        fprintf(f1,"\n\t->\tBilled by \"%s\"\n",empName);
        fprintf(f1,"<======--------------------------------------------------======>\n");
        fclose(f1);
        clearBillList();
        exit(0);
    }
}

void Newpassword() {
    char password[9];
    FILE *f1;

    // Open the file in binary write mode
    f1 = fopen("Encrypted.bin", "wb");
    if (f1 == NULL) {
        printf("Error opening file\n");
        return;
    }

    printf("Enter new password: ");
    for (int i = 0; i < 8; i++){
        password[i] = getch();
        printf("*");
    }
    // Write the password to the file
    fwrite(password, sizeof(password), 1, f1);

    fclose(f1);
    return;
}

int password() {
    char password[9], verify[9];
    FILE *f1;
    f1 = fopen("Encrypted.bin", "ab+");
    if(f1==NULL){
        printf("File Currupted\n");
        return 0;
    }
    fread(verify, sizeof(verify), 1, f1);
    // printf("%s\n",verify);
    // _getch();

    if(ftell(f1)==0){
        Newpassword();
        return 1;
    }
    fclose(f1);
    printf("Password: ");
    for (int i = 0; i < 8; i++){
        password[i] = getch();
        printf("*");
    }
    password[8]='\0';
    // printf("%d__%d\n",strlen(password),strcmp(verify, password));
    if (strcmp(verify, password) == 0)
        return 1;
    else
        return 0;
}