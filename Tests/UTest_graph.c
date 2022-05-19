//
// Created by Marie on 16/04/22.
//
#include "../Model/model.h"

#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

char * mem(char * in){
    char * out = malloc((sizeof(char))*TMAX);
    strcpy(out,in);
    return out;
}

/*
 * def test Vertex List
 */
static void test_VertexList_Init(){
    VertexList * g= initGraph();
    assert_true(g->current==NULL);
    assert_true(g->first==NULL);
    assert_true(g->last==NULL);
    deleteGraph(g);
}
static void test_VertexList_EmptyTrue(){
    VertexList * g= initGraph();
    assert_true(isEmptyVertexList(g));
    assert_false(!isEmptyVertexList(g));
    deleteGraph(g);
}
static void test_VertexList_addEmpty1(){
    VertexList * g= initGraph();
    char * label="Vertex2";
    insertFirstVertex(g,mem(label),2);
    assert_int_equal(g->first,g->last);
    assert_string_equal(g->first->label,"Vertex2");
    assert_string_equal(g->last->label,"Vertex2");
    assert_int_equal(g->first->enigma_solved,0);
    assert_int_equal(g->first->enigma_number,2);
    assert_true(g->first->connect->first==NULL);
    assert_true(g->first->connect->current==NULL);
    assert_true(g->first->connect->last==NULL);
    deleteGraph(g);
}
static void test_VertexList_addEmpty2(){
    VertexList * g= initGraph();
    char * label="Vertex2";
    insertLastVertex(g,mem(label),2);
    assert_int_equal(g->first,g->last);
    assert_string_equal(g->first->label,"Vertex2");
    assert_string_equal(g->last->label,"Vertex2");
    assert_int_equal(g->first->enigma_solved,0);
    assert_int_equal(g->first->enigma_number,2);
    assert_true(g->first->connect->first==NULL);
    assert_true(g->first->connect->current==NULL);
    assert_true(g->first->connect->last==NULL);
    deleteGraph(g);
}
static void test_VertexList_EmptyFalse(){
    VertexList * g= initGraph();
    char * label="Vertex2";
    insertLastVertex(g,mem(label),2);
    assert_true(!isEmptyVertexList(g));
    assert_false(isEmptyVertexList(g));
    deleteGraph(g);
}
static void test_VertexList_addFirst(){
    VertexList * g= initGraph();
    char * label2="Vertex2";
    char * label1="Vertex1";
    insertFirstVertex(g,mem(label2),2);
    insertFirstVertex(g,mem(label1),2);
    assert_string_equal(g->first->label,"Vertex1");
    assert_string_equal(g->last->label,"Vertex2");
    deleteGraph(g);
}
static void test_VertexList_addLast(){
    VertexList * g= initGraph();
    char * label2="Vertex2";
    char * label1="Vertex1";
    char * label3="Vertex3";
    insertFirstVertex(g,mem(label2),2);
    insertFirstVertex(g,mem(label1),2);
    insertLastVertex(g,mem(label3),2);
    assert_string_equal(g->first->label,"Vertex1");
    assert_string_equal(g->last->label,"Vertex3");
    deleteGraph(g);
}
static void test_VertexList_setFirst(){
    VertexList * g= initGraph();
    char * label2="Vertex2";
    char * label1="Vertex1";
    char * label3="Vertex3";
    insertFirstVertex(g,mem(label2),2);
    insertFirstVertex(g,mem(label1),2);
    insertLastVertex(g,mem(label3),2);
    setOnFirstVertex(g);
    assert_string_equal(g->current->label,"Vertex1");
    deleteGraph(g);
}
static void test_VertexList_setNext(){
    VertexList * g= initGraph();
    char * label2="Vertex2";
    char * label1="Vertex1";
    char * label3="Vertex3";
    insertFirstVertex(g,mem(label2),2);
    insertFirstVertex(g,mem(label1),2);
    insertLastVertex(g,mem(label3),2);
    setOnFirstVertex(g);
    setOnNextVertex(g);
    assert_string_equal(g->current->label,"Vertex2");
    deleteGraph(g);
}
static void test_VertexList_setLast(){
    VertexList * g= initGraph();
    char * label2="Vertex2";
    char * label1="Vertex1";
    char * label3="Vertex3";
    insertFirstVertex(g,mem(label2),2);
    insertFirstVertex(g,mem(label1),2);
    insertLastVertex(g,mem(label3),2);
    setOnLastVertex(g);
    assert_string_equal(g->current->label,"Vertex3");
    deleteGraph(g);
}
static void test_VertexList_setPrevious(){
    VertexList * g= initGraph();
    char * label2="Vertex2";
    char * label1="Vertex1";
    char * label3="Vertex3";
    insertFirstVertex(g,mem(label2),2);
    insertFirstVertex(g,mem(label1),2);
    insertLastVertex(g,mem(label3),2);
    setOnLastVertex(g);
    setOnPreviousVertex(g);
    assert_string_equal(g->current->label,"Vertex2");
    deleteGraph(g);
}

static void test_VertexList_find(){
    VertexList * g= initGraph();
    char * label2="Vertex2";
    char * label1="Vertex1";
    char * label3="Vertex3";
    insertFirstVertex(g,mem(label2),2);
    insertFirstVertex(g,mem(label1),2);
    insertLastVertex(g,mem(label3),2);
    Vertex * v= findVertex(g,label2);
    assert_string_equal(v->label,"Vertex2");
    v= findVertex(g,label1);
    assert_string_equal(v->label,"Vertex1");
    v= findVertex(g,label3);
    assert_string_equal(v->label,"Vertex3");
    deleteGraph(g);
}
static void test_VertexList_NotFound(){
    VertexList * g= initGraph();
    char * label2="Vertex2";
    char * label1="Vertex1";
    char * label3="Vertex3";
    insertFirstVertex(g,mem(label2),2);
    insertFirstVertex(g,mem(label1),2);
    Vertex * v= findVertex(g,label3);
    assert_true(v==NULL);
    deleteGraph(g);
}
static void test_VertexList_addLink(){
    VertexList * g= initGraph();
    char * label2="Vertex2";
    char * label1="Vertex1";
    char * label3="Vertex3";
    insertFirstVertex(g,mem(label2),2);
    insertFirstVertex(g,mem(label1),2);
    insertLastVertex(g,mem(label3),2);
    char * obj1="Object1";
    char * obj2="Object2";
    Vertex * v =findVertex(g,label1);
    addLink(v,findVertex(g,label2),mem(obj1));
    addLink(v,findVertex(g,label3),mem(obj2));
    assert_string_equal(v->connect->first->obj_label,"Object1");
    assert_string_equal(v->connect->last->obj_label,"Object2");
    assert_string_equal(v->connect->first->v_next->label,"Vertex2");
    assert_string_equal(v->connect->last->v_next->label,"Vertex3");
    deleteGraph(g);
}
static void test_VertexList_deleteFirst(){
    VertexList * g= initGraph();
    char * label2="Vertex2";
    char * label1="Vertex1";
    char * label3="Vertex3";
    insertFirstVertex(g,mem(label2),2);
    insertFirstVertex(g,mem(label1),2);
    insertLastVertex(g,mem(label3),2);
    deleteFirstVertex(g);
    assert_string_equal(g->first->label,"Vertex2");
    assert_string_equal(g->last->label,"Vertex3");
    deleteGraph(g);
}
static void test_VertexList_delete_toAnEmpty(){
    VertexList * g= initGraph();
    char * label="Vertex2";
    insertLastVertex(g,mem(label),2);
    deleteFirstVertex(g);
    assert_true(isEmptyVertexList);
    assert_true(g->first==NULL);
    assert_true(g->last==NULL);
    deleteGraph(g);
}
static void Test_Print(){
    VertexList * g= initGraph();
    char * label2="Vertex2";
    char * label1="Vertex1";
    char * label3="Vertex3";
    insertFirstVertex(g,mem(label2),2);
    insertFirstVertex(g,mem(label1),2);
    insertLastVertex(g,mem(label3),2);
    char * obj1="Object1";
    char * obj2="Object2";
    char * obj3="Object3";
    char * obj4="Object4";
    char * obj5="Object5";
    char * obj6="Object6";
    addLink(findVertex(g,label1),findVertex(g,label2),mem(obj1));
    addLink(findVertex(g,label1),findVertex(g,label3),mem(obj2));
    addLink(findVertex(g,label3),findVertex(g,label2),mem(obj3));
    addLink(findVertex(g,label3),findVertex(g,label1),mem(obj4));
    addLink(findVertex(g,label3),findVertex(g,label3),mem(obj5));
    addLink(findVertex(g,label1),findVertex(g,label1),mem(obj6));
    printGraph(g);
    deleteGraph(g);
}

static void Test_free(){
    VertexList * graph = readGraphFile("../Files_descriptors/Graph.txt");
    Room * room1 = readRoomFile("../Files_descriptors/Room1.txt");
    Room * room2 = readRoomFile("../Files_descriptors/Room2.txt");

    associateRoomWithVertexList(graph,room1);
    associateRoomWithVertexList(graph, room2);

    printGraph(graph);
    setOnFirstVertex(graph);
    printRoom(graph->current->R);
    setOnNextVertex(graph);
    printRoom(room2);

    freeStateMachine(graph);
}

int main(void){
    /**
     * Test Graph : EdgeList
     */
   const struct CMUnitTest tests[]={
            cmocka_unit_test(test_VertexList_Init),
            cmocka_unit_test(test_VertexList_EmptyTrue),
            cmocka_unit_test(test_VertexList_addEmpty1),
            cmocka_unit_test(test_VertexList_addEmpty2),
            cmocka_unit_test(test_VertexList_EmptyFalse),
            cmocka_unit_test(test_VertexList_addFirst),
            cmocka_unit_test(test_VertexList_addLast),
            cmocka_unit_test(test_VertexList_setFirst),
            cmocka_unit_test(test_VertexList_setLast),
            cmocka_unit_test(test_VertexList_setNext),
            cmocka_unit_test(test_VertexList_setPrevious),
            cmocka_unit_test(test_VertexList_find),
            cmocka_unit_test(test_VertexList_NotFound),
            cmocka_unit_test(test_VertexList_delete_toAnEmpty),
            cmocka_unit_test(test_VertexList_deleteFirst),
            cmocka_unit_test(test_VertexList_addLink),
            cmocka_unit_test(Test_free)
    };
    Test_Print();
    return cmocka_run_group_tests_name("test Graph",tests,NULL,NULL);
}
