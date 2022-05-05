//
// Created by Marie on 04/05/22.
//
#include "./Controller/controller.h"
#include "./View/main_view.h"
#include "./Model/model.h"

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

static Vertex * CreateVertex(){
    Vertex  * v = (Vertex *) malloc( sizeof(Vertex));
    v->label="VertexForTest";
    v->connect=NULL;
    v->enigma_number=1;
    v->enigma_solved=0;
    v->next_v=NULL;
}

/*
 * def test Edge List
 */
static void test_EdgeList_Init(){
    EdgeList * c = (EdgeList *) malloc(sizeof(EdgeList));
    initEdgeList(c);
    assert_false(c->first!=NULL);
    assert_false(c->last!=NULL);
    assert_true(c->current==NULL);
}
static void test_EdgeList_Empty_true(){
    EdgeList * c = (EdgeList *) malloc(sizeof(EdgeList));
    initEdgeList(c);
    assert_true(isEmptyEdgeList(c));
    assert_false(!isEmptyEdgeList(c));
}
static void test_EdgeList_add_Empty1(){
    EdgeList * c = (EdgeList *) malloc(sizeof(EdgeList));
    initEdgeList(c);
    char obj[]= "Object2";
    Vertex * v=CreateVertex();
    insertFirstEdge(c,obj,v);
    assert_int_equal(c->last,c->first);
    assert_string_equal(c->first->obj_label,"Object2");
    assert_string_equal(c->last->obj_label,"Object2");
}
static void test_EdgeList_add_Empty2(){
    EdgeList * c = (EdgeList *) malloc(sizeof(EdgeList));
    initEdgeList(c);
    char obj[]= "Object2";
    Vertex * v=CreateVertex();
    insertLastEdge(c,obj,v);
    assert_int_equal(c->last,c->first);
    assert_string_equal(c->first->obj_label,"Object2");
    assert_string_equal(c->last->obj_label,"Object2");
}
static void test_EdgeList_Empty_false(){
    EdgeList * c = (EdgeList *) malloc(sizeof(EdgeList));
    initEdgeList(c);
    char obj[]= "Object2";
    Vertex * v=CreateVertex();
    insertLastEdge(c,obj,v);
    assert_false(isEmptyEdgeList(c));
    assert_true(!isEmptyEdgeList(c));
}
static void test_EdgeList_addFirst(){
    EdgeList * c = (EdgeList *) malloc(sizeof(EdgeList));
    initEdgeList(c);
    char obj2[]= "Object2";
    char obj1[]= "Object1";
    Vertex * v=CreateVertex();
    insertLastEdge(c,obj2,v);
    insertFirstEdge(c,obj1,v);
    assert_string_equal(c->first->obj_label,"Object1");
    assert_string_equal(c->last->obj_label,"Object2");
}
static void test_EdgeList_addLast(){
    EdgeList * c = (EdgeList *) malloc(sizeof(EdgeList));
    initEdgeList(c);
    char obj2[]= "Object2";
    char obj1[]= "Object1";
    char obj3[]= "Object3";
    Vertex * v=CreateVertex();
    insertLastEdge(c,obj2,v);
    insertFirstEdge(c,obj1,v);
    insertLastEdge(c,obj3,v);
    assert_string_equal(c->first->obj_label,"Object1");
    assert_string_equal(c->first->next_e->obj_label,"Object2");
    assert_string_equal(c->last->obj_label,"Object3");
}
static void test_EdgeList_setFirst(){
    EdgeList * c = (EdgeList *) malloc(sizeof(EdgeList));
    initEdgeList(c);
    char obj2[]= "Object2";
    char obj1[]= "Object1";
    char obj3[]= "Object3";
    Vertex * v=CreateVertex();
    insertLastEdge(c,obj2,v);
    insertFirstEdge(c,obj1,v);
    insertLastEdge(c,obj3,v);
    setOnFirstEdge(c);
    assert_string_equal(c->current->obj_label,"Object1");
}
static void test_EdgeList_setNext(){
    EdgeList * c = (EdgeList *) malloc(sizeof(EdgeList));
    initEdgeList(c);
    char obj2[]= "Object2";
    char obj1[]= "Object1";
    char obj3[]= "Object3";
    Vertex * v=CreateVertex();
    insertLastEdge(c,obj2,v);
    insertFirstEdge(c,obj1,v);
    insertLastEdge(c,obj3,v);
    setOnFirstEdge(c);
    setOnNextEdge(c);
    assert_string_equal(c->current->obj_label,"Object2");
}
static void test_EdgeList_setLast(){
    EdgeList * c = (EdgeList *) malloc(sizeof(EdgeList));
    initEdgeList(c);
    char obj2[]= "Object2";
    char obj1[]= "Object1";
    char obj3[]= "Object3";
    Vertex * v=CreateVertex();
    insertLastEdge(c,obj2,v);
    insertFirstEdge(c,obj1,v);
    insertLastEdge(c,obj3,v);
    setOnLastEdge(c);
    assert_string_equal(c->current->obj_label,"Object3");

}
static void test_EdgeList_find(){
    EdgeList * c = (EdgeList *) malloc(sizeof(EdgeList));
    initEdgeList(c);
    char obj2[]= "Object2";
    char obj1[]= "Object1";
    char obj3[]= "Object3";
    Vertex * v=CreateVertex();
    insertLastEdge(c,obj2,v);
    insertFirstEdge(c,obj1,v);
    insertLastEdge(c,obj3,v);
    Edge * e= findEdge(c,obj2);
    assert_string_equal(e->obj_label,"Object2");
    e= findEdge(c,obj1);
    assert_string_equal(e->obj_label,"Object1");
    e= findEdge(c,obj3);
    assert_string_equal(e->obj_label,"Object3");
}
static void test_EdgeList_deleteFirst(){
    EdgeList * c = (EdgeList *) malloc(sizeof(EdgeList));
    initEdgeList(c);
    char obj2[]= "Object2";
    char obj1[]= "Object1";
    char obj3[]= "Object3";
    Vertex * v=CreateVertex();
    insertLastEdge(c,obj2,v);
    insertFirstEdge(c,obj1,v);
    insertLastEdge(c,obj3,v);
    deleteFirstEdge(c);
    assert_string_not_equal(c->first->obj_label,"Object1");
}
static void test_EdgeList_deleteFirst_toAnEmpty(){
    EdgeList * c = (EdgeList *) malloc(sizeof(EdgeList));
    initEdgeList(c);
    char obj1[]= "Object1";
    Vertex * v=CreateVertex();
    insertFirstEdge(c,obj1,v);
    deleteFirstEdge(c);
    assert_true(isEmptyEdgeList);
    assert_true(c->first==NULL);
    assert_true(c->last==NULL);
    deleteEdgeList(c);
}

static void test_print(){
    EdgeList * c = (EdgeList *) malloc(sizeof(EdgeList));
    initEdgeList(c);
    char obj2[]= "Object2";
    char obj1[]= "Object1";
    char obj3[]= "Object3";
    Vertex * v=CreateVertex();
    insertLastEdge(c,obj2,v);
    insertFirstEdge(c,obj1,v);
    insertLastEdge(c,obj3,v);
    printEdgeList(c);
}


int main(void){
    /**
     * Test Graph : EdgeList
     */
    const struct CMUnitTest tests[]={
            cmocka_unit_test(test_EdgeList_Init),
            cmocka_unit_test(test_EdgeList_Empty_true),
            cmocka_unit_test(test_EdgeList_add_Empty1),
            cmocka_unit_test(test_EdgeList_add_Empty2),
            cmocka_unit_test(test_EdgeList_Empty_false),
            cmocka_unit_test(test_EdgeList_addFirst),
            cmocka_unit_test(test_EdgeList_addLast),
            cmocka_unit_test(test_EdgeList_setFirst),
            cmocka_unit_test(test_EdgeList_setNext),
            cmocka_unit_test(test_EdgeList_setLast),
            cmocka_unit_test(test_EdgeList_find),
            cmocka_unit_test(test_EdgeList_deleteFirst),
            cmocka_unit_test(test_EdgeList_deleteFirst_toAnEmpty)
    };
    test_print();
    return cmocka_run_group_tests_name("test Graph",tests,NULL,NULL);
}