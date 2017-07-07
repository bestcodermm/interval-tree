all:
	g++ testcase1.cpp interval.cpp IntervalNode.cpp IntervalTree.cpp XPoints.cpp -o TESTCASE1 -O3
	g++ testcase2.cpp interval.cpp IntervalNode.cpp IntervalTree.cpp XPoints.cpp -o TESTCASE2 -O3
	g++ testcase3.cpp interval.cpp IntervalNode.cpp IntervalTree.cpp XPoints.cpp -o TESTCASE3 -O3
	g++ testcase4.cpp interval.cpp IntervalNode.cpp IntervalTree.cpp XPoints.cpp -o TESTCASE4 -O3


clean:
	$(RM) TESTCASE1
	$(RM) TESTCASE2
	$(RM) TESTCASE3
	$(RM) TESTCASE4
