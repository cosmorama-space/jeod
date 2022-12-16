//=============================================================================
// Notices:
//
// Copyright © 2022 United States Government as represented by the Administrator
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
 * @addtogroup Dynamics
 * @{
 * @addtogroup BodyAction
 * @{
 *
 * @file models/dynamics/body_action/include/dyn_body_init_ned_rot_state.hh
 * Define the class DynBodyInitNedRotState, which initialize a vehicle's
 * rotational state wrt some other vehicle's North-East-Down frame.
 */

/*******************************************************************************

Purpose:
  ()

Library dependencies:
  ((dyn_body_init_ned_rot_state.o))



*******************************************************************************/


#ifndef JEOD_DYN_BODY_INIT_NED_ROT_STATE_HH
#define JEOD_DYN_BODY_INIT_NED_ROT_STATE_HH


// System includes

// JEOD includes
#include "dynamics/dyn_manager/include/class_declarations.hh"
#include "utils/sim_interface/include/jeod_class.hh"

// Model includes
#include "dyn_body_init_ned_state.hh"


//! Namespace jeod
namespace jeod {

/**
 * Initialize a vehicle's rotational state wrt some vehicle's
 * North-East-Down frame.
 */
class DynBodyInitNedRotState : public DynBodyInitNedState {

   JEOD_MAKE_SIM_INTERFACES(DynBodyInitNedRotState)


 // No member data. This class adds no member data to DynBodyInitNedState.


 // Member functions

 // The copy constructor and assignment operator for this class are
 // declared private and are not implemented.
 private:

   DynBodyInitNedRotState (const DynBodyInitNedRotState&);
   DynBodyInitNedRotState & operator = (const DynBodyInitNedRotState&);


 public:

   // Default constructor, destructor
   DynBodyInitNedRotState ();
   virtual ~DynBodyInitNedRotState ();

   // initialize: Initialize the initializer.
   virtual void initialize (DynManager & dyn_manager);

};

} // End JEOD namespace

#endif

/**
 * @}
 * @}
 * @}
 */
