/*
PURPOSE:
    (Provides data values for the TAI to UTC time converter.
     This data file was generated by executing the "parser.py"
     script.)

     Time Span: mm dd yy to mm dd yy - ${entries[0].month} ${entries[0].day} ${entries[0].year} to ${entries[-1].month} ${entries[-1].day} ${entries[-1].year} )

REFERENCE:
    ((http://www.iers.org)
     (http://data.iers.org/products/214/14443/orig/eopc04_08_IAU2000.62-now)
     (Seidelmann, "Explanatory Supplement to the Astronomical Almanac,"
      University Science Books, Mill Valley, California, 1992.))

ASSUMPTIONS AND LIMITATIONS:
    ((DUT1 is interpolated linearly between tabular values wrt date))


*/


namespace jeod {
class TimeConverter_TAI_UT1;
}
#define JEOD_FRIEND_CLASS TimeConverter_TAI_UT1_tai_to_ut1_default_data

// JEOD includes
#include "environment/time/include/time_converter_tai_ut1.hh"
#include "utils/memory/include/jeod_alloc.hh"

// Unsupported includes
#include "../include/tai_to_ut1.hh"



//! Namespace jeod
namespace jeod {


void
TimeConverter_TAI_UT1_tai_to_ut1_default_data::initialize (
   TimeConverter_TAI_UT1 * TimeConverter_TAI_UT1_ptr)
{
   TimeConverter_TAI_UT1_ptr->override_data_table = false;
   TimeConverter_TAI_UT1_ptr->last_index = ${len(entries)-1};
   TimeConverter_TAI_UT1_ptr->when_vec =
      JEOD_ALLOC_PRIM_ARRAY (${len(entries)}, double);
   TimeConverter_TAI_UT1_ptr->val_vec =
      JEOD_ALLOC_PRIM_ARRAY (${len(entries)}, double);

% for entryIdx in range(len(entries)):
   TimeConverter_TAI_UT1_ptr->when_vec[${entryIdx}] = ${entries[entryIdx].mjd-40000.0}; /* ${entries[entryIdx].year} ${entries[entryIdx].month} ${entries[entryIdx].day} */
   TimeConverter_TAI_UT1_ptr->val_vec[${entryIdx}] = ${entries[entryIdx].dut - getLeapSecondsFromMjd(entries[entryIdx].mjd)};
% endfor

}


} // End JEOD namespace
