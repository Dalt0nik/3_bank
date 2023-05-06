#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "priorityQueue.h"
#include "queue.h"

//compile: gcc main.c priorityQueue.c -o main.exe

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
    char fileName[20] = "Protokolas.txt";

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



    pagrindineSuma = 50000;
    ismokuKiekis = 40;
    palukanos = 3;
    delspinigiai = 5;
    alga = 1000;
    algosInfliacija = 10;
    


    fprintf(protokolas, "Evgenij Shapovalov. PS1, 3 grupe, 4 pogrupis.\n"
    "ADS 3 uzduotis. 9 variantas: Banko skolu dengimas.\n\n"
    "Salyga:\nBankas išduoda klientui paskolą, pagal jos sumą ir paskolos laikotarpį sudaromas grąžinimo grafikas (paskolinta suma grąžinama lygiomis dalimis kas 30 dienų).\n"
    "Deja, ne visi klientai sugeba grąžinti paskolą laiku.\n"
    "Atėjus mokėjimo dienai klientas gali turėti tik tiek pinigų, kiek reikia einamajai įmokai pagal grafiką dengti,\n"
    "arba kažkiek daugiau pinigų (tokiu atveju jis dengia ir įsiskolinimus, jei tokių yra),\n"
    "arba kažkiek mažiau pinigų (tokiu atveju auga skolos).\n"
    "Palūkanos skaičiuojamos už visą tam momentui negrąžintą paskolos sumą.\n"
    "Už laiku negrąžintą paskolos dalį imami delspinigiai (delspinigiai neskaičiuojami nuo palūkanų ir delspinigių).\n\n"
    "Galimos 2 skolu dengimo strategijos.\n"
    "Strategija 1: dengiamos seniausios skolos, neatsižvelgiant į jų tipą.\n"
    "Strategija 2: dengiama pagal prioritetus: pagrindinė suma, palūkanos, delspinigiai.\n\n"
    "Tikslas: įvertinti šių strategijų ekonominį poveikį klientui.\n\n");

    fprintf(protokolas,"Dalis I. Ivesti rodikliai:\n"
    "1) Pagrindine suma: %5.0f Eur.\n"
    "2) Ismoku kiekis:   %5.0f\n"
    "3) Palukanos:       %5.0f %%\n"
    "4) Delspinigiai:    %5.0f %%\n"
    "6) Alga:            %5.0f Eur.\n"
    "7) Algos infliacija:%5.0f %%\n\n"
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

        fprintf(protokolas,"\n\nDALIS III. Rezultatai\n\nPradine skolos suma:  %.2f\n\nStrategija 1:\n1)Viso sumoketa pinigu: %.2f\n2)Viso ismoku T:        %d\n\nStrategija 2:\n1)Viso sumoketa pinigu: %.2f\n2)Viso ismoku T:        %d\n", pagrindineSuma, sumoketaSuma1, T1-1, sumoketaSuma2, T2-1);

}

void strategija1(double pagrindineSuma, double ismokuKiekis, double palukanos, double delspinigiai, double alga, double algosInfliacija, FILE *protokolas, int *T1, double *sumoketaSuma1)
{
    char tipai[4][20] = {"", "delspinigiai", "palukanos", "pagrindines ismokos"};
    int ismoka = 0;
    double pradineSuma = pagrindineSuma, bendraSkola = pagrindineSuma, skolaPagrindine = pagrindineSuma, skolaPalukanos = 0, skolaDelspinigiai = 0, klientoPinigai = 0;
    *sumoketaSuma1 = 0;
    Queue* skolos = create();

    fprintf(protokolas, "\nStrategija 1.\n");

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
            fprintf(protokolas, "  Nera naujos pagrindiniu ismoku skolos\n");
        if(skolaPalukanos > 0)
            fprintf(protokolas, "  Nauja palukanu skola:    %10.2f Eur.\n", skolaPalukanos);
        else
            fprintf(protokolas, "  Nera naujos palukanu skolos\n");
        if(skolaDelspinigiai > 0)
            fprintf(protokolas, "  Nauja delspinigiu skola: %10.2f Eur.\n\n", skolaDelspinigiai);
        else
            fprintf(protokolas, "  Nera naujos delspinigiu skolos\n\n");


        klientoPinigai += alga;
        fprintf(protokolas, "  Kliento pinigu kiekis:   %10.2f Eur.\n\n", klientoPinigai);

        if(klientoPinigai > 0)
            fprintf(protokolas, "  Klientas sugebejo apmoketi sekancias skolas:\n");
        else
            fprintf(protokolas, "  Klientas nesumokejo jokiu skolu\n");



        while(klientoPinigai > 0 && isempty(skolos) != 1)
        {          
            int virsutinisTipas;
            double virsutineSkola;
            peekfirst(skolos, &virsutineSkola, &virsutinisTipas);
            if(klientoPinigai >= virsutineSkola)
            {
                dequeue(skolos, &virsutineSkola, &virsutinisTipas);
                fprintf(protokolas, "  Suma: %8.2f Eur, tipas: %s.\n", virsutineSkola, tipai[virsutinisTipas]);
                klientoPinigai -= virsutineSkola;
                *sumoketaSuma1 += virsutineSkola;
            }
            else
            {
                dequeue(skolos, &virsutineSkola, &virsutinisTipas);
                fprintf(protokolas, "  Suma: %8.2f Eur, tipas: %s.\n", klientoPinigai, tipai[virsutinisTipas]);

                enqueue(skolos, virsutineSkola-klientoPinigai, virsutinisTipas);
                *sumoketaSuma1 += klientoPinigai;
                klientoPinigai = 0;
            } 
        }
        

        fprintf(protokolas, "\n  Likusios skolos:\n");
        likoSkoluQ(skolos, protokolas);

        fprintf(protokolas, "  Likusi pagrindine skola:       %8.2f Eur.\n\n", bendraSkola);

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
    char tipai[4][20] = {"", "delspinigiai", "palukanos", "pagrindines ismokos"};
    int ismoka = 0;
    double pradineSuma = pagrindineSuma, bendraSkola = pagrindineSuma, skolaPagrindine = pagrindineSuma, skolaPalukanos = 0, skolaDelspinigiai = 0, klientoPinigai = 0;
    *sumoketaSuma2 = 0;
    priorityQueue* skolos = createQ(); //3 -> 2 -> 1

    fprintf(protokolas, "\n\nStrategija 2.\n");

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
            fprintf(protokolas, "  Nera naujos pagrindiniu ismoku skolos\n");
        if(skolaPalukanos > 0)
            fprintf(protokolas, "  Nauja palukanu skola:    %10.2f Eur.\n", skolaPalukanos);
        else
            fprintf(protokolas, "  Nera naujos palukanu skolos\n");
        if(skolaDelspinigiai > 0)
            fprintf(protokolas, "  Nauja delspinigiu skola: %10.2f Eur.\n\n", skolaDelspinigiai);
        else
            fprintf(protokolas, "  Nera naujos delspinigiu skolos\n\n");

        //fprintf(protokolas, "  Naujos skolos:\n  Pagrindine ismoka:       %10.2f\n  Nauja palukanu skola:    %10.2f\n  Nauja delspinigiu skola: %10.2f\n\n",skolaPagrindine,skolaPalukanos,skolaDelspinigiai);    

        klientoPinigai += alga;
        fprintf(protokolas, "  Kliento pinigu kiekis:   %10.2f Eur.\n\n", klientoPinigai);

        if(klientoPinigai > 0)
            fprintf(protokolas, "  Klientas sugebejo apmoketi sekancias skolas:\n");
        else
            fprintf(protokolas, "  Klientas nesumokejo jokiu skolu\n");

        while(klientoPinigai > 0 && isEmpty(skolos) != 1)
        {          
            int virsutinisPrioritetas;
            double virsutineSkola;
            peek(skolos, &virsutineSkola, &virsutinisPrioritetas);
            if(klientoPinigai >= virsutineSkola)
            {
                pop(skolos, &virsutineSkola);
                fprintf(protokolas, "  Suma: %8.2f Eur, tipas: %s.\n", virsutineSkola, tipai[virsutinisPrioritetas]);
                klientoPinigai -= virsutineSkola;
                *sumoketaSuma2 += virsutineSkola;
            }
            else
            {
                pop(skolos, &virsutineSkola);
                fprintf(protokolas, "  Suma: %8.2f Eur, tipas: %s.\n", klientoPinigai, tipai[virsutinisPrioritetas]);

                insert(skolos, virsutineSkola-klientoPinigai, virsutinisPrioritetas);
                *sumoketaSuma2 += klientoPinigai;
                klientoPinigai = 0;
            } 
        }

        fprintf(protokolas, "\n  Likusios skolos:\n");
        likoSkoluPr(skolos, protokolas);

        fprintf(protokolas, "  Likusi pagrindine skola:       %8.2f Eur.\n\n", bendraSkola);

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

    fprintf(protokolas, "  1) Pagrindiniu ismoku skolu suma: %8.2f Eur.\n  2) Palukanu skolu suma:           %8.2f Eur.\n  3) Delspinigiu skolu suma:        %8.2f Eur.\n\n", sumPagrindine, sumPalukanos, sumDelspinigiai);
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

    fprintf(protokolas, "  1) Pagrindiniu ismoku skolu suma: %8.2f Eur.\n  2) Palukanu skolu suma:           %8.2f Eur.\n  3) Delspinigiu skolu suma:        %8.2f Eur.\n\n", sumPagrindine, sumPalukanos, sumDelspinigiai);
}
