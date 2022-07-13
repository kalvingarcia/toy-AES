#ifndef PROJ_IO_H
#define PROJ_IO_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctype.h>

#include "auxi.h"

using namespace std;

/*
  This is an io class that will handle the reading of the files and what not!
*/
class io__ {
  private:
    ifstream _in; //this is to read in from the files
    ofstream _out; //output to our 1 output file

    string f_plaintext; //the file name of the plaintext
    string f_key; //the file name of the key
  public:
    //our constructor which stores in, key and opens the out
    io__(string f_pl, string f_k, string f_cp) {
      f_plaintext = f_pl;
      f_key = f_k;

      _out.open(f_cp);
      if(_out.fail()) {
        cout << "YIKES: Looks like the output file couldn't be created/opened!" << endl;
        exit(1);
      }
    }
    //destructor closes the out, since in's are closed in the funcs they are opened
    ~io__() {
      _out.close();
    }

    //this function returns the key as a string
    string _key() {
      string key = "";
      char c_got;

      _in.open(f_key);
      if(_in.fail()) { //checking if the input file even opened
        cout << "YIKES: Looks like the key file couldn't be created/opened!" << endl;
        exit(1);
      }

      while(_in.get(c_got))
        if(!isspace(c_got) && !ispunct(c_got)) //checking for weird spaces we cant use
            key += c_got; //adding each character to the key string

      _in.close(); //close those files!
      return key;
    }

    //this function returns the plaintext already processed and vigenere'd
    string _pre___sub(string s_k) {
      string read_text = "";
      char c_got;
      int k_track = 0; //to keep track of our place on the key sent through

      _in.open(f_plaintext);
      if(_in.fail()) { //checking for file openning failure
        cout << "YIKES: Looks like the input file couldn't be created/opened!" << endl;
        exit(1);
      }

      while(_in.get(c_got))
        if(!isspace(c_got) && !ispunct(c_got)) { //checking for those pesky whitespace and puncts
          c_got = ((toupper(c_got) + s_k[k_track]) % 26) + 65; //vigenere-ing
          read_text += c_got; //adding it to the string

          k_track = (k_track + 1) % s_k.size(); //handling the position iteration on the key
        }

      _in.close(); //close those file!
      return read_text;
    }
    //this output only handles the string output of the preproc and sub
    void _output(string s_text) {
        cout << "Preprocessing and Substitution:\n";
        cout << s_text << endl << endl;

        _out << "Preprocessing and Substitution:\n";
        _out << s_text << endl << endl;
    }
    //this ouput does all the blocky stuff!
    void _output(vector<block> b_text, int d_step) {
      //we switch between which step we're in
      switch(d_step) {
        case _PADDING:
          cout << "Padding:\n";
          _out << "Padding:\n";
          output_blocks(b_text, false);
          f_output_blocks(b_text, false, _out);
          break;
        case _SHIFTROWS:
          cout << "Shift Rows:\n";
          _out << "Shift Rows:\n";
          output_blocks(b_text, false);
          f_output_blocks(b_text, false, _out);
          break;
        case _PARITY:
          cout << "Partiy Bit:\n";
          _out << "Partiy Bit:\n";
          output_blocks(b_text, true);
          f_output_blocks(b_text, true, _out);
          break;
        case _MIXCOL:
          cout << "Mix Columns:\n";
          _out << "Mix Columns:\n";
          output_blocks(b_text, true);
          f_output_blocks(b_text, true, _out);
          break;
        default:
          break;
      }
    }
};

//handles the block output to cmd
void output_blocks(vector<block> block_list, bool _hex) {
  if(_hex) //if the hex flag is on then we output as hex
    for(int i = 0; i < block_list.size(); ++i) {
      for(int j = 0; j < BLOCK_SIZE; ++j) {
        for(int k = 0; k < BLOCK_SIZE; ++k)
          cout << hex << (int)block_list[i].data[j][k] << " "; //converting the char to int so that it's hex-able

        cout << endl;
      }

      cout << endl;
    }
  else
    for(int i = 0; i < block_list.size(); ++i) {
      for(int j = 0; j < BLOCK_SIZE; ++j) {
        for(int k = 0; k < BLOCK_SIZE; ++k)
          cout << block_list[i].data[j][k] << " ";

        cout << endl;
      }

      cout << endl;
    }
}
//handles the block output to file!
void f_output_blocks(vector<block> block_list, bool _hex, ofstream& file_out) {
  if(_hex) //if the hex flag is on then we output as hex
  for(int i = 0; i < block_list.size(); ++i) {
    for(int j = 0; j < BLOCK_SIZE; ++j) {
      for(int k = 0; k < BLOCK_SIZE; ++k)
        file_out << hex << (int)block_list[i].data[j][k] << " "; //converting the char to int so that it's hex-able

      file_out << endl;
    }

    file_out << endl;
  }
  else
    for(int i = 0; i < block_list.size(); ++i) {
      for(int j = 0; j < BLOCK_SIZE; ++j) {
        for(int k = 0; k < BLOCK_SIZE; ++k)
          file_out << block_list[i].data[j][k] << " ";

        file_out << endl;
      }

      file_out << endl;
    }
}
#endif
