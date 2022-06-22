#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

typedef struct farmacie{
    char nume[100];
    int cantitate;
}farm;
farm f1[100];

/*typedef struct farmaciere{
    char numeMed[100];
    char numeOm[100];
    int cantitate;
}farmre;*/
/*farmre f2[100];*/

int numarfarm;

void meniu()
{
    printf ("\n--------Farmacie--------\n");
    printf ("1. Afiseaza produse disponibile.\n");
    printf ("2. Cauta un produs.\n");
    printf ("3. Rezerva medicamente.\n");
    printf ("4. Adauga medicament.\n");
    printf ("5. Sterge medicament.\n");
    printf ("6. Afiseaza produse rezervate.\n");
    printf ("0. Iesire.\n\n");
}

void cautare(char path[])
{
    int inapoi,i=0,ok=0;
    char linie[50],nume[20];
    printf("\n");
    printf("Introdu numele produsului care doresti sa il cauti: ");
    getchar();
    scanf("%[^\n]",nume);

    printf("\n");

    do{
        if (f1[i].cantitate != 0 && strcmp(nume,f1[i].nume) == 0){
            printf("Exista %d in stoc la momentul actual.\n\n",f1[i].cantitate);
            ok=1;
        }
        i++;
    }while (f1[i].cantitate != 0);
    if (ok==0)
        printf("Nu avem acest produs in baza de date.\n\n");

    printf("0.Inapoi\n\n");
    do{
        printf("Introduceti optiunea dorita: ");
        scanf("%d", &inapoi);
    }while(inapoi!=0);

    system("cls");
}

void rezerva(char path1[] , char path2[])
{
    char numeMed[30],numeOm[50],linie[100];
    int cantitate,x,inapoi,i=0;
    printf("\n--------------\n");
    printf("\nIntroduceti numele medicamentului: ");
    getchar();
    scanf("%[^\n]",numeMed);
    printf("Introduceti numele dumneavoastra: ");
    getchar();
    scanf("%[^\n]",numeOm);
    printf("Introduceti cantitatea: ");
    scanf("%d",&cantitate);

    FILE * filePointer2;
    filePointer2 = fopen(path2, "a");
    FILE * tempPointer;
    tempPointer = fopen("temp.txt", "a");


    for (i=0 ; i<=numarfarm ; i++) {
        if (strcmp(numeMed,f1[i].nume) == 0)
            f1[i].cantitate = f1[i].cantitate - cantitate;
        if (f1[i].cantitate != 0)
            fprintf(tempPointer, "%s,%d\n", f1[i].nume, f1[i].cantitate);
    }
    fprintf(filePointer2, "%s,%d,%s\n", numeMed,cantitate,numeOm);
    fclose(filePointer2);
    fclose(tempPointer);
    remove(path1);
    rename("temp.txt", path1);

    printf("Ati facut o rezervare cu succes\nPuteti sa reveniti la aceasi ora maine sa ridicati comanda\n\n");
    printf("0.Inapoi\n\n");
    do{
        printf("Introduceti optiunea dorita: ");
        scanf("%d", &inapoi);
    }while(inapoi!=0);

    system("cls");
}

void adaugare(char path[])
{
    char nume[30];
    int cantitate;

    FILE * filePointer;
    filePointer = fopen(path, "a");

    printf("\n--------------\n");
    printf("\nIntroduceti numele medicamentului: ");
    getchar();
    scanf("%[^\n]",nume);
    printf("Introduceti cantitatea: ");
    scanf("%d",&cantitate);

    strcpy(f1[numarfarm+1].nume, "");
    if ( filePointer == NULL )
        printf( "Fisierul nu poate fi accesat.\n" ) ;
    else{
        strcpy(f1[numarfarm+1].nume, nume);
        f1[numarfarm+1].cantitate=cantitate;
        /*printf("%s,%d\n", f1[i+1].nume,f1[i+1].cantitate);*/
        fprintf(filePointer, "%s,%d\n", nume, cantitate);
        fclose(filePointer) ;
    }
    printf("--------------\n");
    numarfarm++;

}

void stergere(char path[])
{
    char nume[20];
    char linie[50],i=0,j,lung=0,ok=0;;
    printf("Introduceti numele: ");
    getchar();
    scanf("%[^\n]",nume);

    FILE * tempPointer;
    tempPointer = fopen("temp.txt", "a");

    while (i<=numarfarm){
        if (strcmp(nume,f1[i].nume)==0 && ok==0){
            for (j=i; j<numarfarm; j++){
                /*strcpy(f1[j].nume, f1[j+1].nume);
                f1[j].cantitate=f1[j+1].cantitate;*/
                f1[j]=f1[j+1];
            }
            ok=1;
        }
        i++;
    }

    i=0;
    numarfarm--;
    for (i=0 ; i<=numarfarm ; i++) {
        if(strcmp(nume,f1[i].nume)!=0)
            fprintf(tempPointer, "%s,%d\n", f1[i].nume, f1[i].cantitate);
    }
    fclose(tempPointer);
    remove(path);
    rename("temp.txt", path);

}

void afisare()
{
    int inapoi,i=0;
    char linie[50];
    system("cls");
    printf("\n");

    printf("--------------\n");
    for (i=0 ; i<=numarfarm ; i++) { /*i != 3*/
        printf ("%s - %d\n",f1[i].nume, f1[i].cantitate);
    }
    printf("--------------\n\n");
    printf("0.Inapoi\n\n");

    do{
        printf("Introduceti optiunea dorita: ");
        scanf("%d", &inapoi);
    }while(inapoi!=0);

    system("cls");
}

void afisarere (char path[])
{
    int inapoi;
    char linie[50];
    printf("\n");

    FILE * filePointer;
    filePointer = fopen(path, "r");

    printf("--------------\n");
    if ( filePointer == NULL )
        printf( "Fisierul nu poate fi accesat." ) ;
    else
    {
        while (fgets (linie, 50, filePointer)) {
            if (linie[0] != '\n') {
                linie[strcspn(linie, "\n")] = '\0';
                if (linie[strlen(linie)-1] != '0')
                    printf("%s\n",linie);
            }
        }
        fclose(filePointer) ;
    }
    printf("--------------\n\n");

    printf("0.Inapoi\n\n");
    do{
        printf("Introduceti optiunea dorita: ");
        scanf("%d", &inapoi);
    }while(inapoi!=0);

    system("cls");
}

void iesire(char path[])
{
    system("cls");
    printf("\n");
    printf ("Ati iesit din aplicatie!!!");
    printf("\n");
}

void citire (char path[])
{
    int i=0;
    char linie[50];

    FILE * filePointer;
    filePointer = fopen(path, "r");

    i=0;
    if ( filePointer == NULL )
        printf( "Fisierul nu poate fi accesat." ) ;
    else
    {
        while (fgets (linie, 50, filePointer)) {
            if (linie[0] != '\n') {
                linie[strcspn(linie, "\n")] = '\0';
                sscanf(linie, "%[^,],%d[^\n]", f1[numarfarm].nume, &f1[numarfarm].cantitate);
                /*printf ("%s\n%d\n", f1[i].nume , f1[i].cantitate);*/
                numarfarm++;
            }
        }
        fclose(filePointer) ;
    }
    numarfarm--;
}

void optiuni(int alegere, char path1[], char path2[])
{
    switch(alegere){
        case 1:
            afisare();
            break;
        case 2:
            cautare(path1);
            break;
        case 3:
            rezerva(path1,path2);
            break;
        case 4:
            adaugare(path1);
            break;
        case 5:
            stergere(path1);
            break;
        case 6:
            afisarere(path2);
            break;
        case 0:
            iesire(path1);
            break;
    }
}


int main ()
{
    char path1[]="medicamente.txt",path2[]="listaOameni.txt";
    int alegere;
    citire(path1);
    do{
        /*afisare2(path1);*/
        meniu();
        printf("Introduceti optiunea dorita: ");
        scanf("%d", &alegere);
        optiuni(alegere,path1,path2);
    }while(alegere!=0);
}
