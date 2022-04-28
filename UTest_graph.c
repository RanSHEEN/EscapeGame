//
// Created by Marie on 16/04/22.
//
#include "./Controller/controller.h"
#include "./View/main_view.h"
#include "./Model/main_model.h"

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


/*
 * def test Vertex List
 */
static void test_VertexList_Init(){
    VertexList * g= (VertexList *) malloc(sizeof(VertexList));
    initGraph(g);
    assert_true(g->current==NULL);
    assert_true(g->first==NULL);
    assert_true(g->last==NULL);
}
static void test_VertexList_EmptyTrue(){
    VertexList * g= (VertexList *) malloc(sizeof(VertexList));
    initGraph(g);
    assert_true(isEmptyVertexList(g));
    assert_false(!isEmptyVertexList(g));
}
static void test_VertexList_addEmpty1(){
    VertexList * g= (VertexList *) malloc(sizeof(VertexList));
    initGraph(g);
    char * label="Vertex2";
    insertFirstVertex(g,label,2);
    assert_int_equal(g->first,g->last);
    assert_string_equal(g->first->label,"Vertex2");
    assert_string_equal(g->last->label,"Vertex2");
    assert_int_equal(g->first->enigma_solved,0);
    assert_int_equal(g->first->enigma_number,2);
    assert_true(g->first->connect->first==NULL);
    assert_true(g->first->connect->current==NULL);
    assert_true(g->first->connect->last==NULL);
}
static void test_VertexList_addEmpty2(){
    VertexList * g= (VertexList *) malloc(sizeof(VertexList));
    initGraph(g);
    char * label="Vertex2";
    insertLastVertex(g,label,2);
    assert_int_equal(g->first,g->last);
    assert_string_equal(g->first->label,"Vertex2");
    assert_string_equal(g->last->label,"Vertex2");
    assert_int_equal(g->first->enigma_solved,0);
    assert_int_equal(g->first->enigma_number,2);
    assert_true(g->first->connect->first==NULL);
    assert_true(g->first->connect->current==NULL);
    assert_true(g->first->connect->last==NULL);
}
static void test_VertexList_EmptyFalse(){
    VertexList * g= (VertexList *) malloc(sizeof(VertexList));
    initGraph(g);
    char * label="Vertex2";
    insertLastVertex(g,label,2);
    assert_true(!isEmptyVertexList(g));
    assert_false(isEmptyVertexList(g));
}
static void test_VertexList_addFirst(){
    VertexList * g= (VertexList *) malloc(sizeof(VertexList));
    initGraph(g);
    char * label2="Vertex2";
    char * label1="Vertex1";
    insertFirstVertex(g,label2,2);
    insertFirstVertex(g,label1,2);
    assert_string_equal(g->first->label,"Vertex1");
    assert_string_equal(g->last->label,"Vertex2");
}
static void test_VertexList_addLast(){
    VertexList * g= (VertexList *) malloc(sizeof(VertexList));
    initGraph(g);
    char * label2="Vertex2";
    char * label1="Vertex1";
    char * label3="Vertex3";
    insertFirstVertex(g,label2,2);
    insertFirstVertex(g,label1,2);
    insertLastVertex(g,label3,2);
    assert_string_equal(g->first->label,"Vertex1");
    assert_string_equal(g->last->label,"Vertex3");
}
static void test_VertexList_setFirst(){
    VertexList * g= (VertexList *) malloc(sizeof(VertexList));
    initGraph(g);
    char * label2="Vertex2";
    char * label1="Vertex1";
    char * label3="Vertex3";
    insertFirstVertex(g,label2,2);
    insertFirstVertex(g,label1,2);
    insertLastVertex(g,label3,2);
    setOnFirstVertex(g);
    assert_string_equal(g->current->label,"Vertex1");
}
static void test_VertexList_setLast(){
    VertexList * g= (VertexList *) malloc(sizeof(VertexList));
    initGraph(g);
    char * label2="Vertex2";
    char * label1="Vertex1";
    char * label3="Vertex3";
    insertFirstVertex(g,label2,2);
    insertFirstVertex(g,label1,2);
    insertLastVertex(g,label3,2);
    setOnFirstVertex(g);
    setOnNextVertex(g);
    assert_string_equal(g->current->label,"Vertex2");
}
static void test_VertexList_setNext(){
    VertexList * g= (VertexList *) malloc(sizeof(VertexList));
    initGraph(g);
    char * label2="Vertex2";
    char * label1="Vertex1";
    char * label3="Vertex3";
    insertFirstVertex(g,label2,2);
    insertFirstVertex(g,label1,2);
    insertLastVertex(g,label3,2);
    setOnLastVertex(g);
    assert_string_equal(g->current->label,"Vertex3");
}
static void test_VertexList_find(){
    VertexList * g= (VertexList *) malloc(sizeof(VertexList));
    initGraph(g);
    char * label2="Vertex2";
    char * label1="Vertex1";
    char * label3="Vertex3";
    insertFirstVertex(g,label2,2);
    insertFirstVertex(g,label1,2);
    insertLastVertex(g,label3,2);
    Vertex * v= findVertex(g,label2);
    assert_string_equal(v->label,"Vertex2");
    v= findVertex(g,label1);
    assert_string_equal(v->label,"Vertex1");
    v= findVertex(g,label3);
    assert_string_equal(v->label,"Vertex3");
}
static void test_VertexList_addLink(){
    VertexList * g= (VertexList *) malloc(sizeof(VertexList));
    initGraph(g);
    char * label2="Vertex2";
    char * label1="Vertex1";
    char * label3="Vertex3";
    insertFirstVertex(g,label2,2);
    insertFirstVertex(g,label1,2);
    insertLastVertex(g,label3,2);
    char * obj1="Object1";
    char * obj2="Object2";
    Vertex * v =findVertex(g,label1);
    addLink(v,findVertex(g,label2),obj1);
    addLink(v,findVertex(g,label3),obj2);
    assert_string_equal(v->connect->first->obj_label,"Object1");
    assert_string_equal(v->connect->last->obj_label,"Object2");
    assert_string_equal(v->connect->first->v_next->label,"Vertex2");
    assert_string_equal(v->connect->last->v_next->label,"Vertex3");
}
static void test_VertexList_deleteFirst(){
    VertexList * g= (VertexList *) malloc(sizeof(VertexList));
    initGraph(g);
    char * label2="Vertex2";
    char * label1="Vertex1";
    char * label3="Vertex3";
    insertFirstVertex(g,label2,2);
    insertFirstVertex(g,label1,2);
    insertLastVertex(g,label3,2);
    deleteFirstVertex(g);
    assert_string_equal(g->first->label,"Vertex2");
    assert_string_equal(g->last->label,"Vertex3");
}
static void test_VertexList_delete_toAnEmpty(){
    VertexList * g= (VertexList *) malloc(sizeof(VertexList));
    initGraph(g);
    char * label="Vertex2";
    insertLastVertex(g,label,2);
    deleteFirstVertex(g);
    assert_true(isEmptyVertexList);
    assert_true(g->first==NULL);
    assert_true(g->last==NULL);
    deleteGraph(g);
}
static void Test_Print(){
    VertexList * g= (VertexList *) malloc(sizeof(VertexList));
    initGraph(g);
    char * label2="Vertex2";
    char * label1="Vertex1";
    char * label3="Vertex3";
    insertFirstVertex(g,label2,2);
    insertFirstVertex(g,label1,2);
    insertLastVertex(g,label3,2);
    char * obj1="Object1";
    char * obj2="Object2";
    char * obj3="Object3";
    char * obj4="Object4";
    char * obj5="Object5";
    char * obj6="Object6";
    addLink(findVertex(g,label1),findVertex(g,label2),obj1);
    addLink(findVertex(g,label1),findVertex(g,label3),obj2);
    addLink(findVertex(g,label3),findVertex(g,label2),obj3);
    addLink(findVertex(g,label3),findVertex(g,label1),obj4);
    addLink(findVertex(g,label3),findVertex(g,label3),obj5);
    addLink(findVertex(g,label1),findVertex(g,label1),obj6);
    printGraph(g);
}


/*
 * def change State tests
 */
static VertexList * ForTest(){
    VertexList * g= (VertexList *) malloc(sizeof(VertexList));
    initGraph(g);
    char * label2="Vertex2";
    char * label1="Vertex1";
    char * label3="Vertex3";
    char * w="win";
    insertFirstVertex(g,label2,1);
    insertFirstVertex(g,label1,2);
    insertLastVertex(g,label3,1);
    insertLastVertex(g,w,0);
    char * obj1="Object1";
    char * obj2="Object2";
    char * obj3="Object3";
    char * obj4="Object4";
    addLink(findVertex(g,label1),findVertex(g,label2),obj1);
    addLink(findVertex(g,label1),findVertex(g,label3),obj2);
    addLink(findVertex(g,label3),findVertex(g,w),obj3);
    addLink(findVertex(g,label2),findVertex(g,w),obj4);
    setOnFirstVertex(g);
    return g;
}
static void Test_Change_inf(){
    VertexList * g = ForTest();
    char id[] = "Object1";
    int x = 5;
    int y = 50;
    char file_name[] = "file_Test";
    Object * o = createObject( id, x, y, file_name);
    int a = SolvedEnigma(g,o);
    assert_int_equal(a,0);
}
static void Test_Change_sup(){
    VertexList * g = ForTest();
    char id[] = "Object1";
    int x = 5;
    int y = 50;
    char file_name[] = "file_Test";
    Object * o = createObject( id, x, y, file_name);
    g->current->enigma_solved=3;
    int a = changeState(g,o);
    assert_int_equal(a,-1);
}
static void Test_Change_egal_one_win(){
    VertexList * g = ForTest();
    setOnNextVertex(g); //Vertex2
    char id[] = "Object4";
    int x = 5;
    int y = 50;
    char file_name[] = "file_Test";
    Object * o = createObject( id, x, y, file_name);
    int a = SolvedEnigma(g,o);
    assert_int_equal(a,1);
}
static void Test_Change_egal_more(){
    VertexList * g = ForTest();
    char id[] = "Object1";
    int x = 5;
    int y = 50;
    char file_name[] = "file_Test";
    Object * o = createObject( id, x, y, file_name);

    int a = SolvedEnigma(g,o);
    assert_int_equal(a,0);
    int b= SolvedEnigma(g,o);
    assert_int_equal(b,1);
}





int main_tg(void){
    /**
     * Test Graph : EdgeList
     */
   /*const struct CMUnitTest tests_EdgeList[]={
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
    return cmocka_run_group_tests_name("test Door",tests_EdgeList,NULL,NULL);*/
    /**
     * Test Graph : VertexList
     */
   /* const struct CMUnitTest tests_VertexList[]= {
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
            cmocka_unit_test(test_VertexList_find),
            cmocka_unit_test(test_VertexList_delete_toAnEmpty),
            cmocka_unit_test(test_VertexList_deleteFirst),
            cmocka_unit_test(test_VertexList_addLink)
    };
    Test_Print();
    return cmocka_run_group_tests_name("test VertexList",tests_VertexList,NULL,NULL);*/

   /**
    * Change State Test
    */
    const struct CMUnitTest tests_changeState[]= {
            cmocka_unit_test(Test_Change_inf),
            cmocka_unit_test(Test_Change_sup),
            cmocka_unit_test(Test_Change_egal_one_win),
            cmocka_unit_test(Test_Change_egal_more)
    };
    return cmocka_run_group_tests_name("test Change State",tests_changeState,NULL,NULL);
}
