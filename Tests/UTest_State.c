//
// Created by Marie on 04/05/22.
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
 * def change State tests
 */
static VertexList * ForTest(){
    VertexList * g= (VertexList *) malloc(sizeof(VertexList));
    initGraph(g);
    char * label2="Vertex2";
    char * label1="Vertex1";
    char * label3="Vertex3";
    char * w="win";
    insertFirstVertex(g,mem(label2),1);
    insertFirstVertex(g,mem(label1),2);
    insertLastVertex(g,mem(label3),1);
    insertLastVertex(g,mem(w),0);
    char * obj1="Door1";
    char * obj2="Door2";
    char * obj3="Door3";
    char * obj4="Door4";
    addLink(findVertex(g,label1),findVertex(g,label2),mem(obj1));
    addLink(findVertex(g,label1),findVertex(g,label3),mem(obj2));
    addLink(findVertex(g,label3),findVertex(g,w),mem(obj3));
    addLink(findVertex(g,label2),findVertex(g,w),mem(obj4));
    setOnFirstVertex(g);
    return g;
}
static void Test_ChangeAccess_inf(){
    VertexList * g = ForTest();
    int a = SolvedEnigma(g);
    assert_int_equal(a,0);
}
static void Test_ChangeAccess_sup() {
    VertexList *g = ForTest();
    g->current->enigma_solved = 3;
    int a = SolvedEnigma(g);
    assert_int_equal(a, -1);
}
static void Test_ChangeAccess_equal() {
    VertexList *g = ForTest();
    g->first->R=CreateRoom(mem("PATH"),mem("name"),0);
    addDoor(g->first->R,mem("Door1"),2,0,mem("file_name"));
    addDoor(g->first->R,mem("Door2"),2,8,mem("file_name"));
    setOnFirstVertex(g);
    g->current->enigma_solved=1;
    SolvedEnigma(g);
    assert_int_equal(g->current->R->framing[2][0].d->access,1);
    assert_int_equal(g->current->R->framing[2][8].d->access,1);
}

static void Test_Change_Room() {
    VertexList *g = ForTest();
    g->first->R=CreateRoom(mem("PATH"),mem("name"),0);
    addDoor(g->first->R,mem("Door1"),2,0,mem("file_name"));
    addDoor(g->first->R,mem("Door2"),2,8,mem("file_name"));
    //printRoom(g->first->R);
    setOnFirstVertex(g);
    SolvedEnigma(g);
    int a = changeRoom(g,g->current->R->framing[2][0].d);
    int b = changeRoom(g,g->current->R->framing[2][8].d);
    assert_int_equal(a,0);
    assert_int_equal(b,0);
    SolvedEnigma(g);
    a = changeRoom(g,g->current->R->framing[2][0].d);
    setOnFirstVertex(g);
    b = changeRoom(g,g->current->R->framing[2][8].d);
    assert_int_equal(a,1);
    assert_int_equal(b,1);
}


int main(void){
    /**
     * Test Graph : EdgeList
     */
    const struct CMUnitTest tests[]={
            cmocka_unit_test(Test_ChangeAccess_inf),
            cmocka_unit_test(Test_ChangeAccess_sup),
            cmocka_unit_test(Test_ChangeAccess_equal),
            cmocka_unit_test(Test_Change_Room)
    };
    return cmocka_run_group_tests_name("test State",tests,NULL,NULL);
}