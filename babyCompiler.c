/*
Program: Basic compiler program able to print string number and basic evaluation of expression
Author: Sanket Kumar Mali
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int list=0;
//create and return list of token as a array of string
//lexer is a function taking string argument and returns array of string
char ** lexer(char *file)
{
    int i,track_token=0,state=0,j,k=0,state1=0,sign_state=0;
    puts(file);
    char symbol;
    //string retrieve upto currently fetched character.
    //it is used to matched with any meaningfull token
    char *current_token=malloc(sizeof(char));
    //extra pointer used to clear the current token 
    char *temp,*freememory;
    //string to store the expr 
    char *expr=malloc(sizeof(char)),*temp1;
    //array of string contains tokens of our program
    char ** token=malloc(sizeof(char *));
    for(i=0;i<strlen(file);i++)
    {
        symbol=file[i];
        current_token[track_token]=symbol;
        track_token++;
        //check if the current token is print
        if((strcmp(current_token,"print")==0) && state !=1)
        {
            temp=current_token;
            token[list]=temp;
            list++;
            //clear the current_token string to search new token
            track_token=0;
            free(freememory);
            char *freememory=malloc(sizeof(char));
            current_token=freememory;
        }
        //check the current character is double quotes or not
        else if(symbol=='\"')
        {
            //double quotes and state 0 means start of a string so make the state 1
            //mean everything come after this will be part of the string
            if(state==0)
            {
                state=1;
            }
            //double quotes and state 1 means end of string 
            //return the string and flush the current_token
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
        //check if current char is ; which specify end of line & w'll flush the current_token
        //in case state is 1 then ; will be part of string
        else if(symbol==';' && state1!=1)
        {
            track_token=0;
            free(freememory);
            char *freememory=malloc(sizeof(char));
            current_token=freememory;
        }
        //if state is not 1 means current char is not part of a string and char is a digit then it's part of a number or expression
        else if((symbol=='1' || symbol=='2' || symbol=='3' || symbol=='4' || symbol=='5' || symbol=='6' || symbol=='7' || symbol=='8'|| symbol=='9' || symbol=='0' || symbol==';') && state!=1)
        {
            //set state1 to 1 if it's start of a number or expression
            state1=1;
            //check if it's end of line
            if(symbol==';')
            {
                temp1=expr;
                //sign_state 1 means it contains arithmatic sign means it's a expression 
                //we append an extra portion "@:expr" at the end of expression to identify it later
                if(sign_state==1)
                {
                    token[list]=strcat(temp1,"@:expr");
                }
                //else it's a number so we append ":num" at the end of it
                else
                {
                    token[list]=strcat(temp1,":num");
                }
                list++;
                k=0;
                state1=0;//make state1 0 as the line ends and we get the num or expression
                //clear current_token
                track_token=0;
                free(freememory);
                char *freememory=malloc(sizeof(char));
                expr=freememory;//clear the expr string
                current_token=freememory;
            }   
            //if not end of line just add the digit in the number or expression
            else
            {
                expr[k]=symbol;
                k++;
            }
        }
        //if state is not 1 means it's not part of a string, state1 is 1 means it's part of a num or expression
        //and the symbol is a arithmatic sign 
        else if((state!=1 && (symbol=='-' || symbol=='+')) && state1==1)
        {
            sign_state=1;//set sign_state to 1
            expr[k]=symbol;//add the symbol to the expr
            k++;
        }
        //if the current token is space then ignore it
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
    return token;//return the list of token
}
//substr is a function that takes a string, start of substring, length of the substring and return the substring 
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
//evaluate expression
void evalexpr(char *expr)
{
    //puts(expr);
    char *firstnum=malloc(10*sizeof(char)),*freememory;
    int num1=0,num2=0,j=0,i=0;
    char sign,sign1;
    while(1)
    {
       // printf("expr:%c\n",expr[i]);
        //identify the sign in expression
        switch(expr[i])
        {
            case '+':
            sign1=sign;
            sign='+';
            break;
            case '-':
            sign1=sign;
            sign='-';
            break;
        }
        //if the char is not a sign and not the end of expr then add it to the number
        if(expr[i]!=sign && expr[i]!='@')
        {
            num1=num1*10+(expr[i++]-'0');
            //puts(firstnum);
            //printf("num1:%d\n",num1);
        }
        //if the char is a arithmatic sign
        else if(expr[i]==sign)
        {
            i++;
            //printf("sign1:%c sign:%c\n",sign1,sign);
            if(sign1=='+')//if sign is +
            num2=num2+num1;//add the number to already evaluated part
            else if(sign1=='-')//if sign is -
            {
                if(!num2)
                    num2=num1-num2;//in case first operation is -
                else
                    num2=num2-num1;//otherwise
            }
            else
            num2=num1;
            //printf("num2:%d\n",num2);
            num1=0;//reset num1
        }
        //end of expression
        else if(expr[i]=='@')
        {
            if(sign=='+')
            num2=num2+num1;//sign + add
            else if(sign=='-')
            {
                if(!num2)
                    num2=num1-num2;
                else
                    num2=num2-num1;
            }
            break;
        }
    }
    printf("%d\n",num2);
}
//parse meaningfull token and output them 
void parse(char **token)
{
    int i;
    for(i=0;i<list;i=i+2)
    {
        char *com_token=malloc(2*sizeof(token[i]));
        //concat two consecutive token to create a meaning full statement
        strcat(token[i],token[i+1]);
        com_token=token[i];
        puts(com_token);
        //identifying if the satement contains print in case of string
        if(strcmp(substr(com_token,0,6),"print\"")==0)
        {
            puts(substr(com_token,6,strlen(com_token)-7));
        }
        //print in case of number
        else if(strcmp(substr(com_token,strlen(com_token)-4,4),":num")==0 && strcmp(substr(com_token,0,5),"print")==0)
        {
            puts(substr(com_token,5,strlen(com_token)-9));
        }
        //call evalexpr function in case of expression
        else if(strcmp(substr(com_token,0,5),"print")==0 && strcmp(substr(com_token,strlen(com_token)-5,5),":expr")==0)
        {
           // evalexpr(com_token,5,strlen(com_token)-10);
           evalexpr(substr(com_token,5,strlen(com_token)-10));
           //puts(substr(com_token,5,strlen(com_token)-10));
        }
        
    }

}
//main function for taking file input and convert it to a string call function lexer with the string 
int main(int argc , char *argv[])
{
    FILE *fp;//file pointer
    int i;
    char c;
    char *file=(char *)malloc(10*sizeof(char));
    //open file
    for(i=0;i<argc;i++)
    {
        fp=fopen(argv[i],"r");
    }
    if(fp==NULL)
    {
        printf("Sorry can't open the file\n");
    }
    i=0;
    //ignore newline and space
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
    fclose(fp);
    //call the lexer function which return list of token
    char **ret_token_list=lexer(file);
    //printf("%d\n",list);
    //parse those token
    parse(ret_token_list);
    //evalexpr("46+7@");
    return 0;
}
