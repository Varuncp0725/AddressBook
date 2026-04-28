#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"

int arr[100]={0};  
int search_status=0;

int getChoice()//check the given choice is correct or not
{
    int choice;
    char ch;
    if (scanf("%d%c", &choice, &ch) != 2 || ch != '\n')
    {
        while (getchar() != '\n'); // clears invalid input from buffer
        return -1;
    }
    return choice;
}

void listContacts(AddressBook *addressBook)///List the conatacts upto contact count
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

void initialize(AddressBook *addressBook)  //initialize contact count
{
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook); // loads saved contacts from file into addressBook
}

void print_contact(int sl, Contact contact){ // display matched contact with serial number
    printf("%-5d %-20s %-15s %-30s\n", sl+1, contact.name, contact.phone, contact.email);
}

int name_exist(AddressBook *addressBook, char name[]){// checks if name matches any existing contact
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].name, name) == 0) 
            return 1;
    }
    return 0;
}

int phone_exist(AddressBook *addressBook, char phone[]){// checks if phone matches any existing contact
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0) 
            return 1;
    }
    return 0;
}

int email_exist(AddressBook *addressBook, char email[]){// checks if email matches any existing contact
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].email, email) == 0) 
            return 1;
    }
    return 0;
}

int check_name(char name[])///validate name
{
    int i = 0;
    while (name[i] != '\0')
    {
        if (!((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z') || name[i] == ' '))
        {
            printf("Name should contain only alphabets\n");
            return 0; 
        }
        i++;
        
    }
    if(i<4){
    printf("Name must contain at least 4 characters\n");
    return 0;
    }
    return 1;
}

int check_phone(char phone[]){///validate phone number
    
    int i=1;
    while(phone[i]!='\0'){
        if(!(phone[i]>='0' && phone[i]<='9')){
            printf("Symbols and alphabets are not allowed in phone number\n");
            return 0; 
        }
        i++;
    }
    if(phone[0]<'6' || phone[0]>'9'){
        printf("First digit must be between 6 and 9\n");
        return 0; 
    }
    if(i==10)
        return 1; 
     else
     printf("Phone number must contain exactly 10 digits\n");

    return 0;
}

int check_email(char email[]) { // validate email
    int i = 0;
    int count = 0;
    int at_pos = -1;
    int dot_pos = -1;
    int len = strlen(email);

    while (email[i] != '\0') {
        if (email[i] >= 'A' && email[i] <= 'Z') {
            printf("Invalid: uppercase letters not allowed\n");
            return 0;
        }else if (email[i] == ' ') {
            printf("Invalid: spaces not allowed\n");
            return 0;
        }
        if (email[i] == '@') {
            count++;
            at_pos = i; 
        } else if (email[i] == '.') {
            dot_pos = i; 
        } else if (!((email[i] >= 'a' && email[i] <= 'z') || 
                     (email[i] >= '0' && email[i] <= '9'))) {
            printf("Invalid: only letters, digits, @ and . are allowed\n"); 
            return 0;
        }
        i++;
    }

    if (count == 0) {
        printf("Invalid: missing @\n");
        return 0;
    }else if (count > 1) {
        printf("Invalid: multiple @ symbols not allowed\n"); 
        return 0;
    }

    if (dot_pos == -1) {
        printf("Invalid: missing dot\n");
        return 0;
    }else if (dot_pos == at_pos + 1) {
        printf("Invalid: no character between @ and dot\n"); 
        return 0;
    }

    if (strcmp(&email[len - 4], ".com") != 0) {
        printf("Invalid: no extra characters after domain.com\n"); 
        return 0;
    }else if (at_pos == 0) {
        printf("Invalid: missing characters before @\n");
        return 0;
    }
    
    int domain_dot = -1;
    for(int j = at_pos + 1; j < len; j++){
    if(email[j] == '.'){
        domain_dot = j;
        break; 
    }   
    }

    for(int j = at_pos + 1; j < domain_dot; j++){
    if(!(email[j] >= 'a' && email[j] <= 'z')){
        printf("Invalid: only alphabets allowed in domain name\n");
        return 0;
    }   
    }
    return 1;
    }

void createContact(AddressBook *addressBook) // takes input and adds new contact to addressBook
{
    Contact newcontact;
    int count = 0;

    while (count < 3)
    {
        printf("Enter name: ");
        scanf(" %[^\n]",newcontact.name);
        if (check_name(newcontact.name)) // validates name has only letters and spaces
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
        printf("Too many attempts! try again\n");
        return;
    }

    count=0;
    while (count < 3)
    {
        printf("Enter Phone Number: ");
        scanf(" %s",newcontact.phone);
        if(check_phone(newcontact.phone)) // validates phone format
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
        printf("Too many attempts! try again\n");
        return;
    }
    if(phone_exist(addressBook,newcontact.phone)) // checks for duplicate phone
    {
        printf("Phone Number already exists!\n");
        return;
    }

    count=0;
    while (count < 3)
    {
        printf("Enter Email: ");
        scanf(" %s", newcontact.email);
        if(check_email(newcontact.email)) // validates email format
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
        printf("Too many attempts! try again\n");
        return;
    }
    if(email_exist(addressBook,newcontact.email)) // checks for duplicate email
    {
        printf("Email already exists!\n");
        return;
    }

    addressBook->contacts[addressBook->contactCount]=newcontact;
    addressBook->contactCount++;
    printf("Contact Created Successfully!\n");
    return;
}

void searchbyName(AddressBook *addressBook){   //search by name
    char name[50];
    printf("Enter name to search: ");
    scanf(" %[^\n]",name);

    search_status=0; 

    if(check_name(name)==0){ // validates name input
        printf("Invalid Name!\n");
        return; 
    }
    if(name_exist(addressBook,name)==0){ // checks if name exists in address book
        printf("Contact not found!\n");
        return; 
    }

    printf("\n========================= Address Book =======================\n");
    printf("%-5s %-20s %-15s %-30s\n", "Sl.No", "Name", "Phone", "Email");
    printf("\n");

    for(int j=0;j<100;j++)
        arr[j]=0; 

    for(int i=0;i<addressBook->contactCount;i++){
        if(strcmp(addressBook->contacts[i].name,name)==0){
            arr[search_status]=i; 
            print_contact(search_status,addressBook->contacts[i]); // display matched contact with serial number
            search_status++; 
        }
    }
    return;
}

void searchbyPhone(AddressBook *addressBook){//search by phone number
    char number[20];
    printf("Enter Phone number to search: ");
    scanf(" %s",number);

    search_status=0;

    if(check_phone(number)==0){ // validates phone input
        printf("Invalid Phone Number!\n");
        return; 
    }
    if(phone_exist(addressBook,number)==0){ // checks if phone exists in address book
        printf("Contact not found!\n");
        return; 
    }

    printf("\n========================= Address Book =======================\n");
    printf("%-5s %-20s %-15s %-30s\n", "Sl.No", "Name", "Phone", "Email");
    printf("\n");

    for(int j=0;j<100;j++)
        arr[j]=0; 

    for(int i=0;i<addressBook->contactCount;i++){
        if(strcmp(addressBook->contacts[i].phone,number)==0){
            arr[search_status]=i; 
            print_contact(search_status,addressBook->contacts[i]); // display matched contact with serial number
            search_status++; 
            return;
        }
    }
}

void searchbyEmail(AddressBook *addressBook){///serach by email
    char email[50];
    printf("Enter Email to search: ");
    scanf(" %s",email);

    search_status=0; 

    if(check_email(email)==0){ // validates email input
        printf("Invalid Email!\n");
        return; 
    }
    if(email_exist(addressBook,email)==0){ // checks if email exists in address book
        printf("Contact not found!\n");
        return; 
    }

    printf("\n========================= Address Book =======================\n");
    printf("%-5s %-20s %-15s %-30s\n", "Sl.No", "Name", "Phone", "Email");
    printf("\n");

    for(int j=0;j<100;j++)
        arr[j]=0; // reset index array before storing new search results

    for(int i=0;i<addressBook->contactCount;i++){
        if(strcmp(addressBook->contacts[i].email,email)==0){
            arr[search_status]=i;
            print_contact(search_status,addressBook->contacts[i]); // display matched contact with serial number
            search_status++;
            return;
        }
    }
}

void searchContact(AddressBook *addressBook) // searches contact by name, phone or email
{
    int choice;
    printf("\nSearch by:\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("4. Exit\n");
    printf("Enter choice: ");
    choice = getChoice();
    if(choice == -1){
        printf("Invalid input. Please enter a number(1-4).\n");
        search_status=0; 
        return;
    }
    switch(choice){
        case 1: searchbyName(addressBook);  // search contact using name
                break;
        case 2: searchbyPhone(addressBook); // search contact using phone number
                break;
        case 3: searchbyEmail(addressBook); // search contact using email
                break;
        case 4:
                search_status=0; 
                return;
        default:
                printf("Invalid choice!\n");
                search_status=0;
                return;
    }
    return;
}

void editContact(AddressBook *addressBook) // searches and updates name, phone or email of a contact
{
    int sl_num,select,count=0;

    searchContact(addressBook); // search and display matching contacts
    if(search_status==0){
        return; 
    }

    printf("\n");
    printf("Enter Serial Number to Edit: ");
    scanf(" %d",&sl_num);
    if(sl_num < 1 || sl_num > search_status){
        printf("Invalid serial number!\n");
        return;
    }

    printf("\n");
    printf("Select any one to edit\n");
    printf("1. Edit by Name\n");
    printf("2. Edit by Phone\n");
    printf("3. Edit by Email\n");
    printf("4. Exit\n");
    printf("Select : ");
    select = getChoice();
    if(select == -1){
        printf("Invalid input. Please enter a number(1-4).\n");
        return;
    }
    switch(select){
    case 1:
        count=0;
        while (count < 3){
            char name[50];
            printf("Enter name: ");
            scanf(" %[^\n]",name);
            if (check_name(name) == 1) // validates new name
            {
                strcpy(addressBook->contacts[arr[sl_num-1]].name,name); // updates name at correct contact index
                printf("Contact Name Updated Successfully!\n");
                return;
            }
            else
            {
                printf("Invalid Name!\n");
                count++;
            }
        }
        if(count==3){
            printf("Too many attempts! try again\n");
            return;
        }
        break;

    case 2:
        count=0;
        while (count < 3){
            char phone[20];
            printf("Enter phone Number: ");
            scanf(" %s",phone);
            if (check_phone(phone) == 1) // validates new phone number
            {
                if(phone_exist(addressBook,phone)){ // checks for duplicate phone
                    printf("Phone Number already exists!\n");
                    return;
                }else{
                    strcpy(addressBook->contacts[arr[sl_num-1]].phone,phone); // updates phone at correct contact index
                    printf("Contact Phone Number Updated Successfully!\n");
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
            printf("Too many attempts! try again\n");
            return;
        }
        break;

    case 3:
        count=0;
        while (count < 3){
            char email[50];
            printf("Enter Email: ");
            scanf(" %s",email);
            if (check_email(email) == 1) // validates new email
            {
                if(email_exist(addressBook,email)){ // checks for duplicate email
                    printf("Email already exists!\n");
                    return;
                }else{
                    strcpy(addressBook->contacts[arr[sl_num-1]].email,email); // updates email at correct contact index
                    printf("Contact Email Updated Successfully!\n");
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
            printf("Too many attempts! try again\n");
            return;
        }
        break;

    case 4:
        return;

    default:
        printf("Invalid Choice!\n");
        break;
    }
    return;
}

void deleteContact(AddressBook *addressBook) // searches and removes a contact from addressBook
{
    int sl_num,index;

    searchContact(addressBook); // search and display matching contacts
    if(search_status==0){
        return; 
    }

    printf("\n");
    printf("Enter serial number to delete: ");
    scanf(" %d",&sl_num);
    if(sl_num < 1 || sl_num > search_status){
        printf("Invalid serial number!\n");
        return;
    }
    printf("Are you sure you want to delete? (y/n): ");
    char confirm;
    scanf(" %c", &confirm);
    if(confirm != 'y' && confirm != 'Y'){
    printf("Deletion cancelled!\n");
    return;
    }

    index = arr[sl_num-1]; 

    for(int i = index; i < addressBook->contactCount - 1; i++){
        addressBook->contacts[i] = addressBook->contacts[i+1]; 
    }
    addressBook->contactCount--;
    printf("Contact Deleted Successfully!\n\n");
    return;
}