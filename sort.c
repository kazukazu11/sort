#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Record{ //構造体を利用
	char Id[50];
	int Result;
}Record;

void sort(struct Record *a, struct Record *b) { //前の数字が大きければ後の数字と交換
	if (atoi(a->Id) < atoi(b->Id)) {
		char temp[50];
		strcpy(temp, b->Id);
		strcpy(b->Id, a->Id);
		strcpy(a->Id, temp);
		int y = b->Result;
		b->Result = a->Result;
		a->Result = y;
	}
}

void change0(struct Record *a, struct Record *b) {
	a->Id[1] = '0';
	b->Id[1] = '0';
}

void changeG(struct Record *a) {
	a->Id[1] = 'G';
}

void BubbleSort(struct Record *x,int length){ //バブルソート
	int i;
	int j;
	for(i=0;i<length-1;i++){
		for(j=0;j<length-1;j++){
			change0(&x[j],&x[j+1]);
			sort(&x[j],&x[j+1]);
		}
	}
}

int main(void){
	FILE *fp=fopen("enshu02.txt","r");
	if(fp==NULL){
		printf("ファイルを開けませんでした。\n");
		return -1;
	}
	Record records[80];

	int size=0; //構造体配列の要素数を記憶するための変数
	char str[15]; //ファイルから読み込んだ1行の文字列を一時的に記憶するための箱
	while(fgets(str,sizeof(str),fp)!=NULL){ //読み込めなくなるまで
		char *p=strchr(str,(int)'\n'); //改行コードを終端文字に変える
		if(p!=NULL) *p='\0';

		char *token; //一つずつ切り取っていく
		token=strtok(str,"\t");
		strcpy(records[size].Id,token);
		token=strtok(NULL,"\t");
		records[size].Result=atof(token);
		size++;
	}
	BubbleSort(records,size);

	
	int i;
	for(i=0;i<size;i++){
		changeG(&records[i]);
		printf("%s %d\n",records[i].Id,records[i].Result);
	}
	
	
	fclose(fp);
	return 0;
}