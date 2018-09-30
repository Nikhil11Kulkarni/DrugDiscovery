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
bool solutionExists;

vector<vector<int> > ksubgraph, edgeMatrixGraph, edgeSpanMatrix;
//vector<vector<int> > numksubgraph, numedgeMatrixGraph, numedgeSpanMatrix;

//Take Input here.
//read the graph edges as adjacency matrix(GIVE APPROPRIATE NAME FOR MATRIX: SO THAT I CAN GET IT)
void splitString(string message, string delimiter, string result[], int n) {
    cout<<"spl start";
    int i = 0, pos = 0, length = 0, temp;
    temp = message.find ( delimiter.c_str ( ), pos );
    while ( temp != -1 )
    {
       // cout<<"iiiii\n"<<i;
        length = temp - pos;
        result[i] = message.substr ( pos, length );
        pos = temp + delimiter.size ( );
        temp = message.find ( delimiter.c_str ( ), pos );
        i++;
    }
    result[i] = message.substr ( pos );
    i++;
    cout<<"\nOUTTTT";
    // if ( i != n )
    // {
    //     cout << "The similarity matrix does not have the correct format.";
    //     exit ( 0 );
    // }
}

void takeInputNumVertex(string filename){
    
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
    numVertex = atof ( elements[0].c_str () ); //(0 - numVertex-1) 
    numEdges = atof ( elements[1].c_str () );
    k = atof ( elements[2].c_str () );

}


void takeInputKsubgraph(string filename){
    cout <<"start2";
    filename=filename+".satoutput";
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
    if(tempLine=="UNSAT"){
        solutionExists=false;
    }
    else if(tempLine=="SAT"){
        solutionExists=true;
cout <<"end1";
        string tempLine1 = lines[1];
        cout <<"start1";
        int numVarInKsubgraphs = numVertex * k + numVertex*numVertex + numVertex*numVertex ;
        cout <<"start1.";
        string *elements = new string[numVarInKsubgraphs];
        cout <<"start1000";
        splitString ( tempLine1, " ", elements, numVarInKsubgraphs );
cout <<"start123";        
        ksubgraph.resize(k, vector<int> (numVertex, 0));
int count=0;
cout <<"start145";
        for(int i=0;i<k;i++){
            for(int j=0;j<numVertex;j++){
                if(atof ( elements[count].c_str ())>0)ksubgraph[i][j]=1;
                else if(atof ( elements[count].c_str ())<0)ksubgraph[i][j]=0;
                count++;
            }
        }
    }
    cout <<"end2";
}


void takeInputKsubgraphnew(string filename){
    ifstream inFile; 
    inFile.open(filename+".satoutput");
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    
    string tempLine ;
    inFile>>tempLine;

    if(tempLine=="UNSAT"){
        solutionExists=false;
    }
    else if(tempLine=="SAT"){
        solutionExists=true;

        int numVarInKsubgraphs = numVertex * k + numVertex*numVertex + numVertex*numVertex ;
        ksubgraph.resize(k, vector<int> (numVertex, 0));
        int count=0;
        for(int i=0;i<k;i++){
            for(int j=0;j<numVertex;j++){
                int elements;
                inFile>>elements;
                if(elements>0)ksubgraph[i][j]=1;
                else if(elements<0)ksubgraph[i][j]=0;
                count++;
            }
        }
    }
}









void printInOutoutFile(string filename){


    ofstream fout;
    filename=filename+".graphoutput";  
    fout.open(filename, ios::out | ios::app);

if(solutionExists==false){
    fout <<"0";
}
else if(solutionExists==true){
    for(int i=0;i<k;i++){
        string temp1="",temp2="";
        temp1=temp1+"#"+to_string(i+1);
        int countVertex=0;
        for(int j=0;j<numVertex;j++){
            if(ksubgraph[i][j]==1){ temp2=temp2+ to_string(j+1)+" "; countVertex++;}
        }
        temp1= temp1+" "+to_string(countVertex) ;
        fout<<temp1<<"\n";
        fout<<temp2<<"\n";
    }
    fout.close();

    }
}

int main(int argc, char** argv ) {

	    string inputfilename ( argv[1] );
		takeInputNumVertex(inputfilename);
        takeInputKsubgraphnew(inputfilename);

        //ready with graph indexes as 1-n(vertex) and edges as matriz[n+1][n+1] (I think 1 indexed would be easier; Think first then implemnt)
		//CNF for 3 properties-->(span the global graph in nodes and edges), (complete graph), (NO subgraph of each other)
		//k subgraohs represented as (k*n bool/ (0-1) matrix); every row represents vertices corresponding to it.
	   printInOutoutFile(inputfilename);
}


