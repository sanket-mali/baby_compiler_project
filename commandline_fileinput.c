#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int list=0;
char ** lexer(char *file)
{
    int i,track_token=0,state=0,j;
    puts(file);
    char symbol;
    char *current_token=malloc(sizeof(char)),*temp,*freememory;
    char ** token=malloc(sizeof(char *));
    for(i=0;i<strlen(file);i++)
    {
        current_token[track_token]=file[i];
        symbol=file[i];
        //puts(current_token);
        track_token++;
        if((strcmp(current_token,"print")==0) && state !=1)
        {
            printf("found print\n");
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
                printf("first quote\n");
                state=1;
            }
            else if(state==1)
            {
                printf("found string\n");
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
        else if(strcmp(current_token," ")==0 && state!=1)
        {
            printf("found space\n");
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
    for(i=start;i<length;i++)
    {
        substring[j]=str[i];
        j++;
    }
    return substring;
}
void parse(char **token)
{
    int i;
    for(i=0;i<list;i=i+2)
    {
       /* char *com_token=malloc(2*sizeof(token[i]));
        strcat(token[i],token[i+1]);
        com_token=token[i];
        if(strcmp(com_token,"print\""))*/
        strcat(token[i],token[i+1]);
        puts(token[i]);
        puts(substr(token[i],0,6));
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
    /*printf("%d\n",list);
    for(i=0;i<list;i=i+2)
    {
        printf("%s %s\n",ret_token_list[i],ret_token_list[i+1]);
    }*/
    parse(ret_token_list);
    return 0;
}
