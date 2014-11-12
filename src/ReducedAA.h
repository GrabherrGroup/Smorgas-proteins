#ifndef _REDUCEDAA_H
#define _REDUCEDAA_H

#include "base/SVector.h"
#include "src/DNAVector.h"


class ReducedAA
{
 public:
  ReducedAA() {
    m_list.resize(10);
    m_list[0].push_back('A');

    m_list[1].push_back('K');
    m_list[1].push_back('R');

    m_list[2].push_back('E');
    m_list[2].push_back('D');
    m_list[2].push_back('N');
    m_list[2].push_back('Q');

    m_list[3].push_back('C');

    m_list[4].push_back('G');

    m_list[5].push_back('H');

    m_list[6].push_back('I');
    m_list[6].push_back('L');
    m_list[6].push_back('V');
    m_list[6].push_back('M');

    m_list[7].push_back('F');
    m_list[7].push_back('Y');
    m_list[7].push_back('W');
  
    m_list[8].push_back('P');

    m_list[9].push_back('S');
    m_list[9].push_back('T');

    m_map.resize(256, -1);
    for (int i=0; i<m_list.isize(); i++) {
      svec<char> & l = m_list[i];
      for (int j=0; j<l.isize(); j++) 
	m_map[l[j]] = l[0];
    }
  }

  void Reduce(DNAVector & out, const DNAVector & in) {
    int i;
    out.resize(in.isize());
    for (i=0; i<in.isize(); i++) {
      out[i] = in[i];
      char c = m_map[in[i]];
      if (c > 0)
	out[i] = c;
    }
  }
  
  void Reduce(DNAVector & inout) {
    int i;
    
    for (i=0; i<inout.isize(); i++) {
      
      char c = m_map[inout[i]];
      if (c > 0)
	inout[i] = c;
    }
  }
  

 private:
  svec<char> m_map;
  svec< svec < char > > m_list;
};

#endif //_REDUCEDAA_H


