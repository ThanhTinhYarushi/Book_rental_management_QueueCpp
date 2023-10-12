      /**
      * @author:Trần Thanh Tịnh
      * 
      * * Github:github.com/ThanhTinhYarushi
      * * Email : ThanhTinh.Yarushi@gmail.com
      */
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<cstring>
#include<iostream>
#include<iomanip>
using namespace std;
// * struct ------------------------------------
struct Sach{
	char bookname[30], author[40];
	double price;
	int quantity;
};
typedef struct Sach Book;
struct NODE{
	Sach data;
	NODE* next;
};
typedef struct NODE* Node;
typedef struct QUEUE{
	NODE* front, *rear; // front - back
}Queue;
// * func ------------------------------------- support
void Menu();
void PressAnyKey();
bool DocDongTrong(FILE* file); // ! Xoa Dau Xuong Dong Khi Nhap File 
NODE* makeNode(Sach data);
void init(Queue &q){ q.front = q.rear = nullptr; }
bool isEmpty(Queue q){ return q.front == nullptr; }
void enQueue(Queue &q, Sach data);
bool deQueue(Queue &q, Sach &data);
void NhapSach(Sach &s);
void TieuDe();
void Duoi();

// * func ------------------------------------- main
bool NhapSachTuFile(Sach &sach, FILE *file);
bool NhapSachTuFile1(Sach &sach, FILE *file);
void Them1CuonSach(Queue &q);
void XuatDanhSachSachHienCo(Queue q);
bool ThemSachTuFile(Queue &q,const char* tenFile);
void XuatSachHienCo(Queue q);
int TinhTongSoLuongSach(Queue q);
bool TimCuonSachTheoTen(Queue q, const char* tenSach);
void ThueTruyen(Queue &q,Queue &qThue);
void TraTruyen(Queue &q,Queue &qThue);
void XuatCacCuonSachDangThue(Queue qThue);
void XuatCacTruyenRaFile(Queue q, const char* tenTep);

// * main -------------------------------------
int main(){
	Queue q;
	init(q);
	Queue qThue;
	init(qThue);
    // Sach sach;
    int chon;//, soLuongSach = 0;
    do{
    	system("cls");
    	Menu();
    	cin >> chon;
    	getchar();
    	switch(chon){
    		case 0:{
    			system("cls");
    			std::cout << "Cam on ban da su dung chuong trinh ^^" << std::endl;
				break;
			}
    		case 1:{ /* Nhap Sach Tu File */
				bool success = ThemSachTuFile(q,"Sach2.input");
				if(success)	cout << "Them Vao Thanh cong!" << endl;
				else cout << "Them Khong Thanh Cong!" << endl;
				getchar();
				PressAnyKey();
				break;
			}
			case 2:{ /* Xuat Cac Cuon Sach Hien Co */
				XuatDanhSachSachHienCo(q);
				cout << "Tong Luong Sach Trong Kho La:" << TinhTongSoLuongSach(q);
				getchar();
				PressAnyKey();
				break;
			}
			case 3:{ /* Them 1 cuon sach */
				Them1CuonSach(q);
				break;
			}
			case 4:{ /*Thue Truyen*/
				ThueTruyen(q,qThue);
				PressAnyKey();
				break;
			}
			case 5:{ /*Tra Truyen */
				TraTruyen(q,qThue);
				PressAnyKey();
				break;
			}
			case 6:{ /* cac cuon truyen dang thue */
				XuatCacCuonSachDangThue(qThue);
				PressAnyKey();
				break;
			}
			case 7:{
				XuatCacTruyenRaFile(q,"Sach2.output");
				PressAnyKey();
				break;
			}
    		default:{
    			break;
    		}
		}
	}while(chon != 0);
    return 0;
}

// * func ------------------------------------- support
void Menu(){
	std::cout << "@============Menu Quan Ly Sach============@" << std::endl;
	std::cout << "|1.Nhap Cac Cuon Sach Tu File.            |" << std::endl;
	std::cout << "|2.Xuat Cac Cuon Sach Hien Co Trong Kho.  |" << std::endl;
	std::cout << "|3.Nhap 1 Cuon Sach.                      |" << std::endl;
	std::cout << "|4.Thue Sach.                             |" << std::endl;
	std::cout << "|5.Tra Sach.                              |" << std::endl;
	std::cout << "|6.Xuat Cac Cuon Sach Dang Duoc Thue.     |" << std::endl;
	std::cout << "|7.Xuat Truyen Hien Co Ra File.           |" << std::endl;
	std::cout << "|Nhan 0 De Thoat Chuong Trinh.            |" << std::endl;
	std::cout << "@=========================================@" << std::endl;
	std::cout << "-> Lua Chon Cua Ban:";
}

void PressAnyKey(){
	cout << "Nhan Phim Bat Ky De Tiep Tuc...";
	getchar();
	system("cls");
}

bool DocDongTrong(FILE* file){
    char buffer[2];
    if (fgets(buffer, sizeof(buffer), file) == NULL || buffer[0] != '\n'){
        return false;
    }
    return true;
}

NODE* makeNode(Sach x){
	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	newNode->data = x;
	newNode->next = NULL;
	return newNode;
}

void enQueue(Queue &q, Sach data){
	Node newNode = makeNode(data);
	if(isEmpty(q)){ q.front = q.rear = newNode; }
	else{
		q.rear->next = newNode;
		q.rear = newNode;
	}
}

bool deQueue(Queue &q, Sach &data){
	if(isEmpty(q)){ return false; }
	NODE* tmp = q.front;
	data = tmp->data;
	q.front = q.front->next;
	delete tmp;
	if(q.front == nullptr){
		q.rear = nullptr;
	}
	return true;
}

void NhapSach(Sach &s){
	cout << "Nhap ten Sach:";
	cin.getline(s.bookname,sizeof(s.bookname));
	cout << "Nhap ten tac gia:";
	cin.getline(s.author,sizeof(s.author));
	cout << "Nhap gia cua cuon sach:";
	cin >> s.price;
	cout << "Nhap so luong:";
	cin >> s.quantity;
}

void TieuDe(){
	std::cout << "Danh sach cac cuon sach trong kho duoi dang bang:" << std::endl;
    std::cout << "+--------------------------------------+----------------------+------------+---------+" << std::endl;
    std::cout << "|      Ten Sach                        |       Tac Gia        |    Gia     | So luong|" << std::endl;
    std::cout << "+--------------------------------------+----------------------+------------+---------+" << std::endl;
}

void Duoi(){
	std::cout << "+--------------------------------------+----------------------+------------+---------+" <<std::endl;
}

// * func ------------------------------------- main

bool NhapSachTuFile(Sach &sach, FILE *file){
    if (fgets(sach.bookname, sizeof(sach.bookname), file) == NULL) {
        return false;
    }
    if (fgets(sach.author, sizeof(sach.author), file) == NULL) {
        return false;
    }
    if (fscanf(file, "%lf", &sach.price) != 1) {
        return false;
    }
    if (fscanf(file, "%d", &sach.quantity) != 1) {
        return false;
    }
    DocDongTrong(file);
    return true;
}

bool NhapSachTuFile1(Sach &sach, FILE *file){
    char buffer[200]; // Dùng để đọc dòng đầu tiên chứa thông tin của cuốn sách
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        return false;
    }
    // Tách thông tin thành các phần riêng biệt bằng dấu ","
    char *token = strtok(buffer, ",");
    if (token != nullptr) {
        strncpy(sach.bookname, token, sizeof(sach.bookname));
    }

    token = strtok(NULL, ",");
    if (token != nullptr) {
        strncpy(sach.author, token, sizeof(sach.author));
    }

    token = strtok(NULL, ",");
    if (token != nullptr) {
        sach.price = atof(token);
    }

    token = strtok(NULL, ",");
    if (token != nullptr) {
        sach.quantity = atoi(token);
    }

    return true;
}

void Them1CuonSach(Queue &q){
	Sach sachmoi;
	NhapSach(sachmoi);
	enQueue(q,sachmoi);
	cout << "Sach da them vao hang doi" << endl;
}

void XuatDanhSachSachHienCo(Queue q){
    if (isEmpty(q)){
        std::cout << "Danh Sach Cac Cuon Sach Hien Tai Dang Trong!!" << std::endl;
        return;
    }
    TieuDe();
    Node currentNode = q.front;
     while (currentNode != nullptr) {
        cout << "| " << left << setw(37) << currentNode->data.bookname
             << "| " << left << setw(21) << currentNode->data.author
             << "| " << left << setw(11) << fixed << setprecision(2) << currentNode->data.price
             << "| " << left << setw(7) << currentNode->data.quantity
             << " |" << endl;
        currentNode = currentNode->next;
    }
    Duoi(); // Kết thúc bảng
}

void XuatSachHienCo(Queue q){
    if (isEmpty(q)) {
        std::cout << "Danh Sach Cac Cuon Sach Hien Tai Dang Trong!!" << std::endl;
        return;
    }
    Node currentNode = q.front;
    while (currentNode != nullptr) {
        cout << currentNode->data.bookname << " - " << currentNode->data.author << " - " << currentNode->data.price << " - " << currentNode->data.quantity << endl;
        currentNode = currentNode->next;
    }
}

bool ThemSachTuFile(Queue &q, const char* tenFile){
    FILE* file = fopen(tenFile, "r");
    if (file == NULL) {
        cout << "Khong The Mo Tep!!";
        return false;
    }
    Sach sach;
    while (NhapSachTuFile1(sach, file)){
        enQueue(q, sach);
        cout << "Ten sach vua duoc them vao hang doi: " << sach.bookname << endl ;
    }
    fclose(file);
    return true;
}

int TinhTongSoLuongSach(Queue q){
    int tongSoLuong = 0;
    Node currentNode = q.front;
    while (currentNode != nullptr) {
        tongSoLuong += currentNode->data.quantity;
        currentNode = currentNode->next;
    }
    return tongSoLuong;
}

bool TimCuonSachTheoTen(Queue q, const char* tenSach){
    Node currentNode = q.front;
    while (currentNode != nullptr) {
        if (strcmp(currentNode->data.bookname, tenSach) == 0) {
            // Tìm thấy cuốn sách với tên cần tìm
            return true;
        }
        currentNode = currentNode->next;
    }
    // Không tìm thấy cuốn sách với tên cần tìm
    return false;
}

void ThueTruyen(Queue &q, Queue &qThue){
    if (isEmpty(q)) {
        std::cout << "Danh Sach Trong,Khong Co Truyen De Thue." << std::endl;
        return;
    }

    Sach sachThue;
    if (deQueue(q, sachThue)) {
        std::cout << "Ban Da Thue Truyen Thanh Cong, Day La Thong Tin Truyen Ban Da Thue:" << std::endl;
        std::cout << "Ten Sach: " << sachThue.bookname << std::endl;
        std::cout << "Tac Gia: " << sachThue.author << std::endl;
        std::cout << "Gia: " << sachThue.price << std::endl;
        std::cout << "So luong: " << sachThue.quantity << std::endl;

        // Enqueue truyện đã thuê vào hàng đợi đã cho thuê.
        enQueue(qThue, sachThue);
    } else {
        std::cout << "Khong con truyen nao de cho thue." << std::endl;
    }
}

void TraTruyen(Queue &q, Queue &qThue){
    if (isEmpty(qThue)) {
        cout << "Hien Khong Co Truyen Duoc Thue." << endl;
    } else {
        Sach sachTra;
        if (deQueue(qThue, sachTra)){
            cout << "Ban Da Tra Truyen Thanh Cong, Day La Thong Tin Cuon Truyen Ban Da Tra:" << endl;
            cout << "Ten Truyen: " << sachTra.bookname << endl;
            cout << "Tac Gia: " << sachTra.author << endl;
            cout << "Gia: " << sachTra.price << endl;
            cout << "So luong: " << sachTra.quantity << endl;

            // Sau khi trả truyện thành công, bạn cần enqueue nó vào hàng đợi `q` (truyện hiện có).
            enQueue(q, sachTra);
        } else {
            cout << "Hien Khong Co Truyen Duoc Thue." << endl;
        }
    }
}

void XuatCacCuonSachDangThue(Queue qThue){
    if (isEmpty(qThue)) {
        cout << "Hien Khong Co Cuon Sach Dang Duoc Thue." << endl;
    } else {
        cout << "Danh Sach Cuon Sach Dang Duoc Thue:" << endl;
        XuatSachHienCo(qThue);
    }
}

void XuatCacTruyenRaFile(Queue q, const char* tenTep){
    FILE* outputFile = fopen(tenTep, "w"); // Mở tệp để ghi

    if (outputFile == NULL) {
        cout << "Khong The Mo Tep De Ghi!" << endl;
    } else {
        Node currentNode = q.front;
        while (currentNode != nullptr) {
            fprintf(outputFile, "Ten Truyen: %s\n", currentNode->data.bookname);
            fprintf(outputFile, "Tac Gia: %s\n", currentNode->data.author);
            fprintf(outputFile, "Gia: %.2lf\n", currentNode->data.price);
            fprintf(outputFile, "So luong: %d\n", currentNode->data.quantity);
            fprintf(outputFile, "---------------------------\n");

            currentNode = currentNode->next;
        }

        fclose(outputFile); // Đóng tệp sau khi ghi xong
        cout << "Da Xuat Danh Sach Truyen Ra Tep: " << tenTep << endl;
    }
}