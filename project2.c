#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <getopt.h>

void remove_nonalpha(char *input);

typedef struct node {
  int count;
  struct node * next;
  char word[100];
} node;

int main (int argc, char **argv){

  FILE *pFile;

  double max_freq;
  int temp_max_count=0;
  int freq;
  char input[100];
  char input_x;
  int max_count=0;
  int number=0;
  int max_length=0;
  double percentage;
  int plot_area;
  int pattern;
  int word_sum;

  int w_flag = 0;
  int c_flag = 0;
  int l_value = 10;
  static int s_flag=0;
  char buffer[20];
  char buffer1[10];
  int a;

  opterr = 0;
  int option_index = 0;
  static struct option long_options[] =
        {
          {"scaled", no_argument, &s_flag, 1},                    
          {0, 0, 0, 0}
        };


  if(argc < 2){
    printf("No input files were given\nusage: freq [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n");
    return 0;
  }

  while ((a = getopt_long (argc, argv, "wcl:",long_options, &option_index)) != -1)
    switch (a){
      case 'w':
        w_flag = 1;
        if(w_flag==1 && c_flag==1){
        printf("[-c] and [-w] cannot use together\nusage: freq [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n");
        return 0;
        }
      break;
      
      
      case 'c':
        c_flag = 1;
        if(w_flag==1 && c_flag==1){
        printf("[-c] and [-w] cannot use together\nusage: freq [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n");
        return 0;
        }
      break;

      
      case 'l':
        l_value = atoi(optarg);
        
        if(strcmp("0",optarg)==0){
          return 0;
        }

        if(l_value==0){
          printf("Invalid options for [-l]\nusage: freq [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n");
          return 0;
        }
       
        sprintf(buffer,"%d",l_value);
        if(strcmp(buffer,optarg)!=0){
          printf("Invalid options for [-l]\nusage: freq [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n");
          return 0;
        }
        else if(l_value<0){
          printf("Invalid option for [-l]\nusage: freq [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n");
          return 0;
        }
      break;
      

      case '?':
        if (optopt == 'l'){     // When no value for l is specified
          printf("Not enough options for [-l]\nusage: freq [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n");
          return 0;
        } 
        else if (isprint (optopt)){
          printf("Invalid option [-%c]\nusage: freq [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n", optopt);
          return 0;
        }
        else {
          printf("Invalid option [%s]\nusage: freq [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n", argv[optind-1]);
          return 0;
        }

        default: break;  
      }


      if((optind)==argc){  // No input files are given
        printf("No input files were given\nusage: freq [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n");
        return 0;
      }
      

      if(c_flag==0){      // Default option
        w_flag=1;
      }
      

if(w_flag==1) {
    
  node *head;    
  head = (node*)malloc(sizeof(node));
  head->count=0;
  head->next=NULL;
    
  for(int i=optind;i<argc;i++){      // Iterating through each text file
    pFile = fopen(argv[i],"r");
      
    if(pFile==NULL){    // For files of incorrect format
      printf("Cannot open one or more given files\n");
      return 0;
    }
    
    node *new_node;
    node *current;
    
    while(fscanf(pFile,"%s",input) != EOF){
      current=head->next;
      remove_nonalpha(input);     
      
      if(strlen(input)==0){     // When input is a null character
        continue;
      }
      head->count=(head->count)+1;
      
      while(current!=NULL){
        if(strcmp(input,current->word)==0){
          current->count=(current->count)+1;
          break;            
        }
        else{
        current=current->next;
        }
      }

      if(current==NULL){
        new_node = (node*)malloc(sizeof(node));
        strcpy(new_node->word,input);
        new_node->count=1;        
        new_node->next=head->next;
        head->next=new_node;    
      }
    }
    fclose(pFile);
  }
   
    word_sum=head->count;     // Total number of words in all the input files
    node *current;
    current = head->next;
    node *max_node;
      
      while(current!=NULL){
        number=number+1;
        current=current->next;
      }

      if (number<l_value){
        l_value=number;
      }

      node *temp_head;    
      temp_head = (node*)malloc(sizeof(node));
      temp_head->next=NULL;
      node *new_node;
      current = head->next;
  

      for(int i=0;i<l_value;i++){
        while(current!=NULL){
          if((current->count)>=max_count){
            max_count=current->count;
            max_node=current;

             
          }
          current=current->next;    
        }
        new_node = (node*)malloc(sizeof(node));
        strcpy(new_node->word,max_node->word);
        new_node->count=max_node->count;        
        new_node->next=temp_head->next;
        temp_head->next=new_node; 

        if((strlen(max_node->word))>max_length){
          max_length=strlen(max_node->word);
        }
        
        max_node->count=0;
        max_count=0;
        current=head->next;
      }
      max_count=0;

    /*
      node * temp;  // Printing the linked list
      temp=temp_head->next;
 
      while(temp!=NULL){
        printf("%s\t%d\n",temp->word,temp->count);
        temp=temp->next;
      }
      printf("%d\n",max_length);
      */
      

      current = temp_head->next;
      while(current!=NULL){
          if((current->count)>=max_count){
            max_count=current->count;
            max_node=current;
          }
          current=current->next;          
      }

      max_freq =((double)max_count/word_sum*100);
      temp_max_count = max_count;
      sprintf(buffer1,"%.2f",max_freq);
      
      plot_area = 80-strlen(buffer1)-4-max_length;     
      if(s_flag==1){    // Scaled option
        pattern=(plot_area*max_count)/(temp_max_count); 
      }
      else{
        pattern=(plot_area*max_count)/(word_sum);
      }

      
      printf("\n");
      for(int i=0;i<(max_length+2);i++){
          printf(" ");
        }
        printf("│");
        
        for(int j=0;j<pattern;j++){
          printf("░");
        }
        printf("\n");

        printf(" %s",max_node->word);
        for(int i=0;i<(max_length-(strlen(max_node->word)-1));i++){
          printf(" ");
        }
        printf("│");
        
        for(int j=0;j<pattern;j++){
          printf("░");
        }
        printf("%0.2f%%\n",max_freq);

      for(int i=0;i<(max_length+2);i++){
          printf(" ");
        }
        printf("│");
        
        for(int j=0;j<pattern;j++){
          printf("░");
        }
        printf("\n");

      for(int i=0;i<(max_length+2);i++){
          printf(" ");
        }
        printf("│\n");
      
      max_node->count=0;
      max_count=0;
      current=temp_head->next;


      for(int i=1;i<l_value;i++){
          while(current!=NULL){
            if((current->count)>=max_count){
              max_count=current->count;
              max_node=current;
            }
            current=current->next;          
          }
      
        percentage =  ((double)max_count/head->count)*100;
        if(s_flag==1){    // Scaled option
          pattern=(plot_area*max_count)/(temp_max_count); 
        }
        else{
          pattern=(plot_area*max_count)/(word_sum);
        }
          

        for(int i=0;i<(max_length+2);i++){
            printf(" ");
          }
        printf("│");
        
        for(int j=0;j<pattern;j++){
          printf("░");
        }
        printf("\n %s",max_node->word);
        
        for(int i=0;i<(max_length-(strlen(max_node->word)-1));i++){
          printf(" ");
        }
        printf("│");
          
        for(int j=0;j<pattern;j++){
          printf("░");
        }
        printf("%0.2f%%\n",percentage);

        for(int i=0;i<(max_length+2);i++){
            printf(" ");
        }
        printf("│");
          
        for(int j=0;j<pattern;j++){
          printf("░");
        }
        printf("\n");

        for(int i=0;i<(max_length+2);i++){
          printf(" ");
        }
        printf("│\n");

        max_node->count=0;
        max_count=0;
        current=temp_head->next;
      }


      for(int i=0;i<(max_length+2);i++){    // Bottomline
          printf(" ");
      }
      printf("└");
      for(int i=0;i<(80-(max_length+3));i++){
        printf("─");
      }
      printf("\n");
      
}

if(c_flag==1){
  char character_array[36]= {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8','9'};
  int count_array[36]= {0};
  int order[36]={0};
  int k=1;
  int char_sum=0;
  int position=0;

  for(int i=optind;i<argc;i++){   // Iterating throught the input files
      pFile = fopen(argv[i],"r");

    if(pFile==NULL){   // For files of incorrect format
      printf("Cannot open one or more given files\n");
      return 0;
    }

    while(fscanf(pFile,"%c",&input_x) != EOF){
      if(isalpha(input_x) || isdigit(input_x)){
        input_x=tolower(input_x);
      }
      else{
        continue;
      }

      for(int i=0;i<36;i++){
        if(input_x==character_array[i]){
          count_array[i]=count_array[i]+1;
          char_sum=char_sum+1;    // Total number of characters in all the input files
          if(order[i]==0){
            order[i]=k;
            k++;
          }
          break;
        }
      }
    }
  fclose(pFile);
  }
      
  for(int i=0;i<36;i++){
      if(count_array[i]!=0){
        number=number+1;
      }
  }

  if(number<l_value){
    l_value=number;
  }
    
    for(int i=0;i<36;i++){
      if(count_array[i]>max_count){
        max_count=count_array[i];
        position=i;
        max_freq=((float)max_count/char_sum*100); 
      }
      else if(count_array[i]==max_count && max_count!=0){
        if(order[i]<order[position]){
          max_count=count_array[i];
          position=i;
          max_freq=((float)max_count/char_sum*100); 
        }
      }
    }
    temp_max_count=max_count;
    sprintf(buffer1,"%.2f",max_freq);

    plot_area=76-strlen(buffer1)-1;
    if(s_flag==1){
      pattern=(plot_area*max_count)/(temp_max_count);
    }
    else{
      pattern=(plot_area*max_count)/(char_sum);
    }

      printf("\n   │");
      for(int j=0;j<pattern;j++){
        printf("░");
      }
      printf("\n %c │",character_array[position]);
  
      for(int j=0;j<pattern;j++){
        printf("░");
      }
      printf("%0.2f%%\n   │",max_freq);

      for(int j=0;j<pattern;j++){
        printf("░");
      }
      printf("\n   │");

    count_array[position]=0;
    max_count=0;
   

    for(int j=1;j<l_value;j++){
      for(int i=0;i<36;i++){
        if(count_array[i]>max_count){
          max_count=count_array[i];
          position=i;  
        }
        else if(count_array[i]==max_count && max_count!=0){
          if(order[i]<order[position]){
            max_count=count_array[i];
            position=i;
          }
        } 
      }

      percentage=((float)max_count/char_sum*100);
      if(s_flag==1){
        pattern=(plot_area*max_count)/(temp_max_count);
      }
      else{
        pattern=(plot_area*max_count)/(char_sum);
      }
    
      printf("\n   │");
      for(int j=0;j<pattern;j++){
        printf("░");
      }
      printf("\n %c │",character_array[position]);
  
      for(int j=0;j<pattern;j++){
        printf("░");
      }
      printf("%0.2f%%\n   │",percentage);

      for(int j=0;j<pattern;j++){
        printf("░");
      }
      printf("\n   │");

      count_array[position]=0;
      max_count=0;
     
    }
      printf("\n   └");
      for(int i=0;i<76;i++){
          printf("─");
      }
      printf("\n"); 

}

  return 0;
}

void remove_nonalpha(char *input){

  for(int i=0;i<strlen(input);i++){
    if(isalpha(input[i]) || isdigit(input[i])){
      input[i]=tolower(input[i]);
    }
    else{
      for(int j=i;j<strlen(input);j++){
      input[j]=input[j+1];
      }
      i--;
    }
  }
}
