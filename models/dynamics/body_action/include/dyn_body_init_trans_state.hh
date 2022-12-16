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
 * @file models/dynamics/body_action/include/dyn_body_init_trans_state.hh
 * Define the class DynBodyInitTransState that initialize aspects of a vehicle's
 * translational state.
 */

/*******************************************************************************

Purpose:
  ()

Library dependencies:
  ((dyn_body_init_trans_state.o))



*******************************************************************************/


#ifndef JEOD_DYN_BODY_INIT_TRANS_STATE_HH
#define JEOD_DYN_BODY_INIT_TRANS_STATE_HH


// System includes

// JEOD includes
#include "utils/sim_interface/include/jeod_class.hh"

// Model includes
#include "class_declarations.hh"
#include "dyn_body_init.hh"


//! Namespace jeod
namespace jeod {

/**
 * Initialize aspects of a vehicle's translational state.
 */
class DynBodyInitTransState : public DynBodyInit {

   JEOD_MAKE_SIM_INTERFACES(DynBodyInitTransState)


 // Enumerations
 public:
   /**
    * Identify which of position/velocity is to be initialized.
    */
   enum StateItems {
      Both      = 0,            ///< Initialize both position and velocity
      Position  = 1,            ///< Initialize position only
      Velocity  = 2             ///< Initialize velocity only
   };


 // Member data

 public:

   /**
    * State items to be initialized -- position, velocity, or both.
    */
   StateItems state_items; //!< trick_units(--)


 // Member functions

 public:

   // Default constructor.
   DynBodyInitTransState ();

   // Destructor.
   virtual ~DynBodyInitTransState ();

   // initialize: Initialize the initializer.
   virtual void initialize (DynManager & dyn_manager);

   // apply: Apply the state to the subject body.
   virtual void apply (DynManager & dyn_manager);

   // initializes_what: Indicate what aspect of the state is initialized.
   // The DynBodyInitTransSate initializes position and velocity.
   virtual RefFrameItems::Items initializes_what (void);

   // is_ready: Indicate whether the initializer is ready to be applied.
   // The base DynBodyInit is always ready.
   virtual bool is_ready (void);


 private:

   DynBodyInitTransState (const DynBodyInitTransState&);
   DynBodyInitTransState & operator = (const DynBodyInitTransState&);

};


/**
 * Destructor.
 */
inline
DynBodyInitTransState::~DynBodyInitTransState (
   void)
{
   ; // Empty
}

} // End JEOD namespace

#endif

/**
 * @}
 * @}
 * @}
 */
