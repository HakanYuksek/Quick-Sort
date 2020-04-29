#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void yazdir(int *A,int n){//parametre olarak aldigi dizinin elemanlarini yazdirir
	int i;
	for(i=0;i<n;i++){
		printf("%d\t",A[i]);
	}
	printf("\n");
}
void diziyiOku(int *A,int n){
	int i;
	for(i=0;i<n;i++){
		printf("%d inci elemani giriniz:",i+1);
		scanf("%d",&A[i]);
	}
	
}
int search(int *A,int n,int x){//sequential search algoritmasi ile arama yapar
	int i=0;
	while(i<n & A[i]!=x){
		i++;
	}
	if(i<n){
		return i;
	}else{
		printf("\nhatali giris...\n");
		getch();
		exit(0);//aranan eleman yok demektir
	}
}

int partition(int pivot,int *A,int n,int left,int right){
	int tmp;
	int pindex=search(A,n,pivot);//pivot ile ayni degere sahip eleman dizi icerisinde aranip bulunur
	tmp=A[left];//bulunan eleman dizinin en soluna atilir
	A[left]=A[pindex];
	A[pindex]=tmp;
	pindex=left;
	printf("%d ile %d indisleri arasindaki elemanlari icin ",left,(right-1));
	printf("partition kismi--->\n");
	do{
		do{
			left++;
		}while(left<right && pivot>=A[left]);
		do{
			right--;
		}while(left<right && pivot<A[right]);	
		yazdir(A,n);
		tmp=A[left];
		A[left]=A[right];
		A[right]=tmp;	
	}while(left<=right);
	tmp=A[left];
	A[left]=A[right];
	A[right]=tmp;
	tmp=A[pindex];//pivotun degerini dizi icerisinde uygun yere koymamiz gerekiyor
	A[pindex]=A[right];
	A[right]=tmp;
	yazdir(A,n);
	return right;//pivotun dizi icerisindeki konumu = right
}

void SortArrays(int *Key,int *Lock,int n,int left,int right){//anahtar ve kilitlerden birbirine uyanlari bulmamizi saglar
	int i,pindex,pivot;
	if(left<right){
		i=(rand()%(right-left))+left; //pivotu random seciyoruz
		pivot=Key[i];
		printf("-------------------------------\n");
		printf("pivot--->%d\n",pivot);
		printf("Lock dizisinin\n");
		pindex=partition(pivot,Lock,n,left,right);//once lock dizisi uzerinde partition islemi gerceklestirilir
		pivot=Lock[pindex];
		printf("Key dizisinin\n");
		pindex=partition(pivot,Key,n,left,right);//daha sonra lock dizisindeki elemana gore Key dizisi uzerinde partition yapilir
		printf("Bu adim sonrasi Lock dizisi----->\n");
		yazdir(Lock,n);
		printf("Bu adim sonrasi Key dizisi----->\n ");
		yazdir(Key,n);
		SortArrays(Key,Lock,n,left,pindex);
		SortArrays(Key,Lock,n,pindex+1,right);
	}
}



int main(){
	int *Key,*Lock,n;//n degiskeni Key ve Lock dizilerinin eleman sayisini tutar
	srand(time(NULL));
	printf("Iki dizi girmeniz istenecektir\n");
	printf("Bu iki dizi ayni elemanlardan olusmalidir. Ancak bu elemanlarin yeri karisik olabilir.\n");
	printf("Bu iki dizi Quick Sort ile siralanacak ve sonuclari gosterilecektir.\n\n");
	printf("Lutfen kilit ve anahtar sayisini giriniz:");
	scanf("%d",&n);
	printf("\n");
	Key=(int*)malloc(sizeof(int)*n);//Key dizisi icin dynamic memory allocation yapildi
	Lock=(int*)malloc(sizeof(int)*n);//Lock dizisi icin dynamic memory allocation yapildi
	printf("Key dizisinin elemanlarini sirasiyla giriniz...\n");	
	diziyiOku(Key,n);
	printf("\n");
	printf("Lock dizisinin elemanlarini sirasiyla giriniz...\n");
	diziyiOku(Lock,n);
	printf("\n");
	printf("Key dizisi:\n");
	yazdir(Key,n);
	printf("Lock dizisi:\n");
	yazdir(Lock,n);
	SortArrays(Key,Lock,n,0,n);
	printf("Eslestirilmis kilit ve anahtarlar:\n ");
	printf("Kilitler:\n");
	yazdir(Lock,n);
	printf("Anahtarlar:\n");
	yazdir(Key,n);
	getch();
	return 0;
}
