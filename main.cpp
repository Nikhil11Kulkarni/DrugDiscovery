#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include<time.h>
#include <limits>
#include <bits/stdc++.h>
#include <ctime>
#include "Board.h"
using namespace std;

//GLOBAL VARIABLES
int numVertex,nummEdges,k;


//Take Input here.
//read the graph edges as adjacency matrix(GIVE APPROPRIATE NAME FOR MATRIX: SO THAT I CAN GET IT)

void takeInput(string inputfilename){
	    vector<string> lines;
    string line;
    ifstream myfile ( filename.c_str () );
    if ( myfile.is_open ( ) )
    {
        while ( getline ( myfile, line ) )
        {
            //cout<<"Line read:"<<line<<endl;
            lines.push_back ( line );
        }
        myfile.close ( );
    }
    else
    {
        cout << "Unable to open input file";
        exit ( 0 );
    }


}

int main(int argc, char** argv ) {
	    string inputfilename ( argv[1] );
		takeInput(inputfilename);
//ready with graph indexes as 1-n(vertex) and edges as matriz[n+1][n+1] (I think 1 indexed would be easier; Think first then implemnt)

		//CNF for 3 properties-->(span the global graph in nodes and edges), (somplete graph), (NO subgraph of each other)

		//k subgraohs represented as (k*n bool/ (0-1) matrix); every row represents vertices corresponding to it.


}
