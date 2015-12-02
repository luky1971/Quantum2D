TARGET=libQuantum2D.a

CXX=g++
INCLUDE=include
SRC=src
BUILD=lib

DUTILS=extern/DiamondUtils

$(BUILD)/$(TARGET): $(BUILD)/Q_QuantumWorld2D.o $(BUILD)/Q_Rigidbody2D.o
	ar rcs $(BUILD)/$(TARGET) $(BUILD)/Q_QuantumWorld2D.o $(BUILD)/Q_Rigidbody2D.o

$(BUILD)/Q_QuantumWorld2D.o: $(SRC)/Q_QuantumWorld2D.cpp $(INCLUDE)/Q_QuantumWorld2D.h
	$(CXX) -o $(BUILD)/Q_QuantumWorld2D.o -c $(SRC)/Q_QuantumWorld2D.cpp -I$(INCLUDE) -I$(DUTILS)/include

$(BUILD)/Q_Rigidbody2D.o: $(SRC)/Q_Rigidbody2D.cpp $(INCLUDE)/Q_Rigidbody2D.h
	$(CXX) -o $(BUILD)/Q_Rigidbody2D.o -c $(SRC)/Q_Rigidbody2D.cpp -I$(INCLUDE) -I$(DUTILS)/include

clean:
	rm -f $(BUILD)/*.o $(BUILD)/$(TARGET)
