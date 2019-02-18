/** @file
 *****************************************************************************
 Test program that exercises the ppzkSNARK (first generator, then
 prover, then verifier) on a synthetic R1CS instance.

 *****************************************************************************
 * @author     This file is part of libsnark, developed by SCIPR Lab
 *             and contributors (see AUTHORS).
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/
#include <cassert>
#include <cstdio>
#include<iostream>
#include<string>

#include <libff/common/profiling.hpp>
#include <libff/common/utils.hpp>

#include <libsnark/common/default_types/r1cs_ppzksnark_pp.hpp>
#include <libsnark/relations/constraint_satisfaction_problems/r1cs/examples/r1cs_examples.hpp>
#include <libsnark/zk_proof_systems/ppzksnark/r1cs_ppzksnark/examples/run_r1cs_ppzksnark.hpp>

using namespace libsnark;

template<typename ppT>
void test_r1cs_ppzksnark(size_t num_a,
                         size_t num_x)
{
    libff::print_header("(enter) Test R1CS ppzkSNARK");


    const bool test_serialization = false;//true;
    //r1cs_example<libff::Fr<ppT> > example = generate_r1cs_example_with_convol<libff::Fr<ppT> >(num_a, num_x);
	std::vector<libff::Fr<ppT>> a;
    for(size_t i=0;i<num_a;i++){
        a.push_back(libff::Fr<ppT>(i+1));
    }
    std::vector<libff::Fr<ppT>> x;
    for(size_t i=0;i<num_x;i++){
        x.push_back(libff::Fr<ppT>(i+1));
    }


	size_t convol =1;
    r1cs_example<libff::Fr<ppT>> example = generate_r1cs_origin_convol_example<libff::Fr<ppT>>(num_x, x, num_a, a, convol);
    //r1cs_convol_example<libff::Fr<ppT>> example = generate_r1cs_convol_example<libff::Fr<ppT>>(num_x, x, num_a, a, convol);
    //r1cs_convol_example<libff::Fr<ppT>> example = generate_r1cs_convol_combi_example<libff::Fr<ppT>>(num_x, x, num_a, a, convol, 5, 10);
    const bool bit = run_r1cs_ppzksnark<ppT>(example, test_serialization);
    //assert(bit);

    libff::print_header("(leave) Test R1CS ppzkSNARK");
}

int main(int argc, char* argv[])
{
    default_r1cs_ppzksnark_pp::init_public_params();
    libff::start_profiling();
	if(argc < 2){
		std::cout<<"wrong input"<<std::endl;
	}

    test_r1cs_ppzksnark<default_r1cs_ppzksnark_pp>(std::stoi(argv[1]), std::stoi(argv[2]));
}
