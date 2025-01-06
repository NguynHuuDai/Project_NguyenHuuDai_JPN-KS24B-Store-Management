

#ifndef DATATYPE_H
#define DATATYPE_H

struct Date {
    int month;
    int day;
    int year;
};

struct Category {
    char CategoryId[50];    
    char CategoryName[50];  
};

struct Product {
    char productId[50];     
    char categoryId[50];     
    char productName[50];    
    int quantity;          
    int price;              
};


struct Order {
    char orderId[50];        
    char customerId[50];    
    struct Date date;       
    struct Product product;  
};

struct Category categories[50];
struct Product products[50]; 

struct AdminCredentials {
    char username[50];
    char password[50];
};
#endif 
























