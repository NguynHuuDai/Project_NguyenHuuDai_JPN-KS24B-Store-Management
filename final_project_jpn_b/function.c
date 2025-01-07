// noi di trien khai cac ham 
#include <assert.h>
#include <stdio.h>   
#include <string.h>  
#include "datatype.h"  
#include "function.h"  




void displayMenu() {  
    printf("\n*** Store management system in C ***\n");  
    printf("\n");  
    printf("====================MENU===================\n");  
    printf(" [1] Chinh sua danh muc                \n");  
    printf(" [2] Chinh sua san pham    \n"); 
	printf(" [0] Thoat chuong trinh \n");               
    printf("===========================================\n\n");  
    printf("Nhap lua chon cua ban: ");  
}  	
void addCategory(struct Category categories[], int *n) {
	
    int num;
    FILE *file = fopen("Category.bin", "rb");

    if (file != NULL) {
        while (fread(&categories[*n], sizeof(struct Category), 1, file) == 1) {
            (*n)++;
        }
        fclose(file);
        printf("\n");
    } else {
        printf("Chua co danh muc nao trong file Category.bin.\n");
    }

    printf("Nhap so luong danh muc can them: ");
    scanf("%d", &num);
    getchar(); 

    if (num <= 0) {
        printf("So luong danh muc khong hop le. Vui long thu lai.\n");
        return;
    }

    for (int i = 0; i < num; i++) {
        char categoryId[50];
        int idExists;

        do {
            printf("Nhap ma danh muc %d: ", i + 1);
            fgets(categoryId, 50, stdin);
            categoryId[strcspn(categoryId, "\n")] = '\0'; 
            
            idExists = isCategoryIdExist(categories, *n, categoryId);
            if (idExists) {
                printf("ID danh muc %s da ton tai. Vui long nhap lai.\n", categoryId);
            }
        } while (idExists); 
        
        strcpy(categories[*n].CategoryId, categoryId);

        printf("Nhap ten danh muc %d: ", i + 1);
        fgets(categories[*n].CategoryName, 50, stdin);
        categories[*n].CategoryName[strcspn(categories[*n].CategoryName, "\n")] = '\0';

        (*n)++;
    }

    file = fopen("Category.bin", "wb");
    if (file == NULL) {
        printf("Khong the mo file de luu danh muc.\n");
        return;
    }

    fwrite(categories, sizeof(struct Category), *n, file);
    fclose(file);

    printf("Danh muc da duoc luu .\n");
    
    printf("Nhan phim bat ki de tiep tuc...\n");
    getchar(); 
    system("cls");
}
int isCategoryIdExist(struct Category categories[], int n, const char* id) {

    for (int i = 0; i < n; i++) {
        if (strcmp(categories[i].CategoryId, id) == 0) {
            return 1; 
        }
    }
    return 0;
}
void displayCategories(struct Category categories[], int *n) {
	
    FILE *file = fopen("Category.bin", "rb");
    if (file == NULL) {
        printf("Khong the mo file Category.bin.\n");
        return;
    }


    *n = 0;
    while (fread(&categories[*n], sizeof(struct Category), 1, file) == 1) {
        (*n)++;
    }
    fclose(file);

    printf("\nDanh sach danh muc:\n");
    printf("ID Danh Muc  | Ten Danh Muc\n");
    printf("=============================\n");

    for (int i = 0; i < *n; i++) {
        printf("%-12s | %-21s\n", categories[i].CategoryId, categories[i].CategoryName);
    }
    printf("=============================\n");
    printf("Nhan phim bat ki de tiep tuc...\n");
    getchar(); 
    system("cls");
}
void addProduct(struct Product products[], int *a) {
    int num;
    FILE *file;
    
    file = fopen("Category.bin", "rb");
    if (file == NULL) {
        printf("Khong the mo file Category.bin.\n");
        return;
    }
    
    struct Category categories[100];  
    int categoryCount = 0; 
    
    while (fread(&categories[categoryCount], sizeof(struct Category), 1, file) == 1) {
        categoryCount++;
    }
    fclose(file);
    
    if (categoryCount == 0) {
        printf("Khong co danh muc trong Category.bin. Vui long them danh muc truoc.\n");
        printf("Nhan phim bat ki de tiep tuc...\n");
	    getchar(); 
	    system("cls");
        return;
    }

    printf("Nhap so luong san pham can them: ");
    scanf("%d", &num);
    getchar();  

    if (num <= 0) {
        printf("So luong san pham khong hop le. Vui long thu lai.\n");
        return;
    }

    for (int i = 0; i < num; i++) {
        printf("Nhap ma san pham %d: ", i + 1);
        fgets(products[*a].productId, 50, stdin);
        products[*a].productId[strcspn(products[*a].productId, "\n")] = '\0'; 

        printf("Nhap ten san pham %d: ", i + 1);
        fgets(products[*a].productName, 50, stdin);
        products[*a].productName[strcspn(products[*a].productName, "\n")] = '\0'; 

        int validCategory = 0;
        while (!validCategory) {
            printf("Nhap ma danh muc san pham %d: ", i + 1);
            fgets(products[*a].categoryId, 50, stdin);
            products[*a].categoryId[strcspn(products[*a].categoryId, "\n")] = '\0'; 

            validCategory = 0;
            for (int j = 0; j < categoryCount; j++) {
                if (strcmp(products[*a].categoryId, categories[j].CategoryId) == 0) {
                    validCategory = 1;
                    break;
                }
            }

            if (!validCategory) {
                printf("Ma danh muc khong ton tai. Vui long nhap lai.\n");
            }
        }

        printf("Nhap gia san pham %d: ", i + 1);
        while (scanf("%d", &products[*a].price) != 1) {
            printf("Gia san pham khong hop le. Vui long nhap lai: ");
            while (getchar() != '\n'); 
        }

        printf("Nhap so luong san pham %d: ", i + 1);
        while (scanf("%d", &products[*a].quantity) != 1) {
            printf("So luong san pham khong hop le. Vui long nhap lai: ");
            while (getchar() != '\n');  
        }

        (*a)++; 
        getchar(); 
    }

    file = fopen("product.bin", "wb"); 
    if (file == NULL) {
        printf("Khong the mo file de luu san pham.\n");
        return;
    }

    fwrite(products, sizeof(struct Product), *a, file);
    fclose(file);

    printf("San pham da duoc luu\n");
    printf("Nhan phim bat ki de tiep tuc...\n");
    getchar(); 
    system("cls");  
}
void displayProducts(struct Product products[], int *a) {

    FILE *file = fopen("product.bin", "rb");
    if (file == NULL) {
        printf("Khong the mo file Product.bin.\n");
        return;
    }

    *a = 0;
    while (fread(&products[*a], sizeof(struct Product), 1, file) == 1) {
        (*a)++;
    }
    fclose(file);

     printf("\nDanh sach san pham:\n");
    printf("+--------------+-----------------------+--------------+---------+------------+\n");
    printf("| %-12s | %-21s | %-12s | %-7s | %-10s |\n", 
           "ID San Pham", "Ten San Pham", "Ma Danh Muc", "Gia", "So Luong");
    printf("+--------------+-----------------------+--------------+---------+------------+\n");

    for (int i = 0; i < *a; i++) {
        printf("| %-12s | %-21s | %-12s | %-7d | %-10d |\n", 
               products[i].productId, 
               products[i].productName, 
               products[i].categoryId, 
               products[i].price, 
               products[i].quantity);
    }
    printf("+--------------+-----------------------+--------------+---------+------------+\n");
    
    printf("Nhan phim bat ki de tiep tuc...\n");
    getchar(); 
    system("cls");
}
void editCategory(struct Category categories[], int *n) {

    FILE *file = fopen("Category.bin", "rb+");  
    if (file == NULL) {
        printf("Khong the mo file Category.bin.\n");
        return;
    }

    char idToEdit[50];
    int categoryFound = 0;

    printf("Nhap ID danh muc can sua: ");
    fgets(idToEdit, 50, stdin);
    idToEdit[strcspn(idToEdit, "\n")] = '\0';

    for (int i = 0; i < *n; i++) {
        if (strcmp(categories[i].CategoryId, idToEdit) == 0) {

            printf("Danh muc hien tai:\n");
            printf("ID: %-12s | Ten: %-20s\n", categories[i].CategoryId, categories[i].CategoryName);

            printf("Nhap ten danh muc moi: ");
            fgets(categories[i].CategoryName, 50, stdin);
            categories[i].CategoryName[strcspn(categories[i].CategoryName, "\n")] = '\0'; 

            fseek(file, i * sizeof(struct Category), SEEK_SET);  
            fwrite(&categories[i], sizeof(struct Category), 1, file); 

            printf("Danh muc da duoc sua thanh cong!\n");
            categoryFound = 1;
            break;
        }
    }

    if (!categoryFound) {
        printf("Khong tim thay danh muc voi ID '%s'.\n", idToEdit);
    }

    fclose(file);
    printf("Nhan phim bat ki de tiep tuc...\n");
    getchar(); 
    system("cls");
}
void deleteCategory(struct Category categories[], int *n) {
    FILE *file = fopen("Category.bin", "rb+"); 
    if (file == NULL) {
        printf("Khong the mo file Category.bin.\n");
        return;
    }

    char idToDelete[50];
    int categoryFound = 0;
    int categoryIndex = -1;

    printf("Nhap ID danh muc can xoa: ");
    fgets(idToDelete, 50, stdin);
    idToDelete[strcspn(idToDelete, "\n")] = '\0';  

    for (int i = 0; i < *n; i++) {
        if (strcmp(categories[i].CategoryId, idToDelete) == 0) {
            categoryFound = 1;
            categoryIndex = i;
            break;
        }
    }

    if (!categoryFound) {
        printf("Khong tim thay danh muc voi ID '%s'.\n", idToDelete);
        printf("Nhan phim bat ki de tiep tuc...\n");
    	getchar(); 
  	    system("cls");
        fclose(file);
        return;
    }

    printf("Danh muc hien tai:\n");
    printf("ID: %-12s | Ten: %-20s\n", categories[categoryIndex].CategoryId, categories[categoryIndex].CategoryName);
    printf("Ban co chac chan muon xoa danh muc nay? (y/n): ");

    char confirm;
    scanf(" %c", &confirm);
    getchar(); 

    if (confirm == 'y' || confirm == 'Y') {

        for (int i = categoryIndex; i < *n - 1; i++) {
            categories[i] = categories[i + 1]; 
        }

        (*n)--;  
        fseek(file, 0, SEEK_SET);  
   
        fwrite(categories, sizeof(struct Category), *n, file);  

        fflush(file);
        ftruncate(fileno(file), *n * sizeof(struct Category));

        printf("Danh muc da duoc xoa thanh cong!\n");
    } else {
        printf("Huy xoa danh muc.\n");
    }

    fclose(file);
    printf("Nhan phim bat ki de tiep tuc...\n");
    getchar(); 
    system("cls");
}
void sortCategories() {
    FILE *categoryFile = fopen("Category.bin", "rb+");
    if (categoryFile == NULL) {
        printf("Khong the mo file Category.bin.\n");
        return;
    }

    fseek(categoryFile, 0, SEEK_END);
    long fileSize = ftell(categoryFile);
    rewind(categoryFile);
    
    int numCategories = fileSize / sizeof(struct Category);
    struct Category categories[numCategories];
    
    for (int i = 0; i < numCategories; i++) {
        fread(&categories[i], sizeof(struct Category), 1, categoryFile);
    }

    
    printf("\nChon thu tu sap xep danh muc:\n");
    printf("1. Sap xep tang dan (A-Z)\n");
    printf("2. Sap xep giam dan (Z-A)\n");
    printf("Nhap lua chon cua ban (1/2): ");
    int choice;
    scanf("%d", &choice);
    getchar();  

    
    if (choice == 1) {
        
        for (int i = 0; i < numCategories - 1; i++) {
            for (int j = i + 1; j < numCategories; j++) {
                if (strcmp(categories[i].CategoryName, categories[j].CategoryName) > 0) {
                  
                    struct Category temp = categories[i];
                    categories[i] = categories[j];
                    categories[j] = temp;
                }
            }
        }
    } else if (choice == 2) {

        for (int i = 0; i < numCategories - 1; i++) {
            for (int j = i + 1; j < numCategories; j++) {
                if (strcmp(categories[i].CategoryName, categories[j].CategoryName) < 0) {
                   
                    struct Category temp = categories[i];
                    categories[i] = categories[j];
                    categories[j] = temp;
                }
            }
        }
    } else {
        printf("Lua chon khong hop le!\n");
        fclose(categoryFile);
        return;
    }

    fseek(categoryFile, 0, SEEK_SET);
    for (int i = 0; i < numCategories; i++) {
        fwrite(&categories[i], sizeof(struct Category), 1, categoryFile);
    }

    printf("\nDanh sach danh muc sau khi sap xep:\n");
    printf("--------------- -----------------------------------------------------------------\n");
    printf("ID Danh Muc   | Ten Danh Muc\n");
    printf("---------------------------------------------------------------------------------\n");

    for (int i = 0; i < numCategories; i++) {
        printf("%-15s | %-50s\n", categories[i].CategoryId, categories[i].CategoryName);
    }

    fclose(categoryFile);
    printf("Nhan phim bat ki de tiep tuc...\n");
    getchar(); 
    system("cls");
}
void searchCategory() {
    FILE *categoryFile = fopen("Category.bin", "rb");
    if (categoryFile == NULL) {
        printf("Khong the mo file Category.bin.\n");
        return;
    }

    char searchName[50];
    int found = 0;

    printf("Nhap ten danh muc can tim: ");
    fgets(searchName, 50, stdin);
    searchName[strcspn(searchName, "\n")] = '\0';  

    printf("\nDanh sach danh muc:\n");
    printf("Ma danh muc\tTen danh muc\n");

    struct Category category;
    while (fread(&category, sizeof(struct Category), 1, categoryFile)) {
        if (strstr(category.CategoryName, searchName) != NULL) {
            printf("%s\t\t%s\n", category.CategoryId, category.CategoryName);
            found = 1;
        }
    }

    if (!found) {
        printf("Khong tim thay danh muc nao.\n");
    }

    fclose(categoryFile);
    printf("Nhan phim bat ki de tiep tuc...\n");
    getchar(); 
    system("cls");
}
void displayMenuCategory(int *n){
	int choiceCategory;
	do{
		
		printf("[1] Them vao danh muc moi\n");
		printf("[2] In ra danh muc san pham \n");
		printf("[3] Sua danh muc\n");
		printf("[4] Xoa danh muc\n");
		printf("[5] Sap xep cac danh muc\n");
		printf("[6] Tim kiem danh muc \n");
		printf("[0] Thoat \n");
		printf("Lua chon cua ban : ");
		scanf("%d", &choiceCategory);
		getchar();
		
		switch(choiceCategory){
			case 1:{
				system("cls");
				addCategory(categories, n);
				break;
			}
			case 2:{
				system("cls");
				displayCategories(categories, n); 
				break;
			}
			case 3:{
				system("cls");
				editCategory(categories, n);
				break;
			}
			case 4:{
				system("cls");
				deleteCategory(categories, n);
				break;
			}
			case 5:{
				system("cls");
				sortCategories(categories, n);
				break;		
			}
			case 6:{
				system("cls");
				searchCategory(categories, n);
				break;
			}
			case 0:{
				system("cls");
				printf("Exiting the program...\n");
				break;
			}
			default: {
                printf("Lua chon khong hop le vui long thu lai.\n");
                break;
            }	
		}
		
	}while(choiceCategory != 0);
	
}
void displayMenuProduct(int *a){
	
	int choiceProduct;
	
	
	do{
		system("cls");
		printf("[1] Them vao san pham moi.\n");
		printf("[2] In ra san pham hien tai.\n");
		printf("[3] Chinh sua san pham    \n"); 	
		printf("[0] Thoat\n");
		printf("Nhap lua chon cua ban : ");
		scanf("%d", &choiceProduct);
		getchar();
		
		switch(choiceProduct){
			case 1:{
				system("cls");
				addProduct(products, a);
				
				break;
			}
			case 2:{
				system("cls");
				displayProducts(products, a);
				
				break;
			}
			case 3:{
				system("cls");
				editProduct(products, a);
				break;
			}
			case 0:{
				system("cls");
				deleteProduct(products, a);
				printf("Exiting the program...\n");
				break;
			}  
		}
		
		
	}while(choiceProduct != 0);
}
void readAdminCredentials(struct AdminCredentials *admin) {
    FILE *file = fopen("pass.bin", "rb");  
    if (file != NULL) {
        fread(admin, sizeof(struct AdminCredentials), 1, file);  
        fclose(file);
    } else {
        printf("Khong the mo file luu tai khoan.\n");
    }
}
void hidePassword(char *password) {
    char ch;
    int i = 0;
    while (1) {
        ch = getch();  
        if (ch == 13) { 
            password[i] = '\0'; 
            break;
        } else if (ch == 8) {  
            if (i > 0) {
                i--;
                printf("\b \b");  
            }
        } else {
            password[i] = ch;
            i++;
            printf("*");  
        }
    }
}
void saveAdminCredentials(const char *username, const char *password) {
    struct AdminCredentials admin;
    strcpy(admin.username, username);
    strcpy(admin.password, password);

    FILE *file = fopen("pass.bin", "wb"); 
    if (file != NULL) {
        fwrite(&admin, sizeof(struct AdminCredentials), 1, file); 
        fclose(file);
    } else {
        printf("Khong the mo file de luu tai khoan.\n");
    }
}
void checkLogin() {
    struct AdminCredentials admin, enteredAdmin;


    readAdminCredentials(&admin);

    while (1) {  
        printf("Nhap tai khoan: ");
        scanf("%s", enteredAdmin.username);

        printf("Nhap mat khau: ");
        hidePassword(enteredAdmin.password);  
        printf("\n");


        if (strcmp(enteredAdmin.username, admin.username) == 0 && strcmp(enteredAdmin.password, admin.password) == 0) {
            printf("Dang nhap thanh cong!\n");
            break;  
        } else {
            printf("Tai khoan hoac mat khau sai. Vui long nhap lai.\n");
        }
    }
}
void editProduct(struct Product *products, int *a) {

    FILE *file = fopen("product.bin", "rb+");  
    if (file == NULL) {
        printf("Khong the mo file product.bin.\n");
        return;
    }

    char idToEdit[50];
    int productFound = 0;

    printf("Nhap ID san pham can sua: ");
    fgets(idToEdit, 50, stdin);
    idToEdit[strcspn(idToEdit, "\n")] = '\0';  
    
    for (int i = 0; i < *a; i++) {  
        if (strcmp(products[i].productId, idToEdit) == 0) {

            printf("San pham hien tai:\n");
            printf("ID: %-12s | Danh muc: %-12s | Ten: %-20s | So luong: %-5d | Gia: %-5d\n", 
                   products[i].productId, products[i].categoryId, products[i].productName, 
                   products[i].quantity, products[i].price);

            printf("Nhap ten san pham moi: ");
            fgets(products[i].productName, 50, stdin);
            products[i].productName[strcspn(products[i].productName, "\n")] = '\0'; 

            printf("Nhap so luong san pham moi: ");
            scanf("%d", &products[i].quantity);
            getchar(); 
            
            printf("Nhap gia san pham moi: ");
            scanf("%d", &products[i].price);
            getchar(); 

            fseek(file, i * sizeof(struct Product), SEEK_SET);  
            fwrite(&products[i], sizeof(struct Product), 1, file);  

            printf("San pham da duoc sua thanh cong!\n");
            productFound = 1;
            break;
        }
    }

    if (!productFound) {
        printf("Khong tim thay san pham voi ID '%s'.\n", idToEdit);
    }

    fclose(file);
    printf("Nhan phim bat ki de tiep tuc...\n");
    getchar(); 
    system("cls");
}

void deleteProduct(struct Product products[], int *a) {
    FILE *file = fopen("product.bin", "rb+"); 
    if (file == NULL) {
        printf("Khong the mo file product.bin.\n");
        return;
    }

    char idToDelete[50];
    int productFound = 0;
    int productIndex = -1;

    printf("Nhap ID san pham can xoa: ");
    fgets(idToDelete, 50, stdin);
    idToDelete[strcspn(idToDelete, "\n")] = '\0'; 

    for (int i = 0; i < *a; i++) {
        if (strcmp(products[i].productId, idToDelete) == 0) {
            productFound = 1;
            productIndex = i;
            break;
        }
    }

    if (!productFound) {
        printf("Khong tim thay san pham voi ID '%s'.\n", idToDelete);
        printf("Nhan phim bat ki de tiep tuc...\n");
        getchar(); 
        system("cls");
        fclose(file);
        return;
    }

    printf("San pham hien tai:\n");
    printf("ID: %-12s | Ten: %-20s | So luong: %-5d | Gia: %-5d\n", 
            products[productIndex].productId, 
            products[productIndex].productName, 
            products[productIndex].quantity, 
            products[productIndex].price);

    printf("Ban co chac chan muon xoa san pham nay? (y/n): ");
    char confirm;
    scanf(" %c", &confirm);
    getchar();  

    if (confirm == 'y' || confirm == 'Y') {
    
        for (int i = productIndex; i < *a - 1; i++) {
            products[i] = products[i + 1]; 
        }

        (*a)--; 

        fseek(file, 0, SEEK_SET);  
        fwrite(products, sizeof(struct Product), *a, file);  

        fflush(file);  
        ftruncate(fileno(file), *a * sizeof(struct Product));  

        printf("San pham da duoc xoa thanh cong!\n");
    } else {
        printf("Huy xoa san pham.\n");
    }

    fclose(file);
    printf("Nhan phim bat ki de tiep tuc...\n");
    getchar(); 
    system("cls");
}

