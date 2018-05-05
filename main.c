#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLETTER 20
#define MAXKEY 50
extern int search(char id);
struct KEY{
    int syn;
    union{
      char Token[MAXLETTER];
      int Sum;
    }value;
    };

char *tab1[26]={"main","if","then","while","do","static",
"int","double","struct","break","else","long","switch",
"case","typdef","char","return","const","float","short",
"continue","for","void","sizeof","default"};

char *tab2[16]={"+","-","*","/",":",":=","<","<>","<=",">",">=","=",
";","(",")","#"};


char* ReadFile(char *filename)
{
    char *buffer=NULL;
    int string_size;
    FILE *handler =fopen(filename,"r");

    if(handler)
    {
        fseek(handler,0,SEEK_END);
        string_size=ftell(handler);
        rewind(handler);
        int i=0;
        char ch;
        buffer=(char*)malloc(sizeof(char)*(string_size+1));
        while((ch=getc(handler))!=EOF)
          *(buffer+i++)=ch;
        *(buffer+i)='\0';
        printf("i=%d,string_size=%d\n",i,string_size);
        fclose(handler);
        return buffer;
   }
   return NULL;
}

int isNum(char c){
    if(c>=0x30&&c<=0x39)
      return 1;
    else
      return 0;
}

int isLetter(char c){
    if(c>=0x61&&c<=0x7A)
      return 1;
    else
      return 0;
}

int isLetterplus(char c){
    if(c>=0x41&&c<=0x5A)
      return 1;
    else
      return 0;
}

int Scans(struct KEY key[],char* string){
    int status=0;
    int i=0,j=0,o=0,n=0;
    char Token[MAXLETTER],ch;
    int sum=0;
    int flag=0;
    ch=*(string+i);

    while(status!=18){
      switch(status){
        case 0:
          if(ch==' '){
            i++;
            ch=*(string+i);
            status=0;
            break;
            }
          if(isLetter(ch)||isLetterplus(ch)){
            status=1;
            break;
          }
          if(isNum(ch)){
            sum=(int)(ch-'0');
            status=3;
            break;
          }
          if(ch=='<'){
            status=5;
            break;
          }
          if(ch=='>'){
            status=9;
            break;
            }
          if(ch==':'){
            status=12;
            break;
            }
          if(ch=='\0'){
            status=18;
            break;
          }else{
            status=15;
            break;
          }
        case 1:
          i++;
          Token[j++]=ch;
          ch=*(string+i);
          if(!isLetter(ch)&&!isLetterplus(ch)&&!isNum(ch))
            status=2;
           // printf("1i=%d\n",i);
          break;

        case 2:
          Token[j]='\0';
          //printf("Token=%s\n",Token);
          if(isLetter(Token[0])){
           for(o=0;o<25;o++){
            if(0 == strcmp(Token,tab1[o])){
              strcpy(key[n].value.Token,Token);
                if(o==25){
                  key[n].syn=39;
                }
                else
                  key[n].syn=o+1;
                n++;
                flag=1;
                o=0;
                break;
            }//识别得出一个关键字
           }
        }
           if(flag==1){
             status=0;
             memset(Token,0,sizeof(Token));
             j=0;
             flag=0;
            // printf("2.1i=%d\n",i);
             break;
             }else{
               status=0;
               strcpy(key[n].value.Token,Token);
                      key[n].syn=25;
                      n++;
                      memset(Token,0,sizeof(Token));
                      j=0;
                     // printf("2.2i=%d\n",i);
                      break;//识别出一个标识符
             }
           case 3:
             i++;
             ch=*(string+i);
             if(isNum(ch)){
               sum+=10*(int)(ch-'0');
               status=3;
            //   printf("3i=%d\n",i);
               break;
             }else{
               status=4;
            //   printf("3i=%d\n",i);
               break;
               }
           case 4:
             key[n].syn=26;
             key[n].value.Sum=sum;
             n++;
             status=0;
           //  printf("4i=%d\n",i);
             break;//识别存储数字
           case 5:
             i++;
             Token[j++]=ch;
             ch=*(string+i);
             if(ch=='='){
               status=6;
           //     printf("5i=%d\n",i);
               break;
             }else if(ch=='>'){
               status=8;
            //   printf("5i=%d\n",i);
               break;
             }else{
               status=7;
           //    printf("5i=%d\n",i);
               break;
             }

           case 6:
             Token[j++]=ch;
             Token[j]='\0';
             key[n].syn=35;
             strcpy(key[n].value.Token,Token);
             n++;
             status=0;
             memset(Token,0,sizeof(Token));
             j=0;
             i++;
             ch=*(string+i);
          //   printf("6i=%d\n",i);
             break;//识别出<=
           case 7:
             key[n].syn=33;
             Token[j]='\0';
             strcpy(key[n].value.Token,Token);
             n++;
             status=0;
             memset(Token,0,sizeof(Token));
             j=0;
          //   printf("7i=%d\n",i);
             break;//识别出'<'

           case 8:
             Token[j++]=ch;
             Token[j]='\0';
             key[n].syn=34;
             strcpy(key[n].value.Token,Token);
             n++;
             status=0;
             memset(Token,0,sizeof(Token));
             j=0;
             i++;
             ch=*(string+i);
          //   printf("8i=%d\n",i);
             break;//识别出'<>'

          case 9:
            Token[j++]=ch;
            i++;
            ch=*(string+i);
            if(ch=='='){
              status=10;
           //   printf("9.1i=%d\n",i);
              break;
            }else{
              status=11;
           //   printf("9.2i=%d\n",i);
              break;
              }

          case 10:
             Token[j++]=ch;
             Token[j]='\0';
             key[n].syn=37;
             strcpy(key[n].value.Token,Token);
             n++;
             status=0;
             memset(Token,0,sizeof(Token));
             j=0;
             i++;
             ch=*(string+i);
          //   printf("10i=%d\n",i);
             break;//识别出'>='

          case 11:
            key[n].syn=36;
            Token[j]='\0';
            strcpy(key[n].value.Token,Token);
            n++;
            status=0;
            memset(Token,0,sizeof(Token));
            j=0;
         //   printf("11i=%d\n",i);
            break;

          case 12:
            Token[j++]=ch;
            i++;
            ch=*(string+i);
            if(ch=='='){
              status=13;
          //    printf("12i=%d\n",i);
              break;
              }else{
              status=14;
           //   printf("12i=%d\n",i);
              break;
              }

          case 13:
            Token[j++]=ch;
            Token[j]='\0';
            i++;
            ch=*(string+i);
            key[n].syn=32;
            strcpy(key[n].value.Token,Token);
            n++;
            status=0;
            memset(Token,0,sizeof(Token));
            j=0;
         //   printf("13i=%d\n",i);
            break;

          case 14:
            key[n].syn=31;
            Token[j]='\0';
            strcpy(key[n].value.Token,Token);
            n++;
            status=0;
            memset(Token,0,sizeof(Token));
            j=0;
         //   printf("14i=%d\n",i);
            break;

          case 15:
            Token[j++]=ch;
            Token[j]='\0';
            if(search(ch)!=-1){
              status=16;
           //   printf("15.1i=%d\n",i);
              break;
              }else{
              status=17;
          //    printf("15.2i=%d\n",i);
              break;
              }

          case 16:
            key[n].syn=search(ch);
         //   printf("16ch=%c\n",ch);
            strcpy(key[n].value.Token,Token);
            //printf("key[%d].Token=%s\n",n,key[n].Token);
            n++;
            status=0;
            memset(Token,0,sizeof(Token));
            j=0;
            i++;
            ch=*(string+i);
         //   printf("16i=%d\n",i);
            break;

         case 17:
           printf("Wrong char input:");
           printf("%c\n",ch);
           printf("press a key to end\n");
           getchar();
           exit(0);
           printf("17i=%d\n",i);
           break;
}
    }
    return n;
    }

    void firstDeal(char *buffer,char *string){
      int i=0,j=0;
       while(*(buffer+i)!='\0'){
          if(*(buffer+i)=='/'){
            if(*(buffer+i+1)=='/'){
              while(*(buffer+i)!='\n')
                i++;
              continue;
              }  //跳过注释
          }

          if(*(buffer+i)=='\n'){
            i++;
            continue;  //跳过换行
            }

          if(*(buffer+i)=='/')
            if(*(buffer+i+1)=='*'){
              while(*(buffer+i)!='*'||*(buffer+i+1)!='/')
                i++;
                i=i+2;
                continue; }

            if(*(buffer+i)==' '){
              if(*(buffer+i+1)==' '){
                while(*(buffer+i+1)==' ')
                i++;
                continue;//跳过空格
              }
            }
          *(string+j)=*(buffer+i);
          j++;
          i++;//录入合法字符
       }
   *(string+j)='\0';
    }



   int main(){
       int n,i;
       char *buffer=ReadFile("input.txt");
       char *string=NULL;
       string=(char*)malloc(sizeof(char)*500);
       firstDeal(buffer,string);
       if(string){
       //puts(buffer);
       puts(string);
       }
       struct KEY key[MAXKEY];
       n=Scans(key,string);
       printf("total key:%d\n",n);
       for(i=0;i<n;i++){
           if(key[i].syn==26)
            printf("<syn=%d  %d  >\n",key[i].syn,key[i].value.Sum);
           else
            printf("<syn=%d  %s  >\n",key[i].syn,key[i].value.Token);

         }
       free(string);
       free(buffer);
       return 0;
   }

