#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int is_in_array(int arr[100], int number, int count)
{
  /*  
    Function that checks is that number occurs in array
    If number is in array function returns index of number
    Otherwise it returns -1
  */
  int i, index=-1;
  for(i=0; i<count; i++)
    if(arr[i] == number)
      index = i;
  return index;
}

void fill_array_with_zeros(int arr[100])
{
  // To make sure, that function fills whole array with zeros
  int i;
  for(i=0; i<100; i++)
    arr[i] = 0;
}

void sort(int numbers[100], int occurences[100], int count)  
{  
    int i, j, temp_number, temp_occurence;
    for (i = 0; i < count-1; i++)
    {
      for (j = 0; j < count-i-1; j++)  
        if (occurences[j] > occurences[j+1] || (occurences[j] == occurences[j+1] && numbers[j] > numbers[j+1]))
        {
          // Swap
          temp_number = numbers[j];
          temp_occurence = occurences[j];
          numbers[j] = numbers[j+1];
          occurences[j] = occurences[j+1];
          numbers[j+1] = temp_number;
          occurences[j+1] = temp_occurence;
        }
    }
}

int main(void) {
  // Opening input and output file
  FILE *inf = fopen("input.txt", "r");
  FILE *outf = fopen("output.txt", "w");

  char buffer[100], temp[5];
  int count=0, i, j, numbers[100], occurences[100], temp_num, num_index;

  // Fill arrays with zeros to get rid of junk values
  fill_array_with_zeros(numbers);
  fill_array_with_zeros(occurences);


  // A loop reads a line in input file
  while( fgets(buffer, 99, inf) )
  {
    // Skip space characters
    for(i=0 ; i < strlen(buffer); ++i)
    {
      while(buffer[i] == ' ')
        i++;

      for(j=0; buffer[i] != ' ' && buffer[i] != '\n' && buffer[i] != '\0'; i++)
        temp[j++] = buffer[i];
      
      temp[j] = '\0';

      // Convert temp number's characters to integer      
      temp_num = atoi(temp);

      num_index = is_in_array(numbers, temp_num, count);
      // Num_index = -1 means there is not this number in occurences array
      if( num_index == -1 )
      {
        numbers[count] = temp_num;
        occurences[count]++;
        count++;
      }
      else
        occurences[num_index]++;
    }
  }

  // Sort before write into output.txt
  sort(numbers, occurences, count);

  // Write into output.txt file
  for(i=0; i<count; i++)
  {
    fprintf(outf, "%d:%d", numbers[i], occurences[i]);
    // Do not add new line at last line
    if(i<count-1)
      fprintf(outf, "\n");
  }

  return 0;
}