#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
int arr[100]={0};
int search_status=0;
// #include "populate.h"

void listContacts(AddressBook *addressBook)
{
    if(addressBook->contactCount == 0){
        printf("Address book is empty!\n");
        return;
    }
    printf("\n========================= Address Book =======================\n");
    printf("\n");
    printf("%-10s %-20s %-20s %-30s\n", "Sl.No", "Name", "Phone", "Email");
    for(int i=0;i<addressBook->contactCount;i++){
        printf("%-10d %-20s %-20s %-30s\n", i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    return;
}
void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);
}
// void saveAndExit(AddressBook *addressBook) {
//     saveContactsToFile(addressBook); // Save contacts to file
//     // exit(EXIT_SUCCESS); // Exit the program
// }

void print_contact(int sl,Contact contact){
printf("%-5d %-20s %-15s %-30s\n", sl+1, contact.name, contact.phone, contact.email);
}

int name_exist(AddressBook *addressBook,char name[]){
for (int i = 0; i < addressBook->contactCount; i++) {
    if (strcmp(addressBook->contacts[i].name,name) == 0) {   
        return 1;
    }
}
  return 0;
}
int phone_exist(AddressBook *addressBook,char phone[]){
for (int i = 0; i < addressBook->contactCount; i++) {
    if (strcmp(addressBook->contacts[i].phone,phone) == 0) {   
        return 1;
    }
}
  return 0;
}
int email_exist(AddressBook *addressBook,char email[]){
for (int i = 0; i < addressBook->contactCount; i++) {
    if (strcmp(addressBook->contacts[i].email,email) == 0) {   
        return 1;
    }
}
  return 0;
}

int check_name(char name[])
{
    int i = 0;
    while (name[i] != '\0')
    {
        if (!((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z') || name[i] == ' '))
        {
        return 0;
        }
    i++;
    }
return 1;
}
int check_phone(char phone[]){
    if(phone[0]<'6' || phone[0]>'9')
    return 0;

    int i=1;
    while(phone[i]!='\0'){
        if(!(phone[i]>='0'&& phone[i]<='9')){
            return 0;
        }
    i++;
    }
    if(i==10)
    return 1;

    return 0;

}
int check_email(char email[]){
    int i = 0;
    int count = 0;
    int pos=-1;

    if(email[0]>='0'&& email[0]<='9')
    return 0;
    int len=strlen(email);

    while (email[i] != '\0')
    {
        if (email[i] >= 'A' && email[i] <= 'Z' )
            return 0;
        
        if (email[i] == ' ')
           return 0;  

        if (email[i] == '@'){
            count++;
            pos = i;
        }

        i++;
    }
    if (count != 1)
        return 0;
    if(pos==-1|| pos>=len-5)
        return 0;

  if (strcmp(&email[len - 4], ".com") != 0)
    return 0;

    char *first = strstr(email, ".com");
    if (first == NULL)
        return 0;

    char *second = strstr(first + 1, ".com");
    if (second != NULL)
        return 0;

    return 1;
}

void createContact(AddressBook *addressBook)
{
    Contact newcontact;
    
    int count = 0;

    while (count < 3)
    {
        printf("Enter name: ");
        scanf(" %[^\n]",newcontact.name);
       
        if (check_name(newcontact.name))
        {
            break;
        }
        else
        {
            printf("Invalid Name!\n");
            count++;
        }
    }
    if(count==3){
        printf("Too many attempts! try again ");
        printf("\n");
        return;
    }
    // int ret1=name_exist(addressBook,newcontact.name);
    // if(ret1==0){
    //     printf("Name already exists!\n");
    //     return;
    // }

    count=0;
    while (count < 3)
    {
        printf("Enter Phone Number: ");
        scanf(" %s",newcontact.phone);
        if(check_phone(newcontact.phone))
        {
            break;
        }
        else
        {
            printf("Invalid Phone Number!\n");
            count++;
        }
    }
    if(count==3){
        printf("Too many attempts! try again");
        printf("\n");
        return;
    }
    if(phone_exist(addressBook,newcontact.phone))
    {
        printf("Phone Number already exists!\n");
        return;
    }
    count=0;
    while (count < 3)
    {
       printf("Enter Email: ");
       scanf(" %s", newcontact.email);
         if(check_email(newcontact.email))
        {
            break;
        }
        else
        {
            printf("Invalid Email id!\n");
            count++;
        }
    }
    if(count==3){
        printf("Too many attempts! try again ");
        printf("\n");
        return;
    }
    if(email_exist(addressBook,newcontact.email))
    {
        printf("Email already exists!\n");
        return;
    }
    addressBook->contacts[addressBook->contactCount]=newcontact;
    addressBook->contactCount++;
    printf("Contact Created Successfully!");
    printf("\n");
    return;
 }

void searchbyName(AddressBook *addressBook){
    char name[50];
    int sl=0;
    printf("Enter name to search: ");
    scanf(" %[^\n]",name);

    if(check_name(name)==0){
        printf("Invalid Name!\n");
        return;
    }
    if(name_exist(addressBook,name)==0){
    printf("Contact not found!\n");
    return;
    }
    printf("\n========================= Address Book =======================\n");
    printf("%-5s %-20s %-15s %-30s\n", "Sl.No", "Name", "Phone", "Email");
    printf("\n");
     for(int j = 0; j < 100; j++)
        arr[j] = 0;
    for(int i=0;i<addressBook->contactCount;i++){
        if(strcmp(addressBook->contacts[i].name,name)==0){ 
            arr[i]=i;
            print_contact(i,addressBook->contacts[i]); 
           
        }
    }
    return;
}
void searchbyPhone(AddressBook *addressBook){
    char number[20];
    int sl=0;
    printf("Enter Phone number to search: ");
    scanf(" %s",number);

    if(check_phone(number)==0){
        printf("Invalid Phone Number!\n");
        return;
    }
    if(phone_exist(addressBook,number)==0){
    printf("Contact not found!\n");
    return;
    }
    printf("\n========================= Address Book =======================\n");
    printf("%-5s %-20s %-15s %-30s\n", "Sl.No", "Name", "Phone", "Email");
    printf("\n");
     for(int j = 0; j < 100; j++)
        arr[j] = 0;
    for(int i=0;i<addressBook->contactCount;i++){
        if(strcmp(addressBook->contacts[i].phone,number)==0){
            arr[i]=i;
            print_contact(i,addressBook->contacts[i]);
          
            return;
        }
    }

}
void searchbyEmail(AddressBook *addressBook){
    char email[20];
    int sl=0;
    printf("Enter Email to search: ");
    scanf(" %s",email);

    if(check_email(email)==0){
        printf("Invalid Email!\n");
        return;
    }
    if(email_exist(addressBook,email)==0){
    printf("Contact not found!\n");
    return;
    }
    printf("\n========================= Address Book =======================\n");
    printf("%-5s %-20s %-15s %-30s\n", "Sl.No", "Name", "Phone", "Email");
    printf("\n");
     for(int j = 0; j < 100; j++)
        arr[j] = 0;
    for(int i=0;i<addressBook->contactCount;i++){
        if(strcmp(addressBook->contacts[i].email,email)==0){
            arr[i]=i;
            print_contact(i,addressBook->contacts[i]);
            return;
        }
    }
}

void searchContact(AddressBook *addressBook)
{
    int choice;
    printf("\nSearch by:\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("Enter choice: ");
    scanf(" %d",&choice);
    switch(choice){
        case 1: searchbyName(addressBook);
                search_status=1;
                break;
        case 2: searchbyPhone(addressBook);
                search_status=1;
                break;
        case 3: searchbyEmail(addressBook);
                search_status=1;
                break;
        default:
                printf("Invalid choice!\n");
                search_status=0;
                return;
    }
    return;
}


void editContact(AddressBook *addressBook)
{    
    search_status=0;
    int sl_num,select,count=0;
    searchContact(addressBook);
    if(search_status==0){
        return;
    }
    printf("\n");
    printf("Enter Serial Number to Edit: ");
    scanf(" %d",&sl_num);
    printf("\n");
    printf("Select any one to edit\n");
    printf("1. Edit by Name\n");
    printf("2. Edit by Phone\n");
    printf("3. Edit by Email\n");
    printf("4. Exit\n");
    printf("Select : ");
    scanf(" %d",&select);

    switch(select){
    case 1:
          count=0;
        while (count < 3){
         
        char name[30];
        printf("Enter name: ");
        scanf(" %[^\n]",name);
        if (check_name(name) == 1)
        {
            if(name_exist(addressBook,name)){
            printf("Name already exists!");
            return;
            }else{
                strcpy(addressBook->contacts[arr[sl_num-1]].name,name);
                printf("Contact Name Updated Successfully!");
                return;
            }
        }
        else
        {
            printf("Invalid Name!\n");
            count++;
        }
    }
    if(count==3){
        printf("Too many attempts! try again ");
        printf("\n");
        return;
    }
    break;
    
    case 2:
         count=0;
        while (count < 3){
            
        char phone[30];
        printf("Enter phone Number: ");
        scanf(" %s",phone);
        if (check_phone(phone) == 1)
        {
              if(phone_exist(addressBook,phone)){
              printf("Phone Number already exists!");
              return;
          }else{
                strcpy(addressBook->contacts[arr[sl_num-1]].phone,phone);
                printf("Contact Phone Number Updated Successfully!");
                return;
            }
        }
        else
        {
            printf("Invalid Phone Number!\n");
            count++;
        }
    }
    if(count==3){
        printf("Too many attempts! try again ");
        printf("\n");
        return;
    }
    break;
        
    case 3:
          count=0;
         while (count < 3){
           
        char email[30];
        printf("Enter Email: ");
        scanf(" %s",email);
        if (check_email(email) == 1 )
        {
           if(email_exist(addressBook,email)){
              printf("Email already exists!");
              return;
        }else{  
                strcpy(addressBook->contacts[arr[sl_num-1]].email,email);
                printf("Contact Email Updated Successfully!");
                return;
            }
        }
        else
        {
            printf("Invalid Email!\n");
            count++;
        }
    }
    if(count==3){
        printf("Too many attempts! try again ");
        printf("\n");
        return;
    }
    break;

    case 4:
          return;

    default:
          printf("Invalid Choice!");
          break;
        }
     return;
}

void deleteContact(AddressBook *addressBook)
{ 
    search_status=0;
    int sl_num;
    searchContact(addressBook);
    if(search_status==0){
        return;
    }
    printf("\n");
    printf("Enter serial number to delete: ");
    scanf("%d",&sl_num);
    int index = arr[sl_num-1];  
    for(int i = index; i < addressBook->contactCount - 1; i++){
        addressBook->contacts[i] = addressBook->contacts[i+1];
    }
    addressBook->contactCount--;
    printf("Contact Deleted Successfully!\n");
    printf("\n");
    return;
}
