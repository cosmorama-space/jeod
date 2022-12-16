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
 * @addtogroup Environment
 * @{
 * @addtogroup Ephemerides
 * @{
 * @addtogroup EphemItem
 * @{
 *
 * @file models/environment/ephemerides/ephem_item/include/ephem_point.hh
 * Define class EphemerisPoint.
 */

/*******************************************************************************

Purpose:
  ()

Library dependencies:
  ((ephem_point.o)
   (ephem_item.o))



*******************************************************************************/


#ifndef JEOD_EPHEM_POINT_HH
#define JEOD_EPHEM_POINT_HH


// System includes

// JEOD includes
#include "utils/sim_interface/include/jeod_class.hh"

// Model includes
#include "class_declarations.hh"
#include "ephem_item.hh"


//! Namespace jeod
namespace jeod {

/**
 * An EphemerisPoint object updates the translational state of an ephemeris
 * reference frame.
 */
class EphemerisPoint : public EphemerisItem {
JEOD_MAKE_SIM_INTERFACES(EphemerisPoint)

public:

   // Member functions
   // Note: The copy constructor and assignment operator are deleted.

   // Constructor and destructor
   EphemerisPoint ();
   virtual ~EphemerisPoint ();


   // EphemerisPoint objects modify the translational state.
   virtual TargetAspect updates_what (void) const;

   // Default suffix, "inertial" in the case of a point.
   virtual const char * default_suffix () const;

   // Disconnect the inertial frame from the ref frame tree.
   virtual void disconnect_from_tree ();

   // Note that the inertial frame's active status has changed
   virtual void note_frame_status_change (RefFrame * frame);

   // Initialize (zero out) the state
   virtual void initialize_state ();

   // Update the state
   virtual void update (const double * pos, const double * vel, double time);
   virtual void update_scaled (const double * pos, const double * vel,
                               double scale, double time);

   // Member data
   // This class does not have add data members.

private:

   // Make the copy constructor and assignment operator private
   // (and unimplemented) to avoid erroneous copies

   ///
   /// Not implemented.
   EphemerisPoint (const EphemerisPoint &);
   ///
   /// Not implemented.
   EphemerisPoint & operator= (const EphemerisPoint &);
};


} // End JEOD namespace

#endif

/**
 * @}
 * @}
 * @}
 * @}
 */
