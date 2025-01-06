#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "function.h"
#include "datatype.h" 
 //run this program using the console pauser or add your own getch, system("pause") or input loop 


int main(int argc, char *argv[]) {
    int choice;
    int a = 0;
	int n = 0;
	saveAdminCredentials("admin", "12345");
	checkLogin();
  
    do {
    	system("cls"); 
        displayMenu();
        scanf("%d", &choice);
        getchar(); 
          
        switch (choice) {
            case 1: {
            	system("cls"); 
            	displayMenuCategory(&n);
                
        	    break;
            }
            case 2: {
            	system("cls"); 
                displayMenuProduct(&a);
        	    break;
            }
           
            case 0: {                
                printf("Exiting the program...\n");
                break;
            }
            default: {
                printf("Lua chon khong hop le vui long thu lai.\n");
                break;
            }
        }
    } while (choice != 0);
    
    return 0;
}



