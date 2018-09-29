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
    vector<string> lines;
    string line;
    ifstream myfile ( filename.c_str () );
    if ( myfile.is_open ( ) )
    {
        while ( getline ( myfile, line ) )
        {   cout<<"Line read:"<<line<<endl;
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
    int numVertex = atof ( elements[0].c_str () );
    int numEdges = atof ( elements[1].c_str () );
    int k = atof ( elements[2].c_str () );

    vector<vector<int> > matrix(numVertex,vector<int> (numVertex,0));
    for(int i=0;i<numEdges;i++){
        string tempLine = lines[i+1];
        string *elements = new string[2];
        splitString ( tempLine, " ", elements, 2 );
        int row = atof ( elements[0].c_str () );
        int col = atof ( elements[1].c_str () );    
        cout<<row<<" "<<col<<endl;
        matrix[row-1][col-1]=1;
        matrix[col-1][row-1]=1;
    }
    cout<<numVertex<<" "<<numEdges<<" "<<k<<endl;
    for(auto x:matrix){
        for(auto y:x){
            cout<<y<<" ";
        }
        cout<<endl;
    }
}

int main(int argc, char** argv ) {
	    //string inputfilename ( argv[1] );
		takeInput("sample.txt");
        
}