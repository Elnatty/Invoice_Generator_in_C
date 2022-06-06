#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

// billgenerator fuction
void generateBillHeader (char name[50], char date[30]){
  printf("\n\n");
    printf("\t    DKING. Invoice Gen");
    printf("\n\t  -------------------");
    printf("\n");
    printf("\nDate: %s", date);
    printf("\n");
    printf("------------------------------------------");
    printf("Items\t\t");
    printf("Qty\t\t");
    printf("Total\t\t");
    printf("--------------------------------------------");
    printf("\n\n");   
}
// function for billBody
void generateBillBody (char item[30], int qty, float price){
  printf("%s\t\t", item);
    printf("%d\t\t", qty);
    printf("%.2f\t\t", qty * price);
    printf("\n");
}
// function to generate billfooter
void generateBillFooter (float total){
  printf("\n");
  float dis = 0.1 * total;
  float netTotal = total - dis;
  float cgst=0.09*netTotal, granfTotal=netTotal + 2*cgst;
  printf("---------------------------------------\n");
  
}