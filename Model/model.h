//
// Created by eii on 07/04/2022.
//

#ifndef ESCAPEGAMEPROJECT_MAIN_MODEL_H
#define ESCAPEGAMEPROJECT_MAIN_MODEL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SCREEN_W 1260
#define SCREEN_H 560
#define TMAX 100
/**
 * \fn object type enum
 * \author Marie
 * \details
 * describe the object type
 */
enum obj_type { Button, clue, code };
/**
 * \fn object struct
 * \author Marie
 * \details
 * an id, his position in the framing, a file name (Path to the .png for the view)
 */
typedef struct {
    char * id;
    int j;
    int i;
    char * file_name;
    enum obj_type type;
}Object;
/**
 * \fn door struct
 * \author Marie
 * \details
 * an id, his position in the framing, a file name (Path to the .png for the view)
 * la variable access indique si la porte peut être traversée
 */
typedef struct {
    char * id;
    int i;
    int j;
    char * file_name;
    int access;
}Door;
/**
 * \fn Frame struct
 * \author Marie
 * \details
 * is a partition of the framing :
 * framing is a table of objects (table ==NULL if no object)
 */
typedef struct {
    int Pos_x; //position height
    int Pos_y; //position Width
    Object * o; //=NULL par defaut
    Door * d;
}frame;
/**
 * \fn room struct
 * \author Marie
 * \details
 * the height and the width of each frame and their number in line and column of the framing
 * the number of objects present in the room
 * the name of the room
 * the path to the background
 * a pointer to the table framing
 */
typedef struct {
    int h;
    int w; //taille de la case
    int nb_obj;
    int nb_j;
    int nb_i;
    char * name;
    char * filename;
    frame ** framing;
}Room;
/**
 * \fn Personage struct
 * \author Marie
 * \details
 * describe the character in the model :
 * is position (x,y)
 */
typedef struct {
    int x_position;
    int y_position;
} Personage;

typedef struct Edge Edge;
typedef struct EdgeList EdgeList;
typedef struct Vertex Vertex;
typedef struct VertexList VertexList;
/*
 * definition des objets
 */
/**
 * \fn Object * createObject(char * id, int x, int y, char * file_name, enum obj_type type)
 * \author Marie
 * \details
 * Crée et alloue un objet
 * @param id : indicateur de l'objet
 * @param j: colonne dans le cadrillage de la Room
 * @param i: ligne dans le cadrillage de la Room
 * @param filename : chemin vers l'image de l'objet
 * @param type : type d'objet
 * @return pointer to the object
 */
Object * createObject(char * id, int x, int y, char * file_name, enum obj_type type);
/**
 * \fn Door * createDoor(char * id, int x, int y, char * file_name)
 * \author Marie
 * \details
 * Crée et alloue une porte
 *  @param id : indicateur de la porte
 *  @param j: colonne dans le cadrillage de la Room
 *  @param i: ligne dans le cadrillage de la Room
 *  @param filename : chemin vers l'image de la porte
 *  @param access : est par défaut initié à 0 (porte fermée)
 *  @return un pointeur vers la porte
 */
Door * createDoor(char * id, int x, int y, char * file_name);
/**
 * \fn void changeAccess(Door *D)
 * \author Marie
 * \details
 * passe le paramète access de la porte à 1 (porte ouverte)
 * @param Door
 */
void changeAccess(Door *D);
/**
 * \fn void freeObject(Object *o)
 * \author Marie
 * \details
 * libère la mémoire liée à l'objet o
 */
void freeObject(Object *o);
/**
 * \fn void freeDoor(Door * D)
 * \author Marie
 * \details
 * libère la mémoire liée à la porte d
 */
void freeDoor(Door * D);


/*
 * definition Frame
 */

//Create Room
/**
 * \fn Room * CreateRoom(char * filename, char * name,int nb_obj)
 * \author Marie
 * \details
 * crée et alloue une Room
 * elle contient le cadrillage qui décrit ce qu'il y a dans la pièce
 * @param name est le nom de la room
 * @param filename est le chemin vers l'image de la pièce
 * @param nb_obj nombre d'objet dans la room
 * @return a pointer to the room
 */
Room * CreateRoom(char * filename, char * name,int nb_obj);
//Create Framing
/**
 * \fn frame ** CreateFraming(int nb_j, int nb_i, int w, int h)
 * \author Marie
 * \details
 * Crée le cadrillage framing
 * @param h est la hauteur d'une case du cadrillage
 * @param w est la largeur d'une case du cadrillage
 * @param nb_j est le nombre de case en largeur
 * @param nb_i est le nombre de case en hauteur
 * l'objet et la porte sont null par défaut
 * @return a pointer to the frame
 */
frame ** CreateFraming(int nb_j, int nb_i, int w, int h);
/**
 * \fn void printRoom(Room *R)
 * \author Marie
 * \details
 * "print" le cadrillage de la room
 * @param R room print
 */
void printRoom(Room *R);

//delete Framing
/**
 * \fn void deleteFraming(frame ** tab)
 * \author Marie
 * \details
 * libère les objets
 * et libère la mémoire liée au cadrillage (framing)
 */
void deleteFraming(frame ** tab);
/**
 * \fn void deleteRoom(Room * R)
 * \author Marie
 * \details
 * libère la mémoire liée à la Room
 */
void deleteRoom(Room * R);

// ajouter un objet dans la pièce
/**
 * \fn void addObject(Room *R, char * id, int i, int j,char *file_name, enum obj_type)
 * \author Marie
 * \details
 * Ajout d'un objet
 * Un objet ne peut pas être créé là où il y a déjà une porte ou un objet
 * Un objet ne peut pas être créé à l'extérieur de la pièce
 * @param id identifiant de l'objet
 * @param type le type de l'objet
 * @param file_name le chemin vers son image.png
 * @param R la room dans laquelle il va être créé
 * @param i ligne du framing où il est
 * @param j colonne du framing où il est
 */
void addObject(Room *R, char * id, int i, int j,char *file_name, enum obj_type);
/**
 * \fn void addDoor(Room *R, char * id, int i, int j,char *file_name)
 * \author Marie
 * \details
 * Ajout d'une porte
 * Une porte ne peut pas être créé qu'en (2,0) ou en (2,8)
 * @param id identifiant de l'objet
 * @param type le type de l'objet
 * @param file_name le chemin vers son image.png
 * @param R la room dans laquelle il va être créé
 * @param i ligne du framing où il est
 * @param j colonne du framing où il est
 */
void addDoor(Room *R, char * id, int i, int j,char *file_name);
/**
 * \fn int * isInteractionPossible(Personage *p, Room * R)
 * \author Marie
 * \details
 * Vérfie que le personnage peut interragir avec un objet
 * @param p le personage
 * @param R la room dans laquelle il est
 * @return un pointeur vers un tableau de int:[i ; j ; t]
 * t = 0 si pas d'interraction
 * t= 1 si interraction avec un objet
 * t= 2 si interraction avec une porte
 */
int * isInteractionPossible(Personage *p, Room * R);
/**
 * \fn void freeTabMemory(int * tab)
 * \author Marie
 * \details
 * libère la mémoire d'un tableau
 * @param tab tableau à libérer
 */
void freeTabMemory(int * tab);
/*
 * definition Personnage
 */
/**
 * \fn Personage * CreatePersonage()
 * \author Marie
 * \details
 * Crée et alloue un personnage
 * en l'initialisant à la position (0;320)
 * @return un pointeur vers le personnage
 */
Personage * CreatePersonage();
/**
 * \fn void DeletePersonage(Personage * p)
 * \author Marie
 * \details
 * Supprime et libère la mémoir du personnage p
 * @param p le personnage à libérer
 */
void DeletePersonage(Personage * p);
/**
 * \fn void move_up(Personage * p, int n)
 * \author Marie
 * \details
 * Le personnage se déplace vers le haut de n pixels
 * @param p le Personnage
 * @param n le nombre de pixel dont il bouge
 */
void move_up(Personage * p, int n);
/**
 * \fn void move_down(Personage * p, int n)
 * \author Marie
 * \details
 * Le personnage se déplace vers le bas de n pixels
 * @param p le Personnage
 * @param n le nombre de pixel dont il bouge
 */
void move_down(Personage * p, int n);
/**
 * \fn void move_left(Personage * p, int n)
 * \author Marie
 * \details
 * Le personnage se déplace vers la gauche de n pixels
 * @param p le Personnage
 * @param n le nombre de pixel dont il bouge
 */
void move_left(Personage * p, int n);
/**
 * \fn void move_right(Personage * p, int n)
 * \author Marie
 * \details
 * Le personnage se déplace vers la droite de n pixels
 * @param p le Personnage
 * @param n le nombre de pixel dont il bouge
 */
void move_right(Personage * p, int n);

/*
 * definition des graph
 * Graph : "Machine d'état" du scénario
 * EdgeList: liste de lien entre le Vertex et ses successeurs
 * Structures
 */
/**
 * \fn Edge struct
 * \author Marie
 * \details
 * lien entre deux Vertex. composé du label de l'objet permettant le changement d'état (de salle) et le Vertex vers lequel il mène
 */
struct Edge{
    char * obj_label;
    Vertex *v_next;
    struct Edge *next_e;
};
/**
 * \fn EdgeList struct
 * \author Marie
 * \details
 * Liste d'Edge
 */
struct EdgeList{
    Edge *first;
    Edge *current;
    Edge *last;
};
/*
 * Fonction Gestion de Liste Edge List
 */
/**
 * \fn void initEdgeList(EdgeList * c)
 * \author Marie
 * \details
 * initialise l'EdgeList en mettant tous les pointeurs (current, first, last) à NULL
 * @param c EdgeList à initialiser
 */
void initEdgeList(EdgeList * c);
/**
 * \fn int isEmptyEdgeList(EdgeList * c)
 * \author Marie
 * \details
 * Teste si la liste est vide
 * @param c EdgeList à tester
 */
int isEmptyEdgeList(EdgeList * c);
/**
 * \fn void insertFirstEdge(EdgeList *c, char *obj, Vertex * v)
 * \author Marie
 * \details
 * ajoute un edge en premier dans la liste d'Edge
 * @param c la liste dans laquelle il est ajouté
 * @param obj non de l'objet qui lui est lié (porte)
 * @param v pointeur vers le vertex qu'il pointe
 */
void insertFirstEdge(EdgeList *c, char *obj, Vertex * v);
/**
 * \fn void insertLastEdge(EdgeList *c, char *obj, Vertex * v)
 * \author Marie
 * \details
 * ajoute un edge en dernier dans la liste d'Edge
 * @param c la liste dans laquelle il est ajouté
 * @param obj non de l'objet qui lui est lié (porte)
 * @param v pointeur vers le vertex qu'il pointe
 */
void insertLastEdge(EdgeList *c, char *obj, Vertex * v);

/*
 * "travel in the List"
 */
/**
 * \fn void setOnFirstEdge(EdgeList *c)
 * \author Marie
 * \details
 * met le pointeur "current" sur le premier Edge de la Liste
 * @param c EdgeList
 */
void setOnFirstEdge(EdgeList *c);
/**
 * \fn void setOnLastEdge(EdgeList *c)
 * \author Marie
 * \details
 * met le pointeur "current" sur le dernier Edge de la Liste
 * @param c EdgeList
 */
void setOnLastEdge(EdgeList *c);
/**
 * \fn void setOnNextEdge(EdgeList *c)
 * \author Marie
 * \details
 * met le pointeur "current" sur l'Edge suivant de la Liste
 * @param c EdgeList
 */
void setOnNextEdge(EdgeList *c);
/**
 * \fn Edge * findEdge(EdgeList *c, char *obj)
 * \author Marie
 * \details
 * cherche dans la liste d'edge et retourne l'edge de label donné en paramètre
 * return NULL si elle n'a pas trouvé l'edge
 * @param c EdgeList dans laquelle on cherche l'Edge
 * @param obj nom de l'objet lié à l'Edge cherché
 */
Edge * findEdge(EdgeList *c, char *obj);
/*
 * Print Edge List
 */
/**
 * \fn void printEdgeList(EdgeList *c)
 * \author Marie
 * \details
 * print the EdgeList
 * @param c EdgeList affichée
 */
void printEdgeList(EdgeList *c);

/*
 * Delete Edge
 */
/**
 * \fn void deleteFirstEdge(EdgeList *c)
 * \author Marie
 * \details
 * supprime le premier Edge de l'EdgeList
 * et en libère la mémoire
 * @param c EdgeList dont on supprime le premier Edge
 */
void deleteFirstEdge(EdgeList *c);
/**
 * \fn void deleteEdgeList(EdgeList * c)
 * \author Marie
 * \details
 * supprime tous les Edges de l'Edge list et en libère la mémoire
 * @param c EdgeList supprimée
 */
void deleteEdgeList(EdgeList * c);

/*
 * VertexList: liste de vertex
 */

/*
 * Structures
 */
/**
* \fn Vertex struct
* \author Marie
* \details
* Etat du jeu, chaque état correspond à une salle du jeu
* Composé du nom du vertex, sa liste de liens, la room à laquelle il est lié, le nombre d'enigme et le nombre d'enigme résolues
*/
struct Vertex{
    char * label;
    EdgeList * connect;//vide de base
    Room * R;
    int enigma_number;
    int enigma_solved; //à 0 de base
    Vertex * previous_v;
    Vertex * next_v;
};
/**
* \fn VertexList struct
* \author Marie
* \details
* Liste de Vertex
*/
struct VertexList{
    Vertex *first;
    Vertex *current;
    Vertex *last;
};
/*
 * Fonction Gestion de Liste Vertex
 */
/**
 * \fn VertexList * initGraph()
 * \author Marie
 * \details
 * crée et alloue un graph (VertexList)
 * Et l'initialise en mettant tous les pointeurs (current, first, last) à NULL
 */
VertexList * initGraph();
/**
 * \fn int isEmptyVertexList(VertexList * g)
 * \author Marie
 * \details
 * Teste si le graph est vide
 * @param g VertexList à tester
 */
int isEmptyVertexList(VertexList * g);
/**
 * \fn void insertFirstVertex(VertexList * g,char * label,int enigma_number)
 * \author Marie
 * \details
 * ajoute un vertex en premier dans la liste de Vertex
 * @param g la liste dans laquelle il est ajouté
 * @param label non de la salle qui lui est lié
 * @param enigma_number nombre d'enigme dans la salle
 */
void insertFirstVertex(VertexList * g,char * label,int enigma_number);
/**
 * \fn void insertLastVertex(VertexList * g,char * label,int enigma_number)
 * \author Marie
 * \details
 * ajoute un vertex en dernier dans la liste de Vertex
 * @param g la liste dans laquelle il est ajouté
 * @param label non de la salle qui lui est lié
 * @param enigma_number nombre d'enigme dans la salle
 */
void insertLastVertex(VertexList * g,char * label,int enigma_number);
/**
 * \fn void addLink(Vertex * v1, Vertex * v2, char * obj_label)
 * \author Marie
 * \details
 * add an edge from the Vretex v1 to the vertex v2
 * @param v1 Vertex dont part l'Edge
 * @param v2 Vertex où va l'Edge
 * @param obj_label nom de l'objet  lié à l'edge (porte)
 */
void addLink(Vertex * v1, Vertex * v2, char * obj_label);

/*
 * "travel in the List"
 */
/**
 * \fn void setOnFirstVertex(VertexList * g)
 * \author Marie
 * \details
 * met le pointeur "current" sur le premier Vertex de la Liste
 * @param g VertexList
 */
void setOnFirstVertex(VertexList * g);
/**
 * \fn void setOnLastVertex(VertexList * g)
 * \author Marie
 * \details
 * met le pointeur "current" sur le dernier Vertex de la Liste
 * @param g VertexList
 */
void setOnLastVertex(VertexList * g);
/**
 * \fn void setOnNextVertex(VertexList * g)
 * \author Marie
 * \details
 * met le pointeur "current" sur le Vertex suivant de la Liste
 * @param g VertexList
 */
void setOnNextVertex(VertexList * g);
/**
 * \fn void setOnPreviousVertex(VertexList *g)
 * \author Marie
 * \details
 * met le pointeur "current" sur le Vertex précédent de la Liste
 * @param g VertexList
 */
void setOnPreviousVertex(VertexList *g);
/**
 * \fn Vertex * findVertex(VertexList * g,char * label)
 * \author Marie
 * \details
 * cherche dans la liste de vertex et retourne le vertex de label donné en paramètre
 * return NULL si elle n'a pas trouvé le Vertex
 * @param g nom de la VertexList où on cherche
 * @param label nom de la salle liée au vertex
 */
Vertex * findVertex(VertexList * g,char * label);
/*
 * Print Vertex List
 */
/**
 * \fn void printGraph(VertexList * g)
 * \author Marie
 * \details
 * print the graph
 * @param g VertexList qu'on affiche
 */
void printGraph(VertexList * g);

/*
 * Delete Vertex
 */
/**
 * \fn void deleteFirstVertex(VertexList * g)
 * \author Marie
 * \details
 * supprime le premier Vertex de la VertexList
 * et en libère la mémoire
 * @param g VertexList dont on supprime le premier Edge
 */
void deleteFirstVertex(VertexList * g);
/**
 * \fn void deleteGraph(VertexList * g)
 * \author Marie
 * \details
 * supprime tous les Vertex de la Vertex list et en libère la mémoire
 * @param g VertexList supprimée
 */
void deleteGraph(VertexList * g);

/**
 * \fn int changeStateAccess(VertexList * g)
 * \author Marie
 * \details
 * Vérifie que le changement de salle peut être autorisée,
 * et si c'est le cas change les accès des porte de la salle
 * @param g VertexList, graph du jeu dans lequel on évolue
 */
int changeStateAccess(VertexList * g);
/**
 * \fn int changeRoom(VertexList *g,Door *d)
 * \author Marie
 * \details
 * Si la porte est déverrouillée, change la salle (Vertex) actuel à la salle à laquele la porte est liée
 * @param g VertexList, graph du jeu dans lequel on évolue
 * @param d Porte avec laquelle on interragit
 */
int changeRoom(VertexList *g,Door *d);
/**
 * \fn int SolvedEnigma(VertexList * g)
 * \author Marie
 * \details
 * augmente de 1 le nombre d'énigme résolu et appelle la fonction state change pour vérifier si le changement d'état est possible
 * @param g VertexList, graph du jeu dans lequel on évolue
 */
int SolvedEnigma(VertexList * g);
/**
 * \fn void freeStateMachine(VertexList * g)
 * \author Marie
 * \details
 * Libère la mémoire liée au jeu
 * en libérant les salle et le Graph
 * @param g VertexList, graph du jeu dans lequel on évolue
 */
void freeStateMachine(VertexList * g);

/*
 * Lecture de fichiers
 */
//open close
/**
 * \fn FILE *openFileRead(char *nom)
 * \author Marie
 * \details
 * ouvre un fichier en mode lecture
 * @param nom chemin vers le fichier à lire
 */
FILE *openFileRead(char *nom);
/**
 * \fn void closeFile(FILE *f)
 * \author Marie
 * \details
 * ferme un fichier
 * @param f fichier à fermer
 */
void closeFile(FILE *f);
//read line
/**
 * \fn char * readFileLine(FILE *f, char *tampon)
 * \author Marie
 * \details
 * lit une ligne et la stock dans le tableau tampon
 * @param f fichier lu
 * @param tampon chaine de caractères qui contient la ligne lu
 */
char * readFileLine(FILE *f, char *tampon);
//read Room file
/**
 * \fn Room * readRoomFile(char * PATH)
 * \author Marie
 * \details
 * Ouvre, lit le fichier au chemin PATH, et crée la Room
 * et appelle la fonction read line pour y ajouter des objets/des portes
 * @param PATH chemin vers le fichier
 */
Room * readRoomFile(char * PATH);
/**
 * \fn void readRoomFileLine(char * tampon,Room *R)
 * \author Marie
 * \details
 * Traite une ligne d'un fichier Room
 * pour ajouter des objets/portes dans la Room (R)
 * @param tampon chaine contenant la ligne à traiter
 * @param R Salle dans laquelle sont ajoutées les objets/portes
 */
void readRoomFileLine(char * tampon,Room *R);
//read Graph File
/**
 * \fn VertexList * readGraphFile(char * PATH);
 * \author Marie
 * \details
 * Ouvre, lit le fichier au chemin PATH, et crée le Graph
 * et appelle la fonction read line pour y ajouter des Vertex/liens.
 * @param PATH chemin vers le fichier
 */
VertexList * readGraphFile(char * PATH);
/**
 * \fn void readGraphFileLine(char * tampon, VertexList * g)
 * \author Marie
 * \details
 * Traite une ligne d'un fichier Graph
 * pour ajouter des Vertex/liens dans le Graph (g)
 * @param tampon chaine contenant la ligne à traiter
 * @param g graph où sont ajoutées les Vertex/ les Edges
 */
void readGraphFileLine(char * tampon, VertexList * g);
/**
 * \fn void associateRoomWithVertexList(VertexList *g,Room *R)
 * \author Marie
 * \details
 * Ajoute le pointeur vers la room R au vertex du même nom
 * @param g graph où est ajoutée la salle
 * @param R room liée
 */
void associateRoomWithVertexList(VertexList *g,Room *R);
#endif //ESCAPEGAMEPROJECT_MAIN_MODEL_H
