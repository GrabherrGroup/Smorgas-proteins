#include <string>
#include "base/CommandLineParser.h"
#include "base/FileParser.h"

class Align
{
public:
  Align() {m_score = 0.;}

  void Set(const string & line, const string & name, double score) {
    m_score = score;
    m_line = line;
    m_name = name;
  }

  bool operator < (const Align & a) const {
    if (m_name != a.m_name)
      return (m_name < a.m_name);
    return (m_score < a.m_score);
  }

  const string & Name() const {return m_name;}
  const string & Line() const {return m_line;}


private:
  double m_score;
  string m_line;
  string m_name;
};

int main( int argc, char** argv )
{

  commandArg<string> fileCmmd("-i","input file");
  commandArg<int> cCmmd("-c","cutoff");
  commandLineParser P(argc,argv);
  P.SetDescription("Testing the file parser.");
  P.registerArg(fileCmmd);
  P.registerArg(cCmmd);
  
  P.parse();
  
  string fileName = P.GetStringValueFor(fileCmmd);
  int cutoff = P.GetIntValueFor(cCmmd);
  

  //comment. ???
  FlatFileParser parser;
  
  parser.Open(fileName);
  svec<Align> aligns;

  while (parser.ParseLine()) {
    if (parser.GetItemCount() == 0)
      continue;
    if (parser.AsString(0) != "Summary")
      continue;

    const string & name = parser.AsString(1);
    double score = parser.AsFloat(13);
    if (score > 0.1)
      continue;

    Align a;
    a.Set(parser.Line(), name, score);
    aligns.push_back(a);
  }

  Sort(aligns);

  int i;
  int max = cutoff;
  string last;
  int k = 0;
  for (i=0; i<aligns.isize(); i++) {
    if (aligns[i].Name() != last)  {
      last = aligns[i].Name();
      k = 0;
    }
    if (k < max) {
      cout << aligns[i].Line() << endl;
      k++;
    }
  }


  return 0;
}
