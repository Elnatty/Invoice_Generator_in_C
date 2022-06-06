//#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

// billgenerator fuction
void generateBillHeader (char name[50], char date[30]){
  printf("\n\n\n\n");
    printf("\t    Invoice Generator");
    printf("\n\t  -----------------------");
    printf("\n");
    printf("\nDate: %s", date);
    printf("\nInvoice To %s", name);
    printf("\n");
    printf("------------------------------------------\n");
    printf("Items\t\t");
    printf("Qty\t\t");
    printf("Total\t\t");
    printf("\n------------------------------------------");
    printf("\n\n");   
}
// function for billBody
void generateBillBody (char item[30], int qty, float price){
  printf("%s\t\t", item);
    printf("%d\t\t", qty);
    printf("%.2f\t\t", qty * price);
    printf("\n");
}

// structure of user purchase details.
struct items{
  char item[20];
  float price;
  int qty;
};
struct orders{
  char customer[50];
  char date[50];
  int numOfItems;
  struct items itm[50];
};

// function to generate billfooter
void generateBillFooter (float total){
  printf("\n");
  float dis = 0.1 * total;
  float netTotal = total - dis;
  float cgst=0.09*netTotal, granfTotal=netTotal + 2*cgst;
  printf("------------------------------------------\n");
  printf("SubTotal\t\t\t%.2f", total);
  printf("\nDiscount @10%s\t\t\t%.2f", "%", dis);
  printf("\n\t\t\t\t----------");
  printf("\nNet Total\t\t\t%.2f", netTotal);
  printf("\nCGST @9%s\t\t\t%.2f", "%", cgst);
  printf("\nSGST @9%s\t\t\t%.2f", "%", cgst);
  printf("\n------------------------------------------");
  printf("\nGrand Total\t\t\t%.2f", granfTotal);
  printf("\n------------------------------------------\n");
}

int main(){
  // dashboard
  int opt, n;    // variable to store user preferred operation from line 54.  //variable for case3
  struct orders ord;   // for case 1 & 2 usecase
  struct orders order; // for case 3 usecase
  char saveBill = 'y', contFlag='y';
  char name[50]; // for case 3 (cus name variable)
  FILE *fp;
  while (contFlag == 'y'){
    float total = 0;
    int invoiceFound=0;
    system("clear");
    printf("\n\n================== DKING. Invoice Gen ==================\n");
    printf("\nplease select your preferred operation:\t");
    printf("\n\n1. Generate Invoice");
    printf("\n2. Show all Invoice");
    printf("\n3. Search Invoice");
    printf("\n4. Exit");
    printf("\n\nYour choice:\t");
    scanf("%d", &opt);
    fgetc(stdin);   // to remove the '\n' created by default by the scanf(line 69).

    switch (opt){
      case 1:
        system("clear");
        printf("\nPlease enter name of customer:\t");
        fgets(ord.customer, 50, stdin); //stores cus name, so first we initialize the struct order(line 63), then call the ord.customer to store the cus name.
        ord.customer[strlen(ord.customer)-1]=0; // to remove the "\n" fgets creates by default.
        strcpy(ord.date, __DATE__);
        printf("\nplease enter number of item:\t");
        scanf("%d", &n);
        ord.numOfItems = n;  // ord.numOfItems takes on the value of n.
        // for loop to take all "n" item.
        for (int i=0; i<n; i++){
          fgetc(stdin);
          printf("\n\n");
          printf("please enter the item %d:\t", i+1);
          fgets(ord.itm[i].item, 20, stdin);
          ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
          printf("please enter quantity:\t\t");   // storing qty into ord.itm[i]
          scanf("%d", &ord.itm[i].qty);
          printf("please enter the unit price:\t");
          scanf("%f", &ord.itm[i].price);
          total += ord.itm[i].qty * ord.itm[i].price;

        }

        generateBillHeader(ord.customer, ord.date);
        for (int i=0; i < ord.numOfItems;  i++){
          generateBillBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
        }
        generateBillFooter(total);

        printf("\nDO you want to save the invoice? [y/n]:\t");
        scanf("%s", &saveBill);
        if (saveBill == 'y'){
          fp = fopen("billGen.dat", "a+");  //the "a+" opens and appends data at the end of file.
          fwrite(&ord, sizeof(struct orders), 1, fp); //"&ord"-->pointer to the structure we want to store,  "sizeof(struct orders)"-->size of the structure, "1"-->how many instance of the order you want to save, "fp"-->file pointer.

          if (fwrite != 0)
            printf("\nsuccessfully saved...");
          else
            printf("\nerror, couldn't save..");
          fclose(fp);
        }
        break;

        case 2:
        system("clear");
        fp = fopen("billGen.dat", "r");
        printf("\n  *****Your Previous Invoices*****\n");
        while (fread(&ord, sizeof(struct orders), 1, fp)){// reading saved invoices
          float tot = 0;
          generateBillHeader(ord.customer, ord.date);
          for (int i=0; i<order.numOfItems; i++){
            generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
            tot += order.itm[i].qty * order.itm[i].price;
          }
          generateBillFooter(tot);
        }
        fclose(fp);
        break;

        case 3:
        printf("\nenter name of customer:\t");
        // fgetc(stdin);
        fgets(name, 50, stdin);
        name[strlen(name)-1] = 0;
        system("clear");
        fp = fopen("billGen.dat", "r");
        printf("\n  *****Invoice of %s*****\n", name);
        while (fread(&order, sizeof(struct orders), 1, fp)){// reading saved invoices
          float tot = 0;
          // compare the name if same with existing name in database.
          if (! strcmp(order.customer, name)){
            generateBillHeader(order.customer, order.date);
            for (int i=0; i<order.numOfItems; i++){
              generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
              tot += order.itm[i].qty * order.itm[i].price;
            }
          generateBillFooter(tot);
          invoiceFound = 1;
          }
        }
        if (! invoiceFound)
            printf("\n\nSorry, invoice for %s does not exists..\n\n", name);
        
        fclose(fp);
        break;

        case 4:
          system("clear");
          printf("\n\t\t Bye Bye :)\n\n");
          exit(0);
          break;

        default:
          system("clear");
          printf("\n\nSorry Invalid Option.. \n\n");
          break;
    }
    printf("\n\nDO you want to perform another Operation? [y/n]:\t");
    scanf("%s", &contFlag); 
  }
  printf("\n\t\t Bye Bye :)\n\n");
  printf("\n\n");

}