#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>

struct wordNode
{
char word[15];
int count;
struct wordNode *rlink, *llink;
};
typedef struct wordNode WNODE;
WNODE *wordList[26];

void insert(char string[100]){
        strlwr(string);
        int index=(int)string[0];
        index-=97;
        
        if(wordList[index]==NULL){
            WNODE *temp=(WNODE *)malloc(sizeof(WNODE));
            temp->llink=temp->rlink=NULL;
            temp->count=0;
            strcpy(temp->word,"#");
            wordList[index]=temp;
        }
        if(wordList[index]->rlink==NULL){
            WNODE *temp=(WNODE *)malloc(sizeof(WNODE));
            temp->rlink=NULL;
            temp->llink=wordList[index];
            wordList[index]->rlink=temp;
            temp->count=1;
            strcpy(temp->word,string);
            wordList[index]->count--;
            return;
        }
        else{
            WNODE *temp;
            temp=wordList[index]->rlink;
            while(temp){
            if(strcmp(temp->word,string)==0){
                temp->count++;
                return;}

            temp=temp->rlink;
            }
        temp=wordList[index]->rlink;
        while(temp&&strcmp(string,temp->word)>0){
            temp=temp->rlink;
        }
        if(temp){
        WNODE * previous=temp->llink,*new=(WNODE*)malloc(sizeof(WNODE));
        wordList[index]->count--;
        new->rlink=temp;
        new->llink=previous;
        previous->rlink=new;
        if(temp)temp->llink=new;
        new->count=1;
        strcpy(new->word,string);
        return;}
        else{
            temp=wordList[index]->rlink;
            while(temp->rlink)temp=temp->rlink;
            WNODE *new=(WNODE*)malloc(sizeof(WNODE));
            wordList[index]->count--;
            new->rlink=NULL;
            new->llink=temp;
            temp->rlink=new;
            new->count=1;
            strcpy(new->word,string);
            return;
        }     
           }
}
void display(WNODE*temp){
    while (temp)
    {
        printf("%s\t",temp->word);
        printf("%d\n",temp->count);
        temp=temp->rlink;
    }
}
int main()
{
    char Unum[100];
    char rword[15];
    printf("Enter the sentence:\n");
    gets(Unum);
    int start=0,final=0,index=0;
    while(Unum[index]!='#'){
        if(Unum[index]==' '||Unum[index]==','||Unum[index]=='.'){
            int k=0;
            for(int i=start;i<final;i++,k++){
                 rword[k]=Unum[i];   
            }
            insert(rword);
            start=index+1;
            final=start;
            // Clearing an array.
            
            for(int i=0;i<15;i++)rword[i]='\0';
        }
        else final++;
        index++;
    }
    for(int i=0;i<2;i++){
    WNODE*ans=wordList[i];
    display(ans);
    }
    // char num1[10]="Abalone";
    // char num2[10]="Abduct";
    // char num3[10]="Abduct";
    // insert(num1);
    // insert(num2);
    // insert(num3);
    // WNODE*ans=wordList[0];
    // display(ans);
}