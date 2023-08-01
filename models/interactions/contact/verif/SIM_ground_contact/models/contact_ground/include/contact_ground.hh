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
/*****************************************************************************

 Purpose:
    (Base class to for the contact manager with ground contact for use
     with contact interaction model)

 Reference:
   (((Derived from OTCM model developed by Hung Nguyen L3-COM)))

 Assumptions and Limitations:
     ((N/A))

 Library dependencies:
    ((../src/contact_ground.cc))

 

*****************************************************************************/

#ifndef CONTACT_GROUND_HH
#define CONTACT_GROUND_HH

// System includes
#include <list>

/* JEOD includes */
#include "dynamics/dyn_manager/include/class_declarations.hh"
#include "utils/sim_interface/include/jeod_class.hh"
#include "utils/container/include/pointer_list.hh"
#include "interactions/contact/include/contact.hh"

// Model includes
#include "ground_interaction.hh"
#include "ground_facet.hh"

//! Namespace jeod
namespace jeod {

// Class declarations
class Planet;
class Terrain;
class ContactFacet;

/*
  Purpose:
    (An base contact class for use in the surface model.)
 */
class ContactGround : public Contact {

   JEOD_MAKE_SIM_INTERFACES(ContactGround)

public:

   bool ground_active; /* trick_units(--) @n
      is the ground active */

   Planet * planet; /* trick_units(--) @n
      Planet object which the terrain is associated with, also need for
      reference frame information. */

   // constructor
   ContactGround ();

   // destructor
   ~ContactGround () override;

   /*
    Create the list of ground interfaces using the pairs list and set the
    and terrain for this contact model.  Note that this should be run before
    initializing ground.
    */
   void initialize_ground (Planet * planet_in, Terrain * terrain_in);

   /*
    Register a GroundFacet with the ContactGround class.
    */
   void register_ground_facet(GroundFacet * ground_facet);

   /*
    Check if a contact facet already has an GroundInterface defined
    */
   bool is_unique_ground_interaction(ContactFacet * facet);

   /*
    Get the ground_interaction for a specific ContactFacet.
    */
   GroundInteraction * get_ground_interaction(ContactFacet * facet);

   /*
    Function to check for contact.  Loops through all the created pairs.
    */
   void check_contact_ground ();

protected:

   Terrain * terrain; /* trick_units(--) @n
      Terrain class that will give an altitude and normal */

   JeodPointerList<GroundInteraction>::type ground_interactions; /* trick_io(**) @n
      list of all possible ContactFacet and ground interfaces. */

   JeodPointerList<GroundFacet>::type ground_facets; /* trick_io(**) @n
      list of all possible ground facets. */

private:
   /* Operator = and copy constructor hidden from use by being private */

   ContactGround& operator = (const ContactGround& rhs);
   ContactGround (const ContactGround& rhs);

};

} // End JEOD namespace


#endif
