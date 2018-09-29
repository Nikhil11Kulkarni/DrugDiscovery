#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <time.h>
#include <limits>
#include <ctime>
#include <vector>

using namespace std;

//GLOBAL VARIABLES
int numVertex,numEdges,k;
int numberOfVariables;

vector<vector<int> > ksubgraph, edgeMatrixGraph, edgeSpanMatrix;
vector<vector<int> > numksubgraph, numedgeMatrixGraph, numedgeSpanMatrix;
//int ksubgraph[k][numVertex], edgeMatrixGraph[numVertex][numVertex], edgeSpanMatrix[numVertex][numVertex]; ///just 0-1 matrix (1 if vertex is present)
//int numksubgraph[k][numVertex], numedgeMatrixGraph[numVertex][numVertex], numedgeSpanMatrix[numVertex][numVertex]; ///numerated

//Take Input here.
//read the graph edges as adjacency matrix(GIVE APPROPRIATE NAME FOR MATRIX: SO THAT I CAN GET IT)
void splitString(string message, string delimiter, string result[], int n) {
    int i = 0, pos = 0, length = 0, temp;
    temp = message.find ( delimiter.c_str ( ), pos );
    while ( temp != -1 )
    {
        length = temp - pos;
        result[i] = message.substr ( pos, length );
        pos = temp + delimiter.size ( );
        temp = message.find ( delimiter.c_str ( ), pos );
        i++;
    }
    result[i] = message.substr ( pos );
    i++;
    if ( i != n )
    {
        cout << "The similarity matrix does not have the correct format.";
        exit ( 0 );
    }
}

void takeInput(string filename){
    filename=filename+".graph";
    vector<string> lines;
    string line;
    ifstream myfile ( filename.c_str () );
    if ( myfile.is_open ( ) )
    {
        while ( getline ( myfile, line ) )
         { //  cout<<"Line read:"<<line<<endl;
            lines.push_back ( line );
        }
        myfile.close ( );
    }
    else
    {
        cout << "Unable to open input file";
        exit ( 0 );
    }
        
    string tempLine = lines[0];
    string *elements = new string[3];
    splitString ( tempLine, " ", elements, 3 );
    numVertex = atof ( elements[0].c_str () );
    numEdges = atof ( elements[1].c_str () );
    k = atof ( elements[2].c_str () );
    // vector<vector<int> > matrix(numVertex,vector<int> (numVertex,0));
    edgeMatrixGraph.resize(numVertex, vector<int> (numVertex, 0));
    for(int i=0;i<numEdges;i++){
        string tempLine = lines[i+1];
        string *elements = new string[2];
        splitString ( tempLine, " ", elements, 2 );
        int row = atof ( elements[0].c_str () );
        int col = atof ( elements[1].c_str () );    
        // cout<<row<<" "<<col<<endl;
        edgeMatrixGraph[row-1][col-1]=1;
        edgeMatrixGraph[col-1][row-1]=1;
    }
    cout<<numVertex<<" "<<numEdges<<" "<<k<<endl;
    // for(auto row:edgeMatrixGraph){
    //     for(auto entry:row){
    //         cout<<entry<<" ";
    //     }
    //     cout<<endl;
    // }

///less assume i have starting 3 parameters as: numV, numE,k
///i filled edgeMatrixGraph by 0/1
    int count=0;
        cout<<"1:"<<numVertex<<" "<<numEdges<<" "<<k<<endl;
    numksubgraph.resize(k, vector<int> (numVertex, 0));
    numedgeMatrixGraph.resize(numVertex, vector<int> (numVertex, 0));
    numedgeSpanMatrix.resize(numVertex, vector<int> (numVertex, 0));
    
       cout<<"2:"<<numVertex<<" "<<numEdges<<" "<<k<<endl; 
    for(int i=0;i<k;i++){
        for(int j=0;j<numVertex;j++){
            numksubgraph[i][j]= count;
            count++;
        }
    }
        cout<<numVertex<<" "<<numEdges<<" "<<k<<endl;
    for(int i=0;i<numVertex;i++){
        for(int j=0;j<numVertex;j++){
            numedgeMatrixGraph[i][j]= count;
            count++;
        }
    }
        cout<<numVertex<<" "<<numEdges<<" "<<k<<endl;
    for(int i=0;i<numVertex;i++){
        for(int j=0;j<numVertex;j++){
            numedgeSpanMatrix[i][j]= count;
            count++;
        }
    }
    numberOfVariables = count;
        cout << "yaay:"<<numberOfVariables;

}


void printInOutoutFile(vector<string> clauses, int numberOfVariables, string filename){

    ofstream fout;
    int numberOfClauses=clauses.size();
    filename=filename+".satinput";  
    fout.open(filename, ios::out | ios::app);
    fout <<"p cnf "<<numberOfVariables<<" "<<numberOfClauses<<"\n";
    for(int i=0;i<numberOfClauses;i++){
        fout<<clauses[i]<<"\n";
        cout<<"\n"<<clauses[i]<<"\n";
    }
    fout.close();


}

int main(int argc, char** argv ) {
cout<<"strat"<<endl;
	    string inputfilename ( argv[1] );
		takeInput(inputfilename);
cout<<"after takeinput"<<endl;
        // takeInput("sample.txt")
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
                temp=temp+to_string(numedgeSpanMatrix[nV1][nV2])+" ";
                temp=temp+to_string(-1*numksubgraph[i][nV1])+" ";
                temp=temp+to_string(-1*numksubgraph[i][nV2]);
                
                clauses.push_back(temp);
            }
        }
    }

    for(int i=0;i<numVertex;i++){
        for(int j=0;j<numVertex;j++){
            string temp1="", temp2="" ;
            temp1 = temp1 + to_string(numedgeMatrixGraph[i][j]) +" "+ to_string(-1*numedgeSpanMatrix[i][j]);
            temp2 = temp2 + to_string(-1*numedgeMatrixGraph[i][j]) +" "+to_string(numedgeSpanMatrix[i][j]);
            clauses.push_back(temp1);
            clauses.push_back(temp2);
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
    // for(int i=0;i<k;i++){
    //     for(int j=0;j<k;j++){
    //         for(int p=0; p<numVertex;p++){
     

    //         }
    //     }
    // }


printInOutoutFile(clauses, numberOfVariables, inputfilename);

}


