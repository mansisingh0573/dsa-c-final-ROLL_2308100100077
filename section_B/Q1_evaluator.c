#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 200

char opStack[MAX];
int opTop = -1;

char postfix[MAX][20];
int postSize = 0;

int valStack[MAX];
int valTop = -1;

void pushOp(char c)
{
    opStack[++opTop] = c;
}

char popOp()
{
    return opStack[opTop--];
}

char peekOp()
{
    return opStack[opTop];
}

int isEmptyOp()
{
    return opTop == -1;
}

void pushVal(int x)
{
    valStack[++valTop] = x;
}

int popVal()
{
    return valStack[valTop--];
}

int precedence(char op)
{
    if(op=='+' || op=='-')
        return 1;
    if(op=='*' || op=='/')
        return 2;
    return 0;
}

int infixToPostfix(char input[])
{
    char *token = strtok(input," ");

    while(token != NULL)
    {
        if(isdigit(token[0]))
        {
            strcpy(postfix[postSize++],token);
        }

        else if(token[0]=='(')
        {
            pushOp('(');
        }

        else if(token[0]==')')
        {
            while(!isEmptyOp() && peekOp()!='(')
            {
                postfix[postSize][0]=popOp();
                postfix[postSize][1]='\0';
                postSize++;
            }

            if(isEmptyOp())
                return 0;

            popOp();
        }

        else
        {
            while(!isEmptyOp() &&
                  peekOp()!='(' &&
                  precedence(peekOp())>=precedence(token[0]))
            {
                postfix[postSize][0]=popOp();
                postfix[postSize][1]='\0';
                postSize++;
            }

            pushOp(token[0]);
        }

        token = strtok(NULL," ");
    }

    while(!isEmptyOp())
    {
        if(peekOp()=='(')
            return 0;

        postfix[postSize][0]=popOp();
        postfix[postSize][1]='\0';
        postSize++;
    }

    return 1;
}

int evaluatePostfix()
{
    for(int i=0;i<postSize;i++)
    {
        if(isdigit(postfix[i][0]))
        {
            pushVal(atoi(postfix[i]));
        }
        else
        {
            int b=popVal();
            int a=popVal();

            switch(postfix[i][0])
            {
                case '+':
                    pushVal(a+b);
                    break;

                case '-':
                    pushVal(a-b);
                    break;

                case '*':
                    pushVal(a*b);
                    break;

                case '/':
                    if(b==0)
                    {
                        printf("ERROR:DIV_BY_ZERO\n");
                        return 0;
                    }
                    pushVal(a/b);
                    break;
            }
        }
    }

    printf("%d\n",popVal());
    return 1;
}

int main()
{
    char input[MAX];

    fgets(input,sizeof(input),stdin);

    input[strcspn(input,"\n")] = '\0';

    if(!infixToPostfix(input))
    {
        printf("ERROR:UNBALANCED\n");
        return 0;
    }

    evaluatePostfix();

    return 0;
}