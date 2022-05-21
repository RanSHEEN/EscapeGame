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
 * object Type enumération
 */
enum obj_type { Button, clue, code };
/**
 * object Type structure
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
 * door Type structure
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
 * Frame structure
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
 * struct room describe the room :
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
 * struct personage describe the character in the model :
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
 * Object * createObject
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
 * Door * createDoor
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
 * void changeAccess
     * passe le paramète access de la porte à 1 (porte ouverte)
     * @param Door
     */
void changeAccess(Door *D);
/**
 * void freeObject
     * libère la mémoire liée à l'objet o
     */
void freeObject(Object *o);
/**
 * void freeDoor
     * libère la mémoire liée à la porte d
     */
void freeDoor(Door * D);


/*
 * definition Frame
 */

//Create Room
/**
 * Room * CreateRoom
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
 * frame ** CreateFraming
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
 * void printRoom
     * "print" le cadrillage de la room @param R :
     *
     * Name
     * Filename
     * (x1,y1):door ou object id or vide ; (x2;y1):door ou object id or vide ; ... (xn;y1):door ou object id or vide
     * (x1;y2):door ou object id or vide ; ...
     * ...
     * (x1;ym):door ou object id or vide ; (x2;ym):door ou object id or vide ; ... (xn;ym):door ou object id or vide
     */
void printRoom(Room *R);

//delete Framing
/**
 * void deleteFraming
     * libère les objets
     * et libère la mémoire liée au cadrillage (framing)
     */
void deleteFraming(frame ** tab);
/**
 * void deleteRoom
     * libère la mémoire liée à la Room
     */
void deleteRoom(Room * R);

// ajouter un objet dans la pièce
/**
 * void addObject
    * Ajout d'un objet
    * @param id identifiant de l'objet
    * @param type le type de l'objet
    * @param file_name le chemin vers son image.png
    * @param R la room dans laquelle il va être créé
    * @param i ligne du framing où il est
    * @param j colonne du framing où il est
    *
    * Un objet ne peut pas être créé là où il y a déjà une porte ou un objet
    * Un objet ne peut pas être créé à l'extérieur de la pièce
    */
void addObject(Room *R, char * id, int i, int j,char *file_name, enum obj_type);
/**
 * void addDoor
     * Ajout d'une porte
     * @param id identifiant de l'objet
    * @param type le type de l'objet
    * @param file_name le chemin vers son image.png
    * @param R la room dans laquelle il va être créé
    * @param i ligne du framing où il est
    * @param j colonne du framing où il est
    *
     * Une porte ne peut pas être créé qu'en (2,0) ou en (2,8)
     */
void addDoor(Room *R, char * id, int i, int j,char *file_name);
/**
 * int * isInteractionPossible
     * Vérfie que le personnage peut interragir avec un objet
     * @param p le personage
     * @param R la room dans laquelle il est
     * @return un pointeur vers un tableau de int:
     * [i ; j ; t]
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
 * Personage * CreatePersonage
     * Crée et alloue un personnage
     * en l'initialisant à la position (0;320)
     *
     * @return un pointeur vers le personnage
     */
Personage * CreatePersonage();
/**
 * void DeletePersonage
     * Supprime et libère la mémoir du personnage p
     * @param p le personnage à libérer
     */
void DeletePersonage(Personage * p);
/**
     * Le personnage se déplace vers le haut de n pixels
     * @param p le Personnage
     * @param n le nombre de pixel dont il bouge
     */
void move_up(Personage * p, int n);
/**
     * Le personnage se déplace vers le bas de n pixels
     * @param p le Personnage
     * @param n le nombre de pixel dont il bouge
     */
void move_down(Personage * p, int n);
/**
     * Le personnage se déplace vers la gauche de n pixels
     * @param p le Personnage
     * @param n le nombre de pixel dont il bouge
     */
void move_left(Personage * p, int n);
/**
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
struct Edge{
    char * obj_label;
    Vertex *v_next;
    struct Edge *next_e;
};
struct EdgeList{
    Edge *first;
    Edge *current;
    Edge *last;
};
/**
 * Graph : VertexList représentant la machine d'état du jeu
 * VertexList: liste de vertex
 * EdgeList: liste de lien entre le Vertex et ses successeurs
 *
 */
/*
 * Fonction Gestion de Liste Edge List
 */
/**
     * initialise l'EdgeList en mettant tous les pointeurs (current, first, last) à NULL
     * @param c EdgeList à initialiser
     */
void initEdgeList(EdgeList * c);
/**
     * Teste si la liste est vide
     * @param c EdgeList à tester
     */
int isEmptyEdgeList(EdgeList * c);
/**
     * ajoute un edge en premier dans la liste d'Edge
     * @param c la liste dans laquelle il est ajouté
     * @param obj non de l'objet qui lui est lié (porte)
     * @param v pointeur vers le vertex qu'il pointe
     */
void insertFirstEdge(EdgeList *c, char *obj, Vertex * v);
/**
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
     * met le pointeur "current" sur le premier Edge de la Liste
     * @param c EdgeList
     */
void setOnFirstEdge(EdgeList *c);
/**
     * met le pointeur "current" sur le dernier Edge de la Liste
     * @param c EdgeList
     */
void setOnLastEdge(EdgeList *c);
/**
     * met le pointeur "current" sur l'Edge suivant de la Liste
     * @param c EdgeList
     */
void setOnNextEdge(EdgeList *c);
/**
     * cherche dans la liste d'edge et retourne l'edge de label donné en paramètre
     * return NULL si elle n'a pas trouvé l'edge
     * @param c EdgeList dans laquelle on cherche l'Edge
     * @param obj nom de l'objet lié à l'Edge cherché
     */
Edge * findEdge(EdgeList *c, char *obj);
/*
 * Print Edge List
 */
/**print the EdgeList:
   *    --obj_label--> label
   *    --obj_label--> label
   *    --obj_label--> label
   * @param c EdgeList affichée
  */
void printEdgeList(EdgeList *c);

/*
 * Delete Edge
 */
/**
     * supprime le premier Edge de l'EdgeList
     * et en libère la mémoire
     * @param c EdgeList dont on supprime le premier Edge
     */
void deleteFirstEdge(EdgeList *c);
/**
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
struct Vertex{
    char * label;
    EdgeList * connect;//vide de base
    Room * R;
    int enigma_number;
    Vertex * previous_v;
    Vertex * next_v;
    int enigma_solved; //à 0 de base
};
struct VertexList{
    Vertex *first;
    Vertex *current;
    Vertex *last;
};
/*
 * Fonction Gestion de Liste Vertex
 */
/**
     * crée et alloue un graph (VertexList)
     * Et l'initialise en mettant tous les pointeurs (current, first, last) à NULL
     */
VertexList * initGraph();
/**
     * Teste si le graph est vide
     * @param g VertexList à tester
     */
int isEmptyVertexList(VertexList * g);
/**
     * ajoute un vertex en premier dans la liste de Vertex
     * @param g la liste dans laquelle il est ajouté
     * @param label non de la salle qui lui est lié
     * @param enigma_number nombre d'enigme dans la salle
     */
void insertFirstVertex(VertexList * g,char * label,int enigma_number);
/**
     * ajoute un vertex en dernier dans la liste de Vertex
     * @param g la liste dans laquelle il est ajouté
     * @param label non de la salle qui lui est lié
     * @param enigma_number nombre d'enigme dans la salle
     */
void insertLastVertex(VertexList * g,char * label,int enigma_number);
/**
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
     * met le pointeur "current" sur le premier Vertex de la Liste
     * @param g VertexList
     */
void setOnFirstVertex(VertexList * g);
/**
     * met le pointeur "current" sur le dernier Vertex de la Liste
     * @param g VertexList
     */
void setOnLastVertex(VertexList * g);
/**
     * met le pointeur "current" sur le Vertex suivant de la Liste
     * @param g VertexList
     */
void setOnNextVertex(VertexList * g);
/**
     * met le pointeur "current" sur le Vertex précédent de la Liste
     * @param g VertexList
     */
void setOnPreviousVertex(VertexList *g);
/**
 * cherche dans la liste de vertex et retourne le vertex de label donné en paramètre
 * return NULL si elle n'a pas trouvé le Vertex
 * @param g nom de la VertexList où on cherche
 * @param label nom de la salle liée au vertex
 */
Vertex * findVertex(VertexList * g,char * label);
/*
 * Print Vertex List
 */
/**print the graph:
     * label :
     *    --obj_label--> label
     *    --obj_label--> label
     *    --obj_label--> label
     * @param g VertexList qu'on affiche
    */
void printGraph(VertexList * g);

/*
 * Delete Vertex
 */
/**
     * supprime le premier Vertex de la VertexList
     * et en libère la mémoire
     * @param g VertexList dont on supprime le premier Edge
     */
void deleteFirstVertex(VertexList * g);
/**
     * supprime tous les Vertex de la Vertex list et en libère la mémoire
     * @param g VertexList supprimée
     */
void deleteGraph(VertexList * g);

/**
 * State Change
 * Notre graph s'apparente à uns machine d'état
 * quand on résout les énigmes de l'étape on change d'état
 */

/**
     * Vérifie que le changement de salle peut être autorisée,
     * et si c'est le cas change les accès des porte de la salle
     * @param g VertexList, graph du jeu dans lequel on évolue
     */
int changeStateAccess(VertexList * g);
/**
     * Si la porte est déverrouillée, change la salle (Vertex) actuel à la salle à laquele la porte est liée
     * @param g VertexList, graph du jeu dans lequel on évolue
     * @param d Porte avec laquelle on interragit
     */
int changeRoom(VertexList *g,Door *d);
/**
     * augmente de 1 le nombre d'énigme résolu et appelle la fonction state change pour vérifier si le changement d'état est possible
     * @param g VertexList, graph du jeu dans lequel on évolue
     */
int SolvedEnigma(VertexList * g);
/**
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
     * ouvre un fichier en mode lecture
     * @param nom chemin vers le fichier à lire
     */
FILE *openFileRead(char *nom);
/**
     * ferme un fichier
     * @param f fichier à fermer
     */
void closeFile(FILE *f);
//read line
/**
     * lit une ligne et la stock dans le tableau tampon
     * @param f fichier lu
     * @param tampon chaine de caractères qui contient la ligne lu
     */
char * readFileLine(FILE *f, char *tampon);
//read Room file
/**
     * Ouvre, lit le fichier au chemin PATH, et crée la Room
     * et appelle la fonction read line pour y ajouter des objets/des portes
     * @param PATH chemin vers le fichier
     */
Room * readRoomFile(char * PATH);
/**
     * Traite une ligne d'un fichier Room
     * pour ajouter des objets/portes dans la Room (R)
     * @param tampon chaine contenant la ligne à traiter
     * @param R Salle dans laquelle sont ajoutées les objets/portes
     */
void readRoomFileLine(char * tampon,Room *R);
//read Graph File
/**
     * Ouvre, lit le fichier au chemin PATH, et crée le Graph
     * et appelle la fonction read line pour y ajouter des Vertex/liens.
     * @param PATH chemin vers le fichier
     */
VertexList * readGraphFile(char * PATH);
/**
    * Traite une ligne d'un fichier Graph
    * pour ajouter des Vertex/liens dans le Graph (g)
    * @param tampon chaine contenant la ligne à traiter
    * @param g graph où sont ajoutées les Vertex/ les Edges
    */
void readGraphFileLine(char * tampon, VertexList * g);
/**
    * Ajoute le pointeur vers la room R au vertex du même nom
    * @param g graph où est ajoutée la salle
    * @param R room liée
    */
void associateRoomWithVertexList(VertexList *g,Room *R);
#endif //ESCAPEGAMEPROJECT_MAIN_MODEL_H
