#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header.h"

/*Reads both texts files and sotcks the information given*/
void readTxtActors(CollList **hash)
{
    int id = 0, source = 0, target = 0;
    char name[100], gender[2], x[3];
    FILE *actors, *coactors;
    printf("A carregar...");
    coactors = fopen("ReadingFiles/big/co-actors.txt", "r");
    while (fscanf(coactors, "%3[^%d]%d\t%*c%*c%d", x, &source, &target) == 3)
    {
        hash_insert_edge(hash, source, target);
        hash_insert_edge(hash, target, source);
    }
    fclose(coactors);
    actors = fopen("ReadingFiles/big/actors.txt", "r");
    while (fscanf(actors, "%3[^%d]%d\t%59[^\t]\t%1s", x, &id, name, gender) == 4)
    {
        hash_update_node(hash, id, name, gender);
    }
    fclose(actors);
}

/*Gets the ammount of actors with a given name*/
int count_names_cl(CollList *lst, char *c)
{
    int count = 0;
    for (; lst; lst = lst->next_coll)
        if (stricmp(lst->name, c) == 0)
        {
            printf("\nID: %-10d Nome: %s  (%s)", lst->id, lst->name, lst->gender);
            count++;
        }
    return count;
}

/*Goes trough all the hash in order to call another function for each collision*/
int count_names(CollList **hash, char *name)
{
    int i, count = 0;
    for (i = 0; i < HASH_SIZE; i++)
        count += count_names_cl(hash[i], name);
    return count;
}

/*Gets the actors that have only acted with womans*/
void only_womans_cl(CollList **hash2, CollList *actor)
{
    int verif = 0;
    CollList *actoraux;
    for (; actor->edges; actor->edges = actor->edges->next_edge)
    {
        actoraux = hash_search(hash2, actor->edges->target);
        if (strcasecmp(actoraux->gender, "M") == 0 || stricmp(actoraux->gender, "?") == 0)
        {
            verif = 1;
            break;
        }
    }
    if (verif == 0)
        printf("\n| %-10d| %s", actor->id, actor->name);
}

/*Goes trough all the hash in order to call another function for each collision*/
void only_womans(CollList **hash, CollList **hash2)
{
    int i;
    for (i = 0; i < HASH_SIZE; i++)
        for (; hash[i]; hash[i] = hash[i]->next_coll)
            only_womans_cl(hash2, hash[i]);
}

/*Gets the ammount of edges for each actor*/
int mostACT_cl(CollList *actor)
{
    int counter = 0;
    EdgeList *edge;
    for (edge = actor->edges; edge; edge = edge->next_edge)
    {
        counter++;
    }
    return counter;
}

/*Goes trough all the hash in order to call another function for each collision*/
void mostACT(CollList **hash)
{
    int i, counter = 0, big = 0;
    CollList **aux = hash;
    CollList *biggest;
    for (i = 0; i < HASH_SIZE; i++)
        for (; aux[i]; aux[i] = aux[i]->next_coll)
        {
            counter = mostACT_cl(aux[i]);
            if (counter > big)
            {
                big = counter;
                biggest = aux[i];
            }
        }
    printf(" -> Ator que contracenou com mais pessoas\n\n ID: %d\n Nome: %s\n Genero: %s", biggest->id, biggest->name, biggest->gender);
    printf("\n\nContracenou com %d atores.", big);
}

/*Creates a new AuxRecord node*/
AuxRecord *new_aux_record(int o)
{
    AuxRecord *new = (AuxRecord *)malloc(sizeof(AuxRecord));
    new->node = o;
    new->connection = new->weight = 0;
    new->next_rec = NULL;
    return new;
}

/*Verifies if the id exists in a given AuxRecord list*/
AuxRecord *aux_rec_search_id(AuxRecord *lst, int number)
{
    for (; lst; lst = lst->next_rec)
    {
        if (lst->node == number)
            break;
    }
    return lst;
}

/*Inserts a new AuxRecord to the list*/
AuxRecord *aux_rec_sorted_insert(AuxRecord *lst, AuxRecord *lst2)
{
    AuxRecord *new = (AuxRecord *)malloc(sizeof(AuxRecord));
    AuxRecord *aux;
    new->node = lst2->node;
    new->weight = lst2->weight;
    new->connection = lst2->connection;
    if (!lst || new->weight < lst->weight)
    {
        new->next_rec = lst;
        lst = new;
    }
    else
    {
        aux = lst;
        while (aux->next_rec && new->weight > aux->next_rec->weight)
            aux = aux->next_rec;
        new->next_rec = aux->next_rec;
        aux->next_rec = new;
    }
    return lst;
}

/*Clears an AuxRecord list*/
void aux_rec_list_free(AuxRecord *lst)
{
    if (lst)
    {
        aux_rec_list_free(lst->next_rec);
        free(lst);
    }
}

/*Dijkstra algorithm to find shortest relation between two id's*/
EdgeList *path_find(CollList **hash, int origin, int target)
{
    AuxRecord *current = NULL;
    AuxRecord *destinationRecord;
    CollList *actor;
    int costSoFar, destination;
    AuxRecord *open = new_aux_record(origin);
    AuxRecord *closed = NULL;
    EdgeList *path = NULL;
    
    while (open)
    {
        current = open;
        open = open->next_rec;
        current->next_rec = NULL;
        if (current->node == target)
            break;
        actor = hash_search(hash, current->node);
        for (; actor->edges; actor->edges = actor->edges->next_edge)
        {
            destination = actor->edges->target;
            destinationRecord = NULL;
            if (aux_rec_search_id(closed, destination))
                continue;
            costSoFar = current->weight + 1;
            destinationRecord = aux_rec_search_id(open, destination);

            if (destinationRecord){
                if (costSoFar >= destinationRecord->weight)
                    continue;
            }
            else
                destinationRecord = new_aux_record(destination);

            destinationRecord->weight = costSoFar;
            destinationRecord->connection = current->node;

            open = aux_rec_sorted_insert(open, destinationRecord);
        }
        closed = aux_rec_sorted_insert(closed, current);
    }

    if (current->node != target)
        return NULL;

    path = insert_incidence(path, current->node);
    while (current->node != origin)
    {
        path = insert_incidence(path, current->connection);
        current = aux_rec_search_id(closed, current->connection);
    }
    aux_rec_list_free(open);
    aux_rec_list_free(closed);
    return path;
}