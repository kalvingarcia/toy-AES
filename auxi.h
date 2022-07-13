#ifndef AUXI_H
#define AUXI_H

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define BLOCK_SIZE 4

struct block{
  unsigned char data[BLOCK_SIZE][BLOCK_SIZE];
};

enum __step {
  _PRE__SUB, _PADDING, _SHIFTROWS, _PARITY, _MIXCOL
};

//the func declatations for the output handlers!
void output_blocks(vector<block>, bool);
void f_output_blocks(vector<block>, bool, ofstream&);

//counts the 1's in a binary number
int count_ups(unsigned char);
//handles the RG field multiplication, just like Mark Thompson PhD taught me
unsigned char rgf_mul(unsigned char, int);

//handle all the steps of encryption
//blockify turns a string into blocks and adds them to a vector, and pads blocks that are empty!
vector<block> blockify(string);
//shifts the rows of those blocks!
vector<block> shift_rows(vector<block>);
//handles the parity checking of those unsigned chars
vector<block> parity(vector<block>);
//does the RG matrix multiplication
vector<block> mix_col(vector<block>);

#endif
