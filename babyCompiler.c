#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int list=0;
char ** lexer(char *file)
{
    int i,track_token=0,state=0,j,k=0,state1=0,sign_state=0;
    puts(file);
    char symbol;
    char *current_token=malloc(sizeof(char)),*temp,*freememory,*expr=malloc(sizeof(char)),*temp1;
    char ** token=malloc(sizeof(char *));
    for(i=0;i<strlen(file);i++)
    {
        symbol=file[i];
        current_token[track_token]=symbol;
        track_token++;
        if((strcmp(current_token,"print")==0) && state !=1)
        {
            temp=current_token;
            token[list]=temp;
            list++;
            track_token=0;
            free(freememory);
            char *freememory=malloc(sizeof(char));
            current_token=freememory;
        }
        else if(symbol=='\"')
        {
            if(state==0)
            {
                state=1;
            }
            else if(state==1)
            {
                state=0;
                temp=current_token;
                token[list]=temp;
                list++;
                track_token=0;
                free(freememory);
                char *freememory=malloc(sizeof(char));
                current_token=freememory;
            }
        }
        else if(symbol==';' && state1!=1)
        {
            track_token=0;
            free(freememory);
            char *freememory=malloc(sizeof(char));
            current_token=freememory;
        }
        else if((symbol=='1' || symbol=='2' || symbol=='3' || symbol=='4' || symbol=='5' || symbol=='6' || symbol=='7' || symbol=='8'|| symbol=='9' || symbol=='0' || symbol==';') && state!=1)
        {
            state1=1;
            if(symbol==';')
            {
                temp1=expr;
                if(sign_state==1)
                {
                    token[list]=strcat(temp1,":expr");
                }
                else
                {
                    token[list]=strcat(temp1,":num");
                }
                list++;
                k=0;
                state1=0;
                track_token=0;
                free(freememory);
                char *freememory=malloc(sizeof(char));
                expr=freememory;
                current_token=freememory;
            }   
            else
            {
                expr[k]=symbol;
                k++;
            }
        }
        else if((state!=1 && symbol=='+') && state1==1)
        {
            sign_state=1;
            expr[k]='+';
            k++;
        }
        else if(strcmp(current_token," ")==0 && state!=1)
        {
            track_token=0;
            free(freememory);
            char *freememory=malloc(sizeof(char));
            current_token=freememory;
        }
        else
        {

        }
    }
    return token;
}
char *substr(char *str,int start,int length)
{
    char *substring=malloc(sizeof(str));
    int i,j=0;
    for(i=start;i<start+length;i++)
    {
        substring[j]=str[i];
        j++;
    }
    return substring;
}
void evalexpr()
{
    
}
void parse(char **token)
{
    int i;
    for(i=0;i<list;i=i+2)
    {
        char *com_token=malloc(2*sizeof(token[i]));
        //if()
        strcat(token[i],token[i+1]);
        com_token=token[i];
        puts(com_token);
        if(strcmp(substr(com_token,0,6),"print\"")==0)
        {
            puts(substr(com_token,6,strlen(com_token)-7));
        }
        else if(strcmp(substr(com_token,strlen(com_token)-4,4),":num")==0 && strcmp(substr(com_token,0,5),"print")==0)
        {
            puts(substr(com_token,5,strlen(com_token)-9));
        }
        else if(strcmp(substr(com_token,0,5),"print")==0 && strcmp(substr(com_token,strlen(com_token)-5,5),":expr")==0)
        {
            evalexpr(com_token,5,strlen(com_token)-10);
        }
        /*else
        {
            printf("ok");
            printf("check your program at line no:%d\n",i/2);
        }*/
    }

}
int main(int argc , char *argv[])
{
    FILE *fp;
    int i;
    char c;
    char *file=(char *)malloc(10*sizeof(char));
    for(i=0;i<argc;i++)
    {
        fp=fopen(argv[i],"r");
    }
    if(fp==NULL)
    {
        printf("Sorry can't open the file\n");
    }
    i=0;
    while((c=getc(fp))!=EOF)
    {
        if(c=='\n')
        {
            c=' ';
        }
        if(c==' ')
        {
            c=' ';
        }
        file[i] = c;
        i++;
    }
    //puts(file);
    fclose(fp);
    char **ret_token_list=lexer(file);
    //int len=strlen(ret)/;
    printf("%d\n",list);
    for(i=0;i<list;i++)
    {
      //  printf("lex:%s\n",ret_token_list[i]);
    }
    parse(ret_token_list);
    return 0;
}
