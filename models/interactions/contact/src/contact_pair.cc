/**
 * @addtogroup Models
 * @{
 * @addtogroup Interactions
 * @{
 * @addtogroup Contact
 * @{
 *
 * @file models/interactions/contact/src/contact_pair.cc
 * ContactPair class for use with contact interaction model
 */

/*****************************************************************************

 Purpose:
 ()

 Reference:
 (((Derived from OTCM model developed by Hung Nguyen L3-COM)))

 Assumptions and Limitations:
 ((N/A))

 Library dependencies:
 ((contact_pair.o))

 

 *****************************************************************************/

/* System includes */
#include <cmath>

/* JEOD includes */
#include "utils/math/include/vector3.hh"
#include "dynamics/mass/include/mass.hh"

/* Model includes */
#include "../include/contact_pair.hh"

//! Namespace jeod
namespace jeod {

/**
 * Default Constructor
 */
ContactPair::ContactPair (
   void)
: // Return: -- None
interaction (NULL),
interaction_distance(0.0),
subject (NULL),
target (NULL)
{

}


/**
 * Destructor
 */
ContactPair::~ContactPair (
   void)
{

}

/**
 * test whether the pair is in range for interaction
 * @return bool
 */
bool
ContactPair::in_range (
   void)
{
   rel_state.update();
   if (std::fpclassify(interaction_distance) == FP_ZERO || interaction_distance >= Vector3::vmag(rel_state.rel_state.trans.position)) {
      return true;
   }
   return false;
}

/**
 * Determine if contact can occur between the two facets.
 * @return bool
 */
bool
ContactPair::is_active (
   void)
{
   if(subject->active && target->active && check_tree()) {
      return true;
   }
   return false;
}

/**
 * Determine if the pair has a target facet.
 * @return bool
 */
bool
ContactPair::is_complete (
   void)
{
   if(target != NULL) {
      return true;
   }
   return false;
}

/**
 * Determine if the pair has a target facet.
 * @return subject ContactFacet
 */
ContactFacet *
ContactPair::get_subject (
   void)
{
   return subject;
}

/**
 * Determine if the pair has a target facet.
 * @return target ContactFacet
 */
ContactFacet *
ContactPair::get_target (
   void)
{
   return target;
}

/**
 * Make sure the two contact facets are not on the same mass tree.
 * @return bool
 */
bool
ContactPair::check_tree(
   void)
{
   const MassBody * subject_root_mass;
   const MassBody * target_root_mass;

   subject_root_mass = subject->base_facet->get_mass_body_ptr()->get_root_body ();
   target_root_mass = target->base_facet->get_mass_body_ptr()->get_root_body ();

   if (subject_root_mass != target_root_mass) {
      // The pair is not on the same mass tree.
      return true;
   }
   return false;
}

/**
 * Initialize the relstate using the DynManager provided by Contact
 * class.
 * \param[in] dyn_manager dynamics manager
 */
void
ContactPair::initialize_relstate (
   DynManager * dyn_manager)
{
   rel_state.initialize (*(subject->vehicle_body), *dyn_manager);
}



} // End JEOD namespace

/**
 * @}
 * @}
 * @}
 */
