#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct dictionary_entry
{
    char* word;
    int priority;
};
void eliberare(struct dictionary_entry *a, int n)
{
    int i;
    for(i = 0; i < n ; i++)
        free(a[i].word);
    free(a);
}
void adaugare(struct dictionary_entry **a, int *n, char aux[])
{
    *n = (*n) + 1;
    *a = (struct dictionary_entry *) realloc((*a),sizeof(struct dictionary_entry ) * (*n)); // s-ar putea sa mearga si mai cu n + 1 trebuie testat
    (*a)[(*n) - 1].word = (char *) malloc(sizeof(char) * (strlen(aux) + 1));
    strcpy((*a)[(*n) - 1].word, aux);
    (*a)[(*n) - 1].priority = 1;
    
}
void cautare(struct dictionary_entry **a, int *n, char aux[])
{
    int i,max_priority = -1, cont_cuv_match = -1;
    char auxx[22], cuv_match[22]; //folosim acest auxiliar pentru a nu distruge cuvantul citit
    for(i = 0 ; i < *n; i++)
    {
        if(strlen(aux) <= strlen((*a)[i].word))
        {
            strcpy(auxx, (*a)[i].word);
            auxx[strlen(aux)] = '\0';
            
            if(strstr(aux,auxx) != NULL)
            {   
                if(max_priority < (*a)[i].priority)
                {
                    max_priority = (*a)[i].priority;
                    cont_cuv_match = i;
                    strcpy(cuv_match,(*a)[i].word);
                }
                else if( max_priority == (*a)[i].priority && strcmp(cuv_match, (*a)[i].word) > 0)
                {   
                    cont_cuv_match = i;
                    strcpy(cuv_match, (*a)[i].word);
                }
            }
        }
    }
    if(max_priority == -1)
    {
        adaugare(a,n,aux);
        printf("%s ",aux);
    }
    else{
        printf("%s ",cuv_match);
        (*a)[cont_cuv_match].priority ++;
        //printf("%d\n",(*a)[cont_cuv_match].priority);

}
}
void citire_cuvinte_dictionar(struct dictionary_entry *a, int n)
{
    char aux[22]; // in aux vom citi pentru a aloca exact atata memorie cat este nevoie
    int i;
    for(i = 0; i < n; i++)
    {
        scanf("%s",aux);
        a[i].word = (char *) malloc(sizeof(char) * (strlen(aux) + 1));
        strcpy(a[i].word,aux);
        a[i].priority = 0;
    }
}
void problema(int m, struct dictionary_entry *a, int n)
{
    int i, j, x = 1;
    char aux[22];
    for(i = 0; i < m; i++)
    {   
        scanf("%s",aux);
        if(aux[0] >= 'A' && aux[0]<='z')
        {
            if(aux[strlen(aux) - 1] == '*')
            {
                x = 1;
                aux[strlen(aux)-1]='\0';
                printf("%s ",aux);
                for( j = 0 ; j < n && x == 1; j++)
                {
                    if(strcmp(aux, a[j].word)==0)
                    {
                        x = 0;
                        
                    }
                }
                if(x == 0){
                    a[j - 1].priority ++;
                    }
                else if( x == 1)
                    adaugare( &a, &n, aux);
            }
            else
                cautare(&a,&n,aux);//de continuat

        }
        else printf("%c ", aux[0]);//punctuatia
    }
    eliberare(a,n);// eliberarea memoriei alocate dinamic 
}

int main()
{
    struct dictionary_entry *a;
    int n,m;
    scanf("%d",&n);
    getchar();
    a = (struct dictionary_entry *)malloc(sizeof(struct dictionary_entry) * (n)); // experiment daca merge cu n;
    citire_cuvinte_dictionar(a,n);
    scanf("%d",&m);
    getchar();
    problema(m,a,n);
    return 0;
}