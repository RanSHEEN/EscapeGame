CC = gcc
CFLAGS =-Wall -g -MMD -coverage
LDFLAGS= -lcmocka -coverage

Run_Tests:Test_PDO Test_Edge Test_Graph Test_State Test_Files
	./Test_PDO
	./Test_Edge
	./Test_Graph
	./Test_State
	./Test_Files
	make -C ../Model get_coverage_infos
	make clean


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
	rm -f ../Model/*.gc*
	rm -f *.o *.d
	rm -f *.gc*
	rm -f Test_*


clean_Test :
	rm -f ../Tests/Coverage_Info/Model/*
	rm -f ../Tests/Coverage_Info/*.png
	rm -f ../Tests/Coverage_Info/*.html
	rm -f ../Tests/Coverage_Info/*.css
	rm -f ../Tests/Coverage_Info/*.info


include $(wildcart .d)