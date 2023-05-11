#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "priorityQueue.h"
#include "queue.h"

//compile: gcc main.c priorityQueue.c queue.c -o main.exe

void process(double pagrindineSuma, double ismokuKiekis, double palukanos, double delspinigiai, double alga, double algosInfliacija, FILE *protokolas);
void strategija1(double pagrindineSuma, double ismokuKiekis, double palukanos, double delspinigiai, double alga, double algosInfliacija, FILE *protokolas, int *T1, double *sumoketaSuma1);
void strategija2(double pagrindineSuma, double ismokuKiekis, double palukanos, double delspinigiai, double alga, double algosInfliacija, FILE *protokolas, int *T2, double *sumoketaSuma2);
double skaiciuotiDelspinigiusPr(priorityQueue* skolos);
double skaiciuotiDelspinigiusQ(Queue* skolos);
void likoSkoluPr(priorityQueue* skolos, FILE *protokolas);
void likoSkoluQ(Queue* skolos, FILE *protokolas);


int main()
{
    priorityQueue* test = createQ();

    double pagrindineSuma, ismokuKiekis, palukanos, delspinigiai, alga, algosInfliacija;
    char fileName[20] = "Protokolas4.txt";

    FILE *protokolas;
    protokolas = fopen(fileName, "w");
    // printf("Iveskite pagrindine paskolos suma: ");
    // scanf("%d", &pagrindineSuma);
    // printf("Iveskite ismoku kieki (sveikasis skaicius): ");
    // scanf("%d", &ismokuKiekis);
    // printf("Iveskite kliento vidutine alga: ");
    // scanf("%d", &vidutineAlga);
    // printf("Iveskite kliento algos paklaida eur.: ");
    // scanf("%d", &algosPaklaida);



    pagrindineSuma = 30000;
    ismokuKiekis = 60;
    palukanos = 10;
    delspinigiai = 3;
    alga = 2000;
    algosInfliacija = 10;
    


    fprintf(protokolas,
    "Evgenij Shapovalov. PS1, 3 grupe, 4 pogrupis.\n"
    "ADS 3 uzduotis. 9 variantas: Banko skolu dengimas.\n\n"
    "Salyga:\nBankas isduoda klientui paskola, pagal jos suma ir paskolos\n"
    "laikotarpi sudaromas grazinimo grafikas (paskolinta suma grazinama\n"
    "lygiomis dalimis kas 30 dienu).\n"
    "Deja, ne visi klientai sugeba grazinti paskola laiku. Atejus mokejimo\n"
    "dienai klientas gali tureti tik tiek pinigu, kiek reikia einamajai\n"
    "imokai pagal grafika dengti, arba kazkiek daugiau pinigu (tokiu atveju\n"
    "jis dengia ir isiskolinimus, jei tokiu yra), arba kazkiek maziau pinigu\n"
    "(tokiu atveju auga skolos).\n"
    "Palukanos skaiciuojamos uz visa tam momentui negrazinta paskolos suma.\n"
    "Uz laiku negrazinta paskolos dali imami delspinigiai (delspinigiai\n"
    "neskaiciuojami nuo palukanu ir delspinigiu).\n\n"
    "Galimos dvi skolu dengimo strategijos.\n"
    "Strategija 1: dengiamos seniausios skolos, neatsizvelgiant i ju tipa.\n"
    "Strategijos realizacijoje yra naudojama eile.\n\n"
    "Strategija 2: dengiama pagal prioritetus: pagrindine suma, palukanos,\n"
    "delspinigiai. Strategijos realizacijoje yra naudojama prioritetine eile.\n\n\n"
    "Tikslas: ivertinti siu strategiju ekonomini poveiki klientui.\n\n"
    "Isvada is salygos:\n"
    "Is salygos yra akivaizdu, kad visais atvejais optimalu yra naudoti\n"
    "Strategija 2, pagal kuria pradzioje yra apmokamos pagrindines sumos\n"
    "skolos, kadangi butent nuo ju yra skaiciuojamos papildomos skolos.\n\n");

    fprintf(protokolas,"Dalis I. Ivesti rodikliai:\n"
    "1) Pagrindine suma:         %8.0f Eur.\n"
    "2) Ismoku kiekis:           %8.0f ismoku.\n"
    "3) Palukanos:               %8.0f %%\n"
    "4) Delspinigiai:            %8.0f %%\n"
    "6) Alga:                    %8.0f Eur.\n"
    "7) Algos kasmetinis augimas:%8.0f %%\n\n"
    "DALIS II. Protokolas\n",pagrindineSuma, ismokuKiekis,palukanos,delspinigiai,alga,algosInfliacija);

    process(pagrindineSuma,ismokuKiekis,palukanos,delspinigiai,alga,algosInfliacija, protokolas);
    


    return 0;
}

void process(double pagrindineSuma, double ismokuKiekis, double palukanos, double delspinigiai, double alga, double algosInfliacija, FILE *protokolas)
{
    int T1, T2;
    double sumoketaSuma1, sumoketaSuma2;
    strategija1(pagrindineSuma, ismokuKiekis, palukanos, delspinigiai, alga, algosInfliacija, protokolas, &T1, &sumoketaSuma1);
    strategija2(pagrindineSuma, ismokuKiekis, palukanos, delspinigiai, alga, algosInfliacija, protokolas, &T2, &sumoketaSuma2);

    fprintf(protokolas,"\n\nDALIS III. Rezultatai\n\nPradine skolos suma:  %.2f Eur.\n\nStrategija 1:\n1)Viso sumoketa pinigu: %10.2f Eur.\n2)Viso ismoku T:        %10d ismoku.\n\nStrategija 2:\n1)Viso sumoketa pinigu: %10.2f Eur.\n2)Viso ismoku T:        %10d ismoku.\n\n", pagrindineSuma, sumoketaSuma1, T1-1, sumoketaSuma2, T2-1);
    
    fprintf(protokolas, "Isvada:\n");
    if(sumoketaSuma1 > sumoketaSuma2)
        fprintf(protokolas, "Su ivestais rodikliais, naudodamasis Strategija 2, klientas uzmoka %.2f Eur maziau.", sumoketaSuma1-sumoketaSuma2);
    else if(sumoketaSuma2 > sumoketaSuma1)
        fprintf(protokolas, "Su ivestais rodikliais, naudodamasis Strategija 1, klientas uzmoka %.2f Eur maziau.", sumoketaSuma2-sumoketaSuma1);
    else
        fprintf(protokolas, "Su ivestais rodikliais Strategija 1 ir Strategija 2 veikia vienodai.");

}

void strategija1(double pagrindineSuma, double ismokuKiekis, double palukanos, double delspinigiai, double alga, double algosInfliacija, FILE *protokolas, int *T1, double *sumoketaSuma1)
{
    char tipai[4][25] = {"", "delspinigiai", "palukanos", "pagrindines ismokos"};
    int ismoka = 0;
    double pradineSuma = pagrindineSuma, bendraSkola = pagrindineSuma, skolaPagrindine = pagrindineSuma, skolaPalukanos = 0, skolaDelspinigiai = 0, klientoPinigai = 0;
    *sumoketaSuma1 = 0;
    Queue* skolos = create();

    fprintf(protokolas, "\nSTRATEGIJA 1.\n");

    while(bendraSkola > 0 || isempty(skolos) != 1)
    {
        fprintf(protokolas, "\nT = %d.\n\n", ismoka);

        if(bendraSkola > 0)
            skolaPagrindine = (pradineSuma/ismokuKiekis); //atimam pagrindine ismoka
        bendraSkola -= skolaPagrindine;
        skolaPalukanos = bendraSkola / 100 * palukanos;
        skolaDelspinigiai = skaiciuotiDelspinigiusQ(skolos) / 100 * delspinigiai;
        if(skolaPagrindine > 0)
            enqueue(skolos, skolaPagrindine, 3);
        if(skolaPalukanos > 0)
            enqueue(skolos, skolaPalukanos, 2);
        if(skolaDelspinigiai > 0)
            enqueue(skolos, skolaDelspinigiai, 1);


        if(skolaPagrindine > 0)
            fprintf(protokolas, "  Pagrindine ismoka:       %10.2f Eur.\n", skolaPagrindine);
        else
            fprintf(protokolas, "  Nera naujos pagrindiniu ismoku skolos.\n");
        if(skolaPalukanos > 0)
            fprintf(protokolas, "  Nauja palukanu skola:    %10.2f Eur.\n", skolaPalukanos);
        else
            fprintf(protokolas, "  Nera naujos palukanu skolos.\n");
        if(skolaDelspinigiai > 0)
            fprintf(protokolas, "  Nauja delspinigiu skola: %10.2f Eur.\n\n", skolaDelspinigiai);
        else
            fprintf(protokolas, "  Nera naujos delspinigiu skolos.\n\n");


        klientoPinigai += alga;
        fprintf(protokolas, "  Kliento pinigu kiekis:   %10.2f Eur.\n\n", klientoPinigai);

        if(klientoPinigai > 0)
            fprintf(protokolas, "  Klientas sugebejo apmoketi sias skolas:\n");
        else
            fprintf(protokolas, "  Klientas neapmokejo jokiu skolu\n");



        while(klientoPinigai > 0 && isempty(skolos) != 1)
        {          
            int virsutinisTipas;
            double virsutineSkola;
            peekfirst(skolos, &virsutineSkola, &virsutinisTipas);
            if(klientoPinigai >= virsutineSkola)
            {
                dequeue(skolos, &virsutineSkola, &virsutinisTipas);
                fprintf(protokolas, "  Suma %8.2f Eur, tipas - %s.\n", virsutineSkola, tipai[virsutinisTipas]);
                klientoPinigai -= virsutineSkola;
                *sumoketaSuma1 += virsutineSkola;
            }
            else
            {
                dequeue(skolos, &virsutineSkola, &virsutinisTipas);
                fprintf(protokolas, "  Suma %8.2f Eur, tipas - %s.\n", klientoPinigai, tipai[virsutinisTipas]);

                enqueue(skolos, virsutineSkola-klientoPinigai, virsutinisTipas);
                *sumoketaSuma1 += klientoPinigai;
                klientoPinigai = 0;
            } 
        }
        

        fprintf(protokolas, "\n  Likusios skolos:\n");
        likoSkoluQ(skolos, protokolas);

        fprintf(protokolas, "  Likusi pagrindine skola:            %10.2f Eur.\n\n", bendraSkola);

        skolaPagrindine = 0;
        skolaPalukanos = 0;
        skolaDelspinigiai = 0;
        ismoka++;
        if(ismoka % 12 == 0)
            alga = alga * (1 + algosInfliacija/100);
    }

    *T1 = ismoka;
    

}

void strategija2(double pagrindineSuma, double ismokuKiekis, double palukanos, double delspinigiai, double alga, double algosInfliacija, FILE *protokolas, int *T2, double *sumoketaSuma2)
{
    char tipai[4][25] = {"", "delspinigiai", "palukanos", "pagrindines ismokos"};
    int ismoka = 0;
    double pradineSuma = pagrindineSuma, bendraSkola = pagrindineSuma, skolaPagrindine = pagrindineSuma, skolaPalukanos = 0, skolaDelspinigiai = 0, klientoPinigai = 0;
    *sumoketaSuma2 = 0;
    priorityQueue* skolos = createQ(); //3 -> 2 -> 1

    fprintf(protokolas, "\nSTRATEGIJA 2.\n");

    while(bendraSkola > 0 || isEmpty(skolos) != 1)
    {
        fprintf(protokolas, "\nT = %d.\n\n", ismoka);

        if(bendraSkola > 0)
            skolaPagrindine = (pradineSuma/ismokuKiekis); //atimam pagrindine ismoka
        bendraSkola -= skolaPagrindine;
        skolaPalukanos = bendraSkola / 100 * palukanos;
        skolaDelspinigiai = skaiciuotiDelspinigiusPr(skolos) / 100 * delspinigiai;
        if(skolaPagrindine > 0)
            insert(skolos, skolaPagrindine, 3);
        if(skolaPalukanos > 0)
            insert(skolos, skolaPalukanos, 2);
        if(skolaDelspinigiai > 0)
            insert(skolos, skolaDelspinigiai, 1);
        

        if(skolaPagrindine > 0)
            fprintf(protokolas, "  Pagrindine ismoka:       %10.2f Eur.\n", skolaPagrindine);
        else
            fprintf(protokolas, "  Nera naujos pagrindiniu ismoku skolos.\n");
        if(skolaPalukanos > 0)
            fprintf(protokolas, "  Nauja palukanu skola:    %10.2f Eur.\n", skolaPalukanos);
        else
            fprintf(protokolas, "  Nera naujos palukanu skolos.\n");
        if(skolaDelspinigiai > 0)
            fprintf(protokolas, "  Nauja delspinigiu skola: %10.2f Eur.\n\n", skolaDelspinigiai);
        else
            fprintf(protokolas, "  Nera naujos delspinigiu skolos.\n\n");

        //fprintf(protokolas, "  Naujos skolos:\n  Pagrindine ismoka:       %10.2f\n  Nauja palukanu skola:    %10.2f\n  Nauja delspinigiu skola: %10.2f\n\n",skolaPagrindine,skolaPalukanos,skolaDelspinigiai);    

        klientoPinigai += alga;
        fprintf(protokolas, "  Kliento pinigu kiekis:   %10.2f Eur.\n\n", klientoPinigai);

        if(klientoPinigai > 0)
            fprintf(protokolas, "  Klientas sugebejo apmoketi sias skolas:\n");
        else
            fprintf(protokolas, "  Klientas neapmokejo jokiu skolu\n");

        while(klientoPinigai > 0 && isEmpty(skolos) != 1)
        {          
            int virsutinisPrioritetas;
            double virsutineSkola;
            peek(skolos, &virsutineSkola, &virsutinisPrioritetas);
            if(klientoPinigai >= virsutineSkola)
            {
                pop(skolos, &virsutineSkola);
                fprintf(protokolas, "  Suma %8.2f Eur, tipas - %s.\n", virsutineSkola, tipai[virsutinisPrioritetas]);
                klientoPinigai -= virsutineSkola;
                *sumoketaSuma2 += virsutineSkola;
            }
            else
            {
                pop(skolos, &virsutineSkola);
                fprintf(protokolas, "  Suma %8.2f Eur, tipas - %s.\n", klientoPinigai, tipai[virsutinisPrioritetas]);

                insert(skolos, virsutineSkola-klientoPinigai, virsutinisPrioritetas);
                *sumoketaSuma2 += klientoPinigai;
                klientoPinigai = 0;
            } 
        }

        fprintf(protokolas, "\n  Likusios skolos:\n");
        likoSkoluPr(skolos, protokolas);

        fprintf(protokolas, "  Likusi pagrindine skola:             %10.2f Eur.\n\n", bendraSkola);

        skolaPagrindine = 0;
        skolaPalukanos = 0;
        skolaDelspinigiai = 0;
        ismoka++;
        if(ismoka % 12 == 0)
            alga = alga * (1 + algosInfliacija/100);
    }

    *T2 = ismoka;
}

double skaiciuotiDelspinigiusPr(priorityQueue* skolos)
{
    double suma = 0;

    node* current, *prev;
    current = skolos->front;

    while(current != NULL)
    {
        if((current->priority) == 3)
            suma += current->value;

        current = current->next;
    }

    return suma;
}

double skaiciuotiDelspinigiusQ(Queue* skolos)
{
    double suma = 0;

    if(skolos == NULL)
    {
            return suma;
    }

    QueueNode *currentNode = skolos->headNode;
    while(currentNode != NULL)
    {
            if(currentNode->type == 3)
            {
                suma += currentNode->value;
            }   
        currentNode = currentNode->next; 
    }

    return suma;
}

void likoSkoluPr(priorityQueue* skolos, FILE *protokolas)
{
    double sumPagrindine = 0, sumPalukanos = 0, sumDelspinigiai = 0;

    node* current, *prev;
    current = skolos->front;

    while(current != NULL)
    {
        if(current->priority == 3)
            sumPagrindine += current->value;
        else if(current->priority == 2)
            sumPalukanos += current->value;
        else if(current->priority == 1)
            sumDelspinigiai += current->value;

        current = current->next;
    }

    fprintf(protokolas, "  1) Pagrindiniu ismoku skolu suma:    %10.2f Eur.\n  2) Palukanu skolu suma:              %10.2f Eur.\n  3) Delspinigiu skolu suma:           %10.2f Eur.\n\n", sumPagrindine, sumPalukanos, sumDelspinigiai);
}

void likoSkoluQ(Queue* skolos, FILE *protokolas)
{
    double sumPagrindine = 0, sumPalukanos = 0, sumDelspinigiai = 0;

    if(skolos != NULL)
    {
        QueueNode *currentNode = skolos->headNode;
        while(currentNode != NULL)
        {
            if(currentNode->type == 3)
                sumPagrindine += currentNode->value;
            else if(currentNode->type == 2)
                sumPalukanos += currentNode->value;
            else if(currentNode->type == 1)
                sumDelspinigiai += currentNode->value;
 
            currentNode = currentNode->next; 
        }
    }

    fprintf(protokolas, "  1) Pagrindiniu ismoku skolu suma:   %10.2f Eur.\n  2) Palukanu skolu suma:             %10.2f Eur.\n  3) Delspinigiu skolu suma:          %10.2f Eur.\n\n", sumPagrindine, sumPalukanos, sumDelspinigiai);
}
