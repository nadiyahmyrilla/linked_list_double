#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

//Menambahkan variabel dengan struct
struct node {
	int data;
    struct node *left;
    struct node *right;

};
typedef struct node node;

//node *createNode(void);
void tambahAwal(node **head);
void tambahData(node **head);
void tambahAkhir(node **head);
void hapusAwal(node **head);
void hapusData(node **head);
void hapusAkhir(node **head);
void totalData(node **head);
void totalValue(node **head);
void cariData(node **head);
void tranverse(node *head);


//Data utama
int main() {
  node *head; 
  char pilih; 

  head = NULL;
  do{
     system("cls");
     printf("=================//========================\n");
     printf("Masukkan Apa Yang Ingin Tambahkan\n");
     printf("1. Tambah data diawal\n");
     printf("2. Tambah data ditengah list\n");
     printf("3. Tambah data diakhir\n");
     printf("4. Hapus data diawal\n");
     printf("5. Hapus data ditengah list\n");
     printf("6. Hapus data diakhir\n");
     printf("7. Total jumlah data\n");
     printf("8. Total value link list\n");
     printf("9. Mencari data didalam link list\n");
     printf("0. cetak isi list\n");
     printf("MASUKKAN PILIHAN (tekan q untuk logout) : ");
     fflush(stdin); scanf("%c", &pilih);
     if (pilih == '1')
     		tambahAwal(&head);
     else if (pilih == '2')
			tambahData(&head);
	 else if (pilih == '3')
			tambahAkhir(&head);
	 else if (pilih == '4')
			hapusAwal(&head);
	 else if (pilih == '5')
			hapusData(&head);
	 else if (pilih == '6')
			hapusAkhir(&head);
	 else if (pilih == '7')
			totalData(&head);
	 else if (pilih == '8')
			totalValue(&head);
	 else if (pilih == '9')
			cariData(&head);
     else if (pilih == '0'){
     		tranverse(head);
            getch();
     }
  } while (pilih != 'q');
  
  return 0;
}

//Menambah linked list diawal
void tambahAwal(node **pHead) {
    int bil;
    node *pNew = (node *)malloc(sizeof(node));

    system("cls");
    printf("Masukkan bilangan : ");
    scanf("%d", &bil);
    
    if (pNew == NULL) {
        printf("Alokasi memori gagal\n");
        return;
    }

    pNew->data = bil;
    pNew->right = *pHead;
    pNew->left = NULL; //Karena awal maka untuk ke kiri adalah NULL

    if (*pHead != NULL) {
        (*pHead)->left = pNew; // Update previous head's left pointer
    }

    *pHead = pNew; // Move head to point to the new node
}

//Menambah data ditengah
void tambahData(node **head){
    int pos, bil;
    int count = 1;
    node *pCur = *head;
    node *pNew = (node *)malloc(sizeof(node));

    system("cls");
    tranverse(*head); //menampilkan linked lisst yang telah dimasukan
    printf("\nLetak penyisipan pada urutan data ke-: ");
    fflush(stdin); scanf("%d", &pos); //menyimpan posisi target
    
    if (pos <= 1) {
        printf("Posisi tidak valid. Harus > 1.\n");
        free(pNew); // Bebaskan memori jika tidak digunakan
        getch();
        return;
    }
    
    printf("Masukkan bilangan: ");
    fflush(stdin); scanf("%d", &bil);
    pNew->data = bil;
    pNew->right = NULL;
    pNew->left = NULL;
    
    while (pCur != NULL && count < pos - 1) { //untuk pCur tidak sama dengan null dan tidak sama dengan target
        pCur = pCur->right; //pCur berjalan
        count++;
    }

    if (pCur == NULL){
        printf("\nUrutan tidak ditemukan, Data ditambahkan diakhir linked list."); 
	    // Menambah node baru di akhir
        if (*head == NULL) {
            *head = pNew; // Jika list kosong, node baru menjadi head
        } else {
            pCur = *head;
            while (pCur->right != NULL) {
                pCur = pCur->right;
            }
            pCur->right = pNew;
            pNew->left = pCur;
        }
    } else {
        // Menyisipkan node baru pada posisi yang diinginkan
        pNew->right = pCur->right;
        pCur->right = pNew;
        pNew->left = pCur;
        if (pNew->right != NULL) {
            pNew->right->left = pNew;
        }
        printf("\nData berhasil ditambahkan di urutan ke-%d.\n", pos);
    }
}

//Menambah linked list diakhir
void tambahAkhir(node **head) {
    int bil;
    node *pNew = (node *)malloc(sizeof(node));

    system("cls");
    tranverse(*head);
    printf("\nMasukkan bilangan : ");
    fflush(stdin); scanf("%d", &bil);
    pNew->data = bil; 
    pNew->right = NULL;
    pNew->left = NULL;  
    
    if (pNew == NULL) {
        printf("Alokasi memori gagal");
        getch();
        return;
    }
    if (*head == NULL) { // Jika list kosong
        *head = pNew;   // Node baru menjadi head
    } else {
        node *pCur = *head;
        while (pCur->right != NULL) { // Menelusuri hingga akhir list
            pCur = pCur->right;
        }
        pCur->right = pNew;
        pNew->left = pCur;
    }
}

//Menghapuskan data awal
void hapusAwal(node **head) {
	node *pCur;
	
	if (*head == NULL) { // pemeriksaan list kosong
      printf("List kosong, tidak ada yang dihapus.\n"); 
	  getch();
      return;
    }
    
	system("cls");
    tranverse(*head);
    pCur = *head; // memasukan pointer ke node pertama
    *head = pCur->right;
    free(pCur);
    printf("\nData telah dihapus!"); 
	getch();
	
}

// Hapus data di tengah
void hapusData(node **head) {
    int pos;
    int count = 1;
    node *pPrev = NULL;
    node *pCur = *head;

    system("cls");
    tranverse(*head);
    printf("\nMasukkan urutan data yang ingin dihapus: ");
    fflush(stdin); 
    scanf("%d", &pos);
    
    if (pos < 1) {
        printf("Posisi tidak valid. Harus > 1.\n");
        getch();
        return;
    }

    while (pCur != NULL && count < pos) {
        pPrev = pCur;
        pCur = pCur->right;
        count++;
    }

    // Jika pCur adalah NULL, berarti posisi lebih besar dari jumlah node
    if (pCur == NULL) {
        printf("\nPosisi tidak ditemukan, tidak ada data yang dihapus."); 
        getch();
        return;
    }

    // Jika pCur adalah head
    if (pCur == *head) {
        *head = pCur->right;
        if (*head != NULL) {
            (*head)->left = NULL;
        }
    } else {
        pPrev->right = pCur->right;
        if (pCur->right != NULL) {
            pCur->right->left = pPrev; 
        }
    }

    free(pCur);
    printf("\nData telah dihapus!"); 
    getch();
}

//Menghapus linked list diakhir
void hapusAkhir(node **head) {
    int bil;
    node *pCur = *head;

    system("cls");
    tranverse(*head);
    
    
    if (*head == NULL) {
        printf("List kosong, tidak ada data yang dihapus\n");
        getch();
        return;
    }
    
    //jika hanya 1 node
    if (pCur->right == NULL) {
        free(pCur);
        *head = NULL; // Ubah head menjadi NULL
    } else {
        // Menelusuri hingga node sebelum yang terakhir
        while (pCur->right != NULL) {
            pCur = pCur->right;
        }
        node *pPrev = pCur->left;
        free(pCur);
        if (pPrev != NULL) {
            pPrev->right = NULL;
        }
    }
    
    printf("\nData telah dihapus!");
    getch();
}

//Total data yang dimiliki
void totalData(node **head) {
	int count = 0;
	node *pWalker = *head;
	
	system("cls");
	tranverse(*head);
	
	if (*head == NULL) {
        printf("List kosong, tidak ada data.\n");
        getch();
        return;
    }
	
	while (pWalker != NULL){
	  count++;
	  pWalker = pWalker->right;
    }
    
	printf("\nJumlah data dalam linked list: %d\n", count);
    getch();
}

//Total value yang dimiliki
void totalValue(node **head) {
	int total = 0;
	node *pWalker = *head;
	
	if (*head == NULL) {
        printf("List kosong, tidak ada data.\n");
        getch();
        return;
    }
	
	system("cls");
	tranverse(*head);
	
	printf("\nData: "); // agar menampilkan data dengan, ex data: 1+2+3+4...
	while (pWalker != NULL){
	  total += pWalker -> data; // Tambahkan nilai dari node saat ini ke total
	  printf("%d", pWalker->data);
	   if (pWalker->right != NULL) {
            printf(" + ");
        }
	  pWalker = pWalker->right;
    }
    
	printf("\nJumlah total value linked list: %d\n", total);
    getch();
}

// Mencari data di dalam linked list
void cariData(node **head) {
    int target;
    node *pWalker = *head;
    int found = 0; // mencari data

    system("cls");
    printf("Masukkan nilai yang ingin dicari: ");
    fflush(stdin);
    scanf("%d", &target);

    while (pWalker != NULL) {
        if (pWalker->data == target) {
            found = 1; // Tandai bahwa data ditemukan
            break; // Hentikan pencarian
        }
        pWalker = pWalker->right; // Pindah ke node berikutnya
    }

    if (found) {
        printf("Data %d ditemukan dalam linked list.\n", target);
    } else {
        printf("Data %d tidak ditemukan dalam linked list.\n", target);
    }
    getch();
}

//Menampilkan linked list
void tranverse(node *head) {
    node *pWalker;
    system("cls");
    pWalker = head;
    while (pWalker != NULL) {
        printf("%d <-> ", pWalker->data);
        pWalker = pWalker->right;
    }
    
    printf("NULL\n");
}

