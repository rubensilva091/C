#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef HEADER_H_
#define HEADHER_H_

#define HASH_SIZE 2000

/* Data Structure */

typedef struct _edgeList
{
    int target;
    struct _edgeList *next_edge;
} EdgeList;

typedef struct _collList
{
    int id;
    char *name, *gender;
    EdgeList *edges;
    struct _collList *next_coll;
} CollList;

typedef struct _auxRecord {
    int node;
    int connection;
    int weight;
    struct _auxRecord *next_rec;
} AuxRecord;

/* Functions */

AuxRecord *aux_rec_search_id(AuxRecord *lst, int number);
AuxRecord *aux_rec_sorted_insert(AuxRecord *lst, AuxRecord *lst2);
AuxRecord *new_aux_record(int o);
CollList **hash_new();
CollList *hash_insert_edge_cl(CollList *lst, int id, int target);
CollList *hash_search(CollList **hash, int id);
CollList *hash_search_cl(CollList *lst, int id);
CollList *hash_update_node_cl(CollList *lst, int id, char *name, char *gender);
EdgeList *edge_head_insert(EdgeList *lst, int id);
EdgeList *insert_incidence(EdgeList *lst, int target);
EdgeList *path_find(CollList **hash, int origin, int target);
int count_cames_cl(CollList* lst, char name[100]);
int count_names (CollList **lst, char name[100]);
int hash_entry(int id);
int mostACT_cl(CollList *actor);
void collision_visit(CollList* lst);
void aux_rec_list_free(AuxRecord *lst);
void hash_insert_edge(CollList **hash, int id, int target);
void hash_update_node(CollList **hash, int id, char *name, char *gender);
void mostACT(CollList **hash);
void only_womans(CollList **hash, CollList** hash2);
void only_womans_cl(CollList** hash2, CollList *actor);
void only_womans_hub(CollList **hash);
void readTxtActors(CollList **hash);

#endif