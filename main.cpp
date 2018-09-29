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
int numVertex,numEdges,k;
int ksubgraph[k][numVertex], edgeMatrixGraph[numVertex][numVertex], edgeSpanMatrix[numVertex][numVertex]; ///just 0-1 matrix (1 if vertex is present)
int numksubgraph[k][numVertex], numedgeMatrixGraph[numVertex][numVertex], numedgeSpanMatrix[numVertex][numVertex]; ///numerated

//Take Input here.
//read the graph edges as adjacency matrix(GIVE APPROPRIATE NAME FOR MATRIX: SO THAT I CAN GET IT)

void takeInput(string filename){
    filename=filename+".graph";//------>UNCOMMENT BEFORE SUBMITING-- test.graph now
    vector<string> lines;
    string line;
    ifstream myfile ( filename.c_str () );
    if ( myfile.is_open ( ) )
    {
        while ( getline ( myfile, line ) )
        {//cout<<"Line read:"<<line<<endl;
            lines.push_back ( line );
        }
        myfile.close ( );
    }
    else
    {
        cout << "Unable to open input file";
        exit ( 0 );
    }

        string startTempLine = lines[0];
        string startElements[n];
        splitString ( tempLine, " ", elements, n );
///less assume i have starting 3 parameters as: numV, numE,k
///i filled edgeMatrixGraph by 0/1
int count=0;
    for(int i=0;i<k;i++){
        for(int j=0;j<numVertex;j++){
            numksubgraph[i][j]= count;
            count++;
        }
    }
    for(int i=0;i<numVertex;i++){
        for(int j=0;j<numVertex;j++){
            numedgeMatrixGraph[i][j]= count;
            count++;
        }
    }
    for(int i=0;i<numVertex;i++){
        for(int j=0;j<numVertex;j++){
            numedgeSpanMatrix[i][j]= count;
            count++;
        }
    }

}


void printInOutoutFile(vector<string> clauses, int numberOfVariables, string filename){

    ofstream fout;
    int numberOfClauses=clauses.size();
    filename=filename+".satinput";  
    fout.open(filename, ios::out | ios::app);
    fout <<"p cnf "<<numberOfVariables<<" "<<numberOfClauses<<"\n";
    for(int i=0;i<numberOfClauses;i++){
        fout<<clauses[i]<<"\n";
    }
    fout.close();


}

int main(int argc, char** argv ) {
	    string inputfilename ( argv[1] );
		takeInput(inputfilename);
//ready with graph indexes as 1-n(vertex) and edges as matriz[n+1][n+1] (I think 1 indexed would be easier; Think first then implemnt)
		//CNF for 3 properties-->(span the global graph in nodes and edges), (complete graph), (NO subgraph of each other)
		//k subgraohs represented as (k*n bool/ (0-1) matrix); every row represents vertices corresponding to it.
	
    vector<string> clauses;

//::--EDGEMATRXIGRAPH 
for(int i=0;i<numVertex;i++){
    for(int j=0;j<numVertex;j++){
        string temp;
        if(edgeMatrixGraph[i][j]==1){temp = to_string(numedgeMatrixGraph[i][j]);}
        else if(edgeMatrixGraph[i][j]==0){temp = to_string(-1*numedgeMatrixGraph[i][j]);}        
        clauses.push_back(temp);
    }
}

//SPAN--VERTEX
	for(int i=0;i<numVertex;i++){
        string temp="";
		for(int j=0;j<k;j++){
            temp=temp+to_string(numksubgraph[j][i])+" " ;//EXTRA " " space is printed at the end TAKE A NOTE numksubgraph[k][n] 
		}
        clauses.push_back(temp);
	}

//SPAN--EDGE
    for(int i=0;i<k;i++){
        for(int nV1=0;nV1<numVertex;nV1++){
            for(int nV2=0; nV2<numVertex;nV2++){
                string temp="";
                temp=temp+to_string(numedgeMatrixGraph[nV1][nV2])+" ";
                temp=temp+to_string(-1*numksubgraph[i][nV1])+" ";
                temp=temp+to_string(-1*numksubgraph[i][nV2]);
                
                clauses.push_back(temp);
            }
        }
    }
    
//COMPLETE
    for(int i=0;i<k;i++){
        for(int nV1=0;nV1<numVertex;nV1++){
            for(int nV2=0; nV2<numVertex;nV2++){
                string temp="";
                temp=temp+to_string(numedgeMatrixGraph[nV1][nV2])+" ";
                temp=temp+to_string(-1*numksubgraph[i][nV1])+" ";
                temp=temp+to_string(-1*numksubgraph[i][nV2]);
                
                clauses.push_back(temp);
            }
        }
    }
//NO SUBGRAPH    
    for(int i=0;i<k;i++){
        for(int nV1=0;nV1<numVertex;nV1++){
            for(int nV2=0; nV2<numVertex;nV2++){
                if(edgeMatrixGraph[][])
            }
        }
    }



printInOutoutFile(clauses, numberOfVariables, inputfilename);

}


