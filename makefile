#
# Copyright 2015 Ahnaf Siddiqui
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
# http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

TARGET=libQuantum2D.a

CXX=g++
CFLAGS=-std=c++11
INCLUDE=include
SRC=src
BUILD=lib

DUTILS=extern/DiamondUtils

$(BUILD)/$(TARGET): $(BUILD)/Q_QuantumWorld2D.o $(BUILD)/Q_Rigidbody2D.o
	ar rcs $(BUILD)/$(TARGET) $(BUILD)/Q_QuantumWorld2D.o $(BUILD)/Q_Rigidbody2D.o && rm -f $(BUILD)/*.o

$(BUILD)/Q_QuantumWorld2D.o: $(SRC)/Q_QuantumWorld2D.cpp $(INCLUDE)/Q_QuantumWorld2D.h
	$(CXX) $(CFLAGS) -o $(BUILD)/Q_QuantumWorld2D.o -c $(SRC)/Q_QuantumWorld2D.cpp -I$(INCLUDE) -I$(DUTILS)/include

$(BUILD)/Q_Rigidbody2D.o: $(SRC)/Q_Rigidbody2D.cpp $(INCLUDE)/Q_Rigidbody2D.h
	$(CXX) $(CFLAGS) -o $(BUILD)/Q_Rigidbody2D.o -c $(SRC)/Q_Rigidbody2D.cpp -I$(INCLUDE) -I$(DUTILS)/include

clean:
	rm -f $(BUILD)/*.o $(BUILD)/$(TARGET)
