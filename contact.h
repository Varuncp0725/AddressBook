#ifndef CONTACT_H
#define CONTACT_H


#define MAX_CONTACTS 100 

typedef struct {
    char name[50];  
    char phone[20];
    char email[50]; 
} Contact;


typedef struct {
    Contact contacts[100]; 
    int contactCount;      
} AddressBook;

int getChoice();  // reads and validates integer input from user
void createContact(AddressBook *addressBook);  // takes input and adds new contact to addressBook
void searchContact(AddressBook *addressBook);  // searches contact by name, phone or email
void editContact(AddressBook *addressBook);    // searches and updates name, phone or email of a contact
void deleteContact(AddressBook *addressBook);  // searches and removes a contact from addressBook
void listContacts(AddressBook *addressBook);   // displays all contacts in addressBook
void initialize(AddressBook *addressBook);     // loads saved contacts from file into addressBook
void saveContactsToFile(AddressBook *addressBook); // saves all contacts to file before exit

#endif