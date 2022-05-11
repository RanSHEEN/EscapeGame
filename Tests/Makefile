CC = gcc
CFLAGS =-Wall -g -MMD
LDFLAGS= -lcmocka


Test_PDO: ../Model/model.o ../Model/graph.o ../Model/object.o ../Model/file.o UTest.o
	$(CC) $^  $(LDFLAGS) -o $@

Test_Edge: ../Model/model.o ../Model/graph.o ../Model/object.o ../Model/file.o UTest_Edge.o
	$(CC) $^  $(LDFLAGS) -o $@

Test_Graph: ../Model/model.o ../Model/graph.o ../Model/object.o ../Model/file.o UTest_graph.o
	$(CC) $^  $(LDFLAGS) -o $@

Test_State: ../Model/model.o ../Model/graph.o ../Model/object.o ../Model/file.o UTest_State.o
	$(CC) $^  $(LDFLAGS) -o $@

Test_Files: ../Model/model.o ../Model/graph.o ../Model/object.o ../Model/file.o UTest_files.o
	$(CC) $^  $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	rm -f ../Model/*.o
	rm -f ../Model/*.d
	rm -f *.o *.d
	rm -f Test_*


include $(wildcart .d)