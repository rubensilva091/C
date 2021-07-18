#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header.h"

/*Finds the right key for the hash with the given id*/
int hash_entry(int id)
{
    return id % HASH_SIZE;
}

/*Updates the node with new information*/
CollList *hash_update_node_cl(CollList *lst, int id, char *name, char *gender)
{
    if (lst && lst->id == id)
    {
        lst->name = strdup(name);
        lst->gender = strdup(gender);
    }
    else if (lst)
        lst->next_coll = hash_update_node_cl(lst->next_coll, id, name, gender);
    return lst;
}

/*Finds the position of the node to update with new information*/
void hash_update_node(CollList **hash, int id, char *name, char *gender)
{
    int pos = hash_entry(id);
    hash[pos] = hash_update_node_cl(hash[pos], id, name, gender);
}

/*Finds the right id in the list of incidences*/
CollList *hash_search_cl(CollList *lst, int id)
{
    if (lst && lst->id == id)
        return lst;
    if (lst)
        return hash_search_cl(lst->next_coll, id);
    return NULL;
}

/*Finds the position where the id must be*/
CollList *hash_search(CollList **hash, int id)
{
    int pos = hash_entry(id);
    return hash_search_cl(hash[pos], id);
}

/*Allocates memory for a new hash*/
CollList **hash_new()
{
    return (CollList **)calloc(HASH_SIZE, sizeof(CollList *));
}

/*Creates a new incidence*/
EdgeList *insert_incidence(EdgeList *lst, int target)
{
    EdgeList *new = (EdgeList *)malloc(sizeof(EdgeList));
    new->target = target;
    new->next_edge = lst;
    return new;
}

/*Creates a new edge in the right incidence*/
CollList *hash_insert_edge_cl(CollList *lst, int id, int target)
{
    if (lst && lst->id == id)
    {
        lst->edges = insert_incidence(lst->edges, target);
    }
    else if (lst && lst->id < id)
    {
        lst->next_coll = hash_insert_edge_cl(lst->next_coll, id, target);
    }
    else
    {
        CollList *new = (CollList *)malloc(sizeof(CollList));
        new->id = id;
        new->gender = NULL;
        new->name = NULL;
        new->next_coll = lst;
        new->edges = insert_incidence(NULL, target);
        lst = new;
    }
    return lst;
}

/*Finds the position for a new edge in the right incidence*/
void hash_insert_edge(CollList **hash, int id, int target)
{
    int pos = hash_entry(id);
    hash[pos] = hash_insert_edge_cl(hash[pos], id, target);
}