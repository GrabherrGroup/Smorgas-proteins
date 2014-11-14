#ifndef _AAPROPERTY_H
#define _AAPROPERTY_H

#include "base/SVector.h"
#include "src/DNAVector.h"

#define POLAR 0.33
#define NONPOLAR -0.33
#define BASIC -1.
#define ACIDIC 1.

#define POSITIVE 1.
#define NEUTRAL 0.
#define NEGATIVE -1.


class AAProperty
{
 public:
  AAProperty() {
    m_polarity.resize(21, 0.);
    m_charge.resize(21, 0.);
    m_hydropathy.resize(21, 0.);


    m_polarity[AminoAcidIndex('A')] = NONPOLAR;
    m_charge[AminoAcidIndex('A')] = NEUTRAL;
    m_hydropathy[AminoAcidIndex('A')] = 1.8;

    m_polarity[AminoAcidIndex('R')] = BASIC;
    m_charge[AminoAcidIndex('R')] = POSITIVE;
    m_hydropathy[AminoAcidIndex('R')] = -4.5;

    m_polarity[AminoAcidIndex('N')] = POLAR;
    m_charge[AminoAcidIndex('N')] = NEUTRAL;
    m_hydropathy[AminoAcidIndex('N')] = -3.5;

    m_polarity[AminoAcidIndex('D')] = ACIDIC;
    m_charge[AminoAcidIndex('D')] = NEGATIVE;
    m_hydropathy[AminoAcidIndex('D')] = -3.5;

    m_polarity[AminoAcidIndex('C')] = NONPOLAR;
    m_charge[AminoAcidIndex('C')] = NEUTRAL;
    m_hydropathy[AminoAcidIndex('C')] = 2.5;

    m_polarity[AminoAcidIndex('E')] = ACIDIC;
    m_charge[AminoAcidIndex('E')] = NEGATIVE;
    m_hydropathy[AminoAcidIndex('E')] = -3.5;

    m_polarity[AminoAcidIndex('Q')] = POLAR;
    m_charge[AminoAcidIndex('Q')] = NEUTRAL;
    m_hydropathy[AminoAcidIndex('Q')] = -3.5;

    m_polarity[AminoAcidIndex('G')] = NONPOLAR;
    m_charge[AminoAcidIndex('G')] = NEUTRAL;
    m_hydropathy[AminoAcidIndex('G')] = -0.4;

    m_polarity[AminoAcidIndex('H')] = BASIC;
    m_charge[AminoAcidIndex('H')] = 0.1*POSITIVE;
    m_hydropathy[AminoAcidIndex('H')] = -3.2;

    m_polarity[AminoAcidIndex('I')] = NONPOLAR;
    m_charge[AminoAcidIndex('I')] = NEUTRAL;
    m_hydropathy[AminoAcidIndex('I')] = 4.5;

    m_polarity[AminoAcidIndex('L')] = NONPOLAR;
    m_charge[AminoAcidIndex('L')] = NEUTRAL;
    m_hydropathy[AminoAcidIndex('L')] = 3.8;

    m_polarity[AminoAcidIndex('K')] = BASIC;
    m_charge[AminoAcidIndex('K')] = POSITIVE;
    m_hydropathy[AminoAcidIndex('K')] = -3.9;

    m_polarity[AminoAcidIndex('M')] = NONPOLAR;
    m_charge[AminoAcidIndex('M')] = NEUTRAL;
    m_hydropathy[AminoAcidIndex('M')] = 1.9;

    m_polarity[AminoAcidIndex('F')] = NONPOLAR;
    m_charge[AminoAcidIndex('F')] = NEUTRAL;
    m_hydropathy[AminoAcidIndex('F')] = 2.8;

    m_polarity[AminoAcidIndex('P')] = NONPOLAR;
    m_charge[AminoAcidIndex('P')] = NEUTRAL;
    m_hydropathy[AminoAcidIndex('P')] = -1.6;

    m_polarity[AminoAcidIndex('S')] = POLAR;
    m_charge[AminoAcidIndex('S')] = NEUTRAL;
    m_hydropathy[AminoAcidIndex('S')] = -0.8;

    m_polarity[AminoAcidIndex('T')] = POLAR;
    m_charge[AminoAcidIndex('T')] = NEUTRAL;
    m_hydropathy[AminoAcidIndex('T')] = -0.7;

    m_polarity[AminoAcidIndex('W')] = NONPOLAR;
    m_charge[AminoAcidIndex('W')] = NEUTRAL;
    m_hydropathy[AminoAcidIndex('W')] = -0.9;

    m_polarity[AminoAcidIndex('Y')] = POLAR;
    m_charge[AminoAcidIndex('Y')] = NEUTRAL;
    m_hydropathy[AminoAcidIndex('Y')] = -1.3;

    m_polarity[AminoAcidIndex('V')] = NONPOLAR;
    m_charge[AminoAcidIndex('V')] = NEUTRAL;
    m_hydropathy[AminoAcidIndex('V')] = 4.2;

  }

  double Polarity(char aa) const {
    if (AminoAcidIndex(aa) < 0)
      return 0.;
    return m_polarity[AminoAcidIndex(aa)];
  }
  double Charge(char aa) const {
   if (AminoAcidIndex(aa) < 0)
      return 0.;
    return m_charge[AminoAcidIndex(aa)];
  }
  double Hydropathy(char aa) const {
   if (AminoAcidIndex(aa) < 0)
      return 0.;
   return m_hydropathy[AminoAcidIndex(aa)]/4.;
  }


 private:
  svec<float> m_polarity;
  svec<float> m_charge;
  svec<float> m_hydropathy;

};


#endif //_AAPROPERTY_H
