conversion:conversion.cpp
	g++ -o $@ $^ 

.PHONY:clean
clean:
	rm -rf conversion
