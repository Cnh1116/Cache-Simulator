
// File Name: Cache_Simulator.cpp
// Authors: Carson Holland, Robert Bonham, Chris Le
// Skeleton Code Provided by: Dr. Qasem
// This program uses Dr. Qasem's skeleton code of a cache class
// to input data into the cache. The program will then output
// a output file that has address MISS/HITs.
//
//
#include<iostream>
#include<cstdlib>   // for atoi
#include "cache_class.cpp"

using namespace std;
const int MAX_SIZE = 1000;

int main(int argc, char*argv[])
{
    //Variable Declaration
    int memoryAddress;
    int counter = 0;
    int associativityIndex = 0;
    int assocCounter = 0;
    bool found = false;
    bool foundMemoryAddress;


    //If Command Line Arguments less than 2, invalid
    if (argc < 2) {
      cout << "Usage: " << endl;
      cout << "   ./file_process filename" << endl;
      return 0;
    }

    //Base file name from command-line
    string filename = argv[1];

    //Generating File Names
    string input_filename = filename + "_input";
    string output_filename = filename + "_output";

  //If arguments are less than 4, invalid.
  if (argc < 4) {
    cout << "Usage: " << endl;
    cout << "   ./cache num_entries associativity filename" << endl;
    return 0;
  }

    //Converting arguments into useable variables
    unsigned num_entries = atoi(argv[1]);
    unsigned assoc = atoi(argv[2]);
    Cache cacheObject(num_entries, assoc); //CACHE DECLARATION

    //Populating the CACHE as empty
      int twoDimensionalArray[assoc][num_entries]; //[ASSOC][NUM_ENTRIES]
      for (int i=0; i<assoc; i++) //ASSOC
      {
        for (int j=0; j<num_entries; j++)//NUM_ENTRIES
      {
          twoDimensionalArray[i][j] = -1;
          cout << twoDimensionalArray[i][j] << " ";
      }cout << endl;
      }

  cout << "Number of entries: " << num_entries << endl;
  cout << "Associativity: " << assoc << endl;
  cout << "Input File Name: " << input_filename << endl;

  //FILE I/O COPY GOES BELOW THIS LINE------------------------------------------------------------------

  /* create input and output files streams */
  ofstream output;
  ifstream input;


  /* open input stream for reading */
  input.open(input_filename); //FILE INPUT NAME

  /* check if input stream has been succesfully opened; bail otherwise */
  if (!input.is_open()) {
    cerr << "Could not open input file " << "input0.txt" << ". Exiting ..." << endl;
    exit(0);
  }

  unsigned long *nums = new unsigned long[MAX_SIZE];
  int count = 0;
  while (!input.eof() && count < MAX_SIZE) {
    input >> nums[count];
    count++;
  }

  /* done reading from input file; close the stream */
  input.close();

  /* open output file stream for writing */
  output.open(output_filename);

  /* no need to check if output file is open; we will create new file if it doesn't exist;
     overwrite otherwise */
  for (int i = 0; i < count-1; i++)
  {
    cout << nums[i];
    memoryAddress = nums[i];

    found = false;
    foundMemoryAddress = false;

    cout << "\nThe index of " << memoryAddress << " is " << cacheObject.get_index(memoryAddress) << endl;
    cout << "The tag of " << memoryAddress << " is " << cacheObject.get_tag(memoryAddress) << endl << endl;

    for (int k=0; k<assoc; k++) //ASSOC
    {
        for (int j=0; j<num_entries; j++)//NUM_ENTRIES
        {
            if(twoDimensionalArray[k][j]*num_entries + j == memoryAddress)
            {
                cout << "HIT. Memory Address " << memoryAddress << " was in the cache.**********************************************\n";
                output << memoryAddress << "HIT\n";
                foundMemoryAddress = true;
            }
        }
    }

    if(foundMemoryAddress == false)
    {
        cout << "MISS. Memory Address " << memoryAddress << " was NOT in the cache.!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
        output << memoryAddress << "MISS\n";
    do
    {
      if(twoDimensionalArray[counter][cacheObject.get_index(memoryAddress)] == -1)
      {
        twoDimensionalArray[counter][cacheObject.get_index(memoryAddress)] = cacheObject.get_tag(memoryAddress);
        found = true;
        break;
      }

      else
        counter++;
  }while (counter < assoc);

  if(!found)
  {
      cout << "The assocCounter is : " << assocCounter << endl;
      associativityIndex= assocCounter % assoc;
      twoDimensionalArray[associativityIndex][cacheObject.get_index(memoryAddress)] = cacheObject.get_tag(memoryAddress);
      assocCounter++;
  }

    for (int i=0; i<assoc; i++) //ASSOC
    {
        for (int j=0; j<num_entries; j++)//NUM_ENTRIES
        {
        cout << twoDimensionalArray[i][j] << " ";
        } cout << endl;
    }
    counter = 0;
  }//END OF IF FOUND ADDRESS IS FALSE


    //output << "ADDR : " << nums[i] << endl;
  }

  /* close output stream */
  output.close();

  return 0;
}


