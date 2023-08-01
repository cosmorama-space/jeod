//=============================================================================
// Notices:
//
// Copyright © 2023 United States Government as represented by the Administrator
// of the National Aeronautics and Space Administration.  All Rights Reserved.
//
//
// Disclaimers:
//
// No Warranty: THE SUBJECT SOFTWARE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY OF
// ANY KIND, EITHER EXPRESSED, IMPLIED, OR STATUTORY, INCLUDING, BUT NOT LIMITED
// TO, ANY WARRANTY THAT THE SUBJECT SOFTWARE WILL CONFORM TO SPECIFICATIONS, ANY
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR
// FREEDOM FROM INFRINGEMENT, ANY WARRANTY THAT THE SUBJECT SOFTWARE WILL BE ERROR
// FREE, OR ANY WARRANTY THAT DOCUMENTATION, IF PROVIDED, WILL CONFORM TO THE
// SUBJECT SOFTWARE. THIS AGREEMENT DOES NOT, IN ANY MANNER, CONSTITUTE AN
// ENDORSEMENT BY GOVERNMENT AGENCY OR ANY PRIOR RECIPIENT OF ANY RESULTS,
// RESULTING DESIGNS, HARDWARE, SOFTWARE PRODUCTS OR ANY OTHER APPLICATIONS
// RESULTING FROM USE OF THE SUBJECT SOFTWARE.  FURTHER, GOVERNMENT AGENCY
// DISCLAIMS ALL WARRANTIES AND LIABILITIES REGARDING THIRD-PARTY SOFTWARE,
// IF PRESENT IN THE ORIGINAL SOFTWARE, AND DISTRIBUTES IT "AS IS."
//
// Waiver and Indemnity:  RECIPIENT AGREES TO WAIVE ANY AND ALL CLAIMS AGAINST THE
// UNITED STATES GOVERNMENT, ITS CONTRACTORS AND SUBCONTRACTORS, AS WELL AS ANY
// PRIOR RECIPIENT.  IF RECIPIENT'S USE OF THE SUBJECT SOFTWARE RESULTS IN ANY
// LIABILITIES, DEMANDS, DAMAGES, EXPENSES OR LOSSES ARISING FROM SUCH USE,
// INCLUDING ANY DAMAGES FROM PRODUCTS BASED ON, OR RESULTING FROM, RECIPIENT'S
// USE OF THE SUBJECT SOFTWARE, RECIPIENT SHALL INDEMNIFY AND HOLD HARMLESS THE
// UNITED STATES GOVERNMENT, ITS CONTRACTORS AND SUBCONTRACTORS, AS WELL AS ANY
// PRIOR RECIPIENT, TO THE EXTENT PERMITTED BY LAW.  RECIPIENT'S SOLE REMEDY FOR
// ANY SUCH MATTER SHALL BE THE IMMEDIATE, UNILATERAL TERMINATION OF THIS
// AGREEMENT.
//
//=============================================================================
//
//
/**
 * @addtogroup Models
 * @{
 * @addtogroup Utils
 * @{
 * @addtogroup Integration
 * @{
 * @addtogroup GaussJackson
 * @{
 *
 * @file models/utils/integration/gauss_jackson/include/gauss_jackson_two_state.hh
 * Defines the class GaussJacksonTwoState, which contains a pair of double*
 * pointers.
 */


/*
Purpose: ()
*/

#ifndef JEOD_GAUSS_JACKSON_TWO_STATE_HH
#define JEOD_GAUSS_JACKSON_TWO_STATE_HH

// JEOD includes
#include "utils/sim_interface/include/jeod_class.hh"

// System includes
#include <cstddef>


//! Namespace jeod 
namespace jeod {

/**
 * Essentially just std::pair<double*>.
 */
class GaussJacksonTwoState {

  JEOD_MAKE_SIM_INTERFACES(GaussJacksonTwoState)

public:

   /**
    * The first element of the pair.
    */
   double* first; //!< trick_units(--)

   /**
    * The second element of the pair.
    */
   double* second; //!< trick_units(--)


   /**
    * Default constructor.
    */
   GaussJacksonTwoState ()
   :
      first (nullptr),
      second (nullptr)
   {}

   /**
    * Non-default constructor.
    * @param  first_in   The first element of the pair.
    * @param  second_in  The second element of the pair.
    */
   GaussJacksonTwoState (
      double* first_in,
      double* second_in)
   :
      first (first_in),
      second (second_in)
   {}
};

} // End JEOD namespace

#endif

/**
 * @}
 * @}
 * @}
 * @}
 */
