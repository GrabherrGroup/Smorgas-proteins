#include "src/FPTable.h"
#include "base/FileParser.h"


void FPTable::Read(const string & fileName)
{
  FlatFileParser parser;
  
  parser.Open(fileName);
  parser.ParseLine();
  int n = parser.AsInt(0);
  m_data.clear();
  m_data.resize(n);
  int k = 0;
  int i = 0;
  while (parser.ParseLine()) {
    if (parser.GetItemCount() == 0)
      continue;
    if (parser.AsString(0) == "len") {
      k++;
      m_data[k].SetSize(parser.AsInt(3));
      i = 0;
      continue;
    }
    m_data[k].Set(i, parser.AsFloat(0));
  }

}


void FPTable::Write(const string & fileName)
{
  FILE * p = fopen(fileName.c_str(), "w");
  int i, j;
  fprintf(p, "%d\n", m_data.isize());
  for (i=0; i<m_data.isize(); i++) {
    const Dist & d = Table(i);

    fprintf(p, "len %d data % d\n", i, d.Size());
    for (j=0; j<d.Size(); j++) 
      fprintf(p, "%e\n", d.Get(j));
  }
  fclose(p);
}

void FPTable::Add(int size, double ident)
{
  if (size >= m_data.isize())
    size = m_data.isize()-1;
  //cout << size << " " << m_data.isize() << endl;
  m_data[size].Add(ident);
}

void FPTable::Compute()
{
  for (int i=0; i<m_data.isize(); i++)
    m_data[i].Normalize();
}
