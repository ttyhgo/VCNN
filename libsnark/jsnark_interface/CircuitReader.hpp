/*
 * CircuitReader.hpp
 *
 *      Author: Ahmed Kosba
 */

#include "Util.hpp"
#include <libsnark/gadgetlib2/integration.hpp>
#include <libsnark/gadgetlib2/adapters.hpp>
#include <libff/common/profiling.hpp>


#include <memory.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <list>
#include <vector>
#include <set>
#include <map>
#include <ctime>

#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <proc/readproc.h>

using namespace libsnark;
using namespace gadgetlib2;
using namespace std;

//typedef unsigned int Wire;
typedef string Wire;

typedef libff::Fr<libff::default_ec_pp> FieldT;
typedef ::std::shared_ptr<LinearCombination> LinearCombinationPtr;
typedef ::std::map<Wire, unsigned int> WireMap;

#define ADD_OPCODE 1
#define MUL_OPCODE 2
#define SPLIT_OPCODE 3
#define NONZEROCHECK_OPCODE 4
#define PACK_OPCODE 5
#define MULCONST_OPCODE 6
#define XOR_OPCODE 7
#define OR_OPCODE 8
#define CONSTRAINT_OPCODE 9
#define CONVOL_OPCODE 10
#define CONVOL2D_OPCODE 11

class CircuitReader {
public:
	CircuitReader(char* arithFilepath, char* inputsFilepath, ProtoboardPtr pb);

	int getNumInputs() { return inputWireIds.size();}
	int getNumOutputs() { return outputWireIds.size();}
	int getCmNumInputs() { return cminputWireIds.size();}
	std::vector<Wire> getInputWireIds() const { return inputWireIds; }
	std::vector<Wire> getOutputWireIds() const { return outputWireIds; }

private:
	ProtoboardPtr pb;

	std::vector<VariablePtr> variables;
	std::map<Wire,LinearCombinationPtr> wireLinearCombinations;
	std::vector<LinearCombinationPtr> zeroPwires;

	WireMap variableMap;
	WireMap zeropMap;

	std::map<Wire,unsigned int> wireUseCounters;
	std::map<Wire,FieldT> wireValues;

	std::vector<Wire> toClean;

	std::vector<Wire> inputWireIds;
	std::vector<Wire> nizkWireIds;
	std::vector<Wire> outputWireIds;
	std::vector<Wire> cminputWireIds;

	unsigned int currentVariableIdx, currentLinearCombinationIdx;

	void parseAndEval(char* arithFilepath, char* inputsFilepath);
	void constructCircuit(char*);  // Second Pass:
	void mapValuesToProtoboard();

	int find(const Wire&, LinearCombinationPtr&, bool intentionToEdit = false);
	void clean();

	void addMulConstraint(char*, char*);
	void addXorConstraint(char*, char*);

	void addOrConstraint(char*, char*);
	void addAssertionConstraint(char*, char*);

	void addSplitConstraint(char*, char*, unsigned short);
	void addPackConstraint(char*, char*, unsigned short);
	void addNonzeroCheckConstraint(char*, char*);

	void handleAddition(char*, char*);
	void handleMulConst(char*, char*, char*);
	void handleMulNegConst(char*, char*, char*);

	void addConvol1DConstraint(char*, char* , unsigned short , unsigned short );
	void addConvol2DConstraint(char*, char* , char*,  unsigned short , unsigned short, unsigned short);
	void addConvolConstraint(char*, char* , unsigned short , unsigned short );


};

