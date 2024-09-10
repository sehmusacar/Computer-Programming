#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define NOT 1
#define OR 2
#define AND 3
#define FLIPFLOP 4
#define INPUT 5
#define len 100
#define lenght 11
struct kapi
{
    char name[lenght]; 
    int type; //Type of the kapi :INPUT,AND, OR, NOT, etc
    int deger;
    char inputname1[lenght];
    char inputname2[lenght];
    struct kapi *input1; 
    struct kapi *input2;
};

int kapinot(int deger){
	if(deger==0)
	{
		return 1;
	}	
	if(deger==1)
	{
		return 0;
	}		
}

int kapior(int deger1,int deger2){
	if(deger1==0 && deger2==0){ // if both of them 0 result 0
		return 0;
	}else{	// else result 1
		return 1;
	}
}

int kapiand(int deger1,int deger2){
	if(deger1==1 && deger2==1){ // if both of them 1 result 1
		return 1;
	}else{	// else result 0
		return 0;
	}
}

int kapiflipflop(int deger1,int deger2){
	if(deger1==deger2){
		return 0;
	}else{
		return 1;
	}
}

void RemoveSpaces(char* source)
{
  char* afterchar = source;
  char* thechar = source;
  if(*thechar!=0){
	  	while(*thechar != 0)
	  	{
		    *afterchar = *thechar++; // sync to the next char

		    if(*afterchar != ' ') // checks for space

		      afterchar++;
		}
		*afterchar = 0;	 // aftercharı does 0 again
  }  
}

int find_arraysize(){
	FILE *fileptr;
	char str[len],*token;
	int count=0;
	fileptr=fopen("circuit.txt","r");
		fgets(str,100,fileptr);
			token=strtok(str," ");
			while(token!=NULL){
				count++;
				token=strtok(NULL," ");
			}
		while(fgets(str,len,fileptr)!=NULL){
			count++;
		}	
	fclose(fileptr);
	
	return count-1;	
}

struct kapi* create(char name[],int type,char inputname1[],char inputname2[]) 
{ 
    struct kapi* new_node = (struct kapi*) malloc(sizeof(struct kapi)); // allocation 
     	// Assignments 
    new_node->type  =type; 
    strcpy(new_node->name,name);
    strcpy(new_node->inputname1,inputname1);
    strcpy(new_node->inputname2,inputname2);
    
    return new_node; 
} 
 
int strcp(char s[],char * t){
	int i=0;
	while(*t!='\0'){
		if(*t=='\n' || *t=='\r')t++;
		s[i++]=*t++;
	}
	s[i]='\0';
    return i;	
}

int store(struct kapi **array){
	FILE *fileptr;
	char str[len],*token;
	int count=0,i=0;
	char name[lenght];
	char type[lenght];
	char inputname1[lenght];
	char inputname2[lenght];
	fileptr=fopen("circuit.txt","r");
		fgets(str,100,fileptr);
			token=strtok(str," ");
			while(token!=NULL){
				
				if(count>0){
				strcp(name,token);
				array[i++]=create(name,INPUT," "," ");
				}
			    count++;	
				token=strtok(NULL," ");
			
	       	}
		while(fscanf(fileptr,"%s%s%s%[^\n]s\n",type,name,inputname1,inputname2)!=EOF){  
			RemoveSpaces(inputname2);
			if(strstr(type,"NOT")){
			array[i++]=create(name,NOT,inputname1,inputname2);
			}else if(strstr(type,"OR")){
			array[i++]=create(name,OR,inputname1,inputname2);
			}else if(strstr(type,"AND")){
			array[i++]=create(name,AND,inputname1,inputname2);
			}else if(strstr(type,"FLIPFLOP")){
			array[i++]=create(name,FLIPFLOP,inputname1,inputname2);
		    }
		    inputname2[0]=0;
		}	
	fclose(fileptr);
return count-1;
}

int recursivee (struct kapi *root) {// recursive
    if (root->type == INPUT)
        return root->deger;
    else if (root->type == OR) {
        return kapior(recursivee(root->input1), recursivee(root->input2)); 
    } else if (root->type == AND) {
        return kapiand(recursivee(root->input1), recursivee(root->input2));
    }else if (root->type == NOT) {
        return kapinot(recursivee(root->input1));
    }else if (root->type == FLIPFLOP) {
         root->deger=kapiflipflop(recursivee(root->input1),root->deger);
         return root->deger;
    } 
}

int main(){
  struct kapi **array;	
  int count=find_arraysize();
  int i,j;
  int okunan,arrindex,sonuc;  
  array=(struct kapi **)malloc(count*sizeof(struct kapi *));
  
  int count1=store(array);
  i=0;
  while(i<count){
  	j=0;
  	while(j<count){
  		if(0==strcmp(array[i]->inputname1,array[j]->name)){
  			array[i]->input1=array[j];
		}
		if(0==strcmp(array[i]->inputname2,array[j]->name)){
  		    array[i]->input2=array[j];
		}
  		j++;	
  	}
  	i++;
  }


	FILE *fileptr=fopen("input.txt","r");//read input - calculate- write output
	FILE *fout=fopen("output.txt","w");
		while(!feof(fileptr)){
			arrindex=0;
			while(arrindex<count1){
				fscanf(fileptr,"%d",&okunan);
				array[arrindex]->deger=okunan;
				arrindex++;
			}	
		sonuc=recursivee(array[count-1]);		
		fprintf(fout,"%d\n",sonuc);
		}
	fclose(fout);
	fclose(fileptr);
 return 0;
}