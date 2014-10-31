#include <string>

#include "base/CommandLineParser.h"
#include "src/DNAVector.h"


int main(int argc,char** argv)
{

  
  commandArg<string> aStringCmmd("-i","input fasta");
  commandArg<int> nCmmd("-n","how many");
  commandLineParser P(argc,argv);
  P.SetDescription("Splits up a fatsa file into equal chunks");
  P.registerArg(aStringCmmd);
  P.registerArg(nCmmd);
 
  P.parse();

  string aString = P.GetStringValueFor(aStringCmmd);
  int howMany = P.GetIntValueFor(nCmmd);
   
  vecDNAVector test;
  
  cout << "Reading file..." << endl;
  test.Read(aString);

  int n = (test.isize() + howMany)/howMany;


  int i, j;
  for (j=0; j<howMany; j++) {
    vecDNAVector out;
    for (i=0; i<test.isize(); i++) {
      int index = i % howMany;
      if (index == j)
	out.push_back(test[i], test.Name(i));     
    }
    char tmp[256];
    sprintf(tmp, ".%d", j);

    out.Write(aString + tmp);
  }

  cout << "done!" << endl;

  return 0;

}
  
