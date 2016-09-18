//coding:utf-8
#include <stdio.h>
#include <stdlib.h>

//The chars
#define ADD '+'
#define SUB '-'
#define NXT '>'
#define PRV '<'
#define INN '.'
#define OUT ','
#define IFS '['
#define IFE ']'
//string 
#define s_infile_error "[error]:打开文件%s失败\n"
#define s_ife_error "[error]:在代码的%d处没有与之对应的']'\n"
// The paper sheet
#define buffsize 30
char sheet [buffsize]={0};
int cur=0;

//--------------stack start  ----------------

struct stacknode {
	int cur;
	struct stacknode  * next;
};

static stacknode* TheStack ;
int is_empty();
int pop();
void destroystack(){
	while (!is_empty()){
		pop();
	}
}

void push ( int cur ){

	stacknode* testnew;
	testnew = (stacknode *) malloc (sizeof(stacknode ));
	if (testnew == NULL ){
	}else {

		testnew-> cur=cur;
		testnew -> next=TheStack;
		TheStack=testnew;

	}
}

int pop (void ){

	stacknode * f;
	int cur;

	if (!is_empty()){
		f=TheStack;
		cur=f->cur;
		TheStack=f->next;
		free(f);
		return cur;

	}

	return -1;
}


int top (){
	return TheStack->cur;
}

int is_empty(){
	return TheStack==NULL;
}

void printstack(){
	stacknode * p;
	p=TheStack;
	printf("The Stack ");

	if (p==NULL){ printf("Is empty\n");}

	while (p!= NULL){
		printf("%d,",p->cur);
		p=p->next;
	}
	printf("\n");
}
//-----------end the stack --------------------
void printbuff(){

	for (int i=0;i<buffsize;i++){
		if (i!= cur){
			printf("[%03d]\t",sheet[i]);
		}else{
			printf(">%03d<\t",sheet[i]);
		}
		
		if (!((i+1)%10)){
			printf("\n");
		}
	}
}

int toIFE(FILE * f){
	char ch;
	while ((ch=(char)fgetc(f))!= EOF){
		if(ch==IFE){
			//fseek(f,-1L,SEEK_CUR);
			return 0 ;
		}
	}

	return 1;


}
int main (int argn,char *argv[]){

	/* test the stack 
	push(12);
	push(122);
	printstack();
	pop();
	printstack();
	*/
	

	//open file 
	char test_file[]="test.bf";
	FILE * inf;
	inf=fopen(test_file,"r");
	if (inf ==NULL){

		printf(s_infile_error,test_file);
		exit(-1);
	}
	
	char ch;
	while ((ch=(char)fgetc(inf))!= EOF){
		printf("------%d---%c-----\n",(int) ftell(inf),ch);
		switch (ch){
			case ADD: sheet[cur]+=1 ;break;
			case SUB: sheet[cur]-=1 ;break;
			case NXT: cur =(cur+1)%buffsize ;break;
			case PRV: cur =(cur-1+buffsize)%buffsize;break;
			case INN: scanf("%d",&sheet[cur]);break;
			case OUT: printf("%c",sheet[cur]); break;
			case IFS: {
				push((int) ftell(inf));

				if (sheet[cur]){
					
				}else{
					pop();
					if(toIFE(inf)){
						printf(s_ife_error,ftell(inf));
					}
				}

				break;
			}
			case IFE:{
				printstack();

				long cut_f=(long)pop()-1;
				if(cut_f>=0){

					//printf("THE IFE %d\n",cut_f);
					fseek(inf,cut_f,SEEK_SET);

				}else{


				}

				break;

			}
		}
		printbuff();
	}


	return 0;
}