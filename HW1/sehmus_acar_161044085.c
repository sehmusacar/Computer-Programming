//Hocam kod file.txt dosyanın sonunda 100 konulduğu zaman duruyor yoksa sonsuz döngüye giriyor.





#include <stdio.h>
#include<math.h>
int basamak(int x);
int bosluk_sayici(FILE * fp);
int main(void) {
  FILE *fp = fopen("file.txt", "r+");
  char c;
  int m=0;
  int first_num=0;
  int second_num=0;
  int bas_number=0;
  int bosluk_sayisi=0;
  int total=0;
  int total_1=0;
  int new_bas;
  int s=0;
  int total_2;
    fseek(fp,0,SEEK_END); // go to the end of the file
    total=ftell(fp);  //find out how many characters
    m=0;
    fseek(fp,0,SEEK_SET); //return to the beginning of the file
    


    while(first_num!=100){
      fscanf(fp,"%d",&first_num); // read number and we keep first number
      bosluk_sayici(fp);  //pass the space
      total_1=ftell(fp); //find how many characters you have so far
      if(first_num!=100)
        fscanf(fp,"%d",&second_num);
      if(first_num==100)
        second_num=100;
     
      while( second_num!=100){     
          fscanf(fp,"%d",&second_num); //read second number
        new_bas=basamak(second_num); //We take the number 2 and save it continuously
       
        if(first_num==second_num){
          m=0; //if the numbers are the same
          total_2=ftell(fp); //find the number of characters so far
            fseek(fp,total_2-new_bas,SEEK_SET); //subtract the number of digits from the number of characters 
          
          m=0;
          while(m<new_bas){ 
            fprintf(fp," "); //substitute for the same numbers
            m++;   
         }
        }
        bosluk_sayici(fp);
       
      }

      m=0;
      
        fseek(fp,total_1,SEEK_SET);
      bosluk_sayici(fp);
      
  } 
 return 0 ; 
}
int basamak(int x){ //digit counting function
  int bas_number=0;
  while(x>=1){
    x=x/10;
    bas_number++;
  }
  return bas_number;

}
int bosluk_sayici(FILE * fp){//space counting function
  int i=0;
  int m=0;
  char c;
  fscanf(fp,"%c",&c);
  while(c==' '){
    i++;
    fscanf(fp,"%c",&c);
  }
    
  fseek(fp,-1L,SEEK_CUR);
  return i;

}
