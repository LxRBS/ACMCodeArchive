all: drillGenerator shellGenerator slow fast fast2

drillGenerator: drillGenerator.cpp
	g++ -o $@ -std=c++17 $<

shellGenerator: shellGenerator.cpp
	g++ -o $@ -std=c++17 $<

slow: submissions/time_limit_exceeded/soildrilling_slow_sjz.cpp
	g++ -o $@ -std=c++17 $<

fast: submissions/accepted/soildrilling_sjz.cpp
	g++ -o $@ -std=c++17 $<

fast2: submissions/accepted/soildrilling2_sjz.cpp
	g++ -o $@ -std=c++17 $<

data: drillGenerator shellGenerator gendata.sh
	./gendata.sh



