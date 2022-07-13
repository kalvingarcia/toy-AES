/*
  KALVIN GARCIA
  3550.001
  11-12-21

  This program encrypts an input string, kinda like AES, but worse
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctype.h>

#include "auxi.h"
#include "proj_io.h"

using namespace std;

int main() {
  string f_input, f_key, f_output; //user defined file names
  cout << "What is the plaintext file? > ";
  cin >> f_input;
  cout << "What is the key file? > ";
  cin >> f_key;
  cout << "What is the output file? > ";
  cin >> f_output;

  io__ rw_(f_input, f_key, f_output); //setting up the io

  string s_presub = rw_._pre___sub(rw_._key()); //getting the preproc and subbed string
  rw_._output(s_presub); //outputting that

  vector<block> l_blocks = blockify(s_presub); //blockifing the string
  rw_._output(l_blocks, _PADDING); //outputting that

  l_blocks = shift_rows(l_blocks); //shifting them rows
  rw_._output(l_blocks, _SHIFTROWS); //outputting that

  l_blocks = parity(l_blocks); //doing that parity thing
  rw_._output(l_blocks, _PARITY); //outputting that

  l_blocks = mix_col(l_blocks); //mixing them columns
  rw_._output(l_blocks, _MIXCOL); //outputting that

  return 0; //DONE!
}

int count_ups(unsigned char c) {
  int count = 0; //keeps track of those 1's

  while(c > 0) {
    if(c & 1) //checking if the LSB is a 1
      ++count;

    c = c >> 1; //shifting
  }

  return count;
}
unsigned char rgf_mul(unsigned char c, int d) {
  bool parity_flag = false; //this is to see if the MSB is a 1
  unsigned char temp1 = c, temp2 = c;

  if(c >= 128) //check the MSB
    parity_flag = true;

  if(d == 2)
    c = temp1 << 1; //do that mult
  else if(d == 3)
    c = (temp1 << 1) ^ temp2; //do that mult and XOR

  if(parity_flag) //if the parity bit was on, then we need to XOR 27/0x1B/00011011
    return c ^ 0x1B;
  else
    return c;
}

vector<block> blockify(string s_input) {
  int pos = 0, i, j;
  vector<block> block_list; //making that block list baby!

  while(pos < s_input.size()) {
    block* inter_block = new block; //this is the individual block

    for(i = 0; i < BLOCK_SIZE; ++i)
      for(j = 0; j < BLOCK_SIZE; ++j) {
        if(pos < s_input.size()) {
          inter_block->data[i][j] = s_input[pos]; //make the block's data match the string
          ++pos;
        } else
          inter_block->data[i][j] = 'A'; //once there is no more string add 'A'
      }

      block_list.push_back(*inter_block); //puch that intermediate block in the list
  }

  return block_list;
}
vector<block> shift_rows(vector<block> b_input) {
  unsigned char temp; //to keep track of the swap

  for(int i = 0; i < b_input.size(); ++i)
    for(int j = 0; j < BLOCK_SIZE; ++j)
      for(int repeat = 0; repeat < j; ++repeat) { //essentially I decided to do a cyclical swap because I'm lazy
        temp = b_input[i].data[j][0];
        b_input[i].data[j][0] = b_input[i].data[j][1];
        b_input[i].data[j][1] = b_input[i].data[j][2];
        b_input[i].data[j][2] = b_input[i].data[j][3];
        b_input[i].data[j][3] = temp;
      }

    return b_input;
}
vector<block> parity(vector<block> b_input) {
  for(int i = 0; i < b_input.size(); ++i)
    for(int j = 0; j < BLOCK_SIZE; ++j)
      for(int k = 0; k < BLOCK_SIZE; ++k)
        if(count_ups(b_input[i].data[j][k]) % 2 == 1) //checking the count of bits
          b_input[i].data[j][k] = b_input[i].data[j][k] ^ 128; //XOR 10000000 if the number is odd

  return b_input;
}
vector<block> mix_col(vector<block> b_input) {
  vector<block> rgl_block = b_input;

  //RG field matrix stuff that is very complex...
  for(int i = 0; i < b_input.size(); ++i)
    for(int j = 0; j < BLOCK_SIZE; ++j) {
      rgl_block[i].data[0][j] = rgf_mul(b_input[i].data[0][j], 2) ^ rgf_mul(b_input[i].data[1][j], 3) ^ b_input[i].data[2][j] ^ b_input[i].data[3][j];
      rgl_block[i].data[1][j] = b_input[i].data[0][j] ^ rgf_mul(b_input[i].data[1][j], 2) ^ rgf_mul(b_input[i].data[2][j], 3) ^ b_input[i].data[3][j];
      rgl_block[i].data[2][j] = b_input[i].data[0][j] ^ b_input[i].data[1][j] ^ rgf_mul(b_input[i].data[2][j], 2) ^ rgf_mul(b_input[i].data[3][j], 3);
      rgl_block[i].data[3][j] = rgf_mul(b_input[i].data[0][j], 3) ^ b_input[i].data[1][j] ^ b_input[i].data[2][j] ^ rgf_mul(b_input[i].data[3][j], 2);
    }

  return rgl_block;
}
