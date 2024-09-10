#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define MX_size 100 // Maximum size
// Reading function 
void read_function(FILE *inf1, FILE *inf2, double multiple[MX_size],double exponent[MX_size],int *valunumber,int *polnum, double value[MX_size]);
// The Calculating and writing func.
void calculation_function(double multiple[MX_size],double exponent[MX_size],int valunumber,int polnum ,double value[MX_size], FILE *outf);

int main(void) {

  char polynomial[MX_size]; 
  char values;
  double value[MX_size]; // values
  int i=0;
  double x;
  double multiple[MX_size];
  double exponent[MX_size];
  int k=0;
  
  double result=0;
  int valunumber=0;
  int polnum=0;
  // Opening input and output file
  FILE *inf1 = fopen("values.txt", "r");
  FILE *inf2 = fopen("polynomial.txt", "r");
  FILE *outf = fopen("evaluations.txt", "w");

  read_function(inf1, inf2, multiple, exponent,&valunumber,&polnum,value);
  calculation_function(multiple, exponent, valunumber, polnum, value, outf);

fclose(inf1);
fclose(inf2);
fclose(outf);

return 0;
}
  
void read_function(FILE *inf1, FILE *inf2, double multiple[MX_size],double exponent[MX_size],int *valunumber, int *polnum, double value[MX_size]){

  char polynomial[MX_size]; 
  char values;
  // values
  int i=0;
  double x;
  int k=0;
  double result=0;
  

  do{
  	x=fscanf(inf1,"%lf%c",&value[i],&values); 
  	i++;
  }while(values!='\0' && x!=1  && i<MX_size);
  *valunumber=i;
	fgets(polynomial, MX_size ,inf2);
	i=0;

	while(polynomial[i]!='\0'){
		if(polynomial[i]=='-'){  //enters here if the operator is negative
						i++;
					if(polynomial[i]!='x'){	 // multiple
							sscanf(&polynomial[i],"%lf",&multiple[k]); // reading multiple 
							multiple[k]=-multiple[k];

							while(polynomial[i]!='x'){
							
								i++;
							}
							i++;
							
							if(polynomial[i]=='^'){ //operator
								i++;
								sscanf(&polynomial[i],"%lf",&exponent[k]); // Reading exponent
									while(polynomial[i]!=' ' && polynomial[i]!='\0' && polynomial[i]!='-' && polynomial[i]!='+'){
										i++;
									}
							}
							else{
								exponent[k]=1;
							}			
						}
						else{ // if non multiple so multiple is default -1
							multiple[k]=-1;
							i++;
							if(polynomial[i]=='^'){ //operator
								i++;
								sscanf(&polynomial[i],"%lf",&exponent[k]);
								while(polynomial[i]!=' ' && polynomial[i]!='\0' && polynomial[i]!='-' && polynomial[i]!='+'){
									i++;
								}
							}
							else{
								exponent[k]=1; // IF NON exponent so exponent is default 1
							}			
						}	
				} 
		else if(polynomial[i]=='+' || i==0){  //enters here if the operator is positive
				if(i!=0)
					i++;
				if(polynomial[i]!='x'){	 // katsayi
						sscanf(&polynomial[i],"%lf",&multiple[k]);
						while(polynomial[i]!='x'){
						
							i++;
						}
						i++;
						
						if(polynomial[i]=='^'){ //operator
							i++;
							sscanf(&polynomial[i],"%lf",&exponent[k]);
								while(polynomial[i]!=' ' && polynomial[i]!='\0' && polynomial[i]!='-' && polynomial[i]!='+'){
									i++;
								}
						}
						else{
							exponent[k]=1; //  if non exponent so exponent is default 1
						}			
					}
					else{         //operator
						multiple[k]=1; // if non multiple so multiple is default 1
						i++;
						if(polynomial[i]=='^'){
							i++;
							sscanf(&polynomial[i],"%lf",&exponent[k]);
							while(polynomial[i]!=' ' && polynomial[i]!='\0' && polynomial[i]!='-' && polynomial[i]!='+'){
								i++;
							}
						}
						else{
							exponent[k]=1; // if non exponent so exponent is default 1
						}			
					}	
				}
						
				k++;
			}

		i=0;
		*polnum=k;

}


void calculation_function(double multiple[MX_size],double exponent[MX_size],int valunumber,int polnum,double value[MX_size],FILE *outf){

	int i;
	double result;
	int k;

	for(i=0;i<valunumber;i++){
		for(k=0;k<polnum;k++){
			result=result+multiple[k]*pow(value[i],exponent[k]);
		}
		fprintf(outf ,"%.2lf\n",result);
		result=0;
	}
}


